#include<stdio.h>
#include<algorithm>
using namespace std;
const int N=100005;

struct Data{
	int x,y,z;
}S[N],T[N];
int n,m,A[N],vis[N],B[N],C[N];
long long Ans[N];
void Modify(int x,int d){
	for(int i=x;i<=n;i+=i&-i)C[i]+=d;
}
int GetSum(int x){
	int sum=0;
	for(int i=x;i>=1;i^=i&-i)sum+=C[i];
	return sum;
}
/*
CDQ:
第一维删除时间，最先删的放在后面
第二维数组位置，小的在左边
第三位值
*/
void CDQ(int l,int r){
	if(l==r)return;
	int mid=l+r>>1,tot=0,i=l,j=mid+1,k=l;
	CDQ(l,mid),CDQ(mid+1,r);
	while(i<=mid&&j<=r){
		if(S[i].y<=S[j].y)T[k++]=S[i++];
		else T[k++]=S[j++];
	}
	while(i<=mid)T[k++]=S[i++];
	while(j<=r)T[k++]=S[j++];
	for(i=l;i<=r;i++)S[i]=T[i];
	for(i=l;i<=r;i++){						//统计在i左边的，比A[i]大的
		if(S[i].x<=mid)tot++,Modify(S[i].z,1);
		else Ans[S[i].x]+=tot-GetSum(S[i].z);
	}
	for(i=l;i<=r;i++)
		if(S[i].x<=mid)Modify(S[i].z,-1);
	for(i=r;i>=l;i--){						//统计在i右边的，比A[i]小的
		if(S[i].x<=mid)Modify(S[i].z,1);
		else Ans[S[i].x]+=GetSum(S[i].z);
	}
	for(i=l;i<=r;i++)
		if(S[i].x<=mid)Modify(S[i].z,-1);
}
int main(){
	int i,j,k,x,y;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++){
		scanf("%d",&A[i]);
		B[A[i]]=i;
	}k=n;
	for(i=1;i<=m;i++){
		scanf("%d",&x);vis[B[x]]=1;
		S[k].x=k,S[k].y=B[x],S[k--].z=x;
	}
	for(i=1;i<=n;i++)
		if(!vis[i])S[k].x=k,S[k].y=i,S[k--].z=A[i];
	CDQ(1,n);
	for(i=1;i<=n;i++)Ans[i]+=Ans[i-1];			
	for(i=1;i<=m;i++)printf("%lld\n",Ans[n-i+1]);
}