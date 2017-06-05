using namespace std;
#include <iostream>
#include <vector>

int factorial[10000];
int MOD = 1000000007;

int calF(int n){
	if(n==1)
		return 1;
	if(factorial[n])
		return factorial[n];
	factorial[n] = n*calF(n-1)%MOD;
	return factorial[n];
}
int C(int n,int r){
	return(calF(n)%MOD/(calF(r)%MOD)/(calF(n-r)%MOD)%MOD);
}
int encoder(vector<int> &nums){
	int ans = 0,n = nums.size();
	for(int i = 1;i<n;i++){
		for(int j = i;j<n;j++){
			ans += j*(nums[j] - nums[n-j-1]);
			cout<<ans<<' ';
		}
	}
	return ans;
}
int main(){
	int T;
	cin>>T;
	for(int j = 1;j<=T;j++){
		int N;
		cin>>N;
		vector<int> nums(N,0);
		for(int i = 0;i<N;i++){
			cin>>nums[i];
		}
		cout<<"Case #"<<j<<": "<<encoder(nums)<<endl;
	}
	return 0;
}
