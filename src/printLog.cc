#include "printLog.h"
#include <iostream>

namespace cppServer {

void printConnectLog(int fd, const char *ip, uint16_t port) {
  std::cerr << "new client!\n"
            << "fd: " << fd << "\n"
            << "IP: " << ip << "\n"
            << "port: " << port << "\n";
  std::cerr << std::endl;
}

void printReceiveMessage(int fd, const char *msg) {
  std::cerr << "Receive message from fd: " << fd << "\n"
            << "Message: " << msg << "\n";
  std::cerr << std::endl;
}

void printDisconnectLog(int fd) {
  std::cerr << "Client disconnected!\n"
            << "fd: " << fd << "\n";
  std::cerr << std::endl;
}

void printContinueReading() {
  std::cerr << "Continue reading...\n";
  std::cerr << std::endl;
}

void printFinishReading() {
  std::cerr << "Finish reading.\n";
  std::cerr << std::endl;
}
}  // namespace cppServer