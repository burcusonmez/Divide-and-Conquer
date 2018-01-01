#include<stdio.h>
#include<algorithm>
#include<string.h>
#include<vector>
using namespace std;
typedef pair<int,int> pii;
const int N=300005;

int n,m,K,A[N];

int Tote,Last[N],Next[N],End[N],Len[N];
void Ins(int x,int y,int z){
	End[++Tote]=y;
	Len[Tote]=z;
	Next[Tote]=Last[x];
	Last[x]=Tote;
}

//-----------TreePatition-------------

//Get Partition Tree
int Minn,Root,Rt,Dis,Vis[N],Size[N],Fa[N];
vector<pii>G[N],F[N];
void GetSize(int x,int fa){
	Size[x]=1;
	for(int i=Last[x],u;i;i=Next[i]){
		u=End[i];
		if(u!=fa&&!Vis[u]){
			GetSize(u,x);
			Size[x]+=Size[u];
		}
	}
}
void GetRoot(int x,int tot,int d,int fa){
	int Maxx=tot-Size[x],i,u;
	for(i=Last[x];i;i=Next[i]){
		u=End[i];
		if(u!=fa&&!Vis[u]){
			Maxx=max(Maxx,Size[u]);
			GetRoot(u,tot,d+Len[i],x);
		}
	}
	if(Maxx<Minn)Minn=Maxx,Rt=x,Dis=d;
}
void Pre(int x){
	Minn=1e9;
	GetSize(x,0);
	GetRoot(x,Size[x],0,0);
}
void GetTree(int x){
	Vis[x]=1;
	for(int u,i=Last[x];i;i=Next[i]){
		u=End[i];
		if(Vis[u])continue;
		Pre(u);
		G[x].push_back(pii(Rt,Len[i]+Dis));
		Fa[Rt]=x;
		GetTree(Rt);
	}
}

//Partion Tree Init
void GetSon(int x){
	F[x].push_back(pii(A[x],0));
	for(int u,i=0;i<G[x].size();i++){
		u=G[x][i].first;
		if(u==Fa[x])continue;
		GetSon(u);
		for(int j=0;j<F[u].size();j++)
			F[x].push_back(pii(F[u][j].first,F[u][j].second+G[x][i].second));
	}
	sort(F[x].begin(),F[x].end());
}
void GetPreSum(int x){
	for(int i=0;i<G[x].size();i++)
			GetPreSum(G[x][i].first);
	for(int i=1;i<F[x].size();i++)
		F[x][i].second+=F[x][i-1].second;
}
void GetNewSize(int x){
	Size[x]=1;
	for(int i=0;i<G[x].size();i++){
		GetNewSize(G[x][i].first);
		Size[x]+=Size[G[x][i].first];
	}
}
int GetAns(int x,int l,int r){
	while(x){

		x=Fa[x];
	}
}
int main(){
	int x,y,z,i,j,k,ans;
	scanf("%d%d%d",&n,&m,&K);
	for(i=1;i<=n;i++)scanf("%d",&A[i]);
	for(i=1;i<n;i++){
		scanf("%d%d%d",&x,&y,&z);
		Ins(x,y,z),Ins(y,x,z);
	}
	Pre(1);
	Root=Rt;
	GetTree(Rt);
	GetSon(Root);
	GetPreSum(Root);
	GetNewSize(Root);
	for(i=1;i<=m;i++){
		scanf("%d%d%d",&z,&x,&y);
		x=min((x+ans)%K,(y+ans)%K),y=max((x+ans)%K,(y+ans)%K);
		ans=GetAns(z,x,y);
		printf("%d\n",ans);
	}
}