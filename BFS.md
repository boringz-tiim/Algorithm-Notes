# 126.单词接龙Ⅱ
```cpp
class Solution {
    vector<vector<string>>ans;
    unordered_map<string,vector<string>>pre;
public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        //把字典放到dict  set里面去
        unordered_set<string>dict(wordList.begin(),wordList.end());
        //不存在直接返回空集合
        if(!dict.count(endWord)) return{};
        //BFS初始化
        queue<string>q;
        q.push(beginWord);
        //dist记录beginWord到每个单词的最短距离
        unordered_map<string,int>dist;
        dist[beginWord]=0;
        bool found=false;
        int step=0;
        //队列不空，且还没找到终点
        while(!q.empty()&&!found){
                int sz=q.size();
                //usedThisLevel存这一层新发现的单词
                unordered_set<string> usedThisLevel;
                step++;
                for(int k=0;k<sz;k++){
                    //cur string 取出这一层中的某一单词
                    string cur=q.front();
                    q.pop();
                    //nxt初始化和cur一致，不过等会要变换成下一层的单词
                    string nxt=cur;
                    for(int i=0;i<cur.size();i++){
                        //old char类型，用来记住被替换的字母
                        char old=nxt[i];
                        for(char c='a';c<='z';c++){
                            if(c==old) continue;//和原来一样，不能要
                            nxt[i]=c;
                            if(!dict.count(nxt)) continue;//字典里面没有，也是跳过
                            if(!dist.count(nxt)){//从未记录过到这个单词的最短路径
                            dist[nxt]=step;
                            q.push(nxt);
                            usedThisLevel.insert(nxt);

                            }
                            if(dist[nxt]==dist[cur]+1){
                                //如果nxt的层数正好比cur多1，说明cur是nxt的一个最短路径前驱
                                pre[nxt].push_back(cur);
                            }
                            if(nxt==endWord){
                                //找到重点，但并不立即return 因为当前这一层还要继续处理完
                                found=true;
                            }
                        }
                        //复原
                        nxt[i]=old;
                    }
                }
                for(auto &w:usedThisLevel){
                    //把本层访问过的单词从字典中删掉
                    dict.erase(w);
                }
        }
        if(!found) return {};
        vector<string>path;
        path.push_back(endWord);
        //dfs回溯，Pre存放的是当前单词<-前驱
        dfs(endWord,beginWord,path);
        return ans;

    }
    void dfs(string cur,string beginWord,vector<string>& path){
        if(cur==beginWord){
            vector<string>temp=path;
            reverse(temp.begin(),temp.end());
            ans.push_back(temp);
            return ;
        }
        for(string&p:pre[cur]){
            path.push_back(p);
            dfs(p,beginWord,path);
            //回溯，撤销刚才加入的单词，方便尝试下一条路径
            path.pop_back();
        }
    }
};
```
这道题....光是照着抄都燃尽了....

## 状态BFS+DFS回溯
BFS用于找到最短路径，构造前缀Pre列表
DFS回溯还原所有最短路径，将pre转换成完整路径path


 # 127.单词接龙
 这道题比上一道题简单，不需要进行DFS回溯，只需要BFS找到最短路径即可
 ```cpp
class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> dict(wordList.begin(), wordList.end());

        if(!dict.count(endWord)) return 0;

        queue<pair<string, int>> q;
        q.push({beginWord, 1});

        unordered_set<string> vis;
        vis.insert(beginWord);

        while(!q.empty()) {
            auto [cur, step] = q.front();
            q.pop();

            string nxt = cur;

            for(int i = 0; i < cur.size(); i++) {
                char old = nxt[i];

                for(char c = 'a'; c <= 'z'; c++) {
                    if(c == old) continue;

                    nxt[i] = c;

                    if(nxt == endWord) {
                        return step + 1;
                    }

                    if(dict.count(nxt) && !vis.count(nxt)) {
                        vis.insert(nxt);
                        q.push({nxt, step + 1});
                    }
                }

                nxt[i] = old;
            }
        }

        return 0;
    }
};


 ```

 **这道题可以用双向BFS进行优化**
 ```cpp
 //起点和终点同时往中间找
 class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> dict(wordList.begin(), wordList.end());

        if (!dict.count(endWord)) return 0;

        unordered_set<string> beginSet;
        unordered_set<string> endSet;

        beginSet.insert(beginWord);
        endSet.insert(endWord);

        int step = 1;

        while (!beginSet.empty() && !endSet.empty()) {
            // 每次从数量更少的一边扩展，减少搜索量
            if (beginSet.size() > endSet.size()) {
                swap(beginSet, endSet);
            }
            //记录下一层的单词
            unordered_set<string> nextSet;

            for (string word : beginSet) {
                string cur = word;

                for (int i = 0; i < cur.size(); i++) {
                    char old = cur[i];

                    for (char c = 'a'; c <= 'z'; c++) {
                        if (c == old) continue;

                        cur[i] = c;

                        // 两边相遇，说明找到最短路径
                        //双向BFS的灵魂，如果当前生成的新单词，已经在另一边的当前层里，说明两边接上了
                        if (endSet.count(cur)) {
                            return step + 1;
                        }

                        if (dict.count(cur)) {
                            nextSet.insert(cur);
                            dict.erase(cur); // 防止重复访问
                        }
                    }

                    cur[i] = old;
                }
            }

            beginSet = nextSet;
            step++;
        }

        return 0;
    }
};
```


# 双向 BFS 为什么需要两个 visited？

在普通 BFS 中：

```cpp
queue<string> q;
unordered_set<string> visited;
```

只从一个起点开始搜索，因此一个 `visited` 就够了。

---

但在双向 BFS 中：

```cpp
q1 从 "0000" 开始搜索
q2 从 target 开始搜索
```

是两边同时进行搜索的。

因此需要：

```cpp
vis1：记录从起点方向访问过的状态
vis2：记录从终点方向访问过的状态
```

class Solution {
public:
    int openLock(vector<string>& deadends, string target) {
        unordered_set<string> dead(deadends.begin(), deadends.end());

        if(dead.count("0000")) return -1;
        if(dead.count(target)) return -1;
        if(target == "0000") return 0;

        unordered_set<string> q1, q2;
        unordered_set<string> vis1, vis2;

        q1.insert("0000");
        q2.insert(target);

        vis1.insert("0000");
        vis2.insert(target);

        int step = 0;

        while(!q1.empty() && !q2.empty()) {
            if(q1.size() > q2.size()) {
                swap(q1, q2);
                swap(vis1, vis2);
            }

            unordered_set<string> temp;
            step++;

            for(string cur : q1) {
                for(int i = 0; i < 4; i++) {
                    string up = cur;
                    string down = cur;

                    up[i] = (cur[i] - '0' + 1) % 10 + '0';
                    down[i] = (cur[i] - '0' + 9) % 10 + '0';

                    if(!dead.count(up)) {
                        if(vis2.count(up)) return step;
                        if(!vis1.count(up)) {
                            vis1.insert(up);
                            temp.insert(up);
                        }
                    }

                    if(!dead.count(down)) {
                        if(vis2.count(down)) return step;
                        if(!vis1.count(down)) {
                            vis1.insert(down);
                            temp.insert(down);
                        }
                    }
                }
            }

            q1 = temp;
        }

        return -1;
    }
};


```cpp


```
---

# 两个 visited 的作用

## 1. 防止当前方向重复搜索

例如：

```cpp
if(!vis1.count(up)) {
    vis1.insert(up);
    temp.insert(up);
}
```

表示：

- 如果 `up` 没被当前方向访问过
- 才加入下一层搜索

否则会出现重复搜索甚至死循环。

---

## 2. 判断两边是否相遇

例如：

```cpp
if(vis2.count(up)) return step;
```

表示：

当前从 `q1` 扩展出来的新状态 `up`：

- 已经被另一边搜索到过
- 说明两边已经连通
- 可以直接返回答案

---

# 为什么不能只用一个 visited？

因为：

```cpp
visited.count(next)
```

只能说明：

> “这个状态以前被访问过”

但无法知道：

- 是自己这边访问过的
- 还是对面访问过的

---

# 举例说明

假设：

```text
0000 -> 0001 -> 0000
```

如果只用一个 `visited`：

```cpp
if(visited.count(next)) return step;
```

当再次遇到 `0000` 时：

- 它确实在 visited 中
- 但只是自己绕回来了
- 并不代表和 target 那边相遇

这样就会错误返回。

---

# 双向 BFS 的正确逻辑

```cpp
vis1：起点方向访问过的状态
vis2：终点方向访问过的状态
```

只有：

```cpp
if(vis2.count(next))
```

才说明：

```text
起点方向 -> next <- 终点方向
```

两边真正连接成功。

---

# 本质理解

双向 BFS 的核心：

```text
不是判断“是否访问过”

而是判断：

“这个点是不是被另一边访问过”
```

因此必须区分：

- 哪些状态属于起点方向
- 哪些状态属于终点方向

---

# 另一种写法

也可以只用一个哈希表：

```cpp
unordered_map<string,int> vis;
```

例如：

```cpp
vis[state] = 1; // 起点方向
vis[state] = 2; // 终点方向
```

本质上仍然是在区分：

```text
这个状态是被哪一边访问的
```

因此：

> 双向 BFS 不一定非要两个 visited，
> 但一定要区分访问来源。

