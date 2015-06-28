#ifndef TOKEN
#define TOKEN

#include <iostream>
#include "TokenTypes.h"

using namespace std;

class Token {
 public:
    string token;
    string value;

    Token() {
	this->token = "";
    }

    Token(string token) {
	this->token = token;
    }

    Token(string token, string value) {
	this->token = token;
	this->value = value;
    }

    bool operator<(const Token &other) const {
	return other.token < token;
    }
};

ostream &operator<<(ostream &os, Token const &m) {
    return os << m.token;
}

#endif
