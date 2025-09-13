  #include "Interpreter.h"
  #include <iostream>
  #include <stdexcept>
  #include "../common.h"
  #include "../ast/AST.h"

  void Interpreter::run(const ProgramNode* program) {
    if (!program) return;
    for (const auto& stmt : program->statements) {
        execStmt(stmt.get());
    }
  }

  int Interpreter::evalExpr(const Expr* expr) {
    if (!expr) throw std::runtime_error("Null expression");

    if (auto n = dynamic_cast<const NumberExpr*>(expr)) {
        return n->value;
    }
    if (auto v = dynamic_cast<const VariableExpr*>(expr)) {
        auto it = variables.find(v->name);
        if (it == variables.end()) throw std::runtime_error("Undefined variable: " + v->name);
        return it->second;
    }
    if (auto b = dynamic_cast<const BinaryExpr*>(expr)) {
        int l = evalExpr(b->left.get());
        int r = evalExpr(b->right.get());
        switch (b->op) {
            case TokenType::PLUS:  return l + r;
            case TokenType::MINUS: return l - r;
            case TokenType::MULT:  return l * r;
            case TokenType::DIV:   return l / r;
            default: throw std::runtime_error("Unknown binary operator");
        }
    }
    throw std::runtime_error("Unknown expression type");
  }

  void Interpreter::execStmt(const Stmt* stmt) {
    if (!stmt) throw std::runtime_error("Null statement");

    if (auto v = dynamic_cast<const VarDeclStmt*>(stmt)) {
        int value = evalExpr(v->init.get());
        variables[v->name] = value;
        return;
    }

    if (auto p = dynamic_cast<const PrintStmt*>(stmt)) {
        int value = evalExpr(p->expr.get());
        std::cout << value << std::endl;
        return;
    }

    throw std::runtime_error("Unknown statement type");
  }
 
