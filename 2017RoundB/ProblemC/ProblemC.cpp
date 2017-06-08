using namespace std;
#include <iostream>
#include <cstdio>
#include <vector>
#include <math.h>
#include <algorithm>
int solve(vector<vector<char>> &c, int N, int M, int K) {
	vector<vector<int>> nums(N, vector<int>(M, 0));
	int max_value = 0;
	for (int i = 0; i<N; i++) {
		for (int j = 0; j<M; j++) {
			if (c[i][j] == '.')
				continue;
			//first line
			if (i == 0) {
				nums[i][j] = 1;
				max_value = max(nums[i][j], max_value);
				continue;
			}
			if (j == 0) {
				nums[i][j] = 1;
				max_value = max(nums[i][j], max_value);
				continue;
			}
			nums[i][j] = min(nums[i][j - 1] + 1, nums[i - 1][j - 1] + 2);
			if (nums[i][j] == 2 && nums[i - 1][j] == 0)nums[i][j] = 1;
			max_value = max(nums[i][j], max_value);
		}
	}
	max_value = max_value?(max_value-1) / 2 * 2+1:0;
	return (max_value+1)*(max_value+1)/4;
}
int main() {
	freopen("C-small-practice.in", "r", stdin);
	freopen("C-small-practice.out", "w", stdout);
	int T; 	scanf("%d", &T);
	for (int k = 1; k <= T; k++) {
		int N, M, K;
		scanf("%d %d %d", &N, &M, &K);
		vector<vector<char>> c(N, vector<char>(M, ' '));
		char s[102];
		for (int i = 0; i < N; i++) {
			scanf("%s", s);
			for (int j = 0; j < M; j++)
				c[i][j] = s[j];
		}
		int cc = solve(c, N, M, K);
		printf("Case #%d: %d\n", k, cc);
	}
	return 0;
}