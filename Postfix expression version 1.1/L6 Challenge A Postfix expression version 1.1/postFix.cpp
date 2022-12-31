/*
Name : Muhammad Ismaeel
Roll No : BCSF19M037
*/

#include <iostream>

using namespace std;

template <typename T>
class Stack
{
private:
	T* data;
	int capacity;
	int top;
	void reSize(int newSize)
	{
		T * temp = new T[newSize];
		for (int i = 0; i<top; i++)
			temp[i] = data[i];
		int tempTop = top;
		this->~Stack();
		top = tempTop;
		data = temp;
		capacity = newSize;
	}
public:
	Stack()
	{
		data = nullptr;
		capacity = 0;
		top = 0;
	}
	Stack(const Stack<T>& orig)
	{
		if (orig.data == nullptr)
		{
			data = nullptr;
			capacity = 0;
			top = 0;
			return;
		}
		capacity = orig.capacity;
		data = new T[capacity];
		for (int i = 0; i < capacity; i++)
		{
			data[i] = orig.data[i];
		}
		top = orig.top;
	}
	Stack& operator= (const Stack<T>& rhs)
	{
		if (&rhs == this)
		{
			return *this;
		}
		if (rhs.data == nullptr)
		{
			this->~Stack();
			return *this;
		}
		capacity = rhs.capacity;
		data = new T[capacity];
		for (int i = 0; i < capacity; i++)
		{
			data[i] = rhs.data[i];
		}
		top = rhs.top;
		return *this;
	}

	~Stack()
	{
		if (data != nullptr)
		{
			delete[] data;
			data = nullptr;

			capacity = 0;
			top = 0;
		}
	}

	void push(T val)
	{
		if (isFull())
		{
			if (capacity == 0)
			{
				reSize(1);
			}
			else
			{
				reSize(capacity * 2);
			}
		}

		data[top] = val;
		top++;
	}
	T pop()
	{
		if (isEmpty())
		{
			exit(0);
		}
		top--;
		T val = data[top];
		if (top > 0 && top == capacity / 4)
		{
			reSize(capacity / 2);
		}
		return val;
	}
	T stackTop()
	{
		if (isEmpty())
		{
			exit(0);
		}
		return data[top - 1];
	}
	bool isFull()
	{
		if (top == capacity)
		{
			return true;
		}
		return false;
	}
	bool isEmpty()
	{
		if (top == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	int getCapacity()
	{
		return capacity;
	}
	int getnumberOfElements()
	{
		return top;
	}
};

// helper function to perform operations
double performOperation(double val1,double val2,char opt)	
{
	if (opt == '+')
	{
		return val1 + val2;
	}
	else if (opt == '-')
	{
		return val1 - val2;
	}
	else if(opt == '*')
	{
		return val1*val2;
	}
	else if (opt == '/')
	{
		return val1 / val2;
	}
}

// helper function to check if char is digit
bool isDigit(char val)
{
	if (val >= '0' && val <= '9')
	{
		return true;
	}
	return false;
}

// helper function to check if char is opeartor
bool isOperator(char val)
{
	if (val == '+' || val == '-' || val == '*' || val == '/' )
	{
		return true;
	}
	return false;
}

// TASK
double evaluatePostfixV1(const char * exp)
{
	Stack<double> values;	// using stack
	double val1, val2, result;		// for pushing and poping values from stack
	for (int i = 0; exp[i] != 0; i++)	// Loop till NULL is found
	{
		if (isDigit(exp[i]))	// if it's a digit push it on stack
		{
			values.push((double)(exp[i]-48));
		}
		else if (isOperator(exp[i]))	// if it's an opeartor
		{
			if (values.isEmpty())	// check for empty stack
			{
				cout << "\nWrong expression" << endl;
				exit(0);
			}
			val2 = values.pop();	// pop 1st value
			if (values.isEmpty())
			{
				cout << "\nWrong expression" << endl;
				exit(0);
			}
			val1 = values.pop();	// pop 2nd value
			result = performOperation(val1, val2, exp[i]);	
			values.push(result);	// pop result of operator
		}
		else	// if value of index is other than a digit or opeartor
		{
			cout << "\nExpression have an unknown value." << endl;
			exit(0);
		}
	}
	return values.pop();	// poping final result of expression
}

int main()
{
	cout << evaluatePostfixV1("1347+79/3*-*+?") << endl;
	return 0;
}