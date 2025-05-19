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
 * @brief epoll创建异常
 */
class epollCreateException : public std::runtime_error {
 public:
  explicit epollCreateException() : std::runtime_error("epoll create failed") {}
};

/**
 * @brief epoll添加异常
 */
class epollAddException : public std::runtime_error {
 public:
  explicit epollAddException() : std::runtime_error("epoll add failed") {}
};

/**
 * @brief epoll等待异常
 */
class epollWaitException : public std::runtime_error {
 public:
  explicit epollWaitException() : std::runtime_error("epoll wait failed") {}
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
  explicit clientWriteException() : std::runtime_error("client write failed") {}
};
/**
 * @brief 客户端读取异常
 */
class clientReadException : public std::runtime_error {
 public:
  explicit clientReadException() : std::runtime_error("client read failed") {}
};

}  // namespace cppServer