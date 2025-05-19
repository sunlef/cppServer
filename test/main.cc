#include <iostream>
#include "client.h"

int main() {
  using namespace cppServer;

  int n;
  std::cin >> n;

  int ans = 0;
  for (size_t i = 1; i < n; i++) {
    ans += i;
  }

  std::cout << "The sum of the first " << n << " numbers is: " << ans << "\n";
}