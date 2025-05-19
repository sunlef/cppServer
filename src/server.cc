#include "server.h"
#include "sys/socket.h"
#include "exception.h"
#include <unistd.h>
#include <fcntl.h>
#include "printLog.h"
#include "sys/epoll.h"
#include "constant.h"

namespace cppServer {

// server类实现

server::server(sa_family_t family, __socket_type type, int protocol,
               char const *ip, uint16_t port)
    : baseSocket(family, type, protocol, ip, port) {
  // 绑定socket到指定地址和端口
  int err = bind(sockfd, (sockaddr *)(&addr), sizeof(addr));
  if (err == -1) {
    throw bindException();
  }

  // 开始监听
  err = listen(sockfd, SOMAXCONN);
  if (err == -1) {
    throw listenException();
  }
}

void server::main() {
  // 以下是多路复用的实现
  // 创建epoll实例
  // epoll_create1(0)创建一个新的epoll实例，并返回一个文件描述符
  // 该实例用于监视多个文件描述符的事件
  // 0表示使用默认的epoll选项
  // epoll_create1()函数返回的文件描述符用于后续的epoll操作
  // 例如添加、删除或修改要监视的文件描述符

  int epoll_fd = epoll_create1(0);
  if (epoll_fd == -1) {
    throw epollCreateException();
  }

  epoll_event event[MAX_EVENT]{};
  epoll_event ev{};

  ev.data.fd = sockfd;
  ev.events = EPOLLIN | EPOLLET;                                // 边缘触发
  fcntl(sockfd, F_SETFL, fcntl(sockfd, F_GETFL) | O_NONBLOCK);  // 设置非阻塞

  int err = epoll_ctl(epoll_fd, EPOLL_CTL_ADD, sockfd, &ev);  // 添加监听事件
  if (err == -1) {
    close(epoll_fd);
    throw epollAddException();
  }

  while (true) {
    int nfds = epoll_wait(epoll_fd, event, MAX_EVENT, -1);  // 等待事件发生
    if (nfds == -1) {
      close(epoll_fd);
      throw epollWaitException();
    }

    for (size_t i = 0; i < nfds; ++i) {  // 处理事件
      if (event[i].data.fd == sockfd) {  // 监听到新的连接
        sockaddr_in client_addr{};
        socklen_t client_addr_len = sizeof(client_addr);

        // 接受一个客户端连接
        int client_fd =
            accept(sockfd, (sockaddr *)(&client_addr), &client_addr_len);
        if (client_fd == -1) {
          throw acceptException();
        }

        printConnectLog(client_fd, inet_ntoa(client_addr.sin_addr),
                        ntohs(client_addr.sin_port));

        ev = {};
        ev.data.fd = client_fd;
        ev.events = EPOLLIN | EPOLLET;  // 边缘触发
        fcntl(client_fd, F_SETFL,
              fcntl(client_fd, F_GETFL) | O_NONBLOCK);  // 设置非阻塞

        err = epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client_fd, &ev);  // 添加事件
        if (err == -1) {
          close(client_fd);
          throw epollAddException();
        }
      } else if (event[i].events & EPOLLIN) {  // 处理可读事件

        char buffer[BUFFER_SIZE]{};
        while (true) {  // 循环读取数据，直到没有数据可读
          ssize_t bytes_received =
              read(event[i].data.fd, buffer, sizeof(buffer));

          if (bytes_received > 0) {  // 读取到数据
            printReceiveMessage(event[i].data.fd, buffer);

            int err = write(event[i].data.fd, buffer, bytes_received);
            if (err == -1) {
              close(event[i].data.fd);
              throw serverWriteException();
            }
          } else if (bytes_received == 0) {  // 连接关闭
            printDisconnectLog(event[i].data.fd);
            close(event[i].data.fd);
          } else if (bytes_received == -1 &&
                     errno == EINTR) {  // 客户端正常中断，继续读取
            printContinueReading();
          } else if (bytes_received == -1 &&
                     (errno == EAGAIN ||
                      errno == EWOULDBLOCK)) {  // 没有数据可读
            printFinishReading();
            break;  // 退出循环
          }
        }
      } else {  // TODO: 处理其他事件
      }
    }
  }

  close(epoll_fd);  // 关闭epoll实例
  close(sockfd);    // 关闭socket
}

}  // namespace cppServer