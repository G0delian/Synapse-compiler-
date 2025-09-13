  #pragma once
  #include <string>

  enum class TokenType {
    // keywords
    KEY_INT,
    KEY_PRINT,

    // primary tokens
    IDENTIFIER,
    NUMBER,

    // symbols / operators
    ASSIGN,     // =
    PLUS,       // +
    MINUS,      // -
    MULT,       // *
    DIV,        // /
    SEMICOLON,  // ;
    LPAREN,     // (
    RPAREN,     // )

    // end
    END_OF_FILE
  };

  struct Token {
    TokenType type;
    std::string value; // for IDENTIFIER and NUMBER (and keywords if desired)
  };
