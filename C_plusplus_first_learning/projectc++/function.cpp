#include<iostream>
#include "console.h"
#include "simpio.h"
using namespace std;

void song() {
	cout << "Now this is the story" << endl;
	cout << "all about how" << endl;
	cout << "My life got flipped" << endl;
	cout << "turned upside down" << endl;
}
int main() {
	song()

	cout << "Hello,world" <<  endl;
	int age = getInteger("How old are you");
	cout << "Yeah right! Marty wishes he were" << age << "!" << endl;
	
	song();

	return 0;
}

