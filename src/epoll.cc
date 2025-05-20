#include "epoll.h"
#include "exception.h"
#include "constant.h"
#include <unistd.h>

namespace cppServer {

epoll::epoll() : epoll_fd{-1}, events{} {
  // epoll_create1(0) 创建一个新的 epoll 实例，并返回一个文件描述符。
  epoll_fd = epoll_create1(0);
  if (epoll_fd == -1) {
    throw epollCreateException();
  }

  events = new epoll_event[MAX_EVENT]{};
}

epoll::~epoll() {
  if (epoll_fd != -1) {
    close(epoll_fd);
  }
  delete[] events;
  events = nullptr;
}

void epoll::add_fd(int fd, uint32_t op) {
  epoll_event ev{};

  ev.data.fd = fd;
  ev.events = op;

  int err = epoll_ctl(epoll_fd, EPOLL_CTL_ADD, fd, &ev);
  if (err == -1) {
    throw epollAddException();
  }
}

std::vector<epoll_event> epoll::epoll_poll(int timeout) {
  std::vector<epoll_event> activeEvents;

  int cnt_fd = epoll_wait(epoll_fd, events, MAX_EVENT, timeout);

  if (cnt_fd == -1) {
    throw epollWaitException();
  }

  for (size_t i = 0; i < cnt_fd; i++) {
    activeEvents.push_back(events[i]);
  }

  return activeEvents;
}
}  // namespace cppServer