#include <iostream>
using namespace std;

 int main(int argc, char const *argv[])
{
	int a[2][2];
	int count=0;
	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 2; ++j)
		{
			a[i][j]=count++;
		}
	}
	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 2; ++j)
		{
			cout<<a[i][j]<<" ";
		}
		cout<<endl;
	}
	return 0;
}