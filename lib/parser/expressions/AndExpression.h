#ifndef ANDEXPRESSION
#define ANDEXPRESSION

#include <iostream>
#include "../Token.h"
#include "Expression.h"
#include "../../datastructures/DocIterator.h"
#include "../../datastructures/PostingList.h"
#include "../../datastructures/ConjunctionIterator.h"
#include <vector>

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

    virtual DocIterator* getIterator(map<string, PostingList>& index) {
        vector<DocIterator*> iterators;
        iterators.push_back(left->getIterator(index));
        iterators.push_back(right->getIterator(index));
        return new ConjunctionIterator(iterators);
    }
};

#endif
