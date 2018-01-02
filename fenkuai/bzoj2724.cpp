#include<stdio.h>
#include<math.h>
#include<algorithm>
using namespace std;
const int N=50005,M=255;

int n,m,a[N],Hash[N],Htot,A[M][M],C[M][M];
int Len,tot,Ans,Max;
struct Block{
	int l,r,len,Map[N],F[N],A[M][M];
	void Init(){
		int i,j,t;
		for(i=l,t=0;i<=r;i++)
			if(!Map[a[i]])Map[a[i]]=++t;
		for(i=1;i<=len;i++)
			for(j=i;j<=len;j++)
				A[j][Map[a[i+l-1]]]++;
		for(i=1;i<=r;i++)
			F[a[i]]++;
	}
	int GetF(int d){return F[d];}
	int GetA(int x,int d){return A[x-l+1][Map[d]];}
}B[M];
int GetSum(int x,int d){
	int k=(x-1)/Len+1;
	return B[k-1].GetF(d)+B[k].GetA(x,d);
}
void cmp(int &a,int &b,int c,int d){
	if(d>a||(d==a&&c<b))a=d,b=c;
}
int main(){
	int i,j,k,t,l,r,x,y;
	scanf("%d%d",&n,&m);
	Len=sqrt(n),tot=(n-1)/Len+1;

	for(i=1;i<=n;i++)scanf("%d",&a[i]);
	for(i=1;i<=n;i++)Hash[i]=a[i];
	sort(Hash+1,Hash+1+n);
	Htot=unique(Hash+1,Hash+1+n)-Hash-1;
	for(i=1;i<=n;i++)a[i]=lower_bound(Hash+1,Hash+1+Htot,a[i])-Hash;

	for(i=1;i<=tot;i++){
		B[i].l=(i-1)*Len+1;
		B[i].r=min(i*Len,n);
		B[i].len=B[i].r-B[i].l+1;
		B[i].Init();
	}

	for(i=1;i<=tot;i++)
		for(j=i;j<=tot;j++){
			A[i][j]=A[i][j-1],C[i][j]=C[i][j-1];
			for(k=B[j].l;k<=B[j].r;k++)
				cmp(A[i][j],C[i][j],a[k],B[j].GetF(a[k])-B[i-1].GetF(a[k]));
		}
	while(m--){
		scanf("%d%d",&l,&r);
		l=(l+Ans-1)%n+1,r=(r+Ans-1)%n+1;
		if(l>r)swap(l,r);
		x=(l-1)/Len+1,y=(r-1)/Len+1;

		Max=0,Ans=0;
		if(x==y)
			for(i=l;i<=r;i++)
				cmp(Max,Ans,a[i],GetSum(r,a[i])-GetSum(l-1,a[i]));
		else{
			Max=A[x+1][y-1];
			Ans=C[x+1][y-1];
			for(i=l;i<=x*Len;i++)
				cmp(Max,Ans,a[i],GetSum(r,a[i])-GetSum(l-1,a[i]));
			for(i=(y-1)*Len+1;i<=r;i++)
				cmp(Max,Ans,a[i],GetSum(r,a[i])-GetSum(l-1,a[i]));
		}
		Ans=Hash[Ans];
		printf("%d\n",Ans);
	}
}
