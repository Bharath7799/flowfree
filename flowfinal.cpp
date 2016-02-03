#include <iostream>
#include <bits/stdc++.h>
using namespace std;
int s=0;
int s2=0;
#define siz 6
#define numdots 5

int f[siz][siz];
int fin[numdots]={0};

int x[numdots]={0};
int x2[numdots]; int y2[numdots];
void clearends(int v[siz][siz],int k)
{
	v[x2[k]][y2[k]]=0;
	for (int i = 0; i < siz; ++i)
	{
		for (int j = 0; j < siz; ++j)
		{
			if(v[i][j]>x[k])
				v[i][j]=0;
		}
	}
}
void d(int v[siz][siz])
{
	for (int i = 0; i < siz; ++i)
	{
		for (int j = 0; j < siz; ++j)
		{
			f[i][j]=v[i][j];
		}
	}
}
bool afterend(int i)
{
	if(fin[i]==1)
		return true;
	else 
		return false;
}
void firstplace(int i,int xx,int yy,int x1[numdots],int y1[numdots],int v[siz][siz])
{
	if(xx==x1[i]&&yy==y1[i])
		{
			for (int i2 = 0; i2 < siz; ++i2)
			{
				for (int j = 0; j < siz; ++j)
				{
					if (v[i2][j]==x[i])
					{
						v[i2][j]=0;
					}
				}
			}
		}
		v[xx][yy]=x[i];
}
bool check(int v[siz][siz])
{
	int c=0;
	for (int i = 0; i < siz; ++i)
	{
		for (int j = 0; j < siz; ++j)
		{
			if(v[i][j]==0)
				c++;
		}
	}
	if(c==0)
		return true;
	else
		return false;
}

void p(int v[siz][siz])
{
	for (int i = 0; i < siz; ++i)
	{
		for (int j = 0; j < siz; ++j)
		{
			cout<<v[i][j]<<" ";
		}
		cout<<endl;
	}
}
void p2(int v[numdots])
{
	for (int i = 0; i < numdots; ++i)
	{
		cout<<v[i]<<" ";
	}
}
bool move(int a[siz][siz],int v[siz][siz],int x[numdots],int x1[numdots],int y1[numdots],int xx,int yy,int i)
{
	if(s==0)
	{
	if(i<numdots)
	{

		firstplace(i,xx,yy,x1,y1,v);
	//	p(v);
	//	cout<<endl<<endl;
	//	cout<<a[xx][yy]<<" "<<x[i]<<endl;
		if(a[xx][yy]==x[i]) 
		{
			if(check(v))
				{
					s=1;
					d(v);
				}

			if(xx==x2[i]&&yy==y2[i])
			{
				// finish[i]=1;
				return true;
			}
			
		}
		
	    if(xx<(siz-1))
	    {
	    		firstplace(i,xx,yy,x1,y1,v);
	//    	cout<<"xx<4 : "<<xx<<" "<<yy<<"number index :"<<i<<endl;
			if (v[xx+1][yy]==0)
			{
				if(a[xx+1][yy]==0||a[xx+1][yy]==x[i])
				{
	//				cout<<"moving to pos : "<<xx+1<<" "<<yy<<" "<<i<<endl;
					if(move(a,v,x,x1,y1,xx+1,yy,i))
					{
						if(i<(numdots-1))
						{
							if(move(a,v,x,x1,y1,x1[i+1],y1[i+1],i+1))
							{
								return true;
							}
							else
							{
								return false;
							}
					    }
					}
					else
					{
						v[xx+1][yy]=0;
						v[x2[i]][y2[i]]=0;
					}
				}
		    }
		}
		
		if(xx>0)
		{
				firstplace(i,xx,yy,x1,y1,v);
	//		cout<<"xx>0 : "<<xx<<" "<<yy<<"number index :"<<i<<endl;

			if (v[xx-1][yy]==0)
			{
				if(a[xx-1][yy]==0||a[xx-1][yy]==x[i])
				{
	//				cout<<"moving to pos : "<<xx-1<<" "<<yy<<endl;
					if(move(a,v,x,x1,y1,xx-1,yy,i))
					{
						if(i<(numdots-1))
						{
							if(move(a,v,x,x1,y1,x1[i+1],y1[i+1],i+1))
								return true;
							else
							{
								
								return false;
							}
						}
					}
					else
					{
						v[xx-1][yy]=0;
						v[x2[i]][y2[i]]=0;
					}
				}
			}	
		}
		
		if(yy<(siz-1))
		{
				firstplace(i,xx,yy,x1,y1,v);
	//		cout<<"yy<4 : "<<xx<<" "<<yy<<"number index :"<<i<<endl;
		//	cout<<"inside yy<4 :"<<xx<<" "<<yy<<endl;
			if (v[xx][yy+1]==0)
			{
			//	cout<<"inside checking of visit matrix:\n";
				if(a[xx][yy+1]==0||a[xx][yy+1]==x[i])
				{
	//				cout<<"moving to pos : "<<xx<<" "<<yy+1<<endl;
					if(move(a,v,x,x1,y1,xx,yy+1,i))
					{
						if(i<(numdots-1))
						{
							if(move(a,v,x,x1,y1,x1[i+1],y1[i+1],i+1))
							{
								return true;
							}
							else
							{
								return false;
							}
					    }
					}
					else
					{
						v[xx][yy+1]=0;
						v[x2[i]][y2[i]]=0;
					}
				}
			}
		}
		
		if(yy>0)
		{
		//	cout<<"yy>0 : "<<xx<<" "<<yy<<" : "<<v[xx][yy-1]<<endl;
				firstplace(i,xx,yy,x1,y1,v);
			if (v[xx][yy-1]==0)
			{
				if(a[xx][yy-1]==0||a[xx][yy-1]==x[i])
				{
					if(move(a,v,x,x1,y1,xx,yy-1,i))
					{
						if(i<(numdots-1))
						{
							if(move(a,v,x,x1,y1,x1[i+1],y1[i+1],i+1))
							{
								return true;
							}
							else
							{
								return false;
							}
						}
					}
					else
					{
						v[xx][yy-1]=0;
						v[x2[i]][y2[i]]=0;
					}
				}
			}	
	    }

	    v[xx][yy]=0;
		return false;	

	}
	else
	{

		return false;
	}

}

}

int main(int argc,char *argv[])
{
	int a[siz][siz],v[siz][siz];
	int visited[siz][siz];
	for (int i = 0; i < siz; ++i)
	{
		for (int j = 0; j < siz; ++j)
		{
			a[i][j]=0;
			v[i][j]=0;
			visited[i][j]=0;
		}
	}

	
	 int x1[numdots]; int y1[numdots];


	 int flg[siz+1]={0};
	int c1=0,c2=0,c3=0;
	int xl=strlen(argv[1]);
	//int xl2=int16(sqrt(xl));
	int l=0;
	//cout<<xl2<<endl;


	//int flg[width+1]={0};
	for(int i=0;i<strlen(argv[1]);i++)
	{
		a[i/siz][i%siz] = argv[1][i]-'0';
		 if(a[i/siz][i%siz] != 0 && flg[a[i/siz][i%siz]]==0)
		 {
		 	//v.push_back((i/width)*10+(i%width));
		 	x1[c1]=i/siz; y1[c1]=i%siz; c1++;
		 	for(int k=0;k<strlen(argv[1]);k++){
		 		if(i!=k && a[i/siz][i%siz] == argv[1][k]-'0')
		 		{
		 			//dest.push_back((i/width)*10+(i%width));
		 			 x2[c2]=k/siz; y2[c2]=k%siz; c2++;
					 flg[a[k/siz][k%siz]]=1;
					 flg[a[i/siz][i%siz]]=1;
					 x[c3]=a[i/siz][i%siz]; c3++;
		 			break;
		 		}
		 	}
		 }
	}








	vector<int> vec[numdots];

	bool a3=move(a,v,x,x1,y1,x1[0],y1[0],0);
	cout<<"final output : "<<endl;
	p(f);
	int skr=0;
	//p(visited);
cout<<endl;
	for (int i = 0; i < numdots; ++i)
	{	
		
		cout<<endl;
		int x3=x1[i]; int y3=y1[i];
	//	cout<<endl<<x3<<" "<<y3<<endl;
		visited[x3][y3]=x[i];
		vec[i].push_back(x3*10+y3);
		while(x3!=x2[i]||y3!=y2[i])
		{
			if(x3<siz-1)
			{
				if(visited[x3+1][y3]==0)
				if (f[x3+1][y3]==f[x3][y3])
				{
				//	cout<<endl<<x3<<" "<<y3<<endl;
					int f2=f[x3][y3];
					//x3=x3+1;
					while(x3<siz)
					{
						if(f[x3][y3]==f2)
						{
							visited[x3][y3]=x[i];
							x3++;
						}
						else
						{
							break;
						}
					}
					x3--;
					vec[i].push_back((x3)*10+y3);
				}
			}
			if(x3>0)
			{
				if(visited[x3-1][y3]==0)
				if (f[x3-1][y3]==f[x3][y3])
				{
				//	cout<<endl<<x3<<" "<<y3<<endl;
					int f2=f[x3][y3];
					//x3=x3-1;
					while(x3>=0)
					{
						if(f[x3][y3]==f2)
						{
							visited[x3][y3]=x[i];
							x3--;
						}
						else
							break;
					}
					x3++;
					vec[i].push_back(x3*10+y3);
				}
			}
			if(y3<siz-1)
			{
				if(visited[x3][y3+1]==0)
				if (f[x3][y3+1]==f[x3][y3])
				{
				//	cout<<endl<<x3<<" "<<y3<<endl;
					int f2=f[x3][y3];
					//y3=y3+1;
					while(y3<siz)
					{
						if(f[x3][y3]==f2)
						{
							visited[x3][y3]=x[i];
							y3++;
						}
						else
							break;
					}
					y3--;
					vec[i].push_back(x3*10+y3);
				}
			}
			if(y3>0)
			{
				if(visited[x3][y3-1]==0)
				if (f[x3][y3-1]==f[x3][y3])
				{
				//	cout<<endl<<x3<<" "<<y3<<endl;
					int f2=f[x3][y3];
					//y3=y3-1;
					while(y3>=0)
					{
						if(f[x3][y3]==f2)
						{
							visited[x3][y3]=x[i];
							y3--;
						}
						else
							break;
					}
					y3++;
					vec[i].push_back(x3*10+y3);
				}
			}

		}
	//	p(visited);
	}

	

	for (int i = 0; i < numdots; ++i)
	{
		for (int j = 0; j < vec[i].size(); ++j)
		{
			cout<<vec[i][j]<<" ";
		}
		cout<<endl;
	}

	

}
