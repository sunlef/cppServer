#include "server.h"
#include "sys/socket.h"
#include <iostream>

namespace cppServer {
  
server::server(in_port_t family, __socket_type type, int protocol,
               char const *ip, uint16_t port)
    : baseSocket(family, type, protocol, ip, port) {}

int server::main() {
  int res = bind(sockfd, (sockaddr *)(&addr), sizeof(addr));

  listen(sockfd, SOMAXCONN);

  sockaddr_in client_addr{};
  socklen_t client_addr_len = sizeof(client_addr);

  int client_fd = accept(sockfd, (sockaddr *)(&client_addr), &client_addr_len);

  if (res == 0) {
    std::cout << "new client fd " << client_fd
              << "! IP: " << inet_ntoa(client_addr.sin_addr)
              << ", port: " << ntohs(client_addr.sin_port) << "\n";
  }
  return res;
}

}  // namespace cppServer