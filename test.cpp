#include <iostream>
#include <memory>
using namespace std;
class Manager {
private:
	static shared_ptr<Manager> mgr;

	Manager(int n) {
		this->n = n;
		cout << "construct Manager: " << endl;
	}

	int n;

public:
	static shared_ptr<Manager> getManager() {
		if (!mgr) {
			mgr = shared_ptr<Manager>(new Manager(3));
		}
		return mgr;
	}

	~Manager() {
		cout << "~Manager: " << n << endl;
	}
};

shared_ptr<Manager> Manager::mgr;

int main() {
	shared_ptr<Manager> p = Manager::getManager();
}
