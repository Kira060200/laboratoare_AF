#include<fstream>
#include<vector>
#include<iostream>
#include<queue>
using namespace std;
int n,m;
vector<int> *la;
const char *nume_fisier="graf.in";
ifstream f(nume_fisier);
ofstream g("graf.out");
void citire(int orientat=0)
{
	int x,y;
	f>>n>>m;
    la=new vector<int>[n];

	for(int i=0;i<m;i++)
	{
        f>>x>>y;
		x--;y--;
		la[x].push_back(y);
		if (not orientat)
		    la[y].push_back(x);
	}
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

void DFs(int x, int *viz, vector<int> &parc_df,int *&d,int *&tata){
    viz[x]=1;
    parc_df.push_back(x+1);
    for (int i=0;i<la[x].size();i++){
		int y=la[x][i];
        if (viz[y]==0){
		     tata[y]=x;
             d[y]=d[x]+1;
             DFs(y,viz,parc_df,d,tata);
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
		for (i=0;i<la[x].size();i++){
			int y=la[x][i];//pentru toti vecinii y ai nodului curent x
			if(viz[y]==0)
				{
					viz[y]=1;
					tata[y]=x;
					d[y]=d[x]+1;
					c.push(y);
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
	vector<int> *la,parc_bf,parc_df;
	int s;
	int i,j;
	int *tata,*d;

    cout<<"neorientat"<<endl;
	citire();
    afisare_liste();
    s=1;
   	BF(parc_bf,d,tata,s);
   	afis(parc_bf,d,tata);

   	distanta_min(d, tata);

   	DF(parc_df,d,tata,s);
   	afis(parc_df,d,tata);
   	/*cout<<"orientat"<<endl;
	citire(n,la,1,"grafor.in" );
    afisare_liste(n,la);
    s=1;
   	BF(n,la,parc_bf,d,tata,s);	afis(n,parc_bf,d,tata);
	DF(n,la,parc_df,d,tata,s);
   	afis(n,parc_df,d,tata);
*/
}
