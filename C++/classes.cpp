#include <iostream>
#include <string>
#include <vector>
#include <string.h>

using namespace std;

string name();

class Person {
	private:
		string name;
	public:
		Person () {
			name = "John Doe";
		}

		Person (string s) {
			name = s;
		} 

		string getName() { return name; }
		void setName(string name) { this->name = name; }
};

int main() {
	Person * david = new Person();
	david->setName("David");
	cout << david->getName();
	return 0;
}

string name() {
	return "David";
}