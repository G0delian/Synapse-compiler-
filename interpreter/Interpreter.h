  #pragma once
  #include "../ast/AST.h"
  #include <unordered_map>

  class Interpreter {
  public:
    Interpreter() = default;
    void run(const ProgramNode* program);

  private:
    std::unordered_map<std::string, int> variables;

    int evalExpr(const Expr* expr);
    void execStmt(const Stmt* stmt);
  };
