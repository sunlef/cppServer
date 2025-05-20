#pragma once
#include <arpa/inet.h>

namespace cppServer {

/**
 * @brief 封装了IPv4地址和端口的结构体
 */
class InternetAddress {
 public:
  /**
   * @brief 构造函数，初始化IPv4地址和端口
   * @param family 协议族（如AF_INET）
   * @param ip IP地址字符串
   * @param port 端口号
   */
  InternetAddress(sa_family_t family, char const *ip, uint16_t port);

  /**
   * @brief 默认构造函数
   */
  InternetAddress();

  sockaddr_in addr;  ///< IPv4地址结构体

  socklen_t addr_len;  ///< 地址长度
};
}  // namespace cppServer