#include <iostream>

using namespace std;

class Sample {
public:
	Sample(char c) {
		cout << "construct: " << c << endl;
	}

	Sample(const Sample& sample) {
		cout << "copy" << endl;
	}
	
	void operator=(const Sample& sample) {
		cout << "==" << endl;
	}
};

int main() {
	Sample s = Sample('b');
	Sample t('t');
	t = s;
}	
