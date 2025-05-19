
#include "server.h"
#include <iostream>

int main() {
  using namespace cppServer;

  try {
    server s(AF_INET, SOCK_STREAM, 0, "0.0.0.0", 8888);
    s.main();
  } catch (std::exception &e) {
    std::cerr << "ERROR: " << e.what() << std::endl;
  }

  return 0;
}