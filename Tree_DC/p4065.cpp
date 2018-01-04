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
	void Maintain(){while(Q.size()&&E.size()&&Q.top()==E.top())Q.pop(),E.pop();}
	int top(){Maintain();return Q.top();}
	void del(int x){E.push(x);}
	void push(int x){Q.push(x);}
	int size(){return Q.size()-E.size();}
	int getmax(){
		Maintain();
		int t=Q.top(),rt=t;Q.pop();
		Maintain();
		rt+=Q.top(),Q.push(t);
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
	Dis[x][Dep[k]]=d;
	C[k].push(Dis[x][Dep[k]-1]);
	for(int i=Last[x],u;i;i=Next[i])
	if((u=End[i])!=fa&&!Vis[u])GetDis(u,k,d+1,x);
}
void GetTree(int x){
	Vis[x]=1;
	Dep[x]=Dep[Fa[x]]+1;
	GetDis(x,x,0,0);
	for(int u,t,i=Last[x];i;i=Next[i])
		if(!Vis[u=End[i]]){
			GetPre(u);
			Fa[Rt]=x;t=Rt;
			GetTree(Rt);
			B[x].push(C[t].top());
		}
	B[x].push(0);
	if(B[x].size()>1)Ans.push(B[x].getmax());
}
void Off(int x){
	if(B[x].size()>1)Ans.del(B[x].getmax());
	B[x].push(0);
	if(B[x].size()>1)Ans.push(B[x].getmax());
	for(int u=Fa[x],v=x;u;u=Fa[u],v=Fa[v]){
		if(B[u].size()>1)Ans.del(B[u].getmax());
		if(C[v].size())B[u].del(C[v].top());
		C[v].push(Dis[x][Dep[u]]);
		B[u].push(C[v].top());
		if(B[u].size()>1)Ans.push(B[u].getmax());
	}
}
void On(int x){
	if(B[x].size()>1)Ans.del(B[x].getmax());
	B[x].del(0);
	if(B[x].size()>1)Ans.push(B[x].getmax());
	for(int u=Fa[x],v=x;u;u=Fa[u],v=Fa[v]){
		if(B[u].size()>1)Ans.del(B[u].getmax());
		if(C[v].size())B[u].del(C[v].top());
		C[v].del(Dis[x][Dep[u]]);
		if(C[v].size())B[u].push(C[v].top());
		if(B[u].size()>1)Ans.push(B[u].getmax());
	}
}
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
		if(opt=='C'){
			scanf("%d",&x);
			if(A[x])Off(x);
			else On(x);
			A[x]^=1;
		}
		else if(Ans.size())printf("%d\n",Ans.top());
		else puts("-1");
	}
}