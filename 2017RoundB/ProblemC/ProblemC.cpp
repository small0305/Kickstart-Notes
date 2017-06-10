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
	max_value = max_value ? (max_value - 1) / 2 * 2 + 1 : 0;
	if (K == 1) return (max_value + 1)*(max_value + 1) / 4;
	//K>1
	vector<vector<vector<int>>> sums(N, vector<vector<int>>(M, vector<int>(K + 1, 0)));
	max_value = 0;
	for (int i = 0; i<N; i++) {
		for (int j = 0; j<M; j++) {
			int n = nums[i][j];
			if (n == 0)
				continue;
			//first line
			for (int h = 1; 2 * h - 1 <= n; h++) {
				for (int k = 1; k <= K; k++) {
					if (i - h < 0) {
						for (int l = 0; l<2 * h - 1; l++) {
							sums[i][j - l][1] = max(sums[i][j - l][1], h*h);
						}
						break;
					}
					if (k-1&&sums[i - h][j - h + 1][k - 1] == 0) continue;
					int now_value = sums[i - h][j - h + 1][k - 1] + h*h;
					
					for (int l = 0; l<2 * h - 1; l++) {
						sums[i][j - l][k] = max(sums[i][j - l][k], now_value);
					}
				}
				max_value = max(max_value, sums[i][j][K]);
			}
		}
	}
	return max_value;
}
int main() {
	freopen("C-large-practice.in", "r", stdin);
	freopen("C-large-practice.out", "w", stdout);
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
		int cc = solve(c, N, M, K);//46
		printf("Case #%d: %d\n", k, cc);
	}
	
	return 0;
}