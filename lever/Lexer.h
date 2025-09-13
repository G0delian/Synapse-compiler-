  #pragma once
  #include "../common.h"
  #include <string>
  #include <vector>

  class Lexer {
  public:
    explicit Lexer(const std::string& src);
    std::vector<Token> tokenize();

  private:
    std::string src;
    size_t pos = 0;

    char peek() const;
    char get();
    void skipWhitespace();
    bool isIdentifierStart(char c) const;
    bool isIdentifierPart(char c) const;
  };
 
