# Dijkstra最短路
在一个图里，找从起点到其他点的最短距离
## priority_queue 优先队列
默认是大顶堆，谁大谁先出来

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N=100005;
vector<pair<int,int>> g[N];
int dist[N];

void dijkstra(int n,int start){
    //进行初始化
    for(int i=0;i<=n;i++){
        dist[i]=1e9;
    }
    dist[start] = 0;
priority_queue<
    pair<int,int>,             //存的东西的类型，{距离，节点}
    vector<pair<int,int>>,     //底层容器
    greater<pair<int,int>>> pq; //排序方式（小顶堆
    pq.push({0,start});
    while(!pq.empty()){
        auto[d,u]=pq.top();
        pq.pop();
        if(d>dist[u]) continue;
        for(auto[v,w]:g[u]){
            if(dist[u]+w<dist[v]){
                dist[v]=dist[u]+w;
                pq.push({dist[v],v});
            }
    }
}
```
