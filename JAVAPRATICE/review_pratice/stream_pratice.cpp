#include <iostream>
#include <sstream>
#include <string>
using namespace std;

int main() {
    ostringstream oss;
    oss << "年龄: " << 25 << "分数: " << 95.5;
    string result = oss.str();
    cout << "拼接结果: " << result << endl;
    
    // 从字符串流读取
    istringstream iss("100 200 300");
    int a,b,c;
    iss >> a >> b >>c;
    cout << "a=" << a << "b=" << b << "c=" << c << endl;

    return 0;
}