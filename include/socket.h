#pragma once
#include "internetAddress.h"

namespace cppServer {

/**
 * @brief socket类，封装了socket的基本操作。
 */
class socket {
 public:
  /***
   * @brief 构造函数，创建一个socket实例。
   * @param fd 已存在的socket文件描述符
   */
  socket(const int fd);

  /***
   * @brief 构造函数，创建一个socket实例。
   * @param family 协议族（如AF_INET）
   * @param type 套接字类型（如SOCK_STREAM）
   * @param protocol 协议（通常为0，表示自动选择）
   */
  socket(sa_family_t family, __socket_type type, int protocol);

  ~socket();

  /***
   * @brief 绑定socket到指定地址和端口。
   * @param addr 地址结构体
   */
  void bind(InternetAddress *addr);

  /***
   * @brief 接受客户端连接。
   * @param addr 地址结构体
   */
  int accept(InternetAddress *addr);

  /***
   * @brief 监听socket，等待客户端连接
   */
  void listen();

  /**
   * @brief 获取socket文件描述符
   * @return socket文件描述符
   */
  int getFd() const;

  /***
   * @brief 设置socket为非阻塞模式
   */
  void setNonBlocking();

 private:
  int fd;  ///< socket文件描述符
};
}  // namespace cppServer