#include <iostream>
#include <bits/stdc++.h>
using namespace std;
int s=0;

#define size 5
#define numdots 5
int f[size][size];
int fin[numdots]={0,0,0,0,0};
int x[numdots]={1,2,3,4,5};
int x2[numdots]={2,1,3,3,4}; int y2[numdots]={0,3,1,4,4};
void clearends(int v[size][size],int k)
{
	v[x2[k]][y2[k]]=0;
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			if(v[i][j]>x[k])
				v[i][j]=0;
		}
	}
}
void d(int v[size][size])
{
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
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
void firstplace(int i,int xx,int yy,int x1[numdots],int y1[numdots],int v[size][size])
{
	if(xx==x1[i]&&yy==y1[i])
		{
			for (int i2 = 0; i2 < size; ++i2)
			{
				for (int j = 0; j < size; ++j)
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
bool check(int v[size][size])
{
	int c=0;
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			if(v[i][j]==0)
				c++;
		}
	}
//	cout<<"value of c: "<<c;
	if(c==0)
		return true;
	else
		return false;
}

void p(int v[size][size])
{
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			cout<<v[i][j]<<" ";
		}
		cout<<endl;
	}
}
bool move(int a[size][size],int v[size][size],int x[numdots],int x1[numdots],int y1[numdots],int xx,int yy,int i)
{

	// if(s++>35)
	// 	exit(0);
	
	// clearends(v,i);
	// if(afterend(i,v))
	// {
	// 	clearends(v,i);
	// }
	//cout<<"index : "<< i<<endl;
	
	//cout<<endl<<"in move : "<<xx<<" "<<yy<<endl;
	if(s==0)
	{
	if(i<numdots)
	{

		firstplace(i,xx,yy,x1,y1,v);
		p(v);
		cout<<endl<<endl;
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
		
	    if(xx<(size-1))
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
		
		if(yy<(size-1))
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
			cout<<"yy>0 : "<<xx<<" "<<yy<<" : "<<v[xx][yy-1]<<endl;
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

int main()
{
	int a[size][size],v[size][size];
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			a[i][j]=0;
			v[i][j]=0;
		}
	}
	a[0][3] = a[2][0] = 1;
	a[0][4] = a[1][3] = 2;
	a[1][2] = a[3][1] = 3;
	a[3][0] = a[3][4] = 4;
	a[3][3] = a[4][4] = 5;
	p(a);
	
	int x1[numdots]={0,0,1,3,3}; int y1[numdots]={3,4,2,0,3};

	cout<<"the function move is initialised\n";
	bool a3=move(a,v,x,x1,y1,x1[0],y1[0],0);
	cout<<"final output : "<<endl;
	p(f);

	

}
