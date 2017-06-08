# Kickstart Round B 2017
## [Problem A. Math Encoder](https://code.google.com/codejam/contest/11304486/dashboard)
1. Find all subsets and get the difference between largest & smallest numbers:
[3], largest-smallest = 3 - 3 = 0.
[6], largest-smallest = 6 - 6 = 0.
[7], largest-smallest = 7 - 7 = 0.
[9], largest-smallest = 9 - 9 = 0.
[3, 6], largest-smallest = 6 - 3 = 3.
[3, 7], largest-smallest = 7 - 3 = 4.
[3, 9], largest-smallest = 9 - 3 = 6.
[6, 7], largest-smallest = 7 - 6 = 1.
[6, 9], largest-smallest = 9 - 6 = 3.
[7, 9], largest-smallest = 9 - 7 = 2.
[3, 6, 7], largest-smallest = 7 - 3 = 4.
[3, 6, 9], largest-smallest = 9 - 3 = 6.
[3, 7, 9], largest-smallest = 9 - 3 = 6.
[6, 7, 9], largest-smallest = 9 - 6 = 3.
[3, 6, 7, 9], largest-smallest = 9 - 3 = 6.
2. Find the sum of the differences calculated in the previous step:
3+4+6+1+3+2+4+6+6+3+6
= 44.
3. Find the answer modulo 109 + 7 (1000000007):
44 % 1000000007 = 44

问题是给你一个数组（排好序的），求数组的所有子序列最大值与最小值的差，并作和取余。

找规律可以发现第 $i$ 个数字(0-index)被加的次数为$(1+i+C_i^2+C_i^3+...)$，即**$(2^i)$**（还是看了几个人的代码才意识到）。

看题目应该可以推测出本题实现的是一种编码方式，所以应该会有对应的解码方式，因此计算过程不可能是硬算的，而是按位对应的。

在求解large-problem的过程中，会出现溢出情况。因此在这一步需要在`long long `下计算：
```C++
ans += (long long)pow(i)*(long long)(nums[i] - nums[n-i-1])%MOD
```

最终代码：
```C++
using namespace std;
#include <iostream>
#include <vector>

int pow[10000];
int MOD = 1000000007;

void calc(){
	pow[0] = 1;
	for(int i = 1; i<10000; i++){
		pow[i] = 2 * pow[i-1] % MOD;
	}
}

int encoder(vector<int> &nums){
	long long ans = 0;
	int n = nums.size();
	for(int i = n-1; i>=0; i--){
		ans += (long long)pow[i] * (long long)(nums[i] - nums[n-i-1]);
		ans %= MOD;
		ans += MOD;
		ans %= MOD;
	}
	return ans;
}
int main(){
    calc();
	int T;
	cin >> T;
	for(int j = 1; j<=T; j++){
		int N;
		cin >> N;
		vector<int> nums(N,0);
		for(int i = 0; i<N; i++)
			cin >> nums[i];
		cout << "Case #"<<j<<": "<<encoder(nums)<<endl;
	}
	return 0;
}

```
