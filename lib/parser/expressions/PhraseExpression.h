#ifndef PHRASEEXPRESSION
#define PHRASEEXPRESSION

#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <sstream>
#include <algorithm>
#include <string>
#include <iterator>
#include "../Token.h"
#include "Expression.h"

#include "../../datastructures/DocIterator.h"
#include "../../datastructures/PostingList.h"
#include "../../datastructures/TermIterator.h"
#include "../../datastructures/PhraseIterator.h"
#include "../../datastructures/EmptyIterator.h"
#include "../../misc/stopwords.h"

using namespace std;

class PhraseExpression : public Expression {
 private:
    Token tok;
    vector<string> terms;
    vector<int> offsets;
    set<string> stopWords;

    void splitPhrase() {
        string phrase = tok.value;
        istringstream iss(phrase);
        vector<string> tokens;
        copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(tokens));
        int cur = 0;
        for (int i = 0; i < tokens.size(); i++) {
            std::transform(tokens[i].begin(), tokens[i].end(), tokens[i].begin(), ::tolower);
            if (!stopWords.count(tokens[i])) {
                terms.push_back(tokens[i]);
                if (terms.size() >= 1) offsets.push_back(cur);
                cur = 1;
            } else {
                cur++;
            }
        }
    }

 public:
    PhraseExpression(Token t) {
	tok = t;
    }

    string toString() {
	return "Phrase("+tok.value+")";
    }

    void free() {
	delete this;
    }

    virtual DocIterator* getIterator(map<string, PostingList>& index) {
        splitPhrase();
        if (terms.size() == 0) return new EmptyIterator();
        if (terms.size() == 1) {
            if (index.count(terms[0])==0) return new EmptyIterator();
            return new TermIterator(index[terms[0]]);
        }
        vector<TermIterator*> termIterators;
        for (int i = 0; i < terms.size(); i++) {
            if (index.count(terms[i]) == 0) return new EmptyIterator();
            termIterators.push_back(new TermIterator(index[terms[i]]));
        }
        return new PhraseIterator(termIterators, offsets);
    }

};

#endif
