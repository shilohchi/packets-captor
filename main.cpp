#include <iostream>
#include <memory>

using namespace std;
class A {
public:
	virtual ~A();
};
A::~A() {}

class B : public A {
public:
	virtual ~B();
};
B::~B(){}

int main() {
	shared_ptr<B> p = dynamic_pointer_cast<B>(shared_ptr<A>(new B));
}
