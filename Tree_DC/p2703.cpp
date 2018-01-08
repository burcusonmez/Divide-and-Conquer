#include<stdio.h>
#include<assert.h>
#include<string.h>
#include<vector>
#include<stack>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=100005,Inf=1e9;
#define DEBUG 0
#define BREAK 18
//-----------SBT-----------

struct Node{
	Node* Son[2];
	int Val,Size;
}*T1[N],*T2[N],*null,*tl,pool[N<<7];
stack<Node*>Bin;
void Init_SBT(int sz){
	tl=null=pool;
	for(int i=1;i<=sz;i++)T1[i]=T2[i]=null;
	null->Son[0]=null->Son[1]=null;
	null->Val=null->Size=0;
}
void Rotate(Node* &x,int l){
	int r=l^1;
	Node* y=x->Son[r];
	x->Son[r]=y->Son[l];
	y->Son[l]=x;
	y->Size=x->Size;
	x->Size=x->Son[0]->Size+x->Son[1]->Size+1;
	x=y;
}
void Maintain(Node* &x,bool flag){
	if(flag){
		if(x->Son[1]->Son[1]->Size>x->Son[0]->Size)
			Rotate(x,0);
		else if(x->Son[1]->Son[0]->Size>x->Son[0]->Size)
			Rotate(x->Son[1],1),Rotate(x,0);
		else return;
	}
	else{
		if(x->Son[0]->Son[0]->Size>x->Son[1]->Size)
			Rotate(x,1);
		else if(x->Son[0]->Son[1]->Size>x->Son[1]->Size)
			Rotate(x->Son[0],0),Rotate(x,1);
		else return;
	}
	Maintain(x->Son[0],0);
	Maintain(x->Son[1],1);
	Maintain(x,0);
	Maintain(x,1);
}
void Insert(Node* &x,int v){
	if(x==null){
		if(!Bin.empty())x=Bin.top(),Bin.pop();
		else x=++tl;
		x->Son[0]=x->Son[1]=null;
		x->Val=v,x->Size=1;
		return;
	}
	x->Size++;
	bool l=v>x->Val;
	Insert(x->Son[l],v);
	Maintain(x,l);
}
ll GetSum(Node* x,int k){
	ll sum=0;
	while(x!=null){
		if(k<x->Val)x=x->Son[0];
		else sum+=x->Son[0]->Size+1,x=x->Son[1];
	}
	return sum;
}
void Collect(Node* x){
	Bin.push(x);
	if(x->Son[0]!=null)Collect(x->Son[0]);
	if(x->Son[1]!=null)Collect(x->Son[1]);
}

void Print(Node* x){
	if(x->Son[0]!=null)Print(x->Son[0]);
	printf("%d ",x->Val);
	if(x->Son[1]!=null)Print(x->Son[1]);
}
//-----------Globals-----------

int T,n,Totn;
int D[N];
ll Ans;

//-----------Tree Divide & Conquer-----------

//Point Informations
struct Data{
	int end,len;
	Data(){}
	Data(int y,int z):end(y),len(z){}
};
typedef vector<Data> vt;
typedef vt::iterator vi;
#define nd now->end

vt G[N];
int Size[N],Fa[N],Dep[N];
bool Vis[N];

//Tree DC Data
int CG[35][N];
ll Dis[35][N];

//ReBuild
int Minn,Rt,sz[N];
void Getsz(int x,int fa){
	sz[x]=1;
	for(vi now=G[x].begin();now!=G[x].end();now++)
	if(!Vis[nd]&&nd!=fa)Getsz(nd,x),sz[x]+=sz[nd];
}
void GetRt(int x,int tot,int fa){
	int Maxx=tot-sz[x];
	for(vi now=G[x].begin();now!=G[x].end();now++)
	if(!Vis[nd]&&nd!=fa)GetRt(nd,tot,x),Maxx=max(Maxx,sz[nd]);
	if(Maxx<Minn)Minn=Maxx,Rt=x;
}
void GetPre(int x){
	Minn=1e9;
	Getsz(x,0);
	GetRt(x,sz[x],0);
}
void GetData(int x,ll *dis,ll *predis,int *cg,int k,ll d,int fa){
	dis[x]=d;cg[x]=k;
	Insert(T1[k],dis[x]-D[x]);
	Insert(T2[k],predis[x]-D[x]);
	for(vi now=G[x].begin();now!=G[x].end();now++)
	if(!Vis[nd]&&nd!=fa)GetData(nd,dis,predis,cg,k,d+now->len,x);
}
int GetTree(int x){
	Vis[x]=1,Size[x]=1;
	Dep[x]=Dep[Fa[x]]+1;
#if DEBUG
	for(int i=Dep[x]+1;i<=30;i++)CG[i][x]=0,Dis[i][x]=0;
#endif
	GetData(x,Dis[Dep[x]],Dis[Dep[x]-1],CG[Dep[x]],x,0,0);
	for(vi now=G[x].begin();now!=G[x].end();now++)
		if(!Vis[nd]){
			GetPre(nd);
			Fa[Rt]=x;
			Size[x]+=GetTree(Rt);
		}
	return Size[x];
}
void Clean(int x,int k,int fa){
	Vis[x]=0;
	if(T1[x]!=null)Collect(T1[x]);
	if(T2[x]!=null)Collect(T2[x]);
	T1[x]=T2[x]=null;
	for(vi now=G[x].begin();now!=G[x].end();now++)
	if(CG[Dep[k]][nd]==k&&nd!=fa)Clean(nd,k,x);
}
void ReBuild(int x){			//ReBuild the DC tree from the root x
	Clean(x,x,0);
	GetPre(x);
	Fa[Rt]=Fa[x];
	GetTree(Rt);
}
bool Isbad(int x){
	return (double)Size[x]>(double)Size[Fa[x]]*0.8;
}

//-----------Dymatic Querys-----------

void AddPoint(int fa,int d,int r){
	int x=++Totn,u,v,t=0,i;

	//init point Data
	if(fa){
		G[x].push_back(Data(fa,d));
		G[fa].push_back(Data(x,d));
	}
	D[x]=r;
	Fa[x]=fa;
	Dep[x]=Dep[fa]+1;
	Vis[x]=1;
	Size[x]=1;
	for(u=Fa[x];u;u=Fa[u])Size[u]++;

	//init TreeDc Data
	Dis[0][x]=Inf;
	for(u=Fa[x];u;u=Fa[u]){
		CG[Dep[u]][x]=u;
		Dis[Dep[u]][x]=Dis[Dep[u]][fa]+d/* lca_getdis(u,x) */;
	}

	//init SBT Data
	for(u=x;u;u=Fa[u]){
		Insert(T1[u],Dis[Dep[u]][x]-D[x]);
		Insert(T2[u],Dis[Dep[u]-1][x]-D[x]);
	}

	//If rebuild
	for(u=x;Fa[u];u=Fa[u])
		if(Isbad(u)||Dep[u]>30)t=Fa[u];
	if(t)ReBuild(t);
#if DEBUG
	if(t)printf("ReBuilt :: %d\n",t);
#endif
}
void Query(int x){
	if(D[x]>0)Ans--;
	for(int u=x;u;u=Fa[u])
		Ans+=GetSum(T1[u],D[x]-Dis[Dep[u]][x])-GetSum(T2[u],D[x]-Dis[Dep[u]-1][x]);
}


int main(){
	// freopen("ex_flower2.in","r",stdin);
	int i,j,k,a,b,c;
	scanf("%d",&T);
	scanf("%d",&n);
	Init_SBT(n);
	for(i=1;i<=n;i++){
		scanf("%d%d%d",&a,&b,&c);
		a=(ll)a^(Ans%Inf);
#if DEBUG
		if(i==BREAK){
			// for(j=1;j<=BREAK;j++)Print(T1[j]),puts("");
			// puts("");
			// for(j=1;j<=BREAK;j++)Print(T2[j]),puts("");
			// puts("");
		}
#endif
		AddPoint(a,b,c);
#if DEBUG
		if(i==BREAK){
			// for(j=1;j<=BREAK;j++)Print(T1[j]),puts("");
			// puts("");
			// for(j=1;j<=BREAK;j++)Print(T2[j]),puts("");
			// puts("");
			for(j=1;j<=BREAK;j++)printf("%d ",Fa[j]);
			puts("");

		}
#endif
		Query(Totn);
		printf("%lld\n",Ans);
#if DEBUG
		if(i==18)break;
#endif
	}
}
