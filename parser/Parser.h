  #pragma once
  #include <vector>
  #include <memory>
  #include "../common.h"
  #include "../ast/AST.h"

  class Parser {
  public:
    explicit Parser(const std::vector<Token>& tokens);

    std::unique_ptr<ProgramNode> parseProgram();

    StmtPtr parseStatement();

  private:
    const std::vector<Token>& tokens;
    size_t pos = 0;

    const Token& peek() const;
    const Token& get();
    bool match(TokenType t);

    ExprPtr parseExpression();
    ExprPtr parseTerm();
    ExprPtr parseFactor();
  };
