#pragma once
#include <sys/epoll.h>
#include <vector>
#include "channel.h"

namespace cppServer {

/**
 * @brief epoll类，封装了epoll的基本操作。
 */
class epoll {
 public:
  epoll();

  ~epoll();

  /**
   * @brief 添加文件描述符到epoll实例中。
   * @param fd 文件描述符
   * @param op 操作类型（EPOLL_CTL_ADD、EPOLL_CTL_MOD、EPOLL_CTL_DEL）
   */
  void add_fd(int fd, uint32_t op);

  /**
   * @brief 更新epoll中的channel信息。
   * @param ch channel对象
   */
  void updateChannel(channel *ch);

  /**
   * @brief 等待事件发生并返回就绪的事件列表。
   * @param timeout 超时时间（单位：秒）
   * @return 就绪的事件列表
   */
  std::vector<channel *> poll(int timeout = 1);

 private:
  int epoll_fd;         ///< epoll文件描述符
  epoll_event *events;  ///< epoll事件数组
};
}  // namespace cppServer