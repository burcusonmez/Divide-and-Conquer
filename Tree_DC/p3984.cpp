#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<queue>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,ll> pil;
const int N=100005,Inf=1e9;
const db eps=0.000000001;

int Tote,Last[N],End[N<<1],Next[N<<1];
db Len[N<<1];
void Ins(int x,int y,int z){
	End[++Tote]=y;
	Len[Tote]=z;
	Next[Tote]=Last[x];
	Last[x]=Tote;
}

int n,m,L,U;
int Minn,Rt,tot,Size[N];
bool Vis[N];
db Ans;
void GetSize(int x,int fa){
	Size[x]=1;
	for(int i=Last[x],u;i;i=Next[i])
	if((u=End[i])!=fa&&!Vis[u])GetSize(u,x),Size[x]+=Size[u];
}
void GetRoot(int x,int tot,int fa){
	int Maxx=tot-Size[x],i,u;
	for(i=Last[x];i;i=Next[i])
	if((u=End[i])!=fa&&!Vis[u])GetRoot(u,tot,x),Maxx=max(Maxx,Size[u]);
	if(Maxx<Minn)Minn=Maxx,Rt=x;
}
void GetDis(int x,int h,ll d,int fa){
	S[++tot].first=h,S[tot].second=d;
	for(int i=Last[x],u;i;i=Next[i])
	if((u=End[i])!=fa&&!Vis[u])GetDis(u,h+1,d+Len[i],x);
}
void ModEdg(int x,db d,int fa){
	for(int i=Last[x],u;i;i=Next[i])
	if((u=End[i])!=fa&&!Vis[u])Len[i]+=d,ModEdg(u,d,x);
}
void GetAns(int x,ll d){
	int i,u;
	db L=1.0,R=1000000.0,mid,ans,tmp,maxx;
	priority_queue<db>q;
	while(fabs(R-L)>=eps){
		while(q.size())q.pop();
		q.push(0.0);
		mid=(L+R)/2;
		ModEdg(x,-mid,0);
		for(i=Last[x];i;i=Next[i])
			if(!Vis[u=End[i]]){
				GetMax(u,tmp,0);
				tmp+=Len[i];
			}
		if(maxx>eps)ans=mid,L=mid;
		else R=mid;
		ModEdg(x,mid,0);
	}
	Ans=max(Ans,ans);
}
void TT(int x){
	Vis[x]=1;
	GetAns(x);
	for(int i=Last[x],u;i;i=Next[i])
		if(!Vis[u=End[i]]){
			GetAns(u,Len[i]);
			Minn=Inf;
			GetSize(u,0);
			GetRoot(u,Size[u],0);
			TT(Rt);
		}
}
int main(){
	int i,j,k,x,y,z;
	scanf("%d%d%d",&n,&L,&U);
	for(i=1;i<n;i++){
		scanf("%d%d%d",&x,&y,&z);
		Ins(x,y,z),Ins(y,x,z);
	}
	Minn=Inf;
	GetSize(1,0);
	GetRoot(1,n,0);
	TT(Rt);
	printf("%.3lf",Ans);
}