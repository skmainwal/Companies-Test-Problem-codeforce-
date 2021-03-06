#include<bits/stdc++.h>
using namespace std;

void solve(vector<int> &start, vector<int> &duration, vector<int> &profit)
{
	int n = start.size();
	vector<int> finish = start;

	// Add the duration  to get the end time
	for(int i = 0; i < n; i++)
		finish[i] += duration[i];

	// Stores the (finish time, index)
	vector<pair<int, int>> fin_index;

	for(int i = 0; i < n; i++)
		fin_index.push_back(make_pair(finish[i], i));
	
	// Sort according to finish time
	sort(fin_index.begin(), fin_index.end());

	map<int, int, greater<int>> dp;

	/* dp[end] is the maximum profit that you can earn till time 'end' */
	dp[fin_index.front().first] = profit[fin_index.front().second];

	for(int i = 1; i < n; i++)
	{
		int end_time = fin_index[i].first;
		int ind = fin_index[i].second;

		// Be careful which lower bound to use
		int take_it = dp.lower_bound(start[ind])->second;
		int leave_it = dp.lower_bound(end_time)->second;

		dp[end_time] = max(leave_it, profit[ind] + take_it);
	}

	// DP is sorted in reverse order
	cout << dp.begin()->second << endl;	
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int n;
	cin >> n;

	vector<int> start(n), duration(n), profit(n);

	for(auto &ele : start)
		cin >> ele;
	
	int fake;
	cin >> fake;

	for(auto &ele : duration)
		cin >> ele;

	cin >> fake;
	
	for(auto &ele : profit)
		cin >> ele;

	solve(start, duration, profit);
	return 0;
}
