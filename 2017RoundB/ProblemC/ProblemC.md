# Kickstart Round B 2017
## [Problem C. Christmas Tree](https://code.google.com/codejam/contest/11304486/dashboard#s=p2)

You are given a rectangular grid with N rows and M columns. Each cell of this grid is painted with one of two colors: green and white. Your task is to find the number of green cells in the largest Christmas tree in this grid.

To define a Christmas tree, first we define a good triangle as follows:

A good triangle with top point at row R, column C and height h (h > 0) is an isoceles triangle consisting entirely of green cells and pointing upward. Formally, this means that: The cell (R, C) is green, and for each i from 0 to h-1 inclusive, the cells in row R+i from column C-i to column C+i are all green.

题目要求：

small-input：在二维图像中找最大等腰三角形（1，3，5，...）。

large-input：在二维图像中找最大的圣诞树，圣诞树由相连等边三角形组成。

找三角形的过程可以用dp做。

```
if src[i][j]=='#':
	res[i][j]=min(res[i-1][j]+1,res[i-1][j-1]+2)
```

最后只要取整个数组的最大值即为三角底边值。求解的时候关于边界情况（max_value值为0及1）考虑的不足。

考虑圣诞树问题：

每一个点的结果为max(这个点在圣诞树内，这个店不在圣诞树内）

在圣诞树内的情况则是（这个点所在的所有三角其顶点相邻点所在的最大的K-1个三角圣诞树）只需要考虑这个点为三角右下角顶点的情况，对于数字2n-1，其高度n的三角底边为其左侧侧2n-1个位置，因此当遍历时需要对所有底边赋值。

因此每个点需要储存K个值，分别为这个点位于第k个三角下顶点时这个圣诞树的最大的面积。

遍历每一个点时，例如某一点数字为5，则其所在的三角可能有3种高度，找到这三个三角顶点的三个上邻点。高度为1：a[i][j][k]=a[i-1][j][k-1]+1;高度为2：a[i][j][k] = max(a[i][j][k],a[i-2][j-1][k-1]+4),对a[i][j-1],a[i][j-2]同样处理；高度为3同理。

注意题目要求是excactly K个三角。

代码如下，时间复杂度非常高：

```c++
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
```

