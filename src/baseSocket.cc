#include <unistd.h>
#include "baseSocket.h"
#include "exception.h"

namespace cppServer {

// baseSocket类的实现

baseSocket::baseSocket(sa_family_t family, __socket_type type, int protocol,
                       char const *ip, uint16_t port)
    : sockfd{}, addr{} {

  // 创建socket
  sockfd = socket(family, type, protocol);
  if (sockfd < 0) {
    throw baseSocketCreateException();
  }

  // 初始化地址结构体
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