#include<iostream>
using namespace std;

// 环形队列（循环队列）：数组实现，牺牲一个单元区分空满
class CircleQueue
{
public:
	// 构造函数：申请size+1空间，实际可存储size个元素
	// 牺牲一个单元作为哨兵，区分队空和队满
	// 时间复杂度：O(1)
	CircleQueue(int size = 10) : cap(size + 1), front(0), rear(0)
	{
		arr = new int[cap]();  // 申请cap个单元，初始化为0
	}

	// 析构函数：释放数组内存
	// 时间复杂度：O(1)
	~CircleQueue()
	{
		delete[] arr;
		arr = nullptr;
	}

public:
	// 入队：在队尾添加元素
	// 时间复杂度：O(1)
	void enqueue(int val)
	{
		if ((rear + 1) % cap == front)  // 队满判断：牺牲单元被占用
		{
			throw "queue is full !";
		}
		rear = (rear + 1) % cap;  // rear循环后移
		arr[rear] = val;           // 存入数据
	}

	// 出队：删除队头元素（逻辑删除）
	// 时间复杂度：O(1)
	void dequeue()
	{
		if (front == rear)  // 队空判断：front追上rear
		{
			throw "queue is empty !";
		}
		front = (front + 1) % cap;  // front循环后移，数据不删，覆盖即可
	}

	// 获取队头元素（不出队）
	// 时间复杂度：O(1)
	int getFront() const
	{
		if (front == rear)
		{
			throw "queue is empty !";
		}
		return arr[(front + 1) % cap];  // front指向空单元，实际数据在后一位
	}

	// 判空：队列是否为空
	// 时间复杂度：O(1)
	bool empty() const
	{
		return front == rear;
	}

	// 判满：队列是否已满
	// 时间复杂度：O(1)
	bool full() const
	{
		return (rear + 1) % cap == front;
	}

	// 获取元素个数
	// 时间复杂度：O(1)
	// 注意：实际容量为cap-1（牺牲一个单元）
	int size() const
	{
		return (rear - front + cap) % cap;  // 循环队列长度计算公式
	}

private:
	int* arr;    // 数组内存
	int cap;     // 申请容量（实际size+1）
	int front;   // 队头指针（指向空单元，实际数据在front+1）
	int rear;    // 队尾指针（指向最后一个数据）
};

int main()
{
	// 测试用例：容量5，实际最多存5个元素（申请6个单元）,size+1就是为了此处实际容量等于传入数
	CircleQueue q(5);

	cout << "入队10,20,30,40,50：" << endl;
	q.enqueue(10);
	q.enqueue(20);
	q.enqueue(30);
	q.enqueue(40);
	q.enqueue(50);

	cout << "队头：" << q.getFront() << endl;
	cout << "大小：" << q.size() << endl;
	cout << "是否满：" << (q.full() ? "是" : "否") << endl;

	cout << "\n出队3个：" << endl;
	q.dequeue();
	q.dequeue();
	q.dequeue();

	cout << "队头：" << q.getFront() << endl;
	cout << "大小：" << q.size() << endl;

	cout << "\n再入队60,70：" << endl;
	q.enqueue(60);
	q.enqueue(70);

	cout << "队头：" << q.getFront() << endl;
	cout << "大小：" << q.size() << endl;

	CircleQueue q2;
	cout << "\n新队列是否空：" << (q2.empty() ? "是" : "否") << endl;

	return 0;
}