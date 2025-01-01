#include<bits/stdc++.h>
using namespace std;

#define MAX_N 100
const int INF = INT_MAX;

int dist[MAX_N][MAX_N];
int dp[MAX_N][1<<MAX_N];

int minDistance(int n, int start_mask, int curr)
{
    // Base case: If all cities are visited, 
    // then return the distance to the start city
    if (start_mask == (1 << n) - 1) {
        return dist[curr][0];
    }

    // If the current subproblem is already solved, 
    // return the stored value
    if (dp[curr][start_mask] != INF) {
        return dp[curr][start_mask];
    }

    int min_cost = INF;

    // For all cities not visited yet
    for (int i = 1; i < n; i++)
    {
        // If the city 'i' is not visited in the 
        // current path and it is connected to the 
        // current city 'curr'
        if ((start_mask & (1 << i)) == 0 && dist[curr][i] != INF)
        {
            // Make a new mask with the current city 'i' 
            // added to the visited cities
            int new_mask = start_mask | (1 << i);

            // Recur for the rest of the cities with the 
            // modified mask
            int cost = minDistance(n, new_mask, i);
            
            // Calculate the total cost and update the minimum
            cost += dist[i][0];
            min_cost = min(min_cost, cost);
        }
    }

    // Store the minimum cost in the DP table
    dp[curr][start_mask] = min_cost;

    return min_cost;
}
 
/*  Driver program to test the above function*/
int main()
{
    int n;
    cout << "Enter number of vertices: ";
    cin >> n;

    /* Initialize all distances as non-neighbors 
       and 0 for self distance */
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            dist[i][j] = INF;
        }
        dist[i][i] = 0;
    }

    /* Read all the edge weights from user */
    for (int i = 0; i < n; i++)
    {
        for (int j = i+1; j < n; j++)
        {
            cout << "Enter distance between " << i << " and " << j << ": ";
            cin >> dist[i][j];
            dist[j][i] = dist[i][j];   // Assuming symmetric distances
        }
    }

  
    /* The dp table is used to store subproblem results */
    memset(dp, -1, sizeof(dp));

    /* Calculate minimum cost using the helper function */
    int cost = minDistance(n, 1, 0);

    cout << "\nMinimum cost = " << cost << endl;

    return 0;
}
