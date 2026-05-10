# N皇后问题----DFS回溯
```cpp
class Solution {
public:
    vector<vector<string>> ans;
    vector<string> board;
    vector<bool> col;
    vector<bool> diag1;
    vector<bool> diag2;

    vector<vector<string>> solveNQueens(int n) {
        board = vector<string>(n, string(n, '.'));
        col = vector<bool>(n, false);
        diag1 = vector<bool>(2 * n, false);
        diag2 = vector<bool>(2 * n, false);

        dfs(0, n);

        return ans;
    }

    void dfs(int row, int n) {
        if(row == n) {
            ans.push_back(board);
            return;
        }

        for(int c = 0; c < n; c++) {
            if(col[c]) continue;
            if(diag1[row - c + n]) continue;
            if(diag2[row + c]) continue;

            board[row][c] = 'Q';
            col[c] = true;
            diag1[row - c + n] = true;
            diag2[row + c] = true;

            dfs(row + 1, n);

            board[row][c] = '.';
            col[c] = false;
            diag1[row - c + n] = false;
            diag2[row + c] = false;
        }
    }
};
```

## N 皇后中的对角线判断

在 N 皇后问题中，需要保证：

```text
任意两个皇后不能：
1. 同行
2. 同列
3. 同对角线
```

由于我们采用：

```text
一行只放一个皇后
```

所以：

```text
“同行”天然不会发生
```

只需要判断：

```text
1. 同列
2. 两种对角线
```

---

### 两种对角线

棋盘中的对角线分为：

```text
↘ 主对角线
↙ 副对角线
```

---

# 一、主对角线（↘）

例如：

```text
(0,0)
(1,1)
(2,2)
(3,3)
```

它们有一个共同特点：

```text
row - col 相同
```

验证：

```text
0 - 0 = 0
1 - 1 = 0
2 - 2 = 0
3 - 3 = 0
```

再看另一条：

```text
(0,1)
(1,2)
(2,3)
```

验证：

```text
0 - 1 = -1
1 - 2 = -1
2 - 3 = -1
```

因此：

```text
row - col 相同
⇒ 在同一条 ↘ 主对角线
```

---

## 代码表示

```cpp
diag1[row - col + n]
```

---

## 为什么要 +n ?

因为：

```text
row - col 可能是负数
```

例如：

```text
0 - 3 = -3
```

数组下标不能为负数，所以：

```cpp
row - col + n
```

把它整体平移到正数范围。

---

# 二、副对角线（↙）

例如：

```text
(0,3)
(1,2)
(2,1)
(3,0)
```

它们的特点：

```text
row + col 相同
```

验证：

```text
0 + 3 = 3
1 + 2 = 3
2 + 1 = 3
3 + 0 = 3
```

再看另一条：

```text
(0,1)
(1,0)
```

验证：

```text
0 + 1 = 1
1 + 0 = 1
```

因此：

```text
row + col 相同
⇒ 在同一条 ↙ 副对角线
```

---

## 代码表示

```cpp
diag2[row + col]
```

由于：

```text
row + col 不会为负数
```

所以不用额外处理。

---

## 三、N 皇后中的使用方式

## 定义数组

```cpp
vector<bool> col(n, false);    //表示第c列是否有皇后
vector<bool> diag1(2 * n, false);//表示主对角线是否有皇后
vector<bool> diag2(2 * n, false);//表示副对角线是否有皇后
```



---

# 四、放置皇后

假设在：

```text
(row, col)
```

放置一个皇后：

```cpp
board[row][col] = 'Q';

col[col] = true;
diag1[row - col + n] = true;
diag2[row + col] = true;
```

表示：

```text
这一列被占用
这两条对角线被占用
```

---

# 五、撤销皇后（回溯）

```cpp
board[row][col] = '.';

col[col] = false;
diag1[row - col + n] = false;
diag2[row + col] = false;
```

作用：

```text
恢复现场
尝试下一种放法
```

---

# 六、判断当前位置是否合法

```cpp
if(col[c]) continue;

if(diag1[row - c + n]) continue;

if(diag2[row + c]) continue;
```

意思：

```text
如果这一列已经有皇后
或者任意一条对角线已有皇后
则当前位置不能放
```

---



# 八、为什么这样能快速判断？

原本判断对角线冲突需要：

```text
遍历整个棋盘
```

复杂度较高。

使用数组后：

```cpp
O(1)
```

即可判断某条对角线是否已经有皇后。

这是 N 皇后中的经典剪枝优化。


# 回溯算法（Backtracking）

回溯本质上是一种：

```text
暴力搜索 + 撤销选择
```

的算法思想。

---

# 一、回溯是什么？

回溯可以理解成：

```text
试一种方案，如果不行，撤回来，换下一种方案
```

例如：

```text
走迷宫
下棋
全排列
N 皇后
数独
组合问题
```

本质都是：

```text
枚举所有可能
```

---

# 二、回溯的核心思想

回溯的过程：

```text
做选择
↓
进入下一层搜索
↓
撤销选择
↓
尝试别的选择
```

也叫：

```text
恢复现场
```

---

# 三、经典模板

```cpp
void dfs(当前状态) {

    if(满足结束条件) {
        保存答案;
        return;
    }

    for(所有可能的选择) {

        if(当前选择不合法)
            continue;

        做选择;

        dfs(下一层);

        撤销选择;
    }
}
```

---

# 四、最重要的部分：撤销选择

例如：

```cpp
path.push_back(x);

dfs(...);

path.pop_back();
```

含义：

```text
先把 x 选进来
递归搜索
搜索结束后再删掉 x
恢复成原来的状态
```

这就是：

```text
回溯
```

---

# 五、为什么需要回溯？

因为：

```text
一个位置可能有很多种选择
```

例如：

```text
第1个数选1
第1个数选2
第1个数选3
```

搜索完：

```text
选1 的所有情况
```

之后：

```text
必须撤销 1
才能继续尝试 2
```

---

# 六、回溯与 DFS 的关系

回溯本质上是：

```text
DFS（深度优先搜索）
```

的一种应用。

区别：

---

## 普通 DFS

重点：

```text
遍历
```

例如：

```text
图遍历
树遍历
连通块
```

---

## 回溯 DFS

重点：

```text
枚举所有可能方案
```

例如：

```text
全排列
组合
N 皇后
数独
```

---

# 七、回溯的搜索树

例如：

```text
从 1 2 3 中选数
```

搜索过程：

```text
                 []
            /     |     \
          [1]    [2]    [3]
         /  \    / \    / \
      [1,2] ...
```

回溯本质：

```text
枚举整棵搜索树
```

---

# 八、N 皇后中的回溯

## 放皇后

```cpp
board[row][col] = 'Q';
```

表示：

```text
当前决定：
在这个位置放皇后
```

---

## 继续搜索

```cpp
dfs(row + 1);
```

表示：

```text
继续放下一行
```

---

## 撤销皇后

```cpp
board[row][col] = '.';
```

表示：

```text
尝试失败
恢复现场
换下一个位置
```

---

# 九、经典例子：全排列

```cpp
vector<int> path;
vector<bool> used;

void dfs() {

    if(path.size() == n) {
        ans.push_back(path);
        return;
    }

    for(int i = 0; i < n; i++) {

        if(used[i]) continue;

        path.push_back(nums[i]);
        used[i] = true;

        dfs();

        path.pop_back();
        used[i] = false;
    }
}
```

---

# 十、回溯中的“剪枝”

剪枝：

```text
提前停止不可能成功的搜索
```

例如：

```cpp
if(当前位置冲突)
    continue;
```

作用：

```text
减少搜索数量
加快速度
```

---


## 回溯本质：

```text
DFS 枚举所有可能方案
```

---

## 回溯的灵魂：

```text
恢复现场
```

---

