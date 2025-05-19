#pragma once
#include <stdexcept>

namespace cppServer {
/**
 * @brief 基础socket创建异常类
 */
class baseSocketCreateException : public std::runtime_error {
 public:
  explicit baseSocketCreateException()
      : std::runtime_error("Socket creation failed") {}
};

/**
 * @brief 绑定异常类
 */
class bindException : public std::runtime_error {
 public:
  explicit bindException() : std::runtime_error("bind failed") {}
};

/**
 * @brief 监听异常类
 */
class listenException : public std::runtime_error {
 public:
  explicit listenException() : std::runtime_error("listen failed") {}
};

/**
 * @brief 接受异常类
 */
class acceptException : public std::runtime_error {
 public:
  explicit acceptException() : std::runtime_error("accept failed") {}
};

/**
 * @brief 连接异常类
 */
class connectException : public std::runtime_error {
 public:
  explicit connectException() : std::runtime_error("connect failed") {}
};
}  // namespace cppServer