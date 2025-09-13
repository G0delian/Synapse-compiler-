  #include "Parser.h"
  #include <stdexcept>
  #include <cstdlib>

  Parser::Parser(const std::vector<Token>& tokens) : tokens(tokens), pos(0) {}

  const Token& Parser::peek() const {
    if (pos < tokens.size()) return tokens[pos];
    static Token eof{TokenType::END_OF_FILE, ""};
    return eof;
  }

  const Token& Parser::get() {
    if (pos < tokens.size()) return tokens[pos++];
    static Token eof{TokenType::END_OF_FILE, ""};
    return eof;
  }

  bool Parser::match(TokenType t) {
    if (peek().type == t) { get(); return true; }
    return false;
  }

  std::unique_ptr<ProgramNode> Parser::parseProgram() {
    auto program = std::make_unique<ProgramNode>();
    while (peek().type != TokenType::END_OF_FILE) {
        auto stmt = parseStatement();
        if (!stmt) break;
        program->addStatement(std::move(stmt));
    }
    return program;
  }

  StmtPtr Parser::parseStatement() {
    // var decl: int IDENT = expr ;
    if (peek().type == TokenType::KEY_INT) {
        get(); // consume 'int'
        if (peek().type != TokenType::IDENTIFIER) throw std::runtime_error("Expected identifier after int");
        std::string name = get().value;
        if (!match(TokenType::ASSIGN)) throw std::runtime_error("Expected '=' after identifier");
        ExprPtr init = parseExpression();
        if (!match(TokenType::SEMICOLON)) throw std::runtime_error("Expected ';' after var decl");
        return std::make_unique<VarDeclStmt>(name, std::move(init));
    }

    // print(expr);
    if (peek().type == TokenType::KEY_PRINT) {
        get(); // consume print
        if (!match(TokenType::LPAREN)) throw std::runtime_error("Expected '(' after print");
        ExprPtr e = parseExpression();
        if (!match(TokenType::RPAREN)) throw std::runtime_error("Expected ')' after print expression");
        if (!match(TokenType::SEMICOLON)) throw std::runtime_error("Expected ';' after print");
        return std::make_unique<PrintStmt>(std::move(e));
    }

    return nullptr;
  }

  // expression -> term ( (PLUS|MINUS) term )*
  ExprPtr Parser::parseExpression() {
    ExprPtr node = parseTerm();
    while (peek().type == TokenType::PLUS || peek().type == TokenType::MINUS) {
        TokenType op = get().type;
        ExprPtr right = parseTerm();
        node = std::make_unique<BinaryExpr>(std::move(node), op, std::move(right));
    }
    return node;
  }

  // term -> factor ( (MULT|DIV) factor )*
  ExprPtr Parser::parseTerm() {
    ExprPtr node = parseFactor();
    while (peek().type == TokenType::MULT || peek().type == TokenType::DIV) {
        TokenType op = get().type;
        ExprPtr right = parseFactor();
        node = std::make_unique<BinaryExpr>(std::move(node), op, std::move(right));
    }
    return node;
  }

  // factor -> NUMBER | IDENTIFIER | ( expr )
  ExprPtr Parser::parseFactor() {
    const Token& t = peek();
    if (t.type == TokenType::NUMBER) {
        get();
        return std::make_unique<NumberExpr>(std::stoi(t.value));
    }
    if (t.type == TokenType::IDENTIFIER) {
        get();
        return std::make_unique<VariableExpr>(t.value);
    }
    if (t.type == TokenType::LPAREN) {
        get(); // (
        ExprPtr e = parseExpression();
        if (!match(TokenType::RPAREN)) throw std::runtime_error("Expected ')'");
        return e;
    }
    throw std::runtime_error("Unexpected token in expression");
  }
 
