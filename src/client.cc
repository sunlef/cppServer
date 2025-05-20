#include "client.h"
#include <unistd.h>
#include <cstring>
#include <iostream>
#include "exception.h"
#include "printLog.h"
#include "constant.h"

namespace cppServer {

client::client(sa_family_t family, __socket_type type, int protocol,
               char const *ip, uint16_t port)
    : client_socket{new socket(family, type, protocol)},
      serv_addr{new InternetAddress(family, ip, port)} {}

client::~client() {
  delete client_socket;
  delete serv_addr;
  client_socket = nullptr;
  serv_addr = nullptr;
}

void client::main() {
  try {
    int err = connect(client_socket->getFd(), (sockaddr *)(&serv_addr->addr),
                      sizeof(serv_addr->addr));  // 连接服务器
    if (err == -1) {
      throw connectException();
    }

    while (true) {
      char buffer[BUFFER_SIZE]{};  // 创建缓冲区

      std::cin.getline(buffer, sizeof(buffer));

      ssize_t write_bytes = write(client_socket->getFd(), buffer,
                                  sizeof(buffer));  // 向服务器发送数据

      if (write_bytes == -1) {
        close(client_socket->getFd());
        throw clientWriteException();
      }

      std::fill(buffer, buffer + sizeof(buffer), 0);  // 清空缓冲区

      ssize_t read_bytes = read(client_socket->getFd(), buffer,
                                sizeof(buffer));  // 从服务器读取数据

      if (read_bytes > 0) {  // 如果读取到数据
        printReceiveMessage(client_socket->getFd(), buffer);
      } else if (read_bytes == 0) {  // 服务器关闭连接
        printDisconnectLog(client_socket->getFd());
        break;
      } else {  // 读取失败
        close(client_socket->getFd());
        throw clientReadException();
      }
    }
  } catch (...) {
    throw;
  }
}

}  // namespace cppServer