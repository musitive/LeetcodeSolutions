#include <algorithm>

class Solution {
public:
    int maximumGain(const std::string& s, const int& x, const int& y) {
        setupSolution(x, y);
        
        std::string remaining = fromStringRemoveSubstring(s, higher_substring, higher_score);
        fromStringRemoveSubstring(remaining, lower_substring, lower_score);

        return total_score;
    }

    void setupSolution(const int& x, const int& y) {
        total_score = 0;
        if (x > y) {
            higher_substring = "ab";
            lower_substring = "ba";
            higher_score = x;
            lower_score = y;
        }
        else {
            higher_substring = "ba";
            lower_substring = "ab";
            higher_score = y;
            lower_score = x;
        }
    }

    std::string fromStringRemoveSubstring(const std::string& s, const std::string& substring, const int& point_value) {
        stack<char> chars;
        int n = s.length();

        for (const char& c : s) {
            if (doesCharAndStackMatchSubstring(c, chars, substring)) {
                chars.pop();
                total_score += point_value;
            }
            else chars.push(c);
        }

        return reconstructString(chars);
    }

    inline bool doesCharAndStackMatchSubstring(const char& c, const std::stack<char>& chars, const std::string& substring) const {
        return c == substring[1] && !chars.empty() && chars.top() == substring[0];
    }

    std::string reconstructString(stack<char>& chars) const {
        std::string reconstructed_string;
        while (!chars.empty()) {
            reconstructed_string += chars.top();
            chars.pop();
        }
        reverse(reconstructed_string.begin(), reconstructed_string.end());
        return reconstructed_string;
    }

private:
    std::string higher_substring;
    std::string lower_substring;
    int higher_score;
    int lower_score;
    int total_score;
};