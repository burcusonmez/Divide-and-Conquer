#include<stdio.h>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
const int N=1000005;
const ll Inf=9e18;

int Tote,Last[N],End[N<<1],Len[N<<1],Next[N<<1];
void Ins(int x,int y,int z){
	End[++Tote]=y;
	Len[Tote]=z;
	Next[Tote]=Last[x];
	Last[x]=Tote;
}
ll Size[N],Sum[N],Ans[N],Minn;
void Dfs1(int x,int fa){
	Size[x]=1;
	for(int u,i=Last[x];i;i=Next[i]){
		u=End[i];
		if(u!=fa){
			Dfs1(u,x);
			Size[x]+=Size[u];
			Sum[x]+=Sum[u]+Size[u]*Len[i];
		}
	}
}
int n,tot;
void Dfs2(int x,ll d,int fa){
	Ans[x]+=Sum[x]+d;
	for(int u,i=Last[x];i;i=Next[i])
	if((u=End[i])!=fa)Dfs2(u,d+Sum[x]-(Sum[u]+Size[u]*Len[i])+(n-Size[u])*Len[i],x);
}
int main(){
	int i,j,k,x,y,z;
	scanf("%d",&n);
	for(i=1;i<n;i++){
		scanf("%d%d%d",&x,&y,&z);
		Ins(x,y,z),Ins(y,x,z);
	}
	Dfs1(1,0);
	Dfs2(1,0,0);
	Minn=Inf;
	for(i=1;i<=n;i++)
		Minn=min(Minn,Ans[i]);
	for(i=1;i<=n;i++)
		if(Ans[i]==Minn)tot++;
	printf("%lld %d\n",Minn,tot);
	for(i=1;i<=n;i++)
		if(Ans[i]==Minn)printf("%d ",i);
}