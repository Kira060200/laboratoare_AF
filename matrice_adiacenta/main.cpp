#include <iostream>
#include <fstream>
using namespace std;
ifstream f("graf.in");
int **a,n,m;
void citire(bool orientat)
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
int main()
{
    citire(false);
    afisare();
    return 0;
}
