#include "client.h"
#include "exception.h"

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
}

}  // namespace cppServer