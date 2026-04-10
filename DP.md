# P2834 纸币问题 3 vs P2840 纸币问题 2

这两道题虽然看起来很像，但本质上解决的是两个完全不同的问题：

- **P2840 纸币问题 2**：求的是**排列数**（顺序不同算不同方案）
- **P2834 纸币问题 3**：求的是**组合数**（顺序不同算同一种方案）

---

## 1. 核心区别：顺序是否重要

| 对比项 | P2840 纸币问题 2 | P2834 纸币问题 3 |
| :--- | :--- | :--- |
| **问题描述** | 支付金额 `w` 的**方式**有多少种？ | 支付金额 `w` 的**组合**有多少种？ |
| **关键条件** | **顺序不同**被视为不同的方式 | **顺序不同**被视为同一种方式 |
| **本质** | **排列问题** | **组合问题** |
| **例子 (w=3, 纸币{1,2})** | 1+1+1, 1+2, 2+1 → **3 种** | 1+1+1, 1+2 → **2 种** |

---

## 2. 解法区别：循环顺序

正是“顺序是否重要”这个本质区别，导致了两道题的代码写法完全不同。

### P2834 纸币问题 3 (组合数) – 先纸币，后金额

这种循环顺序确保了每种纸币组合只被计算一次，不会产生 `1+2` 和 `2+1` 这种因顺序不同而重复的方案。

```cpp
// P2834 核心代码
for (int i = 1; i <= n; i++) {          // 外层循环：遍历每种纸币
    for (int j = a[i]; j <= w; j++) {   // 内层循环：遍历金额
        dp[j] = (dp[j] + dp[j - a[i]]) % MOD;
    }
}
```
3. 完整代码对比
P2834 纸币问题 3（组合数）
```cpp
#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

int main() {
    int n, w;
    cin >> n >> w;
    
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    
    vector<long long> dp(w + 1, 0);
    dp[0] = 1;
    
    // 组合数：先物品（纸币），后容量（金额）
    for (int i = 1; i <= n; i++) {
        for (int j = a[i]; j <= w; j++) {
            dp[j] = (dp[j] + dp[j - a[i]]) % MOD;
        }
    }
    
    cout << dp[w] << endl;
    return 0;
}
```
P2840 纸币问题 2（排列数）
```cpp
#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

int main() {
    int n, w;
    cin >> n >> w;
    
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    vector<long long> dp(w + 1, 0);
    dp[0] = 1;
    
    // 排列数：先容量（金额），后物品（纸币）
    for (int j = 1; j <= w; j++) {
        for (int i = 0; i < n; i++) {
            if (j >= a[i]) {
                dp[j] = (dp[j] + dp[j - a[i]]) % MOD;
            }
        }
    }
    
    cout << dp[w] << endl;
    return 0;
}
```

# 记忆化搜索vs动态规划
# 动态规划与记忆化搜索完全笔记

## 一、基本概念

### 1.1 什么是动态规划 (Dynamic Programming, DP)

动态规划是一种通过将原问题分解为**相互重叠的子问题**，并通过**自底向上**的方式求解的算法思想。它通常用于求解**最优化问题**（最大值、最小值、计数等）。

**核心特征：**
- 存在**重叠子问题**（不是分治法的独立子问题）
- 满足**最优子结构**（大问题的最优解包含小问题的最优解）
- 需要**状态转移方程**（如何从子问题推导出原问题）

### 1.2 什么是记忆化搜索 (Memoization Search)

记忆化搜索是一种**递归 + 缓存**的技术。它仍然采用递归的“自顶向下”思考方式，但会将计算过的子问题结果存储起来，避免重复计算。

**核心特征：**
- 递归实现，思维更直观
- 使用备忘录（数组/哈希表）记录已计算结果
- 每次递归前先查表，已计算则直接返回

---

## 二、核心区别对比表

| 维度 | 动态规划 (DP) | 记忆化搜索 |
| :--- | :--- | :--- |
| **计算顺序** | 自底向上 (Bottom-Up) | 自顶向下 (Top-Down) |
| **实现方式** | 循环 (for/while) | 递归 + 备忘录 |
| **思维难度** | 需要想清楚循环顺序 | 只需要会拆分子问题 |
| **代码长度** | 通常较短 | 稍长（需要递归函数） |
| **效率** | 略高（无函数调用开销） | 略低（有递归开销） |
| **空间优化** | 容易（滚动数组） | 困难 |
| **栈溢出风险** | 无 | 有（递归深度过大时） |
| **适用场景** | 状态依赖关系清晰、有明确计算顺序 | 状态依赖关系复杂、顺序难确定 |

---

## 三、优缺点分析

### 3.1 动态规划

**优点：**
- 效率高，无函数调用开销
- 可以轻松进行空间优化（如用两个变量代替整个DP数组）
- 无递归栈溢出风险
- 代码简洁，适合面试和竞赛

**缺点：**
- 状态转移方程和循环顺序有时难以确定
- 需要显式处理所有边界条件
- 对“无序依赖”的问题（如滑雪）不友好

### 3.2 记忆化搜索

**优点：**
- 思维直观，符合人的自然思考方式（递归思维）
- 不需要考虑计算顺序，递归自动处理依赖
- 代码容易编写和调试
- 非常适合处理**有向无环图 (DAG)** 上的问题

**缺点：**
- 递归函数调用有额外开销
- 深度过大时可能导致栈溢出（如Python默认递归深度1000）
- 难以进行空间优化
- 对某些语言（如Python）效率较低

---

## 四、代码模板对比

### 4.1 动态规划模板（以斐波那契数列为例）

```cpp
// 自底向上
int fib(int n) {
    if (n <= 1) return n;
    vector<int> dp(n + 1);
    dp[0] = 0;
    dp[1] = 1;
    for (int i = 2; i <= n; i++) {
        dp[i] = dp[i-1] + dp[i-2];
    }
    return dp[n];
}

// 空间优化版本
int fib(int n) {
    if (n <= 1) return n;
    int prev2 = 0, prev1 = 1, cur;
    for (int i = 2; i <= n; i++) {
        cur = prev1 + prev2;
        prev2 = prev1;
        prev1 = cur;
    }
    return cur;
}
```

# 滑雪 vs 挖地雷：两道经典DP/记忆化搜索题目对比分析

## 一、题目基本信息对比

| 维度 | 挖地雷 (P2196) | 滑雪 (P1434) |
| :--- | :--- | :--- |
| 来源 | NOIP 1996 提高组 | SHOI 2002 |
| 核心标签 | 线性DP、有向图、路径记录 | 记忆化搜索、网格DP、DFS |
| 数据范围 | N ≤ 20 | R, C ≤ 100 |
| 搜索方向 | 只能从小编号走向大编号（有向） | 上下左右，但只能从高到低 |
| 状态定义 | `dp[i]` 表示从 i 出发的最大雷数 | `memo[x][y]` 表示从 (x,y) 出发的最长长度 |
| 计算顺序 | 固定（从 n 到 1 循环） | 不固定（靠递归自动处理） |
| 是否需要DFS | ❌ 不需要，循环即可 | ✅ 需要，因为要探索四个方向 |
| 路径记录 | ✅ 需要输出具体路径 | ❌ 只需要输出长度 |

---

## 二、核心知识点详解

### 2.1 挖地雷（线性DP）

#### 状态定义
dp[i] = 从地窖 i 出发，能挖到的最大地雷数

text

#### 状态转移方程
dp[i] = mine[i] + max(dp[j])
其中 j 满足：j > i 且 i 到 j 有路径（connect[i][j] == 1）

text

#### 关键理解点

1. **为什么从后往前计算？**
   - 因为只能从小编号走向大编号
   - `dp[i]` 依赖所有 `dp[j]`（j > i）
   - 所以先计算大的 i，再计算小的 i

2. **路径如何记录？**
   - 用 `nextCave[i]` 记录从 i 出发的最优路径中，下一个地窖是谁
   - 当找到 `bestNext` 时，`nextCave[i] = bestNext`
   - 最后从 start 开始，沿着 nextCave 一路输出

3. **字典序最小如何处理？**
   - 当 `dp[j] == dp[bestNext]` 时，不更新 bestNext
   - 由于 j 是从小到大遍历的，这样自然保留了更小的编号

#### 答题步骤
步骤1：读入 n，地雷数组 mine[1..n]
步骤2：读入上三角矩阵，存入 connect[i][j]
步骤3：初始化 dp[i] = mine[i]，nextCave[i] = 0
步骤4：for i = n down to 1:
bestNext = 0
for j = i+1 to n:
if connect[i][j] and dp[j] > dp[bestNext]:
bestNext = j
if bestNext != 0:
dp[i] = dp[bestNext] + mine[i]
nextCave[i] = bestNext
步骤5：找到 start，使得 dp[start] 最大
步骤6：从 start 开始，沿 nextCave 输出路径
步骤7：输出 dp[start]

text

---

### 2.2 滑雪（记忆化搜索）

#### 状态定义
memo[x][y] = 从点 (x, y) 出发，能滑的最长长度

text

#### 状态转移方程
memo[x][y] = 1 + max(memo[nx][ny])
其中 (nx, ny) 满足：

在边界内

h[nx][ny] < h[x][y]（只能往低处滑）

text

#### 关键理解点

1. **为什么必须用搜索？**
   - 高度是随机分布的，没有固定顺序
   - 一个点可能依赖上下左右四个方向中比它低的点
   - 无法用简单的循环确定计算顺序

2. **记忆化解决了什么问题？**
   - 纯DFS会重复计算同一个点无数次
   - 用 memo 数组记录每个点的结果，下次直接返回
   - 时间复杂度从指数级降为 O(R × C)

3. **递归边界在哪里？**
   - 当四个方向都不能滑时，res 保持为 1，直接返回
   - 不需要显式写边界条件

#### 答题步骤
步骤1：读入 R, C 和高度矩阵 h[1..R][1..C]
步骤2：初始化 memo 数组为 0（0 表示未计算）
步骤3：定义 dfs(x, y) 函数：
if memo[x][y] != 0: return memo[x][y]
res = 1
for 四个方向:
计算 nx, ny
if 边界内 and h[nx][ny] < h[x][y]:
res = max(res, dfs(nx, ny) + 1)
memo[x][y] = res
return res
步骤4：遍历所有点，调用 dfs(i, j)，更新 ans = max(ans, dfs(i, j))
步骤5：输出 ans

text

---

## 三、代码实现对比

### 3.1 挖地雷（完整代码）

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> mine(n + 1);
    vector<vector<int>> connect(n + 1, vector<int>(n + 1, 0));
    vector<int> dp(n + 1);
    vector<int> nextCave(n + 1);
    
    for (int i = 1; i <= n; i++) cin >> mine[i];
    
    // 读入上三角矩阵
    for (int i = 1; i <= n - 1; i++) {
        for (int j = i + 1; j <= n; j++) {
            cin >> connect[i][j];
        }
    }
    
    // 初始化
    for (int i = 1; i <= n; i++) {
        dp[i] = mine[i];
        nextCave[i] = 0;
    }
    
    // 从后往前DP
    for (int i = n; i >= 1; i--) {
        int bestNext = 0;
        for (int j = i + 1; j <= n; j++) {
            if (connect[i][j] && dp[j] > dp[bestNext]) {
                bestNext = j;
            }
        }
        if (bestNext != 0) {
            dp[i] = dp[bestNext] + mine[i];
            nextCave[i] = bestNext;
        }
    }
    
    // 找最优起点
    int start = 1;
    for (int i = 2; i <= n; i++) {
        if (dp[i] > dp[start]) start = i;
    }
    
    // 输出路径
    int cur = start;
    while (cur != 0) {
        cout << cur << " ";
        cur = nextCave[cur];
    }
    cout << endl << dp[start] << endl;
    
    return 0;
}
```
3.2 滑雪（完整代码）
```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 110;
int h[N][N], memo[N][N];
int R, C;
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

int dfs(int x, int y) {
    if (memo[x][y] != 0) return memo[x][y];
    
    int res = 1;
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx >= 1 && nx <= R && ny >= 1 && ny <= C && h[nx][ny] < h[x][y]) {
            res = max(res, dfs(nx, ny) + 1);
        }
    }
    memo[x][y] = res;
    return res;
}

int main() {
    cin >> R >> C;
    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
            cin >> h[i][j];
        }
    }
    
    int ans = 0;
    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
            ans = max(ans, dfs(i, j));
        }
    }
    cout << ans << endl;
    
    return 0;
}
```