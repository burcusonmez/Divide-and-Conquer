#include<stdio.h>
#include<ctype.h>
#include<algorithm>
#include<vector>
using namespace std;
const int N=505,M=60005;
inline int _R(){
	int d=0;char t=getchar();
	while(!isdigit(t))t=getchar();
	for(;isdigit(t);t=getchar())d=(d<<1)+(d<<3)+t-'0';
	return d;
}

int n,m,a[N][N],Ans[M];
int Hash[N*N],tot;
int C[N][N];
void Modify(int x,int y,int d){
	for(int i=x;i<=n;i+=i&-i)
		for(int j=y;j<=n;j+=j&-j)
			C[i][j]+=d;
}
int GetSum(int x,int y){
	int sum=0;
	for(int i=x;i>=1;i^=i&-i)
		for(int j=y;j>=1;j^=j&-j)
			sum+=C[i][j];
	return sum;
}

struct Node{ int x,y,z; };
struct Query{ int x,y,_x,_y,k,id; };

void DC(int l,int r,vector<Node>v,vector<Query>q){
	if(q.empty())return;
	if(l==r){
		for(vector<Query>::iterator it=q.begin();it!=q.end();it++)
			Ans[it->id]=l;
		return;
	}
	int mid=l+r>>1;
	vector<Node>v1,v2;
	vector<Query>q1,q2;
	for(vector<Node>::iterator it=v.begin();it!=v.end();it++)
		if(it->z<=mid)Modify(it->x,it->y,1);
	for(vector<Query>::iterator it=q.begin();it!=q.end();it++){
		int t=GetSum(it->x,it->y)-GetSum(it->_x-1,it->y)-GetSum(it->x,it->_y-1)+GetSum(it->_x-1,it->_y-1);
		if(t>=it->k)q1.push_back(*it);
		else it->k-=t,q2.push_back(*it);
	}
	for(vector<Node>::iterator it=v.begin();it!=v.end();it++)
		if(it->z<=mid)Modify(it->x,it->y,-1),v1.push_back(*it);
		else v2.push_back(*it);
	DC(l,mid,v1,q1);
	DC(mid+1,r,v2,q2);
}

vector<Node>V;
vector<Query>Q;
int main(){
	int i,j,k,x,y,_x,_y;
	n=_R(),m=_R();
	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++)
			a[i][j]=_R(),Hash[++tot]=a[i][j];
	sort(Hash+1,Hash+1+tot);
	tot=unique(Hash+1,Hash+1+tot)-Hash-1;
	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++)a[i][j]=lower_bound(Hash+1,Hash+1+tot,a[i][j])-Hash;
	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++)
			V.push_back((Node){i,j,a[i][j]});
	for(i=1;i<=m;i++){
		_x=_R(),_y=_R(),x=_R(),y=_R(),k=_R();
		Q.push_back((Query){x,y,_x,_y,k,i});
	}
	DC(1,tot,V,Q);
	for(i=1;i<=m;i++)printf("%d\n",Hash[Ans[i]]);
}
