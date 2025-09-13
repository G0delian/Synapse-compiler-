  #include "AST.h"
  #include <iostream>

  static void printIndent(int indent) {
    for (int i = 0; i < indent; ++i) std::cout.put(' ');
  }

  void NumberExpr::print(int indent) const {
    printIndent(indent);
    std::cout << "Number(" << value << ")\n";
  }

  void VariableExpr::print(int indent) const {
    printIndent(indent);
    std::cout << "Variable(" << name << ")\n";
  }

  void BinaryExpr::print(int indent) const {
    printIndent(indent);
    std::string op;
    switch (op = (op, op), this->op) {
      case TokenType::PLUS: op = "+"; break;
      case TokenType::MINUS: op = "-"; break;
      case TokenType::MULT: op = "*"; break;
      case TokenType::DIV: op = "/"; break;
      default: op = "?"; break;
    }

    std::cout << "Binary(" << op << ")\n";
    if (left) left->print(indent + 2);
    if (right) right->print(indent + 2);
  }

  void VarDeclStmt::print(int indent) const {
    printIndent(indent);
    std::cout << "VarDecl(" << name << ")\n";
    if (init) init->print(indent + 2);
  }

  void PrintStmt::print(int indent) const {
    printIndent(indent);
    std::cout << "Print\n";
    if (expr) expr->print(indent + 2);
  }

  void ProgramNode::print(int indent) const {
    printIndent(indent);
    std::cout << "Program\n";
    for (const auto& s : statements) {
      if (s) s->print(indent + 2);
    }
  }
  
