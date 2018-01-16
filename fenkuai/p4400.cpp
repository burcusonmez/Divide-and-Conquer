#include<stdio.h>
#include<math.h>
#include<algorithm>
#include<vector>
#include<set>
typedef long long ll;
using namespace std;
const int N=100005,M=5005;

int n,m,q,Len;
int a[N],Imsb[M],cnt[M][M];
ll Sum[M],Add[M];
vector<int>G[M],B,V[N];
set<int>s[N];
int main(){
	int i,j,k,x,y;
	char opt[10];
	scanf("%d%d%d",&n,&m,&q);
	Len=sqrt(n);
	for(i=1;i<=n;i++)scanf("%d",&a[i]);
	for(i=1;i<=m;i++){
		scanf("%d",&k);
		for(j=1;j<=k;j++){
			scanf("%d",&x);
			G[i].push_back(x);
			V[x].push_back(i);
			s[i].insert(x);
			Sum[i]+=a[x];
		}
		if(k>Len)B.push_back(i),Imsb[i]=1;
	}
	for(i=1;i<=n;i++)
		for(vector<int>::iterator it=V[i].begin();it!=V[i].end();it++)
			if(Imsb[*it])
				for(vector<int>::iterator jt=V[i].begin();jt!=V[i].end();jt++)
					cnt[*jt][*it]++;
	for(i=1;i<=q;i++){
		scanf("%s",opt);
		if(opt[0]=='?'){
			scanf("%d",&x);
			ll Ans=0;
			if(Imsb[x])Ans+=Sum[x];
			else
				for(vector<int>::iterator it=G[x].begin();it!=G[x].end();it++)
					Ans+=a[*it];
			for(vector<int>::iterator it=B.begin();it!=B.end();it++)
				Ans+=Add[*it]*cnt[x][*it];
			printf("%lld\n",Ans);
		}
		else{
			scanf("%d%d",&x,&y);
			if(Imsb[x])Add[x]+=y;
			else {
				for(vector<int>::iterator it=G[x].begin();it!=G[x].end();it++)
					a[*it]+=y;
				for(vector<int>::iterator it=B.begin();it!=B.end();it++)
					Sum[*it]+=cnt[x][*it]*y;
			}
		}
	}
}
