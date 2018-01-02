#include<stdio.h>
#include<math.h>
#include<algorithm>
typedef long long ll;
ll C[3005];
int A[500005];
int n,m,Len,t,l,r,x,y,i,j;
ll ans;
int main(){
	scanf("%d%d%d",&n,&m,&t);
	Len=pow(n,0.4);
	for(i=1;i<=n;i++)scanf("%d",&A[i]),C[(i-1)/Len+1]+=A[i];
	while(m--){
		scanf("%d%d",&l,&r);
		if(t){
			ans=ans>0?ans:-ans;
			l=((ll)l^ans)%n+1;
			r=((ll)r^ans)%n+1;
			if(l>r)std::swap(l,r);
		}
		ans=0,x=(l-1)/Len+1,y=(r-1)/Len+1;
		if(x==y)
			for(i=l;i<=r;i++)ans+=A[i];
		else{
			for(i=l;i<=x*Len;i++)ans+=A[i];
			for(i=x+1;i<y;i++)ans+=C[i];
			for(i=(y-1)*Len+1;i<=r;i++)ans+=A[i];
		}
		printf("%lld\n",ans);
	}
}