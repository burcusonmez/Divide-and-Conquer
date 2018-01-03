#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<complex>
using namespace std;
typedef double db;
typedef complex<db> cp;
const int N=80005,Inf=1e9;
const db pi=3.14159265358;

//fft
cp f,g,fft_wi[N];
int fft_len;
void fft(cp A[],int ty){
	int i,j,k,m;
	for(i=0;i<fft_len;i++){
		for(j=0,k=i,m=1;m<fft_len;m<<=1,j=(j<<1)|(k&1),k>>=1);
		if(i<j)swap(A[i],A[j]);
	}
	fft_wi[0]=1;
	for(m=1;m<fft_len;m<<=1){
		f=exp(cp(0,ty*pi/m));
		for(i=1;i<m;i++)fft_wi[i]=fft_wi[i-1]*f;
		for(k=0;k<fft_len;k+=m<<1)
			for(i=k;i<k+m;i++){
				f=A[i],g=A[i+m]*fft_wi[i-k];
				A[i]=f+g,A[i+m]=f-g;
			}
	}
	if(ty==1)return;
	f=1.0/fft_len;
	for(i=0;i<fft_len;i++)A[i]*=f;
}
cp A[N],B[N];

int T,n,m,w[N];
int Tote,Last[N],Next[N],End[N];
void Ins(int x,int y){
	End[++Tote]=y;
	Next[Tote]=Last[x];
	Last[x]=Tote;
}
int Rt,Minn,Size[N];
int Cnt[N],Val[N],Ans[N];
bool Vis[N];
void GetSize(int x,int fa){
	Size[x]=1;
	for(int u,i=Last[x];i;i=Next[i])
	if((u=End[i])!=fa&&!Vis[u])GetSize(u,x),Size[x]+=Size[u];
}
void GetRoot(int x,int tot,int fa){
	int u,i,Maxx=tot-Size[x];
	for(i=Last[x];i;i=Next[i])
	if((u=End[i])!=fa&&!Vis[u])GetRoot(u,tot,x),Maxx=max(Maxx,Size[u]);
	if(Maxx<Minn)Minn=Maxx,Rt=x;
}
void GetCnt(int x,int d,int fa){
	Cnt[d]++;
	for(int u,i=Last[x];i;i=Next[i])
	if((u=End[i])!=fa&&!Vis[u])GetCnt(u,d+1,x);
}
void GetAns(int x,int d,int fa,int ty){
	Ans[x]+=ty*Val[d];
	for(int u,i=Last[x];i;i=Next[i])
	if((u=End[i])!=fa&&!Vis[u])GetAns(u,d+1,x,ty);
}
void GetVal(int len){
	int i,j;
	for(fft_len=1;fft_len<len*3+1;fft_len<<=1);
	for(i=0;i<fft_len;i++)A[i]=B[i]=0;
	for(i=0;i<len;i++)A[i]=Cnt[len-i-1];
	for(i=0;i<len*2;i++)B[i]=w[i];
	fft(A,1),fft(B,1);
	for(i=0;i<fft_len;i++)A[i]=A[i]*B[i];
	fft(A,-1);
	for(i=0;i<len;i++)Val[i]=floor(A[i+len-1].real()+0.5);
}
void TT(int x,int sz){
	int i,j,t,u;
	Vis[x]=1;
	GetCnt(x,0,0);
	GetVal(sz);
	GetAns(x,0,0,1);
	for(i=0;i<sz+5;i++)Cnt[i]=0;
	for(i=Last[x];i;i=Next[i])
		if(!Vis[u=End[i]]){
			Minn=Inf;
			GetSize(u,0);t=Size[u];
			GetCnt(u,0,0);
			GetVal(t+2);
			GetAns(u,2,0,-1);
			GetRoot(u,t,0);
			for(j=0;j<t+5;j++)Cnt[j]=0;
			TT(Rt,t);
		}
}
void Init(){
	Tote=0;
	memset(Last,0,sizeof(Last));
	memset(Vis,0,sizeof(Vis));
	memset(Ans,0,sizeof(Ans));
}
int main(){
	int i,j,k,x,y;
	scanf("%d",&T);
	while(T--){
		Init();
		scanf("%d",&n);
		for(i=0;i<n;i++)scanf("%d",&w[i]);
		for(i=1;i<n;i++){
			scanf("%d%d",&x,&y);
			Ins(x,y),Ins(y,x);
		}
		Minn=Inf;
		GetSize(1,0);
		GetRoot(1,n,0);
		TT(Rt,n);
		for(i=1;i<=n;i++)printf("%d ",Ans[i]);
		puts("");
	}
}