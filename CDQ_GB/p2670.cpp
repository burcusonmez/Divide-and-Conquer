#include<stdio.h>
#include<algorithm>
using namespace std;
const int N=200005;

struct Data{
	int x,y,k,opt,id;
}Q[N],q1[N],q2[N];
int n,m,tot,qr,a[N],Ans[N],tmp[N];
int c[N];
void modify(int x,int d){
	for(int i=x;i<=n;i+=i&-i)c[i]+=d;
}
int getsum(int x){
	int sum=0;
	for(int i=x;i>=1;i^=i&-i)sum+=c[i];
	return sum;
}
void DC(int hd,int tl,int l,int r){
	if(hd>tl)return;
	if(l==r){
		for(int i=hd;i<=tl;i++)
			if(Q[i].opt==3)Ans[Q[i].id]=l;
		return;
	}
	int i,j,k,tl1=0,tl2=0,mid=l+r>>1;
	for(i=hd;i<=tl;i++){
		if(Q[i].opt==1&&Q[i].y<=mid)modify(Q[i].x,1);
		else if(Q[i].opt==2&&Q[i].y<=mid)modify(Q[i].x,-1);
		else if(Q[i].opt==3)tmp[i]=getsum(Q[i].y)-getsum(Q[i].x-1);
	}
	for(i=hd;i<=tl;i++){
		if(Q[i].opt==1&&Q[i].y<=mid)modify(Q[i].x,-1);
		else if(Q[i].opt==2&&Q[i].y<=mid)modify(Q[i].x,1);
	}
	for(i=hd;i<=tl;i++){
		if(Q[i].opt==3){
			if(tmp[i]>=Q[i].k)q1[++tl1]=Q[i];
			else Q[i].k-=tmp[i],q2[++tl2]=Q[i];
		}
		else{
			if(Q[i].y<=mid)q1[++tl1]=Q[i];
			else q2[++tl2]=Q[i];
		}
	}
	for(i=1;i<=tl1;i++)Q[hd+i-1]=q1[i];
	for(i=1;i<=tl2;i++)Q[hd+tl1+i-1]=q2[i];
	DC(hd,hd+tl1-1,l,mid);
	DC(hd+tl1,tl,mid+1,r);
}
int main(){
	int i,j,k,x,y,z,maxx=0;
	char opt;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++){
		scanf("%d",&a[i]);
		maxx=max(maxx,a[i]);
		Q[++tot].x=i,Q[tot].y=a[i];
		Q[tot].opt=1;
	}
	for(i=1;i<=m;i++){
		opt=getchar();
		while(opt<'A'||opt>'Z')opt=getchar();
		if(opt=='Q'){
			scanf("%d%d%d",&x,&y,&z);
			Q[++tot].x=x,Q[tot].y=y,Q[tot].k=z;
			Q[tot].id=++qr;
			Q[tot].opt=3;
		}
		else{
			scanf("%d%d",&x,&y);
			maxx=max(maxx,y);
			Q[++tot].x=x,Q[tot].y=a[x];
			Q[tot].opt=2;
			Q[++tot].x=x,Q[tot].y=y;
			Q[tot].opt=1;
			a[x]=y;
		}
	}
	DC(1,tot,1,maxx);
	for(i=1;i<=qr;i++)printf("%d\n",Ans[i]);
}