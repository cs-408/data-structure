#include<iostream>
using namespace std;

// 链栈：链表实现，头插法
class LStack
{
	// 节点结构
	struct Node
	{
		int data;
		Node* next;
		Node(int x = 0) : data(x), next(nullptr) {}
	};

public:
	// 构造函数：创建头节点
	// 时间复杂度：O(1)
	LStack()
	{
		head = new Node();
	}

	// 析构函数：释放所有节点
	// 时间复杂度：O(n)，n为节点个数
	~LStack()
	{
		while (head != nullptr)
		{
			Node* p = head;
			head = head->next;
			delete p;
		}
	}

public:
	// 入栈：头插法，新节点放在第一个
	// 时间复杂度：O(1)
	void push(int val)
	{
		Node* p = new Node(val);
		p->next = head->next;  // 新节点指向原来的栈顶
		head->next = p;        // 头节点指向新节点（新栈顶）
	}

	// 出栈：删除第一个节点
	// 时间复杂度：O(1)
	void pop()
	{
		if (head->next == nullptr)  // 栈空
		{
			throw "stack is empty!";
		}
		Node* p = head->next;   // 保存栈顶
		head->next = p->next;  // 头节点绕过栈顶
		delete p;               // 释放原栈顶
	}

	// 获取栈顶元素（不出栈）
	// 时间复杂度：O(1)
	int GetTop() const
	{
		if (head->next == nullptr)
		{
			throw "stack is empty!";
		}
		return head->next->data;
	}

	// 判空：栈是否为空
	// 时间复杂度：O(1)
	bool empty() const
	{
		return head->next == nullptr;
	}

	// 获取元素个数
	// 时间复杂度：O(n)，遍历计数
	// 优化：维护num成员可实现O(1)
	int size() const
	{
		int n = 0;
		Node* p = head->next;
		while (p != nullptr)
		{
			n++;
			p = p->next;
		}
		return n;
	}

private:
	Node* head;  // 指向头节点
};

int main()
{
	LStack s;

	s.push(10);
	s.push(20);
	s.push(30);
	cout << "栈大小：" << s.size() << endl;
	cout << "栈顶：" << s.GetTop() << endl;

	s.pop();
	cout << "出栈后栈顶：" << s.GetTop() << endl;

	while (!s.empty())
	{
		cout << s.GetTop() << " ";
		s.pop();
	}
	cout << endl;

	return 0;
}
