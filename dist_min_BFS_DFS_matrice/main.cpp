#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;
ifstream f("graf.in");
ofstream g("graf.out");
int **a,n,m;
void citire(bool orientat=false)
{
    f>>n>>m;
    a = new int*[n];
    for(int i=0; i<n; i++)
        a[i] = new int[n];
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            a[i][j]=0;
    int x,y;
    for(int i=0; i<m; i++)
    {
        f>>x>>y;
        x--;
        y--;
        a[x][y] = 1;
        if(!orientat)
            a[y][x] = 1;
    }
}
void afisare()
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
            cout<<a[i][j]<< ' ';
        cout<<endl;
    }
}
void DFs(int x, int *viz, vector<int> &parc_df,int *&d,int *&tata){
    viz[x]=1;
    parc_df.push_back(x+1);
    for (int i=0;i<n;i++){
		if(a[x][i])
            if (viz[i]==0)
            {
                tata[i]=x;
                d[i]=d[x]+1;
                DFs(i,viz,parc_df,d,tata);
            }
    }
}

void DF(vector<int> &parc_df,int *&d,int *&tata, int s=1){
    int *viz=new int[n];
    tata=new int[n+1];
	d=new int[n+1];
	parc_df.clear();
	for(int i=0;i<n;i++){
		tata[i]=d[i]=-1;
		viz[i]=0;
	}
	s--;
    d[s]=0;
    DFs(s,viz,parc_df,d,tata);
}

void BF(vector<int> &parc_bf,int *&d,int *&tata, int s=1)
{
	parc_bf.clear();
	int i,*viz=new int[n];
	tata=new int[n+1];
	d=new int[n+1];
	for(i=0;i<n;i++){
		tata[i]=d[i]=-1;
		viz[i]=0;
	}
	s--;
	queue<int> c;
	c.push(s);
	viz[s]=1;
	d[s]=0;

	while(c.size()>0)
	{
		int x=c.front();//x- nodul curent
		c.pop();
		parc_bf.push_back(x+1);
		for (i=0;i<n;i++){
			if(a[x][i])
                if(viz[i]==0)
				{
					viz[i]=1;
					tata[i]=x;
					d[i]=d[x]+1;
					c.push(i);
				}
		}
	}
}

void afis(vector<int> parc_bf,int *d,int *tata){
	int i;
	for(i=0;i<parc_bf.size();i++)
	    cout<<parc_bf[i]<<" ";
	cout<<endl;
	for(i=0;i<n;i++)
	    cout<<d[i]<<" ";
	cout<<endl;
	for(i=0;i<n;i++)
	    cout<<tata[i]<<" ";
	cout<<endl;
}
void step(int curent, int *tata)
{
    if(curent!=-1)
    {
        step(tata[curent], tata);
        g<<curent+1 << ' ';
    }
}
void distanta_min(int *d,int *tata)
{
    int x, y; //punctele in care trb sa ajung(1 din ele, cel mai apropiat) pe drum cel mai scurt
    f>>x>>y;
    cout<<endl<<x<<' '<<y<<endl;
    if(d[x-1]>d[y-1])
        swap(x,y);
    int curent = x-1;
    step(curent, tata);

}
int main()
{
    vector<int> parc_bf,parc_df;
	int s;
	int i,j;
	int *tata,*d;

    cout<<"neorientat"<<endl;
	citire();
    afisare();
    cout<<endl;
    s=1;
   	BF(parc_bf,d,tata,s);
   	afis(parc_bf,d,tata);

   	distanta_min(d, tata);

   	DF(parc_df,d,tata,s);
   	afis(parc_df,d,tata);
   	return 0;
}
