#pragma once

#include "socket.h"
#include "internetAddress.h"
#include "epoll.h"

namespace cppServer {

/**
 * @brief 服务器类，负责监听端口、接收客户端连接并处理事件。
 */
class server {
 public:
  server() = delete;

  /**
   * @brief 构造函数，初始化服务器监听socket、地址和epoll。
   * @param family 协议族（如AF_INET）
   * @param type 套接字类型（如SOCK_STREAM）
   * @param protocol 协议（通常为0，表示自动选择）
   * @param ip 监听的IP地址
   * @param port 监听的端口号
   */
  server(sa_family_t family, __socket_type type, int protocol, char const *ip,
         uint16_t port);

  ~server();

  /**
   * @brief 服务器主流程，等待并接受客户端连接。
   */
  void main();

 private:
  socket *serv_socket;         ///< 服务器监听socket
  InternetAddress *serv_addr;  ///< 服务器地址
  epoll *ep;                   ///< epoll实例

  void handle_event(int sockfd);  ///< 处理事件的函数
};
}  // namespace cppServer