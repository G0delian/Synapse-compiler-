  #pragma once
  #include <memory>
  #include <string>
  #include <vector>
  #include "../common.h"

  // Forward declarations
  struct ASTNode;
  struct Expr;
  struct Stmt;

  using ASTPtr = std::unique_ptr<ASTNode>;
  using ExprPtr = std::unique_ptr<Expr>;
  using StmtPtr = std::unique_ptr<Stmt>;

// Base class
  struct ASTNode {
    virtual ~ASTNode() = default;
    virtual void print(int indent = 0) const = 0;
  };

  // Expressions
  struct Expr : ASTNode {};

  // Number literal
  struct NumberExpr : Expr {
    int value;
    explicit NumberExpr(int v) : value(v) {}
    void print(int indent = 0) const override;
  };

  // Identifier
  struct VariableExpr : Expr {
    std::string name;
    explicit VariableExpr(std::string n) : name(std::move(n)) {}
    void print(int indent = 0) const override;
  };

  // Binary op: left op right
  struct BinaryExpr : Expr {
    ExprPtr left;
    TokenType op;
    ExprPtr right;
    BinaryExpr(ExprPtr l, TokenType o, ExprPtr r)
        : left(std::move(l)), op(o), right(std::move(r)) {}
    void print(int indent = 0) const override;
  };

  // Statements
  struct Stmt : ASTNode {};

  // Var declaration / assignment: int name = expr;
  struct VarDeclStmt : Stmt {
    std::string name;
    ExprPtr init;
    VarDeclStmt(std::string n, ExprPtr i) : name(std::move(n)), init(std::move(i)) {}
    void print(int indent = 0) const override;
  };

  // Print statement: print(expr);
  struct PrintStmt : Stmt {
    ExprPtr expr;
    explicit PrintStmt(ExprPtr e) : expr(std::move(e)) {}
    void print(int indent = 0) const override;
  };

  // Program root
  struct ProgramNode : ASTNode {
    std::vector<StmtPtr> statements;
    void addStatement(StmtPtr s) { statements.push_back(std::move(s)); }
    void print(int indent = 0) const override;
  };
