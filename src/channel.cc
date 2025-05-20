#include "channel.h"
#include "epoll.h"

namespace cppServer {

channel::channel(epoll *ep, int fd)
    : ep{ep}, fd{fd}, events{0}, revents{0}, inEpoll{false} {}

void channel::enableReading() {
  events = EPOLLIN | EPOLLET;  // 设置为边缘触发模式
  ep->updateChannel(this);
}

int channel::getFd() const { return fd; }

uint32_t channel::getEvents() const { return events; }

uint32_t channel::getRevents() const { return revents; }

bool channel::isInEpoll() const { return inEpoll; }

void channel::setInEpoll() { inEpoll = true; }

void channel::setRevents(uint32_t revents) { this->revents = revents; }

}  // namespace cppServer