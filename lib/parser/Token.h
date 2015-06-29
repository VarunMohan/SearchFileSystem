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
	this->value = "";
    }

    Token(string token) {
	this->token = token;
	this->value = token;
    }

    Token(string token, string value) {
	this->token = token;
	this->value = value;
    }

    bool operator<(const Token &other) const {
	return other.token < token;
    }

    bool operator==(const Token &other) const {
	return other.value == value;
    }
};

ostream &operator<<(ostream &os, Token const &m) {
    return os << m.token;
}

#endif
