#include <iostream>
#include <fstream>
#include <queue>
using namespace std;
//directii
int tl[] = {-1, 0, 1, 0, 1, 1, -1, -1};
int tc[] = {0, 1, 0, -1, 1, -1, -1, 1};
//linii, coloane, matrice julieta, matrice romeo, start point romeo, start point julieta
int n, m, vj[105][105], vr[105][105], stxr, styr, stxj, styj;
int minx=100005, miny=100005, mint=100005;
queue<int>x, y;
string s;
ifstream f("rj.in");
ofstream g("rj.out");
void citire()
{
    f>>n>>m;
    f.ignore();
    for(int i=0;i<n;i++)
    {
        getline(f, s);
        for(int j=0;j<m;j++)
        {
            if(s[j]=='X')
            {
                vr[i][j]=-1;
                vj[i][j]=-1;
            }
            else if(s[j]==' ')
            {
                vr[i][j]=0;
                vj[i][j]=0;
            }
            else if(s[j]=='R')
            {
                stxr=i;
                styr=j;
                vj[i][j]=-1;
            }
            else
            {
                stxj=i;
                styj=j;
                vr[i][j]=-1;
            }
        }
    }
}
void lee(int stx, int sty, int v[105][105])
{
    int xx, yy, curx, cury;
    curx=stx;
    cury=sty;
    x.push(stx);
    y.push(sty);
    v[stx][sty]=1;
    while(!x.empty())
    {
        curx=x.front();
        cury=y.front();
        for(int i=0;i<8;i++)
        {
            xx=curx+tl[i];
            yy=cury+tc[i];
            if(xx<=n&&yy<=m&&xx>=0&&yy>=0&&v[xx][yy]==0)
            {
                v[xx][yy]=v[curx][cury]+1;
                x.push(xx);
                y.push(yy);
            }
        }
        x.pop();
        y.pop();
    }
}
int main()
{
    citire();
    //lee pe matricea lui Romeo
    lee(stxr, styr, vr);
    //lee pe matricea lui Julieta
    lee(stxj, styj, vj);
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            //Daca au ajuns in acelasi punct si punctul a fost vizitat
            if(vj[i][j]==vr[i][j]&&vj[i][j]>=1)
            {
                if(vj[i][j]<mint)
                {
                    minx=i;
                    miny=j;
                    mint=vj[i][j];
                }
            }
        }
    }
    g<<mint<<" "<<minx+1<<" "<<miny+1;
    return 0;
}
