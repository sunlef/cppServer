
#include "client.h"

int main() {
  using namespace cppServer;

  client c(AF_INET, SOCK_STREAM, 0, "127.0.0.1", 8888);
  c.main();
}