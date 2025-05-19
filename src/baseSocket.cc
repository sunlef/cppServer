
#include <unistd.h>
#include "baseSocket.h"

namespace cppServer {
baseSocket::baseSocket(in_port_t family, __socket_type type, int protocol,
                       char const *ip, uint16_t port)
    : sockfd{socket(family, type, protocol)}, addr{} {
  addr.sin_family = family;
  addr.sin_addr.s_addr = inet_addr(ip);
  addr.sin_port = htons(port);
}

baseSocket::~baseSocket() {
  if (sockfd >= 0) {
    close(sockfd);
  }
}

}  // namespace cppServer