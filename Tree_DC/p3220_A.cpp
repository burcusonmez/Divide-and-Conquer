#include<stdio.h>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000005;
const ll Inf=9e18;

int Tote,Last[N],Len[N<<1],Next[N<<1],End[N<<1];
int Root,Rt;
ll Minn;
int Fa[N],Dep[N],Size[N],Si[N],Dis[N][30];
ll Sum[N];
bool Vis[N];

void Ins(int x,int y,int z){
	End[++Tote]=y;
	Len[Tote]=z;
	Next[Tote]=Last[x];
	Last[x]=Tote;
}
void GetSize(int x,int fa){
	Si[x]=1;
	for(int i=Last[x];i;i=Next[i])
	if(!Vis[End[i]]&&End[i]!=fa)GetSize(End[i],x),Si[x]+=Si[End[i]];
}
void GetRoot(int x,int tot,int fa){
	int Maxx=tot-Si[x];
	for(int i=Last[x];i;i=Next[i])
	if(End[i]!=fa&&!Vis[End[i]])GetRoot(End[i],tot,x),Maxx=max(Maxx,Si[End[i]]);
	if(Maxx<Minn)Minn=Maxx,Rt=x;
}
void GetDis(int x,int k,ll d,int fa){
	Dis[x][Dep[k]]=d;
	Sum[k]+=d-Dis[x][Dep[k]-1];
	for(int i=Last[x];i;i=Next[i])
	if(End[i]!=fa&&!Vis[End[i]])GetDis(End[i],k,d+Len[i],x);
}
void GetPre(int x){
	Minn=Inf;
	GetSize(x,0);
	GetRoot(x,Si[x],0);
}
int GetTree(int x){
	Vis[x]=1;Size[x]=1;
	Dep[x]=Dep[Fa[x]]+1;
	GetDis(x,x,0,0);
	for(int i=Last[x],u;i;i=Next[i]){
		u=End[i];
		if(!Vis[u]){
			GetPre(u);
			Fa[Rt]=x;
			Size[x]+=GetTree(Rt);
		}
	}
	return Size[x];
}
ll Query(int x){
	ll sum=0;
	for(int u=x;u;u=Fa[u])
		sum+=Sum[u]+Size[u]*(Dis[x][Dep[u]]-Dis[x][Dep[u]-1]);
	return sum;
}
int n,tot;
ll Ans[N];
int main(){
	int i,j,k,x,y,z;
	scanf("%d",&n);
	for(i=1;i<n;i++){
		scanf("%d%d%d",&x,&y,&z);
		Ins(x,y,z),Ins(y,x,z);
	}
	GetPre(1);
	Root=Rt;
	GetTree(Root);
	Minn=Inf;
	for(i=1;i<=n;i++)
		Ans[i]=Query(i),Minn=min(Minn,Ans[i]);
	for(i=1;i<=n;i++)
		if(Ans[i]==Minn)tot++;
	printf("%lld %d\n",Minn,tot);
	for(i=1;i<=n;i++)
		if(Ans[i]==Minn)printf("%d ",i);
}