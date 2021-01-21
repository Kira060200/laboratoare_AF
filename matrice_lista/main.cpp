#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
ifstream f("graf.in");
int **a,n,m;
vector<int> *la;
void citire_matrice(bool orientat)
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
void afisare_matrice()
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
            cout<<a[i][j]<< ' ';
        cout<<endl;
    }
}

void citire_liste(int orientat=0)
{
	int x,y,m;
	f>>n>>m;
    la=new vector<int>[n];

	while(f>>x>>y)
	{
		x--;y--;
		la[x].push_back(y);
		if (not orientat)
		    la[y].push_back(x);
	}
	f.close();
}
void afisare_liste()
{
	int i,j;
	for(i=0;i<n;i++)
	{
		cout<<i+1<<": ";
		for(j=0;j<la[i].size();j++)
			cout<<la[i][j]+1<<" ";
		cout<<endl;
	}
}

void m_to_l()
{
    la=new vector<int>[n];
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            if(a[i][j])
                la[i].push_back(j);
}
void l_to_m()
{
    a = new int*[n];
    for(int i=0; i<n; i++)
        a[i] = new int[n];
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            a[i][j]=0;
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<la[i].size();j++)
            a[i][la[i][j]]=1;
    }
}
int main()
{
    //citire_matrice(false);
    //m_to_l();
    //afisare_liste();
    citire_liste();
    l_to_m();
    afisare_matrice();
    return 0;
}
