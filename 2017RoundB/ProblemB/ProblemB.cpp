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
