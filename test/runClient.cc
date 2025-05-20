
#include "client.h"
#include <cstring>
#include <iostream>
#include <fstream>

char *fetch_server_ip();

int main() {
  using namespace cppServer;

  char *server_ip = fetch_server_ip();
  if (server_ip == nullptr) {
    std::cerr << "Failed to fetch server IP" << std::endl;
    return 1;
  }

  try {
    client c(AF_INET, SOCK_STREAM, 0, server_ip, 8888);
    c.main();
  } catch (std::exception &e) {
    std::cerr << "ERROR: " << e.what() << std::endl;
  }

  delete[] server_ip;
  return 0;
}

char *fetch_server_ip() {
  std::ifstream ipFile("config/server_ip.txt");
  if (!ipFile.is_open()) {
    std::cerr << "Failed to open server_ip.txt" << std::endl;
    return nullptr;
  }

  std::string ip;
  std::getline(ipFile, ip);
  if (ip.empty()) {
    std::cerr << "server_ip.txt is empty" << std::endl;
    return nullptr;
  }
  ipFile.close();

  char *server_ip = new char[ip.size() + 1]{};
  std::strcpy(server_ip, ip.c_str());
  return server_ip;
}