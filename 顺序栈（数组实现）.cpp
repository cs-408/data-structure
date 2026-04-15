#include<iostream>
using namespace std;

// 顺序栈：数组实现，动态扩容
class ArrStack
{
public:
	// 构造函数：初始化栈，默认容量10
	// 时间复杂度：O(cap)，视为O(1)
	ArrStack(int size = 10) : top(0), cap(size)
	{
		arrstack = new int[cap]();
	}

	// 析构函数：释放数组内存
	// 时间复杂度：O(1)
	~ArrStack()
	{
		delete[] arrstack;
		arrstack = nullptr;
	}

public:
	// 入栈：将元素压入栈顶
	// 均摊时间复杂度：O(1)（扩容时O(n)，极少发生）
	void push(int val)
	{
		if (top == cap)  // 栈满，扩容2倍
		{
			expand(2 * cap);
		}
		arrstack[top++] = val;  // 先赋值，后移动栈顶指针
	}

	// 出栈：删除栈顶元素（逻辑删除）
	// 时间复杂度：O(1)
	void pop()
	{
		if (top == 0)  // 栈空，抛出异常
		{
			throw "stack is empty!";
		}
		top--;  // 仅移动指针，不释放内存，下次push覆盖
	}

	// 获取栈顶元素（不出栈）
	// 时间复杂度：O(1)
	int GetTop() const
	{
		if (top == 0)
		{
			throw "stack is empty!";
		}
		return arrstack[top - 1];  // top指向下一空闲位置，实际元素在top-1
	}

	// 判空：栈是否为空
	// 时间复杂度：O(1)
	bool empty() const
	{
		return top == 0;
	}

	// 获取栈中元素个数
	// 时间复杂度：O(1)
	int size() const
	{
		return top;
	}

private:
	// 内部扩容：申请新数组，复制数据，释放旧数组
	// 时间复杂度：O(n)，n为当前元素个数top
	void expand(int size)
	{
		int* p = new int[size]();
		// 复制有效元素（top个）
		for (int i = 0; i < top; i++)
		{
			p[i] = arrstack[i];
		}
		delete[] arrstack;
		arrstack = p;
		cap = size;
	}

private:
	int* arrstack;  // 指向动态数组内存
	int top;        // 栈顶指针（指向下一空闲位置，即元素个数）
	int cap;        // 栈容量
};

int main()
{
	ArrStack s;

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
