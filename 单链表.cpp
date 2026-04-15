#include<iostream>
using namespace std;

// 带头节点的单链表
class Clink
{
	// 链表节点
	struct Node
	{
		int data;      // 数据域
		Node* next;    // 指针域，指向下一个节点

		Node(int data = 0) : data(data), next(nullptr) {}
	};

public:
	// 构造函数：创建头节点 (引导节点，不存数据)
	// 时间复杂度：O(1)
	Clink()
	{
		head = new Node();
	}

	// 析构函数：遍历释放所有节点，防止内存泄漏
	// 时间复杂度：O(n)，n为节点个数
	~Clink()
	{
		Node* p = head;
		while (p != nullptr)
		{
			head = p->next;  // 保存下一个节点地址
			delete p;        // 释放当前节点
			p = head;        // 继续处理下一个
		}
		head = nullptr;      // 置空，防止野指针
	}

public:
	// 头插法：在链表头部添加元素
	// 时间复杂度：O(1)，常数时间
	void InsertHead(int val)
	{
		Node* node = new Node(val);
		// 新节点指向原来的第一个节点
		node->next = head->next;
		// 头节点指向新节点
		head->next = node;
	}

	// 尾插法：在链表末尾添加元素
	// 时间复杂度：O(n)，需要遍历到末尾
	// 优化方案：维护尾指针成员，可实现O(1)
	void InsertTail(int val)
	{
		Node* p = head;
		// 遍历找到尾节点（p->next == nullptr）
		while (p->next != nullptr)
		{
			p = p->next;
		}
		// 创建新节点，接在末尾
		Node* node = new Node(val);
		p->next = node;
	}

	// 删除第一个值为val的节点
	// 时间复杂度：O(n)，需要遍历查找
	void Remove(int val)
	{
		Node* q = head;        // 前驱指针，初始指向头节点
		Node* p = head->next;  // 当前指针，初始指向第一个有效节点

		while (p != nullptr)
		{
			if (p->data == val)
			{
				// 找到目标，删除并返回
				q->next = p->next;  // 前驱绕过当前节点
				delete p;            // 释放内存
				return;              // 只删除第一个
			}
			// 双指针后移
			q = p;
			p = p->next;
		}
	}

	// 删除所有值为val的节点
	// 时间复杂度：O(n)，一次遍历完成，不重复扫描
	void RemoveAll(int val)
	{
		Node* p = head->next;  // 当前指针
		Node* q = head;        // 前驱指针

		while (p != nullptr)
		{
			if (p->data == val)
			{
				// 删除当前节点，q不动，p后移
				q->next = p->next;
				delete p;
				p = q->next;
			}
			else
			{
				// 不删除，双指针同步后移
				q = p;
				p = p->next;
			}
		}
	}

	// 查找元素：返回是否存在
	// 时间复杂度：O(n)，顺序查找
	bool Find(int val)
	{
		Node* p = head->next;
		while (p != nullptr)
		{
			if (p->data == val)
				return true;
			p = p->next;
		}
		return false;
	}

	// 打印链表：输出所有有效元素
	// 时间复杂度：O(n)
	void Show()
	{
		Node* p = head->next;  // 跳过头节点
		while (p != nullptr)
		{
			cout << p->data << ' ';
			p = p->next;
		}
		cout << endl;
	}

private:
	Node* head;  // 指向头节点
};

int main()
{
	Clink list;

	cout << "头插10,20,30：" << endl;
	list.InsertHead(30);
	list.InsertHead(20);
	list.InsertHead(10);
	list.Show();

	cout << "尾插40,50：" << endl;
	list.InsertTail(40);
	list.InsertTail(50);
	list.Show();

	cout << "删除20：" << endl;
	list.Remove(20);
	list.Show();

	if (list.Find(40))
		cout << "找到40" << endl;
	else
		cout << "未找到40" << endl;

	return 0;
}