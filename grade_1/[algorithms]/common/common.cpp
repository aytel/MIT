#include <iostream>
#include <vector>
#include <algorithm>
#define LOCAL

using namespace std;

struct path {
	int size, head, tail;
	vector < int > tree;
	void build() {
		int sz = 1;
		while (sz < size)
			sz <<= 1;
		size = sz;
		tree.resize(2 * sz - 1);
	}
	int get(int v, int l, int r, int bg, int en) {
		if (l >= en || bg >= r)
			return 0;
		if (bg >= l && r <= en)
			return tree[v];
		int m = (l + r) >> 1;
		return max(get(2 * v + 1, l, m, bg, en), get(2 * v + 2, m, r, bg, en));
	}
	void add(int v, int x) {
		v += size - 1;
		tree[v] += x;
		while (v) {
			v = (v - 1) >> 1;
			tree[v] = max(tree[2 * v + 1], tree[2 * v + 2]);
		}
	}
};

vector < int > sz, us, in, dpth, tin, tout;
vector < path > hld;
vector < vector < int > > up, g;
const int MX = 20;
int T = 0;

void dfs(int v) {
	tin[v] = T++;
	us[v] = 1;
	hld[v].size = 1;
	in[v] = hld[v].head = hld[v].tail = v;
	for (int i = 1; i < MX; i++)
		up[v][i] = up[up[v][i - 1]][i - 1];

	sz[v] = 1;
	int mx = -1;
	for (int i : g[v]) {
		if (i == up[v][0])
			continue;
		up[i][0] = v;
		dpth[i] = dpth[v] + 1;
		dfs(i);
		if (mx == -1 || sz[i] > sz[mx])
			mx = i;
	}

	for (int i : g[v]) {
		if (i == up[v][0] || i == mx)
			continue;
		hld[in[i]].build();
	}

	if (mx == -1)
		return;

	sz[v] += sz[mx];
	in[v] = in[mx];
	hld[in[v]].tail = v;
	tout[v] = T++;
	return;
}


void add(int v, int x) {
	int ind = in[v], pos = dpth[v];
	hld[ind].add(pos, x);
	return;
}

bool ispr(int a, int b) {
	return tin[a] <= tin[b] && tout[a] >= tout[b];
}

int lca(int a, int b) {
	if (ispr(a, b))
		return a;
	if (ispr(b, a))
		return b;
	for (int pw = MX - 1; pw >= 0; pw--) {
		if (!ispr(up[a][pw], b))
			a = up[a][pw];
	}
	return up[a][0];
}

int vget(int dw, int up) {
	int ret = 0;
	while (in[dw] != in[up]) {
		int i = in[dw];
		int bg = dpth[dw], en = dpth[hld[i].tail] + 1;
		ret = max(ret, hld[i].get(0, 0, hld[i].size, bg, en));
		dw = up[hld[i].tail][0];
	}
	int i = in[dw];
	int bg = dpth[dw], en = dpth[up] + 1;
	ret = max(ret, hld[i].get(0, 0, hld[i].size, bg, en));
	return ret;
}

int get(int v, int u) {
	int l = lca(v, u);
	return max(vget(v, l), vget(u, l));
}

int main() {
	iostream::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

#ifndef LOCAL
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif

	int n;
	cin >> n;

	g.resize(n);
	us.resize(n, 0);
	tin.resize(n), tout.resize(n);
	up.resize(n, vector < int >(20, 0));
	in.resize(n);
	hld.resize(n);
	sz.resize(n);
	dpth.resize(n);

	for (int i = 0; i < n - 1; i++) {
		int v, u;
		cin >> v >> u;
		v--, u--;
		g[v].push_back(u);
		g[u].push_back(v);
	}

	dpth[0] = 0;
	dfs(0);
	hld[in[0]].build();

	int q;
	cin >> q;

	while (q--) {
		char c;
		cin >> c;

		if (c == 'I') {
			int v, x;
			cin >> v >> x;
			v--;
			add(v, x);
		}
		else {
			int v, u;
			cin >> v >> u;
			v--, u--;
			cout << get(v, u) << '\n';
		}
	}

	return 0;
}

