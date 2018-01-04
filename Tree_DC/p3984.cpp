#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<queue>
using namespace std;
typedef double db;
const int N=100005,Inf=1e9;
const db eps=0.000000001;

struct Data{
	int end,dep;
	db len;
	Data() {}
	Data(int y,int z):end(y),len(z){}
	bool operator < (const Data& a)const{return dep<a.dep;}
};
typedef vector<Data> vt;
typedef vt::iterator vi;
vt G[N];

int n,m,L,U;
int Minn,Rt,tot,Size[N];
int q[N],h[N],Dep[N],Fa[N];
bool Vis[N];
db Ans,Max[N],Dis[N];
void GetSize(int x,int fa){
	Size[x]=1;
	for(vi now=G[x].begin();now!=G[x].end();now++)
	if(now->end!=fa&&!Vis[now->end])GetSize(now->end,x),Size[x]+=Size[now->end];
}
void GetRoot(int x,int tot,int fa){
	int Maxx=tot-Size[x],i,u;
	for(vi now=G[x].begin();now!=G[x].end();now++)
	if(now->end!=fa&&!Vis[now->end])GetRoot(now->end,tot,x),Maxx=max(Maxx,Size[now->end]);
	if(Maxx<Minn)Minn=Maxx,Rt=x;
}
bool Check(int x,db d){
	int i,u,v,tt,tl,hd,MaxL=0;
	for(vi now=G[x].begin();now!=G[x].end();now++)
		if(!Vis[now->end]){
			hd=1,tl=0;
			q[++tl]=now->end,Fa[now->end]=0,Dep[now->end]=1,Dis[now->end]=now->len-d;
			while(hd<=tl){
				u=q[hd++];
				for(vi nxt=G[u].begin();nxt!=G[u].end();nxt++)
					if(nxt->end!=Fa[u]&&!Vis[nxt->end]){
						Dis[nxt->end]=Dis[u]+nxt->len-d;
						Dep[nxt->end]=Dep[u]+1;
						Fa[nxt->end]=u;
						q[++tl]=nxt->end;
					}
			}
			hd=1,tt=0,v=MaxL;
			for(i=1;i<=tl;i++){
				u=q[i];
				while(v&&v+Dep[u]>=L){
					while(hd<=tt&&Max[h[tt]]<=Max[v])tt--;
					h[++tt]=v--;
				}
				while(hd<=tt&&h[hd]+Dep[u]>U)hd++;
				if(hd<=tt&&Max[h[hd]]+Dis[u]>=-eps)return 1;
			}
			for(i=MaxL+1;i<=Dep[q[tl]];i++)Max[i]=-Inf;
			for(i=1;i<=tl;i++)Max[Dep[q[i]]]=max(Max[Dep[q[i]]],Dis[q[i]]);
			MaxL=max(MaxL,Dep[q[tl]]);
		}
	return 0;
}
void GetDep(int x,int &t,int d,int fa){
	t=max(t,d);
	for(vi now=G[x].begin();now!=G[x].end();now++)
	if(!Vis[now->end]&&now->end!=fa)GetDep(now->end,t,d+1,x);
}
void GetAns(int x){
	int i,u;
	for(vi now=G[x].begin();now!=G[x].end();now++)
	if(!Vis[now->end])GetDep(now->end,now->dep,0,0);
	sort(G[x].begin(),G[x].end());
	db L=Ans,R=1000000.0,mid,ans,tmp,maxx;
	while(fabs(R-L)>=eps){
		mid=(L+R)/2;
		if(Check(x,mid))Ans=mid,L=mid;
		else R=mid;
	}
}
void TT(int x){
	Vis[x]=1;
	GetAns(x);
	for(vi now=G[x].begin();now!=G[x].end();now++)
		if(!Vis[now->end]){
			int u=now->end,t;
			Minn=Inf;
			GetSize(u,0);t=Size[u];
			if(t<L)continue;
			GetRoot(u,t,0);
			TT(Rt);
		}
}
int main(){
	int i,j,k,x,y,z;
	scanf("%d%d%d",&n,&L,&U);
	for(i=1;i<n;i++){
		scanf("%d%d%d",&x,&y,&z);
		G[x].push_back(Data(y,z));
		G[y].push_back(Data(x,z));
	}
	Minn=Inf;
	GetSize(1,0);
	GetRoot(1,n,0);
	TT(Rt);
	printf("%.3lf",Ans);
}