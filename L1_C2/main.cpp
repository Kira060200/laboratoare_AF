#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;
ifstream f("graf.in");
ofstream g("graf.out");
int **a,n,m;
bool cycle=false;
int *viz;
int head=-1;
int tail=-1;
vector<int> stv;
int found = -1;
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
void afis_cycle()
{
    for(int i=found; i<stv.size();i++)
        g<<stv[i]+1<<' ';
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
void DFs(int x, int *viz, vector<int> &parc_df)
{
    viz[x]=1;
    parc_df.push_back(x+1);
    stv.push_back(x);
    for (int i=0;i<n;i++)
    {
		if(a[x][i]&&!cycle)
		{
            if (viz[i])
            {
                for(int j=0;j<stv.size();j++)
                    if(stv[j]==i)
                        found = j;
                if (found!=-1)
                {
                    cycle = true;
                    cout<<"Stack:"<<endl;
                    for(i=0;i<stv.size();i++)
                        cout<<stv[i]<< ' ';
                    cout<<endl;
                    afis_cycle();
                }
            }
            else if (viz[i]==0)
            {
                DFs(i,viz,parc_df);
            }
        }
    }
    stv.pop_back();
}

void DF(vector<int> &parc_df, int s=1)
{
    viz=new int[n];
	parc_df.clear();
	for(int i=0;i<n;i++)
		viz[i]=0;
	s--;
    DFs(s,viz,parc_df);
}
void afis(vector<int> parc_bf)
{
	int i;
	for(i=0;i<parc_bf.size();i++)
	    cout<<parc_bf[i]<<" ";
	cout<<endl;
}
int main()
{
    vector<int> parc_bf,parc_df;
	int s;
	citire(true);
    //afisare();
    cout<<endl;
    s=1;
    DF(parc_df,s);
    for(int i=0;i<n;i++) //daca am trecut prin toate nodurile (atunci cand nu e conex)
        if(!viz[i] && !cycle)
            DF(parc_df,i+1);
    if(found==-1)
        g<<"REALIZABIL";
    //afis(parc_df);
   	return 0;
}
