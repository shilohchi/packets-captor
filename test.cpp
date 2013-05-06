#include <iostream>
#include <memory>
using namespace std;

class Manager {
private:
	static shared_ptr<Manager> mgr;

	Manager() {
		cout << "construct Manager" << endl;
	}


public:
	static shared_ptr<Manager> getManager() {
		if (!mgr) {
			mgr = new Manager();
		}
		return mgr;
	}

	~Manager() {
		cout << "~Manager" << endl;
	}
};

int main() {
	shared_ptr<Manager> p = Manager.getManager();
}
