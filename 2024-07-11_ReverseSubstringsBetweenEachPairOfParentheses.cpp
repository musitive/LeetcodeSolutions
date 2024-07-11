#include <cstring>
#include <stack>

#define OPEN_PAREN '('
#define CLOSE_PAREN ')'

class Solution {
public:
    std::string reverseParentheses(const std::string& s) {
        setUpSolution(s);

        populatePairsOfParentheses();
        std::string result = usePairsToReverse();

        tearDownSolution();
        return result;
    }

private:
    int n;
    std::string s;
    std::vector<int>* pairs;
    std::stack<int>* openParentheses;

    void setUpSolution(const std::string& s) {
        this->s = s;
        n = this->s.length();
        pairs = new std::vector<int>(n);
        openParentheses = new std::stack<int>;
    }

    void tearDownSolution() {
        delete pairs;
        delete openParentheses;
    }

    void populatePairsOfParentheses() {
        for (int i = 0; i < n; ++i)
            evaluateIndexForPair(i);
    }

    inline void evaluateIndexForPair(const int& i) {
        char c = s[i];
        if (isOpenParen(c))
            openParentheses->push(i);
        else if (isCloseParen(c))
            createPairFromIndexAndStack(i);
    }

    inline void createPairFromIndexAndStack(const int& i) {
        int open = openParentheses->top();
        openParentheses->pop();
        (*pairs)[open] = i;
        (*pairs)[i] = open;
    }

    inline bool isOpenParen(const char& c) const {
        return c == OPEN_PAREN;
    }

    inline bool isCloseParen(const char& c) const {
        return c == CLOSE_PAREN;
    }

    std::string usePairsToReverse() {
        std::string result;

        for (int i = 0, direction = 1; i < n; i += direction) {
            char c = s[i];
            if (isParen(c)) updateIndices(i, direction);
            else result += c;
        }

        return result;
    }

    inline void updateIndices(int& i, int& direction) {
        i = (*pairs)[i];
        direction = -direction;
    }

    inline bool isParen(const int& c) const {
        return isOpenParen(c) || isCloseParen(c);
    }
};