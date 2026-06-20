#include <iostream>
using namespace std;
int main()
{
    int a, b, n;
    cin >> a >> b >> n;
    int day = 0;
    while (n > 0) {
        day++;
        if (day % 6 == 0 || day % 7 == 0) {
            n -= b;
        }
        else {
            n -= a;
        }
    }
    cout << day << endl;
    // 请在此输入您的代码
    system("pause");
    return 0;
}
