#include<iostream>
using namespace std;
int main(){
	int arry[5] = {100,46546,300,500,400};
	int k;
	for(k=0; k<5; k++)
	    if(arry[k]>arry[k+1])
	        arry[k+1] = arry[k];
	
	cout << arry[5] << endl;
}
