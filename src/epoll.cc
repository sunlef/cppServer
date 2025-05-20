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

  events = new epoll_event[MAX_EVENTS]{};
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

void epoll::updateChannel(channel *ch) {
  int fd = ch->getFd();

  epoll_event ev{};
  ev.data.ptr = ch;
  ev.events = ch->getEvents();

  if (!ch->isInEpoll()) {
    int err = epoll_ctl(epoll_fd, EPOLL_CTL_ADD, fd, &ev);
    if (err == -1) {
      throw epollAddException();
    }
    ch->setInEpoll();
  } else {
    int err = epoll_ctl(epoll_fd, EPOLL_CTL_MOD, fd, &ev);
    if (err == -1) {
      throw epollModException();
    }
  }
}

std::vector<channel *> epoll::poll(int timeout) {
  std::vector<channel *> activeChannels;
  int cnt_events = epoll_wait(epoll_fd, events, MAX_EVENTS, timeout);
  for (size_t i = 0; i < cnt_events; ++i) {
    channel *ch = static_cast<channel *>(events[i].data.ptr);
    ch->setRevents(events[i].events);
    activeChannels.push_back(ch);
  }
  return activeChannels;
}
}  // namespace cppServer