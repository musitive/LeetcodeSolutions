#define UP_ONE_DIRECTORY "../"
#define CURRENT_DIRECTORY "./"

class Solution {
private:
    int operations;

public:
    int minOperations(vector<string>& logs) {
        operations = 0;

        for (const string& log : logs) {
            updateOperationsFromLog(log);
        }

        return operations;
    }

    inline void updateOperationsFromLog(const string& log) {
        if (log == UP_ONE_DIRECTORY) {
            if (operations > 0) {
                operations -= 1;
            }
        }
        else if (log != CURRENT_DIRECTORY) {
            operations += 1;
        }
    }
};