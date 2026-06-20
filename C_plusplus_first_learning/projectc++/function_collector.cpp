

void swap(int a, int b){
	int temp;
	temp = a;
	a = b;
	b = temp;
}
void datingrange(int age, int& min, int& max) {
	min = age / 2 + 7;
	max = (age - 7) * 2;
}