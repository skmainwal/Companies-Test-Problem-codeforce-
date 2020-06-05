#include<bits/stdc++.h>
using namespace std;

const int m_inf = -1e5;

class Solution
{
public:
	int cherryPickup(vector<vector<int>> &oldGrid);
};

int Solution :: cherryPickup(vector<vector<int>> &oldGrid)
{
	int n = oldGrid.size();

	// Let us create 2 borders by switching to one based index
	vector<vector<int>> grid(n + 1, vector<int>(n + 1, 0));

	for(int i = 0 ; i < n; i++)
		for(int j = 0; j < n; j++)
			grid[i + 1][j + 1] = oldGrid[i][j];

	vector<vector<int>> vec_2d(n + 1, vector<int>(n + 1, m_inf));

	vector<vector<vector<vector<int>>>> dp(n + 1);
	for(auto &vec_3d : dp)
		vec_3d.resize(n + 1, vec_2d);

	/* dp[x][y][p][q] represents the maximum cherries that 2 persons can pick up
	 * if Person 1 goes from (x, y) ---> (1, 1) and Person 2 from (p, q) ---> (1, 1)
	 */

	// Base Case : Already at the destination
	dp[1][1][1][1] = grid[1][1];
	for(int x = 1; x <= n; x++)
	{
		for(int y = 1; y <= n; y++)
		{
			for(int p = 1; p <= n; p++)
			{
				for(int q = 1; q <= n; q++)
				{
					// Atleast one person is stuck
					if( (grid[x][y] == -1) or (grid[p][q] == -1))
						continue;

					int up_up = dp[x - 1][y][p - 1][q];
					int up_left = dp[x - 1][y][p][q - 1];
					int left_up = dp[x][y - 1][p - 1][q];
					int left_left = dp[x][y - 1][p][q - 1];

					int max_val = max(up_up, left_left);
					max_val = max(max_val, max(up_left, left_up));

					// No moves possible from here
					if(max_val < 0)
						continue;

					dp[x][y][p][q] = max_val + grid[x][y];

					// If they are not the same cell, add the contribution
					if( not (x == p and y == q))
						dp[x][y][p][q] += grid[p][q];
				}
			}
		}
	}

	// Don't forget to take maximum (if path doesn't exist)
	return max(0, dp[n][n][n][n]);
}

int main()
{
	int n;
	cin >> n;

	vector<vector<int>> grid(n, vector<int>(n, 0));

	for(auto &row_vec : grid)
		for(auto &ele : row_vec)
			cin >> ele;

	Solution sol;
	cout << sol.cherryPickup(grid) << endl;

	return 0;
}
