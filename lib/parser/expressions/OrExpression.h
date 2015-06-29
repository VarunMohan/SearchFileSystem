#ifndef OREXPRESSION
#define OREXPRESSION

#include <iostream>
#include "../Token.h"
#include "Expression.h"
#include "../../datastructures/DocIterator.h"
#include "../../datastructures/PostingList.h"
#include "../../datastructures/DisjunctionIterator.h"
#include <vector>

using namespace std;

class OrExpression : public Expression {
 private:
    vector<Expression *> expressions;
 public:
    OrExpression(Token orToken, Expression *left, Expression *right) {
	expressions.push_back(left);
	if (right->tok == orToken) {
	    expressions.insert(expressions.end(),
			       ((OrExpression *)right)->expressions.begin(),
			       ((OrExpression *)right)->expressions.end());
	    delete (OrExpression *)right;
	}
	else {
	    expressions.push_back(right);
	}
	this->tok = orToken;
    }

    string toString() {
	string res = "(OR";
	for (int i = 0; i < expressions.size(); i++) {
	    res += ", " + expressions[i]->toString();
	}
	res += ")";
	return res;
    }

    void free() {
	for (int i = 0; i < expressions.size(); i++)
	    expressions[i]->free();
	delete this;
    }

    virtual DocIterator* getIterator(map<string, PostingList>& index) {
        vector<DocIterator*> iterators;
	for (int i = 0; i < expressions.size(); i++) {
	    iterators.push_back(expressions[i]->getIterator(index));
	}
        return new DisjunctionIterator(iterators);
    }
};

#endif
