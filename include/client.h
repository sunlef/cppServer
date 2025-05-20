#pragma once

#include "socket.h"
#include "internetAddress.h"

namespace cppServer {

/***
 * @brief 客户端类，负责连接服务器并进行数据交互。
 */
class client {
 public:
  client() = delete;

  /**
   * @brief 构造函数，初始化客户端socket和地址。
   * @param family 协议族（如AF_INET）
   * @param type 套接字类型（如SOCK_STREAM）
   * @param protocol 协议（通常为0，表示自动选择）
   * @param ip 服务器的IP地址
   * @param port 服务器的端口号
   */
  client(sa_family_t family, __socket_type type, int protocol, char const *ip,
         uint16_t port);

  ~client();

  /**
   * @brief 客户端主流程，连接服务器并进行数据交互。
   */
  void main();

 private:
  socket *client_socket;  /// <客户端socket

  InternetAddress *serv_addr;  /// <服务器地址
};
}  // namespace cppServer