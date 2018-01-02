#include<stdio.h>
#include<algorithm>
#include<queue>
using namespace std;
const int N=100005,Inf=1e9;

int n,m;
bool A[N];

int Tote,Last[N],Next[N<<1],End[N<<1];
void Ins(int x,int y){
	End[++Tote]=y;
	Next[Tote]=Last[x];
	Last[x]=Tote;
}

//TT
struct Heap{
	priority_queue<int>Q,E;
	void Maintain(){while(Q.top()==E.top())Q.pop(),E.pop();}
	int top(){Maintain();return Q.top();}
	void del(int x){E.push(x);}
	void push(int x){Q.push(x);}
	int size(){Maintain();return Q.size();}
	int getmax(){
		if(size()<2)return -1;
		int t=Q.top(),rt=t;
		Q.pop(),rt+=Q.top(),Q.push(t);
		return rt;
	}
}Ans,B[N],C[N];

int Minn,Rt,Root;
int Dep[N],Size[N],Fa[N],Dis[N][30];
bool Vis[N];
void GetSize(int x,int fa){
	Size[x]=1;
	for(int u,i=Last[x];i;i=Next[i])
	if((u=End[i])!=fa&&!Vis[u])GetSize(u,x),Size[x]+=Size[u];
}
void GetRoot(int x,int tot,int fa){
	int i,u,Maxx=tot-Size[x];
	for(i=Last[x];i;i=Next[i])
	if((u=End[i])!=fa&&!Vis[u])GetRoot(u,tot,x),Maxx=max(Maxx,Size[u]);
	if(Maxx<Minn)Minn=Maxx,Rt=x;
}
void GetPre(int x){
	Minn=Inf;
	GetSize(x,0);
	GetRoot(x,Size[x],0);
}
void GetDis(int x,int k,int d,int fa){
	Dis[x][k]=d;
	for(int i=Last[x],u;i;i=Next[i])
	if((u=End[i])!=fa&&!Vis[u])GetDis(u,k,d+1,x);
}
void GetTree(int x){
	Vis[x]=1;
	Dep[x]=Dep[Fa[x]]+1;
	GetDis(x,Dep[x],0,0);
	for(int u,i=Last[x];i;i=Next[i])
		if(!Vis[u=End[i]]){
			GetPre(u);
			Fa[Rt]=x;
			GetTree(Rt);
		}
}
void Add(int x){

int main(){
	int i,j,k,x,y;
	char opt;
	scanf("%d",&n);
	for(i=1;i<n;i++){
		scanf("%d%d",&x,&y);
		Ins(x,y),Ins(y,x);
	}
	GetPre(1);
	Root=Rt;
	GetTree(Root);
	scanf("%d",&m);
	while(m--){
		opt=getchar();
		while(opt<'A'||opt>'Z')opt=getchar();
		if(opt=='C')scanf("%d",&x),Modify(x);
		else if(Ans.size())printf("%d\n",Ans.top());
		else puts("-1");
	}
}