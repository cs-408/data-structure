#if 0
#include<iostream>
using namespace std;

class Array
{
public:
	// 构造函数：初始化数组，默认容量10
	// 时间复杂度：O(cap)，但cap是常数，视为O(1)
	Array(int size = 10) : cur(0), cap(size)
	{
		arr = new int[cap]();
	}

	// 析构函数：释放动态内存，防止内存泄漏
	// 时间复杂度：O(1)
	~Array()
	{
		delete[] arr;
		arr = nullptr;  // 置空，防止野指针
	}

public:
	// 尾部添加元素
	// 均摊时间复杂度：O(1)（扩容时O(n)，但极少发生）
	void push_back(int val)
	{
		if (cur == cap)  // 满了，扩容2倍
		{
			expand(2 * cap);
		}
		arr[cur++] = val;
	}

	// 尾部删除元素（逻辑删除，不释放内存）
	// 时间复杂度：O(1)
	void pop_back()
	{
		if (cur == 0)
		{
			cout << "数组为空，无法删除" << endl;
			return;
		}
		cur--;  // 仅移动游标，下次push_back会覆盖
	}

	// 指定位置插入元素
	// pos范围：[0, cur]，pos==cur相当于push_back
	// 时间复杂度：O(n)，需移动pos后所有元素
	void insert(int pos, int val)
	{
		if (pos < 0 || pos > cur)
		{
			cout << "插入位置不合法" << endl;
			return;
		}
		if (cur == cap)
		{
			expand(2 * cap);
		}
		// 从后向前移动，腾出pos位置
		for (int i = cur - 1; i >= pos; i--)
		{
			arr[i + 1] = arr[i];
		}
		arr[pos] = val;
		cur++;
	}

	// 指定位置删除元素
	// pos范围：[0, cur-1]
	// 时间复杂度：O(n)，需移动pos后所有元素
	void erase(int pos)
	{
		if (pos < 0 || pos >= cur || cur == 0)  // 修正：pos >= cur才越界
		{
			cout << "删除位置不合法" << endl;
			return;
		}
		// 从前向后移动，覆盖被删元素
		for (int i = pos + 1; i < cur; i++)
		{
			arr[i - 1] = arr[i];
		}
		cur--;
	}

	// 查找元素，返回下标，未找到返回-1
	// 时间复杂度：O(n)，顺序查找
	int find(int val)
	{
		for (int i = 0; i < cur; i++)
		{
			if (arr[i] == val)
				return i;
		}
		return -1;
	}

	// 打印所有元素
	// 时间复杂度：O(n)
	void show() const
	{
		for (int i = 0; i < cur; i++)
		{
			cout << arr[i] << ' ';
		}
		cout << endl;
	}

private:
	// 内部扩容：申请新内存，复制数据，释放旧内存
	// 时间复杂度：O(n)，需复制cur个元素
	void expand(int size)
	{
		int* p = new int[size]();
		// 复制有效元素（cur个）
		for (int i = 0; i < top; i++)
		{
			p[i] = arrstack[i];
		}
		delete[] arr;
		arr = p;
		cap = size;
	}

private:
	int* arr;   // 指向动态数组内存
	int cap;    // 数组容量（总空间）
	int cur;    // 当前元素个数（有效数据）
};

int main()
{
	Array arr;


	arr.push_back(10);
	arr.push_back(20);
	arr.push_back(30);
	arr.show();

	arr.insert(1, 15);
	arr.show();

	arr.erase(2);
	arr.show();

	int pos = arr.find(15);
	cout << "15的位置：" << pos << endl;

	return 0;
}
#endif