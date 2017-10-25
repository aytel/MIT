#define _CRT_SECURE_NO_WARNINGS
#pragma comment(linker, "/STACK:16777216")

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
#include <set>
#include <bitset>
#include <map>
#include <iomanip>
#include <deque>
#include <stack>
#include <cmath>
#include <unordered_set>
#include <cassert>
#include <functional>

using namespace std;

typedef long long ll;
const ll md = 1e9 + 7;

vector < vector < int > > g;
vector < int > us, path, tin, tout, tree, fl;
int T = 0, sz = 1;

void dfs(int v) {
	tin[v] = T++;
	path.push_back(v);
	us[v] = 1;

	for (int i : g[v]) {
		if (us[i])
			continue;
		dfs(i);
	}

	tout[v] = T++;
	path.push_back(v);
	return;
}

void build(int v, int l, int r) {
	if (l == r - 1)
		return;
	int m = (l + r) >> 1;
	build(2 * v + 1, l, m), build(2 * v + 2, m, r);
	tree[v] = tree[2 * v + 1] + tree[2 * v + 2];
}

void push(int v, int len) {
	fl[v] = 0;
	tree[v] = len - tree[v];
	if (len != 1) {
		fl[2 * v + 1] ^= 1;
		fl[2 * v + 2] ^= 1;
	}
	return;
}

int ask(int v, int len) {
	if (fl[v])
		return len - tree[v];
	else
		return tree[v];
}

void UP(int v, int l, int r, int bg, int en) {
	if (fl[v])
		push(v, r - l);
	if (bg >= r || l >= en)
		return;
	if (l >= bg && r <= en) {
		fl[v] ^= 1;
		return;
	}
	int m = (l + r) >> 1;
	UP(2 * v + 1, l, m, bg, en), UP(2 * v + 2, m, r, bg, en);
	tree[v] = ask(2 * v + 1, m - l) + ask(2 * v + 2, r - m);
	return;
}

void up(int v) {
	UP(0, 0, sz, tin[v], tout[v] + 1);
}

int GET(int v, int l, int r, int bg, int en) {
	if (fl[v])
		push(v, r - l);
	if (bg >= r || l >= en)
		return 0;
	if (l >= bg && r <= en) {
		return tree[v];
	}
	int m = (l + r) >> 1;
	return GET(2 * v + 1, l, m, bg, en) + GET(2 * v + 2, m, r, bg, en);
}

int get(int v) {
	return GET(0, 0, sz, tin[v], tout[v] + 1);
}

int main() {
	iostream::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif

	int n;
	cin >> n;

	g.resize(n);
	us.resize(n, 0);
	tin.resize(n);
	tout.resize(n);

	for (int i = 0; i < n - 1; i++) {
		int p;
		cin >> p;
		p--;
		g[p].push_back(i + 1);
	}

	dfs(0);

	while (sz < path.size())
		sz <<= 1;

	tree.resize(2 * sz - 1, 0);
	fl.resize(2 * sz - 1, 0);
	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		if (x) {
			tree[tin[i] + sz - 1] = 1;
			tree[tout[i] + sz - 1] = 1;
		}
	}

	build(0, 0, sz);

	int q;
	cin >> q;
	while (q--) {
		string s;
		cin >> s;
		if (s == "get") {
			int v;
			cin >> v;
			v--;
			cout << get(v) / 2 << '\n';
		} else {
			int v;
			cin >> v;
			v--;
			up(v);
		}
	}

	return 0;
}

