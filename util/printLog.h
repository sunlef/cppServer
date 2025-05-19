#pragma once

#include <cstdint>
void printConnectLog(int fd, const char *ip, uint16_t port);

void printDisconnectLog(int fd, const char *ip, uint16_t port);

void printReceiveMessage(int fd, const char *msg);
