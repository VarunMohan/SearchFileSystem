#ifndef OREXPRESSION
#define OREXPRESSION

#include <iostream>
#include <vector>
#include <map>
#include "../Token.h"
#include "Expression.h"
#include "../../datastructures/DocIterator.h"
#include "../../datastructures/PostingList.h"
#include "../../datastructures/DisjunctionIterator.h"

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

    virtual DocIterator* getIterator(map<string, PostingList>& index) {
        vector<DocIterator*> iterators;
        iterators.push_back(left->getIterator(index));
        iterators.push_back(right->getIterator(index));
        return new DisjunctionIterator(iterators);
    }
};

#endif
