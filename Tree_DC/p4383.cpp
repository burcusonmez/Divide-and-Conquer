#include<stdio.h>
#include<string.h>
#include<queue>
#include<vector>
#include<algorithm>
#include<map>
using namespace std;
const int N=30005,Inf=1e9;
#define Debug 0
//-----------Global-----------

int n,m,K,Ans1,Ans2;

//-----------Edge Data-----------

struct Data{
	int end,len;
	Data(){}
	Data(int y,int z):end(y),len(z){}
	bool operator < (const Data& a)const{return end<a.end;}
};
typedef vector<Data> vt;
typedef vt::iterator vi;
#define nd now->end
vt G[N],T[N];

//-----------Dijstra-----------

typedef pair<int,int> pii;
priority_queue<pii,vector<pii>,greater<pii> >q;
bool Mark[N];
int Dis[N],Path[N];
void GetTree(int x){
	Mark[x]=1;
	sort(G[x].begin(),G[x].end());
	for(vi now=G[x].begin();now!=G[x].end();now++)
		if(!Mark[nd]&&Dis[nd]==Dis[x]+now->len){
			T[x].push_back(Data(nd,now->len));
			T[nd].push_back(Data(x,now->len));
			GetTree(nd);
		}
}
void Dijstra(){
	int i,x,u;
	memset(Dis,0x3f,sizeof(Dis));

	Mark[1]=1,Dis[1]=0,q.push(pii(0,1));
	while(!q.empty()){
		x=q.top().second,q.pop(),Mark[x]=0;
		for(vi now=G[x].begin();now!=G[x].end();now++)
			if(Dis[nd]>Dis[x]+now->len){
				Dis[nd]=Dis[x]+now->len;
				if(!Mark[nd])Mark[nd]=1,q.push(pii(Dis[nd],nd));
			}
	}
	memset(Mark,0,sizeof(Mark));
	GetTree(1);
}

//-----------Tree Divide and Conquer-----------

#define ForEach(x) for(vi now=T[x].begin();now!=T[x].end();now++)
bool Vis[N];

//GetCenter
int Minn,Rt,sz[N];
void Getsz(int x,int fa){
	sz[x]=1;
	ForEach(x)
		if(!Vis[nd]&&nd!=fa)
			Getsz(nd,x),sz[x]+=sz[nd];
}
void GetRt(int x,int tot,int fa){
	int Maxx=tot-sz[x];
	ForEach(x)
		if(!Vis[nd]&&nd!=fa)
			GetRt(nd,tot,x),Maxx=max(Maxx,sz[nd]);
	if(Maxx<Minn)Minn=Maxx,Rt=x;
}
void GetCG(int x){
	Minn=Inf;
	Getsz(x,0);
	GetRt(x,sz[x],0);
}

//Ans
int Q[N],Max[N],Cnt[N],Dep[N],Fa[N];
void GetAns(int x,int sz){
	int MaxLen=0,i,j,k,u,tl,hd;
	for(i=1;i<=sz&&i<=K;i++)Max[i]=-Inf,Cnt[i]=0;
	Max[0]=0,Cnt[0]=1;
	ForEach(x)
		if(!Vis[nd]){

			//Take out
			hd=1,tl=0;
			Q[++tl]=nd,Dep[nd]=1,Dis[nd]=now->len,Fa[nd]=x;
			while(hd<=tl){
				u=Q[hd++];
				for(vi nxt=T[u].begin();nxt!=T[u].end();nxt++)
					if( nxt->end!=Fa[u] && !Vis[nxt->end] ){
						Dis[nxt->end]=Dis[u]+nxt->len;
						Dep[nxt->end]=Dep[u]+1;
						Fa[nxt->end]=u;
						Q[++tl]=nxt->end;
					}
			}

			//GetAns
			for(i=1;i<=tl;i++){
				u=Q[i],k=K-1-Dep[u];
				if(Dep[u]>K||k>MaxLen)continue;
				if(Dis[u]+Max[k]>Ans1)Ans1=Dis[u]+Max[k],Ans2=Cnt[k];
				else if(Dis[u]+Max[k]==Ans1)Ans2+=Cnt[k];
			}
			for(i=1;i<=tl;i++){
				u=Q[i],k=Dep[u];
				if(Dep[u]>K)continue;
				if(Dis[u]>Max[k])Max[k]=Dis[u],Cnt[k]=1;
				else if(Dis[u]==Max[k])Cnt[k]++;
			}
			MaxLen=max(MaxLen,Dep[Q[tl]]);
		}
}
void DC(int x,int sz){
	Vis[x]=1;
	GetAns(x,sz);
	ForEach(x)
		if(!Vis[nd]){
			GetCG(nd);
			DC(Rt,::sz[nd]);
		}
}
//-----------Main-----------

int main()
{
	int i,j,k,x,y,z;
	scanf("%d%d%d",&n,&m,&K);
	for(i=1;i<=m;i++){
		scanf("%d%d%d",&x,&y,&z);
		G[x].push_back(Data(y,z));
		G[y].push_back(Data(x,z));
	}
	Dijstra();

	GetCG(1);
	DC(Rt,n);
	printf("%d %d",Ans1,Ans2);
}