#pragma once
#include <stdexcept>

namespace cppServer {
/**
 * @brief 基础socket创建异常
 */
class baseSocketCreateException : public std::runtime_error {
 public:
  explicit baseSocketCreateException()
      : std::runtime_error("Socket creation failed") {}
};

/**
 * @brief 绑定异常
 */
class bindException : public std::runtime_error {
 public:
  explicit bindException() : std::runtime_error("bind failed") {}
};

/**
 * @brief 监听异常
 */
class listenException : public std::runtime_error {
 public:
  explicit listenException() : std::runtime_error("listen failed") {}
};

/**
 * @brief 接受异常
 */
class acceptException : public std::runtime_error {
 public:
  explicit acceptException() : std::runtime_error("accept failed") {}
};

/**
 * @brief 连接异常
 */
class connectException : public std::runtime_error {
 public:
  explicit connectException() : std::runtime_error("connect failed") {}
};

/**
 * @brief 读取异常
 */
class serverReadException : public std::runtime_error {
 public:
  explicit serverReadException() : std::runtime_error("server read failed") {}
};

/**
 * @brief 服务器写入异常
 */
class serverWriteException : public std::runtime_error {
 public:
  explicit serverWriteException() : std::runtime_error("server write failed") {}
};

/**
 * @brief 客户端写入异常
 */
class clientWriteException : public std::runtime_error {
 public:
  explicit clientWriteException() : std::runtime_error("write failed") {}
};

}  // namespace cppServer