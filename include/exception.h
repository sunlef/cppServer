#pragma once
#include <stdexcept>

namespace cppServer {
/**
 * @brief socket创建异常
 */
class socketCreateException : public std::runtime_error {
 public:
  explicit socketCreateException()
      : std::runtime_error("Socket creation failed") {}
};

/**
 * @brief socket设置非阻塞异常
 */
class socketSetNonBlockingException : public std::runtime_error {
 public:
  explicit socketSetNonBlockingException()
      : std::runtime_error("Socket set non-blocking failed") {}
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
 * @brief epoll修改异常
 */
class epollModException : public std::runtime_error {
 public:
  explicit epollModException() : std::runtime_error("epoll mod failed") {}
};

/**
 * @brief epoll等待异常
 */
class epollWaitException : public std::runtime_error {
 public:
  explicit epollWaitException() : std::runtime_error("epoll wait failed") {}
};

/**
 * @brief socket绑定异常
 */
class socketBindException : public std::runtime_error {
 public:
  explicit socketBindException() : std::runtime_error("socket bind failed") {}
};

/**
 * @brief socket监听异常
 */
class socketListenException : public std::runtime_error {
 public:
  explicit socketListenException()
      : std::runtime_error("socket listen failed") {}
};

/**
 * @brief socket接受异常
 */
class socketAcceptException : public std::runtime_error {
 public:
  explicit socketAcceptException()
      : std::runtime_error("socket accept failed") {}
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