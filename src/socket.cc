
#include "socket.h"
#include "exception.h"
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>

namespace cppServer {

socket::socket(sa_family_t family, __socket_type type, int protocol) : fd(-1) {
  fd = ::socket(family, type, protocol);  // 创建socket
  if (fd == -1) {
    throw socketCreateException();
  }
}

socket::socket(const int fd) : fd(fd) {
  if (fd == -1) {
    throw socketCreateException();
  }
}

socket::~socket() {
  if (fd != -1) {
    close(fd);
    fd = -1;
  }
}

void socket::bind(InternetAddress *addr) {
  int err = ::bind(fd, (sockaddr *)&addr->addr, addr->addr_len);
  if (err == -1) {
    throw socketBindException();
  }
}

void socket::listen() {
  int err = ::listen(fd, SOMAXCONN);  // 监听socket
  if (err == -1) {
    throw socketListenException();
  }
}

int socket::accept(InternetAddress *addr) {
  int client_socket_fd =
      ::accept(fd, (sockaddr *)&addr->addr, &addr->addr_len);  // 接受客户端连接
  if (client_socket_fd == -1) {
    throw socketAcceptException();
  }
  return client_socket_fd;
}

int socket::getFd() const { return fd; }

void socket::setNonBlocking() {
  int err = fcntl(fd, F_SETFL, fcntl(fd, F_GETFL) | O_NONBLOCK);
  if (err == -1) {
    throw socketSetNonBlockingException();
  }
}

}  // namespace cppServer