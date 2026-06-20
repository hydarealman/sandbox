#include<stdio.h>
#include<stdlib.h>
#include<math.h>

using namespace std;
int main() {
	float a = 0;
	double b = 0;
	if (fabs(a) < 1e-6) {
		printf("float equal 0");
	}

	if (fabs(b) < 1e-15) {
		printf("double equal 0");
	}
}