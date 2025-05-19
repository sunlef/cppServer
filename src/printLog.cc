#include "printLog.h"
#include <iostream>

void printConnectLog(int fd, const char *ip, uint16_t port) {
  std::cerr << "new client!\n"
            << "fd: " << fd << "\n"
            << "IP: " << ip << "\n"
            << "port: " << port << std::endl;
}