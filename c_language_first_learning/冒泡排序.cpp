#include<iostream>
using namespace std;
int main(){
	int arry[10] = {5,7,8,9,6,4,2,1,3,0}; 
	
cout << "ÅÅĞòÇ°" << endl;
for(int x = 0; x < 10; x++)
    cout << arry[x] << "";
    cout << endl;
	for(int i = 0; i < 10-1; i++)
{
		    for(int j = 0; j < 10-1-i; j++)
	    {
	    	if(arry[j] > arry[j+1])
	    	{
			int wudeyan = arry[j];
	    	arry[j] = arry[j+1];
	    	arry [j+1] = wudeyan;
			}
		}
}
cout << "ÅÅĞòºó£º"<< endl;
for(int x = 0; x < 10; x++)
    cout << arry[x] << "";
	system("pause");
}
