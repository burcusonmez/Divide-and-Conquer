#include<stdio.h>
#include<algorithm>
#include<stack>
#include<vector>
using namespace std;
const int N=200005;

typedef pair<int,int> pii;
stack<pii>Ops;
int Fa[N],Size[N],D[N];
int GetFa(int x){
	while(Fa[x]!=x)x=Fa[x];
	return x;
}
int GetDis(int x){
	int d=0;
	while(Fa[x]!=x)d^=D[x],x=Fa[x];
	return d;
}
void Merge(int x,int y,int z){
	int fx=GetFa(x),fy=GetFa(y);
	if(fx==fy)return;
	if(Size[x]>Size[y])swap(x,y);
	if(Size[x]==Size[y])
		Size[y]++,Ops.push(pii(1,y));
	Fa[x]=y;D[x]=z;Ops.push(pii(2,x));
}
void Recovery(int x){
	while(Ops.size()>x){
		pii tmp=Ops.top();
		Ops.pop();
		if(tmp.first==1)Size[tmp.second]--;
		else Fa[tmp.second]=tmp.second,D[tmp.second]=0;
	}
}

int n,m,T;
bool Ans[N];
struct Edge{
	int x,y,l,r;
};
vector<Edge>v;
typedef vector<Edge>::iterator vi;
void CDQ(int l,int r,vector<Edge>e){
	int mid=l+r>>1,now=Ops.size();
	vector<Edge> v1,v2;
	for(vi it=e.begin();it!=e.end();it++){
		if(it->l==l&&it->r==r){
			int x=GetFa(it->x),y=GetFa(it->y);
			int z=GetDis(it->x)^GetDis(it->y)^1;
			if(x!=y)Merge(x,y,z);
			else if(z&1){
				Recovery(now);
				return;
			}
		}
		else if(it->r<=mid)v1.push_back(*it);
		else if(it->l>mid)v2.push_back(*it);
		else {
			v1.push_back((Edge){it->x,it->y,it->l,mid});
			v2.push_back((Edge){it->x,it->y,mid+1,it->r});
		}
	}
	if(l==r) Ans[l]=1; 
	else CDQ(l,mid,v1),CDQ(mid+1,r,v2);
	Recovery(now);
}
int main(){
	int i,j,k,x,y;
	scanf("%d%d%d",&n,&m,&T);
	for(i=1;i<=m;i++){
		scanf("%d%d%d%d",&x,&y,&j,&k);
		j++;
		if(j>k)continue;
		v.push_back((Edge){x,y,j,k});
	}
	for(i=1;i<=n;i++)Fa[i]=i;
	CDQ(1,T,v);
	for(i=1;i<=T;i++)
		if(Ans[i])puts("Yes");
		else puts("No");
}
