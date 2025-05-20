#include "internetAddress.h"

namespace cppServer {
InternetAddress::InternetAddress() : addr{}, addr_len{sizeof(addr)} {}

InternetAddress::InternetAddress(sa_family_t family, char const *ip,
                                 uint16_t port)
    : addr{}, addr_len{sizeof(addr)} {
  addr.sin_family = family;
  addr.sin_addr.s_addr = inet_addr(ip);
  addr.sin_port = htons(port);
}

}  // namespace cppServer