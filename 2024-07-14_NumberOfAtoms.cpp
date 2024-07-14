#include <map>
#include <algorithm>
#include <stdlib.h>

#define OPEN_PAREN '('
#define CLOSE_PAREN ')'

class Solution {
public:
    string countOfAtoms(string& formula) {
        analyzeFormula(formula, 1);

        return convertElementMapToString();
    }

private:
    map<string, int> element_count;

    void initializeSolution() {
        element_count = map<string, int>();
    }

    void analyzeFormula(string& formula, const int multiplier) {
        int n = formula.length();

        for (string::iterator iter = formula.begin(); iter != formula.end(); ++iter) {
            if (isupper(*iter)) {
                handleUpperCase(iter, formula, multiplier);
            }
            else if (isOpenParen(*iter)) {
                handleOpenParen(iter, formula, multiplier);
            }
        }
    }

    inline void handleUpperCase(string::iterator& iter, string& formula, const int multiplier) {
        string element(1, *iter);
        string::iterator next = iter+1;

        if (next == formula.end()) {
            addElementAndCountToMap(element, multiplier);
            return;
        }
        if (islower(*next)) {
            element += *next;
            ++iter, ++next;
            if (next == formula.end()) {
                addElementAndCountToMap(element, multiplier);
                return;
            }
        }
        int new_multiplier = multiplier * getMultiplier(iter, formula);
        addElementAndCountToMap(element, new_multiplier);
    }

    inline void handleOpenParen(string::iterator& iter, string& formula, const int multiplier) {
        string::iterator subFormulaStart = iter + 1;
        string::iterator subFormulaEnd;

        int new_multiplier = multiplier * (int) getSubFormulaMultiplier(iter, subFormulaEnd, formula);
        string subFormula(subFormulaStart, subFormulaEnd);
        analyzeFormula(subFormula, new_multiplier);
    }

    inline int getSubFormulaMultiplier(string::iterator& iter, string::iterator& subFormulaEnd, string& formula) {
        stack<string::iterator> openParens;
        openParens.push(iter);

        do {
            ++iter;
            if (isOpenParen(*iter)) openParens.push(iter);
            else if (isCloseParen(*iter)) openParens.pop();
        } while(!openParens.empty());

        subFormulaEnd = iter;
        return getMultiplier(iter, formula);
    }

    int getMultiplier(string::iterator& iter, string& formula) {
        if (iter + 1 == formula.end() || !isdigit(*(iter+1))) return 1;
        string multiplier = "";
        do {
            ++iter;
            multiplier += *iter;
        } while (iter + 1 != formula.end() && isdigit(*(iter+1)));
        return stoi(multiplier);
    }

    inline void parseElementFromIterator(string::iterator& iter, string& formula, const int multiplier) {
        string s(1, *iter);
        if (iter+1 == formula.end() || isupper(*(iter+1)) || isParen(*(iter+1))) {
            addElementAndCountToMap(s, multiplier);
            return;
        }
        else if (islower(*(iter+1))) {
            s += *(iter+1);
            ++iter;
        }
        int new_multiplier = multiplier * getMultiplier(iter, formula);
        addElementAndCountToMap(s, new_multiplier);
    }

    inline void addElementAndCountToMap(const string& s, const int& count) {
        map<string, int>::iterator iter = element_count.find(s);
        if (iter == element_count.end())
            element_count[s] = count;
        else
            iter->second += count;
    }

    bool isParen(const char& c) const {
        return isOpenParen(c) || isCloseParen(c);
    }

    inline bool isOpenParen(const char& c) const {
        return c == OPEN_PAREN;
    }

    inline bool isCloseParen(const char& c) const {
        return c == CLOSE_PAREN;
    }

    string convertElementMapToString() {
        string solution = "";
        for (map<string, int>::iterator iter = element_count.begin(); iter != element_count.end(); ++iter) {
            solution += iter->first;
            if (iter->second > 1)
                solution += to_string(iter->second);
        }
        return solution;
    }
};