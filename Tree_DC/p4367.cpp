#include<stdio.h>
#include<algorithm>
#include<string.h>
#include<vector>
using namespace std;
typedef long long ll;
typedef pair<int,ll> pil;
const int N=300005;
const ll Inf=9e18;

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
int Root,Rt,Vis[N],Size[N],Fa[N],Dep[N];
ll Dis,Minn,FLen[N][30];
vector<int>G[N];
vector<pil>F[N][10];
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
void GetDis(int x,int k,int d,int fa){
	FLen[x][k]=d;
	for(int i=Last[x];i;i=Next[i])
		if(End[i]!=fa&&!Vis[End[i]])GetDis(End[i],k,d+Len[i],x);
}
void Pre(int x){
	Minn=Inf;
	GetSize(x,0);
	GetRoot(x,Size[x],0,0);
}
void GetTree(int x){
	Vis[x]=1;
	Dep[x]=Dep[Fa[x]]+1;
	GetDis(x,Dep[x],0,0);
	for(int u,i=Last[x];i;i=Next[i]){
		u=End[i];
		if(!Vis[u]){
			Pre(u);
			G[x].push_back(Rt);
			Fa[Rt]=x;
			GetTree(Rt);
		}
	}
}

//Partion Tree Init
void Collect(int x,int k,int d){
	F[k][d].push_back(pil(A[x],FLen[x][Dep[k]]));
	for(int i=0;i<G[x].size();i++)Collect(G[x][i],k,d);
}
void GetSon(int x){
	for(int i=0;i<G[x].size();i++){
		F[x][i].push_back(pil(-1,0));
		Collect(G[x][i],x,i);
		sort(F[x][i].begin(),F[x][i].end());
		for(int j=1;j<F[x][i].size();j++)F[x][i][j].second+=F[x][i][j-1].second;
	}
	for(int i=0;i<G[x].size();i++)GetSon(G[x][i]);
}

//Tree Partition
ll GetAns(int x,int l,int r){
	int i,j,k,a,b,u,v,o;
	ll ans=0;
	pil R=pil(r,Inf),L=pil(l,0);
	for(i=0;i<G[x].size();i++){
		b=upper_bound(F[x][i].begin(),F[x][i].end(),R)-F[x][i].begin()-1;
		a=lower_bound(F[x][i].begin(),F[x][i].end(),L)-F[x][i].begin()-1;
		ans+=F[x][i][b].second-F[x][i][a].second;
	}
	for(u=Fa[x],v=x,j=Dep[u];u;u=Fa[u],v=Fa[v],j--){
		if(A[u]>=l&&A[u]<=r)ans+=FLen[x][j];
		for(i=0;i<G[u].size();i++){
			o=G[u][i];
			if(o!=v){
				b=upper_bound(F[u][i].begin(),F[u][i].end(),R)-F[u][i].begin()-1;
				a=lower_bound(F[u][i].begin(),F[u][i].end(),L)-F[u][i].begin()-1;
				ans+=F[u][i][b].second-F[u][i][a].second;
				ans+=(b-a)*FLen[x][j];
			}
		}
	}
	return ans;
}

//----------End-----------

int main(){
	int x,y,z,i,j,k;
	ll ans=0;
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
	for(i=1;i<=m;i++){
		scanf("%d%d%d",&z,&x,&y);
		x=(ll)(x+ans)%K,y=(ll)(y+ans)%K;
		if(x>y)swap(x,y);
		ans=GetAns(z,x,y);
		printf("%lld\n",ans);
	}
}