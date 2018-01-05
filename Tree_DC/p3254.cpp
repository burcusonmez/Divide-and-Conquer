#include<stdio.h>
#include<string.h>
#include<algorithm>
#include<vector>
#include<assert.h>
using namespace std;
typedef long long ll;
const int N=100005;

struct Data{
	int end,len;
	Data(){}Data(int y,int z):end(y),len(z){}
};
typedef vector<Data> vt;
typedef vt::iterator vi;
#define nd now->end

int n,m;
vt G[N];
int Minn,Rt,sz[N],Dep[N],Fa[N],CG[22][N];
ll Dis[22][N],Sum[N],Size[N];
bool Vis[N];
void Getsz(int x,int fa){
	sz[x]=1;
	for(vi now=G[x].begin();now!=G[x].end();now++)
	if(nd!=fa&&!Vis[nd])Getsz(nd,x),sz[x]+=sz[nd];
}
void GetRt(int x,int tot,int fa){
	int Maxx=tot-sz[x];
	for(vi now=G[x].begin();now!=G[x].end();now++)
	if(nd!=fa&&!Vis[nd])GetRt(nd,tot,x),Maxx=max(Maxx,sz[nd]);
	if(Maxx<Minn)Minn=Maxx,Rt=x;
}
void GetG(int x){
	Minn=1e9;
	Getsz(x,0);
	GetRt(x,sz[x],0);
}
void GetDis(int x,ll *t,ll d,int fa){
	t[x]=d;
	for(vi now=G[x].begin();now!=G[x].end();now++)
	if(nd!=fa&&!Vis[nd])GetDis(nd,t,d+now->len,x);
}
void SetRt(int x,int *t,int d,int fa){
	t[x]=d;
	for(vi now=G[x].begin();now!=G[x].end();now++)
	if(nd!=fa&&!Vis[nd])SetRt(nd,t,d,x);
}
void GetTree(int x){
	Vis[x]=1;
	Dep[x]=Dep[Fa[x]]+1;
	GetDis(x,Dis[Dep[x]],0,0);
	SetRt(x,CG[Dep[x]],x,0);
	for(vi now=G[x].begin();now!=G[x].end();now++)
		if(!Vis[nd]){
			GetG(nd);
			Fa[Rt]=x;
			GetTree(Rt);
		}
}
ll Query(int x){
	ll sum=0;
	for(int u=x;u;u=Fa[u])
		sum+=Sum[u]+Size[u]*(Dis[Dep[u]][x]-Dis[Dep[u]-1][x]);
	return sum;
}
void Modify(int x,int e){
	for(int u=x;u;u=Fa[u])
		Sum[u]+=e*(Dis[Dep[u]][x]-Dis[Dep[u]-1][x]),
		Size[u]+=e;
}
ll Find(int x,int fa){
	int u=0;
	Vis[x]=1;
	ll a=Query(x),t,rt;
	for(vi now=G[x].begin();now!=G[x].end();now++)
		if(!Vis[nd]){
			t=Query(nd);
			if(t<a)u=nd,a=t;
		}
	if(!u)rt=a;
	else rt=Find(CG[Dep[x]+1][u],x);
	Vis[x]=0;
	return rt;
}
int main(){
	int i,j,k,x,y,z;
	scanf("%d%d",&n,&m);
	for(i=1;i<n;i++){
		scanf("%d%d%d",&x,&y,&z);
		G[x].push_back(Data(y,z));
		G[y].push_back(Data(x,z));
	}
	GetG(1);
	GetTree(Rt);
	for(i=1;i<=n;i++)assert(Sum[i]==0);
	memset(Vis,0,sizeof(Vis));
	while(m--){
		scanf("%d%d",&x,&y);
		Modify(x,y);
		Query(x);
		printf("%lld\n",Find(CG[1][1],0));
	}
}