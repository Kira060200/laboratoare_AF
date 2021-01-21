#include <iostream>
#include <vector>
#include <fstream>
using namespace std;
ifstream f("graf.in");
int n;  //nr varfuri
int m;  //nr muchii
vector<int> adj[10000]; //lista adiacenta
bool viz[10000];
int* niv;
int* niv_min;   //cat de sus putem ajunge (mergand in sensul parcurgerii DFS)
int root; //radacina arbore DFS
bool pct_crit[1000];
void read()
{

    f>>n >> m;
    for(int i=0;i<m;i++)
    {
        int x,y;
        f>>x>>y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
}
void DFS_aux(int i)
{
    viz[i]=1;
    niv_min[i]=niv[i];
    int children = 0;
    for(int j=0; j<adj[i].size();j++)
    {
        int vecin=adj[i][j];
        if (viz[vecin]==0)
        {
            children ++;
            niv[vecin]=niv[i]+1;
            DFS_aux(vecin);
            niv_min[i]=min(niv_min[i],niv_min[vecin]);
            if (i == root && children >= 2) //Daca e radacina arboreului din DFS si are cel putin 2 copii atunci e pct de articulatie (critic)
               pct_crit[i]=true;
            else if(i != root && niv_min[vecin]>=niv[i]) //testam daca e punct critic
                    pct_crit[i]=true;
        }
        else if(niv[i]-1>niv[vecin]) //verificam daca nivelul nodului prin care am mai trecuta are un nivel mai mare decat nivelul nostru actual
                niv_min[i]=min(niv_min[i],niv[vecin]); //actualizam nivelul nostru minim
    }
}
void DFS(int nr_v)
{
    niv = new int[nr_v+1];
    niv_min = new int[nr_v+1];
    for(int i=1; i<=nr_v; i++)  //DFS pe toate componentele
        if(viz[i]==0)
        {
            niv[i]=1;
            root = 1;
            DFS_aux(i);
        }
}
int main()
{
    read();
    DFS(n);
    for(int i=1;i<=n;i++)
        if(pct_crit[i])
            cout<<i<<endl;
}
