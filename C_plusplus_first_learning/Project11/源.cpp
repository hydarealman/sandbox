#include<iostream>
#include<string>
using namespace std;

struct student {
	string name;
	int age;
	int score;
};
void printstudent(struct student s) {
	cout << s.name << s.age << s.score << endl;
}

int main() {
	struct student s;
	s.name = "ÕÅÈı";
	s.age = 18;
	s.score = 100;
	printstudent( s);
}