#ifndef OREXPRESSION
#define OREXPRESSION

#include <iostream>
#include "../Token.h"
#include "Expression.h"

using namespace std;

class OrExpression : public Expression {
 private:
    Expression *left, *right;
 public:
    OrExpression(Expression *left, Expression *right) {
	this->left = left;
	this->right = right;
    }

    string toString() {
	return "(OR, " + left->toString() + ", " + right->toString() + ")";
    }

    void free() {
	left->free();
	right->free();
	delete this;
    }
};

#endif
