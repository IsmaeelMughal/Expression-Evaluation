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
			cout << "\nEMPTY STACK POP\n";
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
			cout << "\nEMPTY STACK TOP\n";
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
	if (val == '+' || val == '-' || val == '*' || val == '/' || val == '%' || val == '^' || val == '~' )
	{
		return true;
	}
	return false;
}

// helper function to check if char is whitespace
bool isWhiteSpace(char val)
{
	if (val == ' ' || val == '\n' || val == '\t')
	{
		return true;
	}
	return false;
}

// HelperFunction for finding valid precedance
bool isValidOperatorForPerformingOperation(char previous, char current)
{
	char operators[7] = { '+','-','*','%','/','^','~' };
	int priority[7] = { 1,1,2,2,3,3,4 };
	int previousPriority,currentPriority;
	for (int i = 0; i < 7; i++)
	{
		if (operators[i] == previous)
		{
			previousPriority = i;
		}
		else if(operators[i] == current)
		{
			currentPriority = i;
		}
	}
	if (priority[previousPriority] >= priority[currentPriority])
	{
		return true;
	}
	return false;
}

// Helper function to perform an operation on two operands
double performOperation(char opt, double val1, double val2 = 0)
{
	if (opt == '+')
	{
		return val1 + val2;
	}
	else if (opt == '-')
	{
		return val1 - val2;
	}
	else if (opt == '*')
	{
		return val1*val2;
	}
	else if (opt == '/')
	{
		if (val2 == 0)
		{
			exit(0);
		}
		return val1 / val2;
	}
	else if (opt == '%')
	{
		return (int)val1%(int)val2;
	}
	else if (opt == '^')
	{
		int temp = val1;
		for (int i = 1; i < val2; i++)
		{
			temp = temp * val1;
		}
		return temp;
	}
	else if (opt == '~')
	{
		return (65535-(int)val1);		// taking 1's complement
	}
}

// TASK
double evaluateInfix(const char * exp)
{
	double value = 0, digit;	// for storing multiple digit number
	double afterDecimalPoint = 10;	// for converting into decimal number
	bool digitSwitch = true;		// for check of spaces
	bool operatorSwitch = true;
	Stack<double> oprandsStack;		// for storing oprands
	Stack<char> operatorStack;			// for storing operators
	double val2, val1, result;	// for push and pop values from stack
	
	for (int i = 0; exp[i] != 0; i++)
	{
		if (exp[i] == '.')	// if expression start with '.'
		{
			i++;	// ignore .
			value = 0;
			while (isDigit(exp[i]))	// start converting into decimal 
			{
				digit = exp[i] - 48;
				digit = digit / afterDecimalPoint;
				value = value + digit;
				afterDecimalPoint = afterDecimalPoint * 10;
				i++;
			}
			oprandsStack.push(value);		// push complete decimal value
			value = 0;	// after pushing set default values back
			afterDecimalPoint = 10;
			digitSwitch = false;	// as next character must be an operator or space
			operatorSwitch = true;
			i--;
		}
		if (isDigit(exp[i]))	// if digit
		{
			if (!digitSwitch)		// check for validity
			{
				cout << "\nExpression have some extra space between digits" << endl;
				exit(0);
			}
			while (isDigit(exp[i])) // start reading digits
			{		// converting into a number
				digit = exp[i] - 48;
				value = value * 10;
				value = value + digit;
				i++;
			}
			if (exp[i] == '.')	// if upper loop ends with a .
			{
				i++;	// ignore .
				while (isDigit(exp[i]))	// start converting into decimal 
				{
					digit = exp[i] - 48;
					digit = digit / afterDecimalPoint;
					value = value + digit;
					afterDecimalPoint = afterDecimalPoint * 10;
					i++;
				}
			}
			oprandsStack.push(value);		// push complete decimal value
			value = 0;	// after pushing set default values back
			afterDecimalPoint = 10;
			digitSwitch = false;	// as next character must be an operator or space
			operatorSwitch = true;
			i--;
		}
		else if(isWhiteSpace(exp[i]))
		{ }			// ignoring white spaces
		else if (exp[i] == '(')		// for opening brace
		{
			operatorStack.push(exp[i]);
			digitSwitch = true;
			operatorSwitch = true;
		}
		else if(exp[i] == ')')		// for closing brace
		{
			while (operatorStack.stackTop() != '(')	// solve complete inner expression
			{
				val2 = oprandsStack.pop();
				val1 = oprandsStack.pop();
				result = performOperation(operatorStack.pop(), val1, val2);
				oprandsStack.push(result);
			}
			operatorStack.pop();
			digitSwitch = false;
			operatorSwitch = true;
		}
		else if (isOperator(exp[i]))	// if next character is an operator
		{
			if (operatorStack.isEmpty() || operatorStack.stackTop() == '(')	// 1st operator
			{
				operatorStack.push(exp[i]);
			}
			else if (operatorStack.stackTop() == exp[i] || operatorStack.stackTop() == '*' && exp[i] == '%' || operatorStack.stackTop() == '%' && exp[i] == '*')
			{
				operatorStack.push(exp[i]);		// Associativity check
			}
			else if (isValidOperatorForPerformingOperation(operatorStack.stackTop(), exp[i]))
			{			// after checking valid precedence for performing valvulation
				if (operatorStack.stackTop() == '~')	// for uniary operator
				{
					val1 = oprandsStack.pop();
					result = performOperation(operatorStack.pop(), val1);
					oprandsStack.push(result);
					operatorStack.push(exp[i]);
				}
				else // for other binary operators
				{		
					val2 = oprandsStack.pop();
					val1 = oprandsStack.pop();
					result = performOperation(operatorStack.pop(), val1, val2);
					oprandsStack.push(result);
					operatorStack.push(exp[i]);
				}
			}
			else
			{
				operatorStack.push(exp[i]);
			}
			digitSwitch = true;
			operatorSwitch = false;
		}
	}
	while (!operatorStack.isEmpty())	// afting reaching NULL complete calculations
	{
		val2 = oprandsStack.pop();
		val1 = oprandsStack.pop();
		result = performOperation(operatorStack.pop(), val1, val2);
		oprandsStack.push(result);
	}
	return oprandsStack.pop();		// return final result
}


int main()
{
	cout << evaluateInfix("~2+5") << endl;

	return 0;
}