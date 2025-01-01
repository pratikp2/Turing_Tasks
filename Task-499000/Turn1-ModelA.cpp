#include <iostream>
#include <vector>
#include <limits.h>
#include <cstring>

#define MAX 20
#define INF INT_MAX

using namespace std;

int dp[1 << MAX][MAX]; // DP array
int dist[MAX][MAX];    // Distance matrix
int n;                 // Number of cities

int tsp(int mask, int pos) {
    // If all cities have been visited, return to start
    if (mask == (1 << n) - 1) {
        return dist[pos][0]; // Return to the starting city
    }

    // Return if the solution has already been computed
    if (dp[mask][pos] != -1) {
        return dp[mask][pos];
    }

    int ans = INF;

    // Try to visit all other unvisited cities
    for (int city = 0; city < n; city++) {
        if ((mask & (1 << city)) == 0) { // If the city is not visited
            int newAns = dist[pos][city] + tsp(mask | (1 << city), city);
            ans = min(ans, newAns);
        }
    }

    return dp[mask][pos] = ans;
}

int main() {
    cout << "Enter the number of cities: ";
    cin >> n;

    cout << "Enter the distance matrix:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> dist[i][j];
        }
    }

    memset(dp, -1, sizeof(dp)); // Initialize dp array with -1
    int result = tsp(1, 0); // Start from city 0 with city 0 visited
    cout << "The minimum cost of the tour is: " << result << endl;
    
    return 0;
}
