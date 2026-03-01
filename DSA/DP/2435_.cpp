#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

//recursion + memoization
class Solution{
    public:
        int mod = 1e9 + 7;
        int n, m;
        vector<vector<vector<int>>> t;

        int solve(int i, int j, int currSum, vector<vector<int>>& grid, int k){
            if(i >= n || j >= m) return 0;

            //base case
            if(i == n-1 && j == m-1){
                return (currSum + grid[i][j]) % k == 0;
            }

            //dp check
            if(t[i][j][currSum] != -1) return t[i][j][currSum];

            int down = solve(i+1, j, (currSum + grid[i][j]) % k, grid, k);
            int right = solve(i, j+1, (currSum + grid[i][j]) % k, grid, k);

            return t[i][j][currSum] = (down + right) % mod;
        }
        int numberOfPaths(vector<vector<int>>& grid, int k){
            n = grid.size();
            m = grid[0].size();

            t.assign(n, vector<vector<int>>(m, vector<int>(k, -1)));
            return solve(0, 0, 0, grid, k);
        }
};


//bottom-up DP
//3d-visualization

//t[i][j][remainder] = number of paths from [i][j] to [n-1][m-1] with current remainder =  remain

class Solution {
public:
    int M = 1e9 + 7;

    int numberOfPaths(vector<vector<int>>& grid, int k) {
        int m = grid.size();
        int n = grid[0].size();

        int t[m+1][n+1][k+1];
        memset(t, 0, sizeof(t));
        // t[i][j][remain] = number of paths from [i][j] to [m-1][n-1] with current remainder = remain

        // Base case same as recursion
        for(int remain = 0; remain < k; remain++) {
            t[m-1][n-1][remain] = ((remain + grid[m-1][n-1]) % k == 0 ? 1 : 0);
        }

        for(int row = m - 1; row >= 0; row--) {
            for(int col = n - 1; col >= 0; col--) {

                for(int remain = 0; remain < k; remain++) {

                    if(row == m - 1 && col == n - 1)
                        continue;

                    int newRemain = (remain + grid[row][col]) % k;

                    long long down  = t[row + 1][col][newRemain];
                    long long right = t[row][col + 1][newRemain];

                    t[row][col][remain] = (down + right) % M;
                }
            }
        }

        return t[0][0][0];
    }
};