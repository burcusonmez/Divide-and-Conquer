#include<stdio.h>
#include<algorithm>
using namespace std;
const int N=200005;

struct Data{
	int x,y,z,id;
	bool operator < (const Data& rhs)const{
		if(x!=rhs.x)return x<rhs.x;
		if(y!=rhs.y)return y<rhs.y;
		return z<rhs.z;
	}
}A[N],S[N];
int n,m,Cnt[N],Ans[N];
int c[N];
void Modify(int x,int d){
	for(int i=x;i<=m;i+=i&-i)c[i]+=d;
}
int GetSum(int x){
	int sum=0;
	for(int i=x;i;i^=i&-i)sum+=c[i];
	return sum;
}
void CDQ(int l,int r){
	if(l==r)return;
	int i,j,k,mid=l+r>>1;
	CDQ(l,mid),CDQ(mid+1,r);
	i=l,j=mid+1,k=l;
	while(i<=mid&&j<=r){
		if(A[i].y<=A[j].y)S[k++]=A[i++];
		else S[k++]=A[j++];
	}
	while(i<=mid)S[k++]=A[i++];
	while(j<=r)S[k++]=A[j++];
	for(i=l;i<=r;i++)A[i]=S[i];
	for(i=l;i<=r;i++){
		if(A[i].id<=mid)Modify(A[i].z,1);
		else Cnt[A[i].id]+=GetSum(A[i].z);
	}
	for(i=l;i<=r;i++)if(A[i].id<=mid)Modify(A[i].z,-1);
}
int main(){
	int i,j,k;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++)scanf("%d%d%d",&A[i].x,&A[i].y,&A[i].z);
	sort(A+1,A+1+n);
	for(i=1;i<=n;i++)A[i].id=i;
	CDQ(1,n);
	for(i=1;i<=n;i++)Ans[Cnt[i]]++;
	for(i=0;i<n;i++)printf("%d ",Ans[i]);
}