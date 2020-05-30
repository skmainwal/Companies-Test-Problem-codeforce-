#include<bits/stdc++.h>
using namespace std;

const int max_weight = 100 + 1;

class Graph
{
public:
	int vertex;
	vector<vector<int>> cc;
	vector<vector<vector<int>>> adj;
	vector<int> visited;
public:
	Graph(int vertex);
	void addEdge(int u, int v, int w);
	void dfs(int source, int cc_no, int w);
	void dfs_wrapper();
};

Graph :: Graph(int vertex)
{
	this->vertex = vertex;
	adj.resize(max_weight, vector<vector<int>>(vertex));
	cc.resize(max_weight, vector<int>(vertex, 0));
}

void Graph :: addEdge(int u, int v, int w)
{
	adj[w][u].push_back(v);
	adj[w][v].push_back(u);
}

void Graph :: dfs(int source, int cc_no, int w)
{
	visited[source] = true;
	
	cc[w][source] = cc_no;

	for(auto child : adj[w][source])
		if(not visited[child])
			dfs(child, cc_no, w);

}

void Graph :: dfs_wrapper()
{
	cc.resize(max_weight, vector<int>(vertex, 0));
	
	for(int w = 1; w < max_weight; w++)
	{
		visited.assign(vertex, false);
		int cc_no = 1;

		for(int source = 0; source < vertex; source++)
		{
			if(not visited[source])
			{
				dfs(source, cc_no, w);
				cc_no++;
			}
		}
	}

	vector<vector<int>> dp(vertex, vector<int>(vertex, 0));

	/* dp[i][j] represents the number of shared interests of `i` and `j` */
	for(int weight = 1; weight < max_weight; weight++)
		for(int i = 0; i < vertex; i++)
			for(int j = i + 1; j < vertex; j++)
				if(cc[weight][i] > 0 and cc[weight][i] == cc[weight][j])
					dp[i][j]++;

	int max_interest = 0;
	for(int i = 0; i < vertex; i++)
		for(int j = i + 1; j < vertex; j++)
			max_interest = max(max_interest, dp[i][j]);

	int res = 0;
	for(int i = 0; i < vertex; i++)
		for(int j = i + 1; j < vertex; j++)
			if(dp[i][j] == max_interest)
				res = max(res, (i + 1)*(j + 1));

	cout << res << endl;
}

void solve()
{
	int vertex, edges;
	cin >> vertex >> edges;

	Graph graph(vertex);

	for(int i = 0; i < edges; i++)
	{
		int u, v, w;
		cin >> u >> v >> w;

		u--; v--;
		graph.addEdge(u, v, w);
	}

	graph.dfs_wrapper();
}

int main()
{
	solve();
	return 0;
}


