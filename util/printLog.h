#pragma once

#include <cstdint>

namespace cppServer {
void printConnectLog(int fd, const char *ip, uint16_t port);

void printDisconnectLog(int fd);

void printReceiveMessage(int fd, const char *msg);

void printContinueReading();

void printFinishReading();
}  // namespace cppServer