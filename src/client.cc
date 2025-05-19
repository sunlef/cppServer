#include "client.h"

namespace cppServer {

client::client(in_port_t family, __socket_type type, int protocol,
               char const *ip, uint16_t port)
    : baseSocket(family, type, protocol, ip, port) {}

int client::main() {
  int res = connect(sockfd, (sockaddr *)(&addr), sizeof(addr));

  return res;
}

}  // namespace cppServer