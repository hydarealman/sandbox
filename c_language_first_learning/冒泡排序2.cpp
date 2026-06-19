#include<iostream>
using namespace std;
int main(){
	int arry[9] = {4,2,8,0,5,7,1,3,9}; 
	cout << "ÅÅÐòÇ°" << endl;
	for(int i=0; i < 9; i++)
	    cout << arry[i] << "";
cout << endl;

for(int i=0; i<9-1; i++)
{
	for(int j = 0; j<9-i-1;j++)
	{
		if(arry[j]>arry[j+1])
		{
			int temp = arry[j];
			arry[j] = arry[j+1];
			arry[j+1] = temp;
		}
	}
}

cout << "ÅÅÐòºó" << endl;

for(int i=0; i < 9; i++)
	    cout << arry[i] << "";
system("pause");
}

