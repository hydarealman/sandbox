#include<iostream>
#include<string>

using namespace std;

int main()
{
    string str;
    getline(cin, str);
    int n = str.size();
    
    for(int i = 0; i < n; i++)
    {
        int j = i;
        
        while(str[j] != ' ') j++;
        
        // cout<<j;
        for(int k = i; k < j; k++) cout<<str[k];
        cout<<endl;
        
        i = j; //循环体执行完后for()中的i才 i++即，下一次开始时 i就到了上一次空格(位置j)的下一位 
    }
    return 0;
}

