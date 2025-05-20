#include "server.h"
#include "sys/socket.h"
#include "exception.h"
#include <unistd.h>
#include <fcntl.h>
#include "printLog.h"
#include "sys/epoll.h"
#include "constant.h"
#include "channel.h"

namespace cppServer {

server::server(sa_family_t family, __socket_type type, int protocol,
               char const *ip, uint16_t port)
    : serv_socket{new socket(family, type, protocol)},
      serv_addr{new InternetAddress(family, ip, port)},
      ep{new epoll()} {
  try {
    serv_socket->bind(serv_addr);   // 绑定socket到指定地址和端口
    serv_socket->listen();          // 监听socket，等待客户端连接
    serv_socket->setNonBlocking();  // 设置socket为非阻塞模式
  } catch (...) {
    throw;
  }
}

server::~server() {
  delete serv_socket;
  delete serv_addr;
  delete ep;
  serv_socket = nullptr;
  serv_addr = nullptr;
  ep = nullptr;
}

void server::main() {
  try {
    channel *ch = new channel(ep, serv_socket->getFd());
    ch->enableReading();

    while (true) {  // 主循环，等待并接受客户端连接
      std::vector<channel *> activeChannel = ep->poll();

      for (auto const &event : activeChannel) {
        const int &channel_fd = event->getFd();
        if (channel_fd == serv_socket->getFd()) {  // 监听到新连接
          InternetAddress *client_addr = new InternetAddress();
          socket *client_socket = new socket(serv_socket->accept(client_addr));

          printConnectLog(client_socket->getFd(),
                          inet_ntoa(client_addr->addr.sin_addr),
                          ntohs(client_addr->addr.sin_port));

          client_socket->setNonBlocking();

          channel *client_channel = new channel(ep, client_socket->getFd());
          client_channel->enableReading();

          //  delete client_addr;
          //  client_addr = nullptr;
          //  delete client_socket;
          //  client_socket = nullptr;
          // 为什么不能删除呢？

        } else if (event->getRevents() & EPOLLIN) {  // 监听到可读事件
          handle_event(channel_fd);
        } else {  // 其他事件
          // TODO:
        }
      }
    }
  } catch (...) {
    throw;
  }
}

void server::handle_event(int sockfd) {
  try {
    char buffer[BUFFER_SIZE]{};
    while (true) {  // 循环读取数据，直到没有数据可读
      std::fill(buffer, buffer + sizeof(buffer), 0);  // 清空缓冲区

      ssize_t bytes_received =
          read(sockfd, buffer, sizeof(buffer));  // 读取数据

      if (bytes_received > 0) {  // 读取到数据
        printReceiveMessage(sockfd, buffer);

        int err = write(sockfd, buffer, sizeof(buffer));
        if (err == -1) {
          close(sockfd);
          throw serverWriteException();
        }
      } else if (bytes_received == 0) {  // 连接关闭
        printDisconnectLog(sockfd);      // 删除epoll事件
        close(sockfd);
        break;
      } else if (bytes_received == -1 &&
                 errno == EINTR) {  // 客户端正常中断，继续读取
        printContinueReading();
        continue;
      } else if (bytes_received == -1 &&
                 (errno == EAGAIN || errno == EWOULDBLOCK)) {  // 没有数据可读
        printFinishReading();
        break;  // 退出循环
      }
    }
  } catch (...) {
    throw;
  }
}

}  // namespace cppServer