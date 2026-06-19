#include<iostream>
#include<string>

struct student {
	string name;
	int age;
	int score;
};

void printstudent(struct student s);

int main() {
	struct student s;
	s.name = "ÕÅÈı";
	s.age = 18;
	s.score = 100;
	void printstudent(struct student s);
}
void printstudent(struct student s) {
	cout << s.name << s.age << s.score << endl;
}
