#include<iostream>
using namespace std;

int m_sum(int icnt, int* ia) {

	for (int sum = 0, ix = 0; ix < icnt; ++ix) {
		sum += ia[ix];
		return sum;
	}
}
int main() {
	const int array_size = 128;
	int ia[array_size];
	int ival, icnt = 0;

	while (cin >> ival && icnt < array_size)
		ia[icnt++] = ival;

	int num = m_sum(icnt,ia);

	int average = num / icnt;

	cout << " sum of  " << icnt
		<< " element " << num
		<< " average " << average << endl;

}