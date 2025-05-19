#include "client.h"
#include <unistd.h>
#include <iostream>
#include "exception.h"
#include "printLog.h"

namespace cppServer {

client::client(sa_family_t family, __socket_type type, int protocol,
               char const *ip, uint16_t port)
    : baseSocket(family, type, protocol, ip, port) {}

void client::main() {
  int err = 0;

  err = connect(sockfd, (sockaddr *)(&addr), sizeof(addr));
  if (err < 0) {
    throw connectException();
  }

  while (true) {
    char buffer[1024]{};

    std::cout << "Please enter a message: ";
    std::cin.getline(buffer, sizeof(buffer));

    ssize_t write_bytes = write(sockfd, buffer, sizeof(buffer));
    if (write_bytes > 0) {
      printReceiveMessage(sockfd, buffer);
    } else if (write_bytes == 0) {
      printDisconnectLog(sockfd, inet_ntoa(addr.sin_addr),
                         ntohs(addr.sin_port));
      close(sockfd);
      break;
    } else {
      close(sockfd);
      throw clientWriteException();
    }
  }
}

}  // namespace cppServer