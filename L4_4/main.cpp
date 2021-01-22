#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;
ifstream f("catun.in");
ofstream g("catun.out");

priority_queue< pair<int, int> , vector< pair<int, int> >, greater< pair<int, int> > > p_queue; //perechi cost destinatie
vector<vector< pair<int,int> >> v;
int *fort,*tata,*d;
int n,m,k,i,j,x,y,z,urm,cost;
bool *viz;

void citire()
{
	f>>n>>m>>k;
	d = new int[n];
	fort = new int[n];
	tata = new int[n];
	viz = new bool[n];
    for(i=0;i<=n;++i)
	{
        d[i] = INT_MAX;  //initializam vectorul de distante
        viz[i]=false;
        tata[i]=0;
        fort[i]=0;
        vector< pair<int,int> > tmp;
        v.push_back(tmp);
    }
	for(i=1;i<=k;++i) //citim fortaretele
	{
        f>>fort[i];
        d[fort[i]]=0;
        tata[fort[i]] = fort[i];
        p_queue.push(make_pair(0,fort[i])); //introducem perechea in coada de prioritati
	}
    for(i=0;i<m;++i)
	{
        f>>x>>y>>z;
        v[x].push_back(make_pair(y,z));
        v[y].push_back(make_pair(x,z));
    }
}
void dijkstra()
{
    while(!p_queue.empty())  //parcurgem coada de prioritat
    {
        pair<int,int> t = p_queue.top(); //luam varful
        p_queue.pop();
        int nod = t.second; //valoarea destinatiei
        if(!viz[nod])
        {
            viz[nod] = 1;

            for(i=0; i<v[nod].size(); ++i)  //parcurgem lista de noduri vecine
            {
                urm = v[nod][i].first; //salvam destinatia si costului nodului curent
                cost = v[nod][i].second;

                if (d[urm] > d[nod] + cost) //daca distanta vecinului e mai mare decat distanta curenta + costul
                {
                    //actualizam
                    d[urm] = d[nod] + cost;
                    tata[urm] = tata[nod];
                    p_queue.push(make_pair(d[urm], urm));
                }
                else if (d[urm] == d[nod] + cost) //daca sunt egale si tatal nodului e mai mic decat al vecinului
                    if (tata[nod] < tata[urm])
                        tata[urm] = tata[nod];   //actualizam tatal vecinului

            }
        }
    }
}
int main()
{
    citire();
    dijkstra();
    for(int i=1;i<=n;++i) //daca suntem in fortareata afisam 1
        if(i==tata[i])
            g<<0<<" ";
        else
            g<<tata[i]<<" ";

    return 0;

}
