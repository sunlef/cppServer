
#include "client.h"
#include <iostream>

int main() {
  using namespace cppServer;

  try {
    client c(AF_INET, SOCK_STREAM, 0, "127.0.0.1", 8888);
    c.main();
  } catch (std::exception &e) {
    std::cerr << "ERROR: " << e.what() << std::endl;
  }

  return 0;
}