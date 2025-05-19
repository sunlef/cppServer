#pragma once

#include "baseSocket.h"

namespace cppServer {

/**
 * @brief TCP客户端类，继承自baseSocket。
 */
class client : public baseSocket {
 public:
  client() = delete;

  /**
   * @brief 构造函数，初始化客户端socket。
   * @param family 协议族
   * @param type 套接字类型
   * @param protocol 协议（0代表自动选择）
   * @param ip 服务器IP地址
   * @param port 服务器端口号
   */
  client(sa_family_t family, __socket_type type, int protocol, char const *ip,
         uint16_t port);

  /**
   * @brief 客户端主流程，连接到服务器。
   */
  void main();

 private:
};
}  // namespace cppServer