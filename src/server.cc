#include "server.h"
#include "sys/socket.h"
#include <iostream>
#include <exception.h>
#include <unistd.h>
#include "printLog.h"

namespace cppServer {

// server类实现

server::server(sa_family_t family, __socket_type type, int protocol,
               char const *ip, uint16_t port)
    : baseSocket(family, type, protocol, ip, port) {}

void server::main() {
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

  sockaddr_in client_addr{};
  socklen_t client_addr_len = sizeof(client_addr);

  // 接受一个客户端连接
  int client_fd = accept(sockfd, (sockaddr *)(&client_addr), &client_addr_len);
  if (client_fd == -1) {
    throw acceptException();
  }

  printConnectLog(client_fd, inet_ntoa(client_addr.sin_addr),
                  ntohs(client_addr.sin_port));

  close(client_fd);
}

}  // namespace cppServer