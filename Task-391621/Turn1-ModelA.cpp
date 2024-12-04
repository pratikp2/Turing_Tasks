#include <iostream>
#include <vector>

using namespace std;

// Function to solve the knapsack problem using dynamic programming
int knapsack(int W, vector<int>& weights, vector<int>& values, int n) {
    // Create a 2D array to store the maximum value for each subproblem
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));

    // Build the dp table
    for (int i = 1; i <= n; ++i) {
        for (int w = 1; w <= W; ++w) {
            if (weights[i - 1] > w) {
                // If the current item's weight is greater than the knapsack weight,
                // ignore it and take the maximum value from the previous subproblem
                dp[i][w] = dp[i - 1][w];
            } else {
                // Otherwise, choose the maximum value either by including or excluding the item
                dp[i][w] = max(dp[i - 1][w], dp[i - 1][w - weights[i - 1]] + values[i - 1]);
            }
        }
    }

    // The result is stored in dp[n][W]
    return dp[n][W];
}

int main() {
    // Input: weights and values of items, knapsack capacity
    int W = 50; // Knapsack capacity
    vector<int> weights = {10, 20, 30};
    vector<int> values = {60, 100, 120};
    int n = weights.size();

    // Call the knapsack function
    int maxValue = knapsack(W, weights, values, n);

    // Output the maximum value that can be achieved
    cout << "Maximum value that can be achieved: " << maxValue << endl;

    return 0;
}
