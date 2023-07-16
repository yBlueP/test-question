# Oppo 计算机视觉算法笔试

## 1. 模拟
把一个字符串的给定范围的出现最多次的字母大小写反转，如果次数一样则都反转。

```
input:
abAb
1 4
2 3
1 3
output:
aBAB
abaB
AbAB
```

思路：
1. 需要找到范围内字母最大的次数。这个通过hashmap就可以找到最大的。
2. 找到最大次数后，要找到这个次数对应哪些字母，放在set里面方便快速查询。
3. 在该范围内遍历，查看字母是不是在set内，在就反转。


## 2. 还原排列
一个1到n组成的排列，只知道前k的数的和的奇偶性，求这个排列，只需要输出一个，不可能则输入-1。0代表前面的和为偶数 ，1为奇数。

```
input:
3
0 1 0
output:
2 1 3
```

思路：
这个题只和奇偶有关，和具体数字多少无关。

## 3. 求期望
a1 a2 a3... an 随机挑一个数的概率是 ak / sum. 小红随机挑一个数把这个数和它的后缀都删掉。小红进行多次操作，求把数组都删掉的数学期望是？
```
input:
2 
1 3
output:
1.75
```

删3，概率0.75 * 2， 要删两次才删完
删1，概率0.25 * 1，一次就删完
数学期望 0.75*2 + 0.25 * 1 = 1.75

思路：
假设dp[n]代表完全删除n个数所需要的期望次数, p[n]代表拿第n个求对应的概率。那么：dp[0] = 0, dp[1] = 1， dp[2] = p[2] * (1 + dp[1]) + p[1] * (1 + dp[0])。也就是如果取第二个数，那么删掉所有数需要两步，先取第二个数，期望是1 * p[2] 次，在取第一个数，期望是 dp[1] * p[1]；另外也可以直接取第一个数，那么就直接一步就可以了，次数为 p[1] * 1。
所以状态转移方程为： dp[k] = p[k] * (1 + dp[k-1]) + p[k-1] * (1 + dp[k-2]) + ... + p[1] * (1 + dp[0])

```c++
#include <bits/stdc++.h>
using namespace std;

int main(int, char**){

    ifstream inf("../data.txt");
    
    int n;
    inf >> n;

    vector<int> data(n);
    vector<int> preSum(1 + n);  // preSum[k] 为第k个数的和为
    // 读取数据并获取前缀和
    for(int i=0; i<n; i++){
        inf >> data[i];
        if(i == 0){
            preSum[i+1] = data[i];
        }else{
            preSum[i+1] = preSum[i] + data[i];
        }
    }

    vector<float> dp(1 + n, 0.0f);
    dp[1] = 1.0f;

    for(int i=2; i<=n; i++){
        int sum = preSum[i];
        for(int j=i-1; j>=0; j--){
            dp[i] += (1.0f + dp[j]) * data[j] / sum;
        }
    }

    cout << dp.back() << endl;

    return 0;
}

```