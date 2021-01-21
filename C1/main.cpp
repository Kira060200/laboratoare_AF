#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;
ifstream f("graf.in");
ofstream g("graf.out");
int **a,n,m;
bool cycle=false;
int *viz;
int head=-1;
int tail=-1;
int *tata,*d;
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
    f.close();
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
void DFs(int x, int *viz, vector<int> &parc_df,int *&d,int *&tata)
{
    viz[x]=1;
    parc_df.push_back(x+1);

    for (int i=0;i<n;i++)
    {
		if(a[x][i]&&!cycle)
		{
            if (viz[i] && tata[x]!=i)
            {
                head = i;
                tail = x;
                //cout<<endl<<endl<<tail<<' '<<head<<endl<<endl;
                cycle = true;
            }
            else if (viz[i]==0)
            {
                tata[i]=x;
                d[i]=d[x]+1;
                DFs(i,viz,parc_df,d,tata);
            }
        }
    }
}

void DF(vector<int> &parc_df,int *&d,int *&tata, int s=1)
{
    viz=new int[n];
    tata=new int[n+1];
	d=new int[n+1];
	parc_df.clear();
	for(int i=0;i<n;i++)
	{
		tata[i]=d[i]=-1;
		viz[i]=0;
	}
	s--;
    d[s]=0;
    DFs(s,viz,parc_df,d,tata);
}
void afis(vector<int> parc_bf,int *d,int *tata)
{
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
void afis_cycle(int x)
{
    if(x!=head)
    {
        afis_cycle(tata[x]);
        g<<x+1<<' ';
    }
    else
        g<<x+1<<' ';
}
int main()
{
    vector<int> parc_bf,parc_df;
	int s;

    cout<<"neorientat"<<endl;
	citire();
    //afisare();
    cout<<endl;
    s=1;
    DF(parc_df,d,tata,s);
        for(int i=0;i<n;i++) //daca am trecut prin toate nodurile (atunci cand nu e conex)
            if(!viz[i] && !cycle)
                DF(parc_df,d,tata,i+1);
    if(head!=-1)
        afis_cycle(tail);
    g<<head+1;
    //afis(parc_df,d,tata);
   	return 0;
}
