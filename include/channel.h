#pragma once
#include "sys/epoll.h"

namespace cppServer {
class epoll;  ///< 前向声明epoll类

class channel {
 public:
  channel() = delete;  ///< 禁用默认构造函数

  /**
   * @brief 构造函数，初始化channel对象。
   * @param ep epoll实例
   * @param fd 文件描述符
   */
  channel(epoll *ep, int fd);

  /**
   * @brief 启用读事件
   */
  void enableReading();
  int getFd() const;
  uint32_t getEvents() const;
  uint32_t getRevents() const;
  bool isInEpoll() const;
  void setInEpoll();
  void setRevents(uint32_t revents);

 private:
  epoll *ep;         ///< epoll实例
  int fd;            ///< 文件描述符
  uint32_t events;   ///< 事件类型
  uint32_t revents;  ///< 返回的事件类型
  bool inEpoll;      ///< 是否在epoll中
};

}  // namespace cppServer