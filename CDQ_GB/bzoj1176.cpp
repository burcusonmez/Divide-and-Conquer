#include<stdio.h>
#include<ctype.h>
#include<algorithm>
using namespace std;
const int N=200005;
inline int _R(){
	int d=0;char t=getchar();
	while(!isdigit(t))t=getchar();
	for(;isdigit(t);t=getchar())d=(d<<3)+(d<<1)+t-'0';
	return d;
}

int s,n,q,qr,Ans[N];
struct Data{
	int t,x,y,_y,z,id;
}A[N],T[N];
int C[N*10];
void Modify(int x,int d){
	for(int i=x;i<=n;i+=i&-i)C[i]+=d;
}
int GetSum(int x){
	int sum=0;
	for(int i=x;i>=1;i^=i&-i)sum+=C[i];
	return sum;
}
void CDQ(int l,int r){
	if(l==r)return;
	int mid=l+r>>1,i=l,j=mid+1,k=l;
	CDQ(l,mid),CDQ(mid+1,r);
	while(i<=mid&&j<=r){
		if(A[i].x<=A[j].x)T[k++]=A[i++];
		else T[k++]=A[j++];
	}
	while(i<=mid)T[k++]=A[i++];
	while(j<=r)T[k++]=A[j++];
	for(i=l;i<=r;i++)A[i]=T[i];
	for(i=l;i<=r;i++){
		if(!A[i].id&&A[i].t<=mid)Modify(A[i].y,A[i].z);
		else if(A[i].id!=0&&A[i].t>mid){
			if(A[i].id>0)Ans[A[i].id]+=GetSum(A[i].y)-GetSum(A[i]._y-1);
			else Ans[-A[i].id]-=GetSum(A[i].y)-GetSum(A[i]._y-1);
		}
	}
	for(i=l;i<=r;i++)
		if(!A[i].id&&A[i].t<=mid)Modify(A[i].y,-A[i].z);
}
int main(){
	int i,j,k,x,y,_x,_y,opt;
	s=_R(),n=_R();
	while((opt=_R())!=3){
		if(opt==1){
			A[++q].x=_R(),A[q].y=_R(),A[q].z=_R();
			A[q].t=q;
		}
		else {
			_x=_R(),_y=_R(),x=_R(),y=_R();
			A[++q].x=x,A[q]._y=_y,A[q].y=y;
			A[q].t=q,A[q].id=++qr;
			A[++q].x=_x-1,A[q]._y=_y,A[q].y=y;
			A[q].t=q,A[q].id=-qr;
			Ans[qr]=(x-_x)*(y-_y)*s;
		}
	}
	CDQ(1,q);
	for(i=1;i<=qr;i++)printf("%d\n",Ans[i]);
}
