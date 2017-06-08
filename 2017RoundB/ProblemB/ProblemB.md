# Kickstart Round B 2017
## [Problem B. Center](https://code.google.com/codejam/contest/11304486/dashboard#s=p1)

There are N weighted points in a plane. Point i is at (Xi, Yi) and has weight Wi.

In this problem, we need to find a special center of these points. The center is a point (X, Y) such that the sum of max(|X-Xi|, |Y-Yi|)*Wi is minimum.

给N个质点的位置及其质量，求一个点使得所有点到它的$max(|X-Xi|, |Y-Yi|)*W_i$和最小。

本质是求一个到所有点加权切比雪夫距离最小的点。本题模拟的是一种仓库中找到最佳仓库位置的问题。

> 切比雪夫距离：设a(x1,y1),b(x2,y2);DIS = max(|x1-x2|,|y1-y2|) = (|x1-x2+y1-y2|+|x1-x2-y1+y2|)/2;
我们将点aa的坐标看成（x1+y1,x1-y1）,bb的坐标看成（x2+y2,x2-y2）,从几何意义上讲相当于点在原坐标系上逆时针旋转45度，并将坐标扩大2倍。
然后求得的最小的曼哈顿距离和的一半即可。

因此转化为曼哈顿距离后可以对x和y分别求最佳的坐标位置。

在leetcode [462. Minimum Moves to Equal Array Elements II](https://leetcode.com/problems/minimum-moves-to-equal-array-elements-ii/#/description)中，就可以发现位置最佳的点并不是平均值，而是中位数。

增加权重后可以考虑通过两个指针的方式，找到一个点使得其两侧重量相近。

整体的思路：

首先把每个坐标值转化为(x+y,x-y)；

然后对x排序，排好序后找到一个点使得它左面的所有质点的质量和与右侧所有质点的质量近似相等（一定可以找到这样的一个点，但可能不是唯一的），得到最终坐标值X；

对y进行同样操作，得到Y；

对这个位置计算SUM((|X-Xi|+|Y-Yi|))，并将结果/2得到最终结果。

参考(http://www.it610.com/article/1700126.htm) (http://m.2cto.com/kf/201501/373178.html)

第一次提交运算结果时候结果不对，发现是float精度太低，遂改为double。

代码：
```c++
using namespace std;
#include <iostream>
#include <cstdio>
#include <vector>
#include <math.h>
#include <algorithm>

bool sort_X(vector<float> a, vector<float> b) {
	return a[0]<b[0];
}
bool sort_Y(vector<float> a, vector<float> b) {
	return a[1]<b[1];
}
double center(vector<vector<float>> &nums) {
	int n = nums.size();
	//transfer to manhaton distance
	for (int i = 0; i < n; i++) {
		double x = nums[i][0], y = nums[i][1];
		nums[i][0] = x + y;
		nums[i][1] = x - y;
	}
	//calculate x
	sort(nums.begin(), nums.end(), sort_X);
	int start = 0, end = n - 1;
	double left = nums[start][2], right = nums[end][2];
	while (start<end) {
		if (left<right) {
			start++;
			left += nums[start][2];
		}
		else {
			end--;
			right += nums[end][2];
		}
	}
	float X = nums[start][0];
	//calculate y
	sort(nums.begin(), nums.end(), sort_Y);
	start = 0, end = n - 1;
	left = nums[start][2], right = nums[end][2];
	while (start<end) {
		if (left<right) {
			start++;
			left += nums[start][2];
		}
		else {
			end--;
			right += nums[end][2];
		}
	}
	float Y = nums[start][1];
	double res = 0;
	for (int i = 0; i < n; i++) {
		float x = nums[i][0], y = nums[i][1], w = nums[i][2];
		res += (abs(x - X) + abs(y - Y))*w;
	}

	return res / 2;
}
int main() {
	freopen("B-large-practice.in", "r", stdin);
	freopen("B-large-practice.out", "w", stdout);
	int T; 	scanf("%d", &T);
	for (int j = 1; j <= T; j++) {
		int N; scanf("%d", &N);
		vector<vector<float>> nums(N, vector<float>(3, 0.0));
		for (int i = 0; i<N; i++)
			scanf("%f %f %f",&nums[i][0],&nums[i][1],&nums[i][2]);
		double cc = center(nums);
		printf("Case #%d: %2.1f\n", j, cc);
	}
	return 0;
}

```

然后看了别人的代码，发现别人都是用一维搜索暴力做的。= =人和人之间的差距啊。

```c++
#include<cstdio>
#include<algorithm>
using namespace std;

const int NMAX = 10000;
double X[NMAX], Y[NMAX], W[NMAX];
int N;

double go(double x, double y){
	double ret = 0;
	for (int i = 0; i < N; i++)
		ret += max(abs(X[i] - x), abs(Y[i] - y))*W[i];
	return ret;
}

double ternary_search(double x){
	double lo = -1000, hi = 1000;
	for (int i = 0; i < 100; i++){
		double m1 = (2 * lo + hi) / 3;
		double m2 = (lo + 2 * hi) / 3;
		double L = go(x, m1), R = go(x, m2);
		if (L <= R) hi = m2;
		else lo = m1;
	}
	return go(x, lo);
}

double process(){
	double lo = -1000, hi = 1000;
	for (int i = 0; i < 100; i++){
		double m1 = (2 * lo + hi) / 3;
		double m2 = (lo + 2 * hi) / 3;
		double L = ternary_search(m1), R = ternary_search(m2);
		if (L <= R) hi = m2;
		else lo = m1;
	}
	return ternary_search(lo);
}

int main(){
	freopen("large.in", "r", stdin);
	freopen("large.out", "w", stdout);

	int T; scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++){
		scanf("%d", &N);
		for (int i = 0; i < N; i++) scanf("%lf%lf%lf", X + i, Y + i, W + i);
		printf("Case #%d: %.10f\n", tc, process());
	}
}
```