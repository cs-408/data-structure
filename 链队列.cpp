#include<iostream>
using namespace std;

// 链队列：链表实现，头删尾插
class ListQueue
{
	struct Node
	{
		int data;
		Node* next;
		Node(int x = 0) : data(x), next(nullptr) {}
	};

public:
	// 构造函数：创建头节点，头尾指针指向头节点
	// 时间复杂度：O(1)
	ListQueue()
	{
		head = tail = new Node();
	}

	// 析构函数：遍历释放所有节点
	// 时间复杂度：O(n)
	~ListQueue()
	{
		while (head != nullptr)
		{
			Node* p = head;
			head = head->next;
			delete p;
		}
		head = tail = nullptr;
	}

public:
	// 入队：尾插法，在队列尾部添加元素
	// 时间复杂度：O(1)
	void enqueue(int val)
	{
		Node* p = new Node(val);
		tail->next = p;
		tail = p;
	}

	// 出队：头删法，删除队列头部元素
	// 时间复杂度：O(1)
	void dequeue()
	{
		if (head == tail)
		{
			throw "queue is empty!";
		}
		Node* p = head->next;
		head->next = p->next;
		if (head->next == nullptr)
		{
			tail = head;
		}
		delete p;
	}

	// 获取队头元素（不出队）
	// 时间复杂度：O(1)
	int getFront() const
	{
		if (head == tail)
		{
			throw "queue is empty!";
		}
		return head->next->data;
	}

	// 判空
	// 时间复杂度：O(1)
	bool empty() const
	{
		return head == tail;
	}

	// 获取元素个数
	// 时间复杂度：O(n)
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
	Node* head;//指向头节点（不存数据）
	Node* tail;//指向尾节点（最后一个有效节点），使入队时间复杂度为O(1),没有则会涨到O(n)
};

int main()
{
	ListQueue q;

	q.enqueue(10);
	q.enqueue(20);
	q.enqueue(30);

	cout << "队头：" << q.getFront() << endl;
	cout << "大小：" << q.size() << endl;

	q.dequeue();
	cout << "出队后队头：" << q.getFront() << endl;

	while (!q.empty())
	{
		cout << q.getFront() << " ";
		q.dequeue();
	}
	cout << endl;

	return 0;
}