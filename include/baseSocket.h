#pragma once

#include "arpa/inet.h"
#include "sys/socket.h"

namespace cppServer {

/**
 * @brief 基础Socket类，封装了socket的创建与地址初始化。
 */
class baseSocket {
 public:
  baseSocket() = delete;

  /**
   * @brief 构造函数，初始化socket和地址信息。
   * @param family 协议族（如AF_INET）
   * @param type 套接字类型（如SOCK_STREAM）
   * @param protocol 协议（0代表自动选择）
   * @param ip 绑定或连接的IP地址
   * @param port 绑定或连接的端口号
   */
  baseSocket(in_port_t family, __socket_type type, int protocol, char const *ip,
             uint16_t port);

  /**
   * @brief 析构函数，关闭socket。
   */
  virtual ~baseSocket();

 protected:
  int sockfd;         ///< socket文件描述符
  sockaddr_in addr;   ///< 地址结构体
};
}  // namespace cppServer