#include <iostream>
#include <vector>

using namespace std;

class A
{
public:
	A()
	{
		var = 1;
		cout << "Constructor called" << endl;
	}

	~A()
	{
		cout << "Destructor called" << endl;
	}

	void output()
	{
		cout << "Value of var: " << var << endl;
		cout << "Value of &this " << this << endl;
	}

	void increment()
	{
		var++;
	}

	A(const A & a)
	{
		cout << "Copy constructor called" << endl;
		var = a.var;	
	}
private:
	int var;
};

void foo(A &obj) { obj.increment(); obj.output(); }

void bar(A obj) { obj.increment(); obj.output(); }

void baz(A *obj) { obj->increment(); obj->output(); }

void blah(vector<A*> objs) 
{
	objs.back()->output();
	delete objs.back();
	objs.pop_back();
}

int main()
{
	A object;
	object.output();

	foo(object);
	bar(object);
	baz(&object);

	A* obj1 = new A;
	A* obj2 = new A;
	A* obj3 = new A;

	vector<A*> objects;

	objects.push_back(obj1);
	objects.push_back(obj2);
	objects.push_back(obj3);

	blah(objects);
	blah(objects);
	blah(objects);

	return 0;
}
