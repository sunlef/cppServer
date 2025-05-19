#pragma once

#include "arpa/inet.h"
#include "baseSocket.h"

namespace cppServer {

class server : public baseSocket {
 public:
  server() = delete;

  server(in_port_t family, __socket_type type, int protocol, char const *ip,
         uint16_t port);

  int main();

 private:
};
}  // namespace cppServer