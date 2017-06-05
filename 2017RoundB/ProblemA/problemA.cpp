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
