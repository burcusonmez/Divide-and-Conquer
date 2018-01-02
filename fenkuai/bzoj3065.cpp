#include<stdio.h>
#include<math.h>
#include<string.h>
#include<cctype>
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
const int N=35005,M=205;
inline int _R(){
	int d=0;bool b=1;char t=getchar();
	while(!isdigit(t))b=t=='-'?0:1,t=getchar();
	for(;isdigit(t);t=getchar())d=(d<<3)+(d<<1)+t-'0';
	return d;
}

int n,m,a[N];
struct Block{
	vector<int>A,T;
	int l,r,sum;
	void Init(){
		for(int i=l;i<=r;i++)
			A.push_back(a[i]),
			T.push_back(a[i]);
		sort(T.begin(),T.end());
	}
	void Insert(int x,int d){
		sum++;
		A.insert(x+A.begin()-1,d);
		T.push_back(d);
		for(int i=sum-2,j=sum-1;i>=0;i--){
			if(d<T[i])swap(T[i],T[j]),j=i;
			else break;
		}
	}
	void Modify(int x,int d){
		int a=A[x-1];
		vector<int>::iterator i=lower_bound(T.begin(),T.end(),a);
		T.erase(i);
		A.erase(x+A.begin()-1);
		sum--;
		Insert(x,d);
	}
	int Get(int k){
		vector<int>::iterator i=lower_bound(T.begin(),T.end(),k);
		return i-T.begin();
	}
	void Print(){
		for(int i=0;i<A.size();i++)
			printf("%d ",A[i]);
		puts("");
		for(int i=0;i<T.size();i++)
			printf("%d ",T[i]);
		puts("");
	}
}B[M];
bool Check(int x,int y,int k,int v){
	int i,l=1,r=1,sum=0;
	while(B[l].sum<x)x-=B[l++].sum;
	while(B[r].sum<y)y-=B[r++].sum;
	if(l==r)
		for(i=x-1;i<y;i++)sum+=B[l].A[i]<v;
	else{
		for(i=x-1;i<B[l].sum;i++)sum+=B[l].A[i]<v;
		for(i=0;i<y;i++)sum+=B[r].A[i]<v;
		for(i=l+1;i<r;i++)sum+=B[i].Get(v);
	}
	return sum+1<=k;
}
int Len,tot;
int main(){
	int i,j,x,y,k,ans=0,L,R,Mid;
	char opt;
	n=_R();
	Len=sqrt(n);
	tot=(n-1)/Len+1;
	for(i=1;i<=n;i++)a[i]=_R();
	for(i=1;i<=tot;i++){
		B[i].l=(i-1)*Len+1;
		B[i].r=min(i*Len,n);
		B[i].sum=B[i].r-B[i].l+1;
		B[i].Init();
		// B[i].Print();
	}
	m=_R();
	while(m--){
		opt=getchar();
		while(opt<'A'||opt>'Z')opt=getchar();
		x=_R()^ans,y=_R()^ans;
		if(opt=='Q'){
			k=_R()^ans;
			L=0,R=70000;
			while(L<=R){
				Mid=L+R>>1;
				if(Check(x,y,k,Mid))ans=Mid,L=Mid+1;
				else R=Mid-1;
			}
			printf("%d\n",ans);
		}
		else if(opt=='M'){
			i=1;
			while(B[i].sum<x)x-=B[i++].sum;
			B[i].Modify(x,y);
		}
		else{
			i=1;
			while(B[i].sum<x&&i<=tot)x-=B[i++].sum;
			if(i>tot)i=tot,x=B[tot].sum;
			B[i].Insert(x,y);
		}
	}
}