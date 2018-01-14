#include<stdio.h>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
const int N=300005,Inf=1e9;

struct Data{
	int x,y,k,opt,id;
}A[N],Q[N],q1[N],q2[N];

typedef vector<int> vt;
typedef vt::iterator vi;
vt G[N];

int n,m,q,Ans[N];

ll c[N],tmp[N];
void Modify(int x,int d){
	for(int i=x;i<=m;i+=i&-i)c[i]+=d;
}
ll GetSum(int x){
	ll sum=0;
	for(int i=x;i>=1;i^=i&-i)sum+=c[i];
	return sum;
}
void DC(int hd,int tl,int l,int r){
	if(hd>tl)return;
	if(l==r){
		for(int i=hd;i<=tl;i++)Ans[Q[i].id]=l;
		return;
	}
	int i,j,k,t1=0,t2=0,mid=l+r>>1;
	for(i=l;i<=mid;i++){
		if(A[i].x<=A[i].y)Modify(A[i].x,A[i].k),Modify(A[i].y+1,-A[i].k);
		else Modify(1,A[i].k),Modify(A[i].y+1,-A[i].k),Modify(A[i].x,A[i].k);
	}
	for(i=hd;i<=tl;i++){
		k=Q[i].id,tmp[k]=0;
		for(vi it=G[k].begin();it!=G[k].end();it++){
			tmp[k]+=GetSum(*it);
			if(tmp[k]>=Q[i].k)break;
		}
		if(tmp[k]>=Q[i].k)q1[++t1]=Q[i];
		else Q[i].k-=tmp[k],q2[++t2]=Q[i];
	}
	for(i=l;i<=mid;i++){
		if(A[i].x<=A[i].y)Modify(A[i].x,-A[i].k),Modify(A[i].y+1,A[i].k);
		else Modify(1,-A[i].k),Modify(A[i].y+1,A[i].k),Modify(A[i].x,-A[i].k);
	}
	for(i=1;i<=t1;i++)Q[hd+i-1]=q1[i];
	for(i=1;i<=t2;i++)Q[hd+t1+i-1]=q2[i];
	DC(hd,hd+t1-1,l,mid);
	DC(hd+t1,tl,mid+1,r);
}
int main(){
	int i,j,k,x,y,z;
	scanf("%d%d",&n,&m);
	for(i=1;i<=m;i++){
		scanf("%d",&x);
		G[x].push_back(i);
	}
	for(i=1;i<=n;i++)scanf("%d",&Q[i].k),Q[i].id=i;
	scanf("%d",&q);
	for(i=1;i<=q;i++)scanf("%d%d%d",&A[i].x,&A[i].y,&A[i].k);
	A[q+1].x=1,A[q+1].y=m,A[q+1].k=Inf;
	DC(1,n,1,q+1);
	for(i=1;i<=n;i++)
		if(Ans[i]==q+1)puts("NIE");
		else printf("%d\n",Ans[i]);
}