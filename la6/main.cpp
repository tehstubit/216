#include <iostream>


using namespace std;

class Test
{
private:
	int m_iValue;
	Test() 
	{
		cout << "The Object has been created." << endl;
		m_iValue = 1;
	}

//	~Test()
//	{
//		cout << "The object has been destroyed." << endl;
//	}
public:
	void increment()
	{
		cout << "increment method called." << endl;
		cout << m_iValue << endl;
		m_iValue++;
	}
	
	static Test instance()
	{
		static Test object;
		return object;
	}

	~Test()
	{
		cout << "The object has been destroyed." << endl;
	}
};
	

void static_test()
{
	static int a = 1;
	cout << a << endl;
	a++;
}

int main()
{
	static_test();
	static_test();
	static_test();
	
	Test::instance().increment();
	Test::instance().increment();
	Test::instance().increment();

	return 0;
}
