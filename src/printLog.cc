#include "printLog.h"
#include <iostream>

void printConnectLog(int fd, const char *ip, uint16_t port) {
  std::cerr << "new client!\n"
            << "fd: " << fd << "\n"
            << "IP: " << ip << "\n"
            << "port: " << port << std::endl;
}

void printReceiveMessage(int fd, const char *msg) {
  std::cerr << "Receive message from fd: " << fd << "\n"
            << "Message: " << msg << std::endl;
}

void printDisconnectLog(int fd, const char *ip, uint16_t port) {
  std::cerr << "Client disconnected!\n"
            << "fd: " << fd << "\n"
            << "IP: " << ip << "\n"
            << "port: " << port << std::endl;
}