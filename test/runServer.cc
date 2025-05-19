
#include "server.h"

int main() {
  using namespace cppServer;

  server s(AF_INET, SOCK_STREAM, 0, "0.0.0.0", 8888);
  s.main();
}