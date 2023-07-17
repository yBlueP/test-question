# Notes



## 二面

数组和链表的区别？

* **逻辑上都是连续（线性）； 物理空间上：数组是连续的，链表是不连续的。**
* **增删改查效率**：
  * **数组适合查找和修改**，随机访问（基址 + 偏移），访问快速，缓存的空间局部性比较好，$O(1)$ ，**除了在尾部进行增删高效，**其他时间都需要挪移元素
  * **链表适合增删**，只需要处理一个节点即可，增删改查都是 $O(N)$ ， 但是它需要访问前一个元素才能找到下一个元素
* **大小：**
  * 数组创建时，大小需要确定（而且是在**编译时期就需要确定**）
  * **链表大小动态改变**
* **空间消耗**：
  * 数组空间利用率不高，可能浪费内存
  * **链表需要额外的指针域，因此需要额外的内存开销**，但是内存利用率高
* 内存来源：
  * 数组内存一般来源于堆内存和栈内存
  * 链表内存一般来源于堆内存





数据结构设计题：存在两个队伍 A 和 队伍 B，需要挑选一部分人从队伍 A 到 B。 选取队伍 A 的第十个人，如果是男生，选择第十二个同学从队伍 A 取出，放入队伍 B 中； 如果是女生，选择第八个同学从队伍 A 取出，放入队伍 B 中，直到选择十个为止。两个队伍需要选择什么样的数据结构？（3 min 思考时间）

面试官给出的结果：队伍 A （双向链表），队伍 B（数组）

**分析的关键（队伍需要的操作）：队伍 A 需要定位元素以及删除中间元素，队伍 B 只需要尾插即可。**

**在这里面，不仅考察数据结构，还需要积极与面试官沟通。**    1. 沟通问题描述（问题大意复述，不清楚的点）   2. 沟通问题细节（有无特殊要求，数据量大小）





10 分钟：非递归翻转单链表 + 编写测试用例

```c++
#include <iostream>
using namespace std;

struct Node {
	Node(int val = 0) : val(val), next(nullptr) {} // 构造函数
	int val;
	Node* next;
};

Node *reverseList(Node* head) {
	Node *pre = nullptr, *cur = head;
	while (cur) {
		Node* nxt = cur->next;
		cur->next = pre;
		pre = cur;
		cur = nxt;
	}
	return pre;
}

int main() {
    // 1 ~ n 个节点
	Node* head = new Node(0);
	Node* pre = head;
    // i <= 0 时, 表示创建 1 个节点的链表
	for (int i = 1; i <= 5; ++i) {
		pre->next = new Node(i);
		pre = pre->next;
	}
	
    // 输出原链表
	Node* cur = head;
	while (cur) {
		cout << cur->val << " ";
		cur = cur->next;
	}
	cout << endl;

	Node* new_head = reverseList(head);
	cur = new_head;
	while (cur) {
		cout << cur->val << " ";
		cur = cur->next;
	}
	cout << endl;
	
    
    // 测试空链表
	Node* test_null = nullptr;
	Node* new_test_null = reverseList(test_null);
	cur = new_test_null;
	while (cur) {
		cout << cur->val << " ";
		cur = cur->next;
	}
	cout << endl;

	return 0;
}
```



口述思路：https://leetcode.cn/problems/house-robber-ii/ 打家劫舍问题 （3 min）

由于之前做过，思路明白，但是不太好描述。 （自己还故意说一个 DFS 算法，结果描述的很烂）其实可以把核心代码写出来进行描述。

后来面试官知道到我大概做过这个问题，就过了。





反问

1. 语言 + 技术栈：不确定，一个月培训语言 + 几个月的组内培训（课题培训） 
2. 对个人建议：**表述能力不够清晰（语言组织条理性，逻辑的条理性）**，链表反转做的还行（链表构造，测试用例全面性（0 节点， 1 节点），bug - free ，构造函数），代码能力过关 ， 考察数据结构选型，考察编程熟练度。
