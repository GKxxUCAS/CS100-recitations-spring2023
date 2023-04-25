#include "expr.hpp"

#include <iostream>

int main() {
  auto expr = -Expr(3.14) * (Expr(20) + Expr(42));
  std::cout << expr.eval() << std::endl;
  std::cout << expr.rep() << std::endl;
  return 0;
}