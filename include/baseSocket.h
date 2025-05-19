#pragma once

#include "arpa/inet.h"
#include "sys/socket.h"

namespace cppServer {

class baseSocket {
 public:
  baseSocket() = delete;

  baseSocket(in_port_t family, __socket_type type, int protocol, char const *ip,
             uint16_t port);

  ~baseSocket();

 protected:
  int sockfd;
  sockaddr_in addr;
};
}  // namespace cppServer