#include <iostream>
using namespace std;
int main()
{
    long long N;
    cin >> N;
    int isnum = 1;
    int cnt = 0;
    for (long long i = 0; i < N; i++) {
        int isresult = 1;
        int num = i;
        while (num >= 0) {
            if (num % 10 % 2 == 1 && isnum == 0) {
                isresult = 0;
                break;
            }
            if (num % 10 % 2 == 0 && isnum == 1) {
                isresult = 0;
                break;
            }
            num /= 10;
            isnum = (isnum + 1) % 2;
        }
        if (isresult == 1) {
            cnt++;
        }
    }
    cout << cnt << endl;
    // 请在此输入您的代码
    return 0;
}