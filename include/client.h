#pragma once

#include "arpa/inet.h"
#include "baseSocket.h"

namespace cppServer {

class client : public baseSocket {
 public:
  client() = delete;

  client(in_port_t family, __socket_type type, int protocol, char const *ip,
         uint16_t port);

  int main();

 private:
};
}  // namespace cppServer