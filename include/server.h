#pragma once

#include "arpa/inet.h"
#include "baseSocket.h"

namespace cppServer {

/**
 * @brief TCP服务器类，继承自baseSocket。
 */
class server : public baseSocket {
 public:
  server() = delete;

  /**
   * @brief 构造函数，初始化服务器socket。
   * @param family 协议族
   * @param type 套接字类型
   * @param protocol 协议（0代表自动选择）
   * @param ip 绑定的IP地址
   * @param port 绑定的端口号
   */
  server(sa_family_t family, __socket_type type, int protocol, char const *ip,
         uint16_t port);

  /**
   * @brief 服务器主流程，等待并接受客户端连接。
   */
  void main();

 private:
};
}  // namespace cppServer