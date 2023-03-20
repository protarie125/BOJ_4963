#include <iostream>
#include <vector>
#include <stack>

using namespace std;

using vb = vector<bool>;
using vvb = vector<vb>;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using sii = stack<pii>;

vvi f;
vvb isChecked;
sii st;
auto dx = vi{ -1,0,1,-1,1,-1,0,1 };
auto dy = vi{ -1,-1,-1,0,0,1,1,1 };
int ans;
void solve(int w, int h, int x, int y) {
	isChecked[y][x] = true;

	for (auto d = 0; d < 8; ++d) {
		const auto& nx = x + dx[d];
		const auto& ny = y + dy[d];
		if (nx < 0 || w <= nx ||
			ny < 0 || h <= ny) {
			continue;
		}

		if (1 == f[ny][nx] &&
			!isChecked[ny][nx]) {
			st.push({ y + dy[d], x + dx[d] });
		}
	}

	while (!st.empty()) {
		auto t = st.top();
		st.pop();
		solve(w, h, t.second, t.first);
	}
}

int main() {
	ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int w, h;
	cin >> w >> h;
	while (!(0 == w && 0 == h)) {
		f = vvi(h, vi(w));
		isChecked = vvb(h, vb(w, false));
		for (auto i = 0; i < h; ++i) {
			for (auto j = 0; j < w; ++j) {
				cin >> f[i][j];
			}
		}

		ans = 0;
		for (auto i = 0; i < h; ++i) {
			for (auto j = 0; j < w; ++j) {
				if (0 == f[i][j]) {
					continue;
				}

				if (isChecked[i][j]) {
					continue;
				}

				solve(w, h, j, i);
				++ans;
			}
		}
		cout << ans << '\n';

		cin >> w >> h;
	}

	return 0;
}