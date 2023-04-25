#ifndef EXPR_HPP
#define EXPR_HPP

#include <cassert>
#include <memory>
#include <string>
#include <utility>

class NodeBase {
 public:
  NodeBase() = default;
  virtual double eval() const = 0;
  virtual std::string rep() const = 0;
  virtual ~NodeBase() = default;
};

class Expr {
  std::shared_ptr<NodeBase> m_ptr;

  Expr(std::shared_ptr<NodeBase> ptr) : m_ptr{ptr} {}

 public:
  Expr(double value);
  double eval() const {
    return m_ptr->eval();
  }
  std::string rep() const {
    return m_ptr->rep();
  }

  friend Expr operator-(const Expr &);
  friend Expr operator+(const Expr &);
  friend Expr operator+(const Expr &, const Expr &);
  friend Expr operator-(const Expr &, const Expr &);
  friend Expr operator*(const Expr &, const Expr &);
  friend Expr operator/(const Expr &, const Expr &);
};

class Constant : public NodeBase {
  double m_value;

  double eval() const override {
    return m_value;
  }
  std::string rep() const override {
    return std::to_string(m_value);
  }

 public:
  Constant(double value) : m_value{value} {}
};

Expr::Expr(double value) : m_ptr{std::make_shared<Constant>(value)} {}

class UnaryOperator : public NodeBase {
  char m_op;
  Expr m_operand;

  double eval() const override {
    return m_op == '+' ? m_operand.eval() : -m_operand.eval();
  }
  std::string rep() const override {
    return m_op + ('(' + m_operand.rep() + ')');
  }

 public:
  UnaryOperator(char op, const Expr &operand) : m_op{op}, m_operand{operand} {}
};

Expr operator-(const Expr &operand) {
  return {std::make_shared<UnaryOperator>('-', operand)};
}

Expr operator+(const Expr &operand) {
  return {std::make_shared<UnaryOperator>('+', operand)};
}

class BinaryOperator : public NodeBase {
  char m_op;
  Expr m_left;
  Expr m_right;

  double eval() const override {
    auto left = m_left.eval(), right = m_right.eval();
    if (m_op == '+')
      return left + right;
    else if (m_op == '-')
      return left - right;
    else if (m_op == '*')
      return left * right;
    else // m_op == '/'
      return left / right;
  }
  std::string rep() const override {
    return '(' + m_left.rep() + ')' + m_op + '(' + m_right.rep() + ')';
  }

 public:
  BinaryOperator(char op, const Expr &left, const Expr &right)
      : m_op{op}, m_left{left}, m_right{right} {}
};

Expr operator+(const Expr &left, const Expr &right) {
  return {std::make_shared<BinaryOperator>('+', left, right)};
}

Expr operator-(const Expr &left, const Expr &right) {
  return {std::make_shared<BinaryOperator>('-', left, right)};
}

Expr operator*(const Expr &left, const Expr &right) {
  return {std::make_shared<BinaryOperator>('*', left, right)};
}

Expr operator/(const Expr &left, const Expr &right) {
  return {std::make_shared<BinaryOperator>('/', left, right)};
}

#endif // EXPR_HPP