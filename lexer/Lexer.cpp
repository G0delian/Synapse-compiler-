  #include "Lexer.h"
  #include <cctype>

  Lexer::Lexer(const std::string& src) : src(src), pos(0) {}

  char Lexer::peek() const {
    return pos < src.size() ? src[pos] : '\0';
  }

  char Lexer::get() {
    return pos < src.size() ? src[pos++] : '\0';
  }

  void Lexer::skipWhitespace() {
    while (std::isspace((unsigned char)peek())) get();
  }

  bool Lexer::isIdentifierStart(char c) const {
    return std::isalpha((unsigned char)c) || c == '_';
  }

  bool Lexer::isIdentifierPart(char c) const {
    return std::isalnum((unsigned char)c) || c == '_';
  }

  std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;
    while (true) {
      skipWhitespace();
      char c = peek();
      if (c == '\0') {
        tokens.push_back({TokenType::END_OF_FILE, ""});
        break;
      }

      // identifier or keyword
      if (isIdentifierStart(c)) {
        std::string s;
        while (isIdentifierPart(peek())) s.push_back(get());
        if (s == "int") tokens.push_back({TokenType::KEY_INT, s});
        else if (s == "print") tokens.push_back({TokenType::KEY_PRINT, s});
        else tokens.push_back({TokenType::IDENTIFIER, s});
        continue;
      }

      // number
      if (std::isdigit((unsigned char)c)) {
        std::string s;
        while (std::isdigit((unsigned char)peek())) s.push_back(get());
        tokens.push_back({TokenType::NUMBER, s});
        continue;
      }

      // symbols / operators
      switch (get()) {
        case '=': tokens.push_back({TokenType::ASSIGN, "="}); break;
        case '+': tokens.push_back({TokenType::PLUS, "+"}); break;
        case '-': tokens.push_back({TokenType::MINUS, "-"}); break;
        case '*': tokens.push_back({TokenType::MULT, "*"}); break;
        case '/': tokens.push_back({TokenType::DIV, "/"}); break;
        case ';': tokens.push_back({TokenType::SEMICOLON, ";"}); break;
        case '(': tokens.push_back({TokenType::LPAREN, "("}); break;
        case ')': tokens.push_back({TokenType::RPAREN, ")"}); break;
        
        default:
          // unknown char -> skip or could throw
          // we'll skip silently for now, but print to stderr to help debugging
          // (in production you'd return error token)
          // putback not implemented; just continue
          break;
      }
    }

    return tokens;
  }
 
