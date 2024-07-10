#include <vector>

class Solution {
private:
    long total_wait_time;
    long current_chef_time;

public:
    double averageWaitingTime(const std::vector<std::vector<int>>& customers) {
        total_wait_time = 0;
        current_chef_time = 1;

        for (int i = 0; i < customers.size(); ++i) {
            updateWaitTimes(customers[i]);
        }

        return (double) total_wait_time / customers.size();
    }

    inline void updateWaitTimes(const std::vector<int>& customer) {
        updateCurrentChefTime(customer[0], customer[1]);
        updateTotalWaitTime(customer[0]);
    }

    inline void updateCurrentChefTime(const int& arrival_time, const int& time_to_complete_order) {
        current_chef_time = std::max(current_chef_time, (long) arrival_time);
        current_chef_time += time_to_complete_order;
    }

    inline void updateTotalWaitTime(const int& arrival_time) {
        total_wait_time += current_chef_time - arrival_time;
    }
};