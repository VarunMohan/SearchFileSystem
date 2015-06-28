#ifndef ANDEXPRESSION
#define ANDEXPRESSION

#include <iostream>
#include "../Token.h"
#include "Expression.h"

using namespace std;

class AndExpression : public Expression {
 private:
    Expression *left, *right;
 public:
    AndExpression(Expression *left, Expression *right) {
	this->left = left;
	this->right = right;
    }

    string toString() {
	return "(AND, " + left->toString() + ", " + right->toString() + ")";
    }

    void free() {
	left->free();
	right->free();
	delete this;
    }
};

#endif
