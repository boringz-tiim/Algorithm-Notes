#include<bits/stdc++.h>
using namespace std;
int main(){
    int N,K;
    cin>>N>>K;
    vector<int>myvec;
    for(int i=0;i<N;i++){
        cin>>myvec[i];
    }
    //连续子序列，变长滑动窗口？？
    //前缀和
    int ans=0;
    vector<int>sum;
    sum[0]=myvec[0];
    if(sum[0]%K==0) ans++;
    for(int i=1;i<N;i++){
        sum[i]=sum[i-1]+myvec[i];
        if(sum[i]%K==0) ans++;
        for(int j=0;j<i;j++){
if((sum[i]-sum[j])%K==0) ans++;
        }
    }
    cout<<ans;
    return 0;

    
    
}