#include <bits/stdc++.h>
using namespace std;
const int width = 5;
void print(int a[][width]){
	for(int i=0;i<width;i++){
		for(int j=0;j<width;j++)
		{
			cout<<a[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<"\n\n";
}
map<int,vector<int> > m;
map<int,int> check;
void solve(int a[][width],int x,int y,vector<int> vec,int k,vector<int> dest){
	//cout<<"yes";

	if(x>=width || y>=width || x<0 || y < 0 )
	{
		return;
	}
	if(x== dest[k]/10 && y == dest[k]%10)
	{
		//cout<<"working\n";
		
		if(k+1<vec.size()){
		y = vec[k+1]%10;
		x = vec[k+1]/10;
		
		solve(a,x,y,vec,k+1,dest);
	}
	else{
		print(a);
		int flg=0;
		map<int,int> ::iterator it1;
		for(int i=0;i<vec.size();i++){
			m[i+1].push_back(vec[i]);
			int p = vec[i]/10;
			int q = vec[i]%10;
			//cout<<"{"<<p<<q<<"}"<<"{"<<dest[i]/10<<dest[i]%10<<"}";
			check.clear();
		 
			while(p!=dest[i]/10 || q!=dest[i]%10){
			
				//cout<<"no";
				//cout<<p<<q<<endl;
				//cout<<"-->"<<a[p+1][q]<<"="<<i+1<<endl;
				if(p!=width-1 && a[p+1][q] ==(i+1) && check.count((p+1)*10+q) == 0)
				{
					while(p<width && a[p][q]==i+1)
						{
							//cout<<"yes"<<p<<q<<endl;
							check[p*10+q]=1;
							p++;}
					p--;
					//cout<<"yes"<<p<<q;
					m[i+1].push_back(p*10+q);
				}
				if(q!=0 && a[p][q-1] == i+1 && check.count(p*10+q-1)==0)
				{
					while(q>=0 && a[p][q]==i+1 )
						{check[p*10+q]=1;q--;}
					q++;
						m[i+1].push_back(p*10+q);
				}
					if(p!=0 && a[p-1][q] == i+1 && check.count((p-1)*10+q)==0){
					while(p>=0 && a[p][q] == i+1)
							{
								check[p*10+q]=1;
								p--;}
					
					p++;
						m[i+1].push_back(p*10+q);
				}
				if(q!=width-1 && a[p][q+1] ==i+1 && check.count(p*10+q+1)==0){
					while(q<width && a[p][q] == i+1)
						{check[p*10+q]=1;q++;}
					q--;
					//cout<<"ok"<<p<<q<<endl;
					m[i+1].push_back(p*10+q);
				}
			}
			/*for(it1 = check.begin();it1!=check.end();it1++)
			{
				cout<<it1->first<<" ";
			}
			cout<<endl;
*/		}
	map<int,vector<int> > ::iterator it;
	vector<int> v;
	/*for(it =m.begin();it!=m.end();it++)
	{
		cout<<it->first<<"-->";
		v = it->second;
		for(int j=0;j<v.size();j++)
		{
			cout<<v[j]<<" ";
		}
		cout<<endl;
	}*/
		exit(0);
	}
	}


	//cout<<"no";

	a[x][y] = k+1;
	//cout<<"{"<<x<<","<<y<<"}\n";
	//print(a);
	int p;
	//cin>>p;
	if(  (a[x-1][y]==0 || (x-1 ==dest[k]/10 && y == dest[k]%10)))
	solve(a,x-1,y,vec,k,dest);
	if(  (a[x+1][y]==0 || (x+1 ==dest[k]/10 && y == dest[k]%10)))
	solve(a,x+1,y,vec,k,dest);
	if( (a[x][y-1]==0 || (x ==dest[k]/10 && y-1 == dest[k]%10)))
	solve(a,x,y-1,vec,k,dest);
	if(  (a[x][y+1]==0 || (x ==dest[k]/10 && y+1 == dest[k]%10)))
	solve(a,x,y+1,vec,k,dest);

	a[x][y]=0;
    
}
int main(int argc,char *argv[]){
	int a[width][width];
	for(int i=0;i<width;i++)
		for(int j=0;j<width;j++)
			a[i][j]=0;
	/*a[0][0] = a[2][1] = 1;
	a[0][1] = a[4][1] = 2;
	a[0][2] = a[4][4] = 3;
	a[4][0] = a[2][2] = 4;*/
	//a[1][4] = a[4][3] = 5;
	vector<int> v,dest;
	int flg[width+1]={0};
	for(int i=0;i<strlen(argv[1]);i++)
	{
		a[i/width][i%width] = argv[1][i]-'0';
		 if(a[i/width][i%width] != 0 && flg[a[i/width][i%width]]==0)
		 {
		 	v.push_back((i/width)*10+(i%width));
		 	for(int k=0;k<strlen(argv[1]);k++){
		 		if(i!=k && a[i/width][i%width] == argv[1][k]-'0')
		 		{
		 			dest.push_back((i/width)*10+(i%width));
		 			break;
		 		}
		 	}
		 }
	}

	print(a);
	
/*	v.push_back(0);dest.push_back(21);
	v.push_back(1);dest.push_back(41);
	v.push_back(2);dest.push_back(44);
	v.push_back(40);dest.push_back(22);*/
	//v.push_back(14);dest.push_back(43);
	solve(a,0,0,v,0,dest);
	int x,y;

	
}