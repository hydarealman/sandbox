#include <iostream>
#include <stack>
#include <vector>
using namespace std;
int main()
{
    // 请在此输入您的代码
    int n;
    cin >> n;
    //集中定义变量
    vector<int> temperatures(n);
    vector<int> ans1(n, -1);
    vector<int> ans2(n, -1);
    vector<int> ans3(n, -1);
    vector<int> ans4(n, -1);
    stack<int> st1;
    stack<int> st2;
    stack<int> st3;
    stack<int> st4;
    //输入格式
    for (int i = 0; i < n; i++) {
        cin >> temperatures[i];
    }
    //第一行输出每个数字其左边第一个比其大的数字
    for (int i = 0; i < n; i++) {
        int t = temperatures[i];
        while (!st1.empty() && t >= temperatures[st1.top()]) {
            st1.pop();
        }
        if (!st1.empty()) {
            ans1[i] = temperatures[st1.top()];
        }
        st1.push(i);
    }
    //第二行输出每个数字其右边第一个比其大的数字
    for (int i = n - 1; i >= 0; i--) {
        int t = temperatures[i];
        while (!st2.empty() && t >= temperatures[st2.top()]) {
            st2.pop();
        }
        if (!st2.empty()) {
            ans2[i] = temperatures[st2.top()];
        }
        st2.push(i);
    }
    //第三行输出每个数字其左边第一个比其小的数字
    for (int i = 0; i < n; i++) {
        int t = temperatures[i];
        while (!st3.empty() && t <= temperatures[st3.top()]) {
            st3.pop();
        }
        if (!st3.empty()) {
            ans3[i] = temperatures[st3.top()];
        }
        st3.push(i);
    }
    //第四行输出每个数字其右边第一个比其小的数字
    for (int i = n - 1; i >= 0; i--) {
        int t = temperatures[i];
        while (!st4.empty() && t <= temperatures[st4.top()]) {
            st4.pop();
        }
        if (!st4.empty()) {
            ans4[i] = temperatures[st4.top()];
        }
        st4.push(i);
    }
    //输出格式
    //输出第一行
    for (int i = 0; i < ans1.size(); i++) {
        cout << ans1[i] << " ";
    }
    cout << endl;
    //输出第二行
    for (int i = 0; i < ans2.size(); i++) {
        cout << ans2[i] << " ";
    }
    cout << endl;
    //输出第三行
    for (int i = 0; i < ans3.size(); i++) {
        cout << ans3[i] << " ";
    }
    cout << endl;
    //输出第四行
    for (int i = 0; i < ans4.size(); i++) {
        cout << ans4[i] << " ";
    }
    cout << endl;
    return 0;
}