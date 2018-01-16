#include<stdio.h>
#include<ctype.h>
#include<algorithm>
#include<stack>
#include<vector>
using namespace std;
typedef long long ll;
const int N=200005;
inline int _R(){
	int d=0;char t=getchar();
	while(!isdigit(t))t=getchar();
	for(;isdigit(t);t=getchar())d=(d<<3)+(d<<1)+t-'0';
	return d;
}
struct Node{
	Node *Son[2],*Max,*Fa;
	int x,y,val,id;
	bool rev;
}pool[N],*null,*it[N];

namespace LCT{

	void Init(int sz){
		it[0]=null=pool;
		null->Son[0]=null->Son[1]=null->Fa=null->Max=null;
		null->x=null->y=null->val=null->rev=0;
		for(int i=1;i<=sz;i++){
			it[i]=pool+i;
			it[i]->Son[0]=it[i]->Son[1]=it[i]->Fa=it[i]->Max=null;
		}
	}
	inline bool IsRoot(Node* x){
		return x->Fa==null||(x->Fa->Son[0]!=x&&x->Fa->Son[1]!=x);
		//return !Fa[x]||(Son[Fa[x]][0]!=x&&Son[Fa[x]][1]!=x);
	}
	inline void Setr(Node* x){
		x->rev^=1;
		swap(x->Son[0],x->Son[1]);
		//Rev[x]^=1;
		//swap(Son[x][0],Son[x][1]);
	}
	inline void PushUp(Node* x){
		x->Max=x;
		if(x->Son[0]->Max->val>x->Max->val)x->Max=x->Son[0]->Max;
		if(x->Son[1]->Max->val>x->Max->val)x->Max=x->Son[1]->Max;
		//if(Val[Max[l]]>Val[Max[x]])Max[x]=Max[l];
		//if(Val[Max[r]]>Val[Max[x]])Max[x]=Max[r];
	}
	inline void PushDown(Node* x){
		if(x->rev){
			x->rev=0;
			if(x->Son[0]!=null)Setr(x->Son[0]);
			if(x->Son[1]!=null)Setr(x->Son[1]);
		}
		//if(Rev[x]){
		//	Rev[x]=0;
		//	if(Son[x][0])Setr(Son[x][0]);
		//	if(Son[x][1])Setr(Son[x][1]);
		//}
	}
	inline void Rotate(Node* x){
		Node *y=x->Fa,*z=y->Fa;
		int l=y->Son[0]==x,r=l^1;
		if(!IsRoot(y))z->Son[z->Son[1]==y]=x;x->Fa=z;
		y->Son[r]=x->Son[l],x->Son[l]->Fa=y,x->Son[l]=y,y->Fa=x;
		PushUp(y),PushUp(x);
		//int y=Fa[x],z=Fa[y],l=Son[y][0]==x,r=l^1;
		//if(!IsRoot(y))Son[z][Son[z][1]==y]=x;Fa[x]=z;
		//Son[y][r]=Son[x][l],Fa[Son[x][l]]=y,Son[x][l]=y,Fa[y]=x;
		//PushUp(y),PushUp(x);
	}
	Node* s[N];
	int top;
	void Splay(Node* x){
		s[top=1]=x;
		for(Node* i=x;!IsRoot(i);i=i->Fa)s[++top]=i->Fa;
		while(top)PushDown(s[top--]);
		while(!IsRoot(x)){
			Node *y=x->Fa,*z=y->Fa;
			//int y=Fa[x],z=Fa[y];
			if(!IsRoot(y)){
				if(z->Son[0]==y^y->Son[0]==x)Rotate(x);
				else Rotate(y);
			}
			else Rotate(x);
		}
	}
	void Access(Node* x){
		for(Node* t=null;x!=null;t=x,x=x->Fa){
			Splay(x);
			x->Son[1]=t;
			PushUp(x);
		}
	}
	void MakeToRoot(Node* x){
		Access(x);Splay(x);Setr(x);
	}
	bool Bridge(int _x,int _y){
		Node *x=it[_x],*y=it[_y];
		Access(x),Splay(x);
		while(x->Son[0]!=null)x=x->Son[0];
		Access(y),Splay(y);
		while(y->Son[0]!=null)y=y->Son[0];
		return x==y;
	}
	void Link(int _x,int _y){
		Node *x=it[_x],*y=it[_y];
		MakeToRoot(x);
		x->Fa=y;
	}
	void Cut(int _x,int _y){
		Node *x=it[_x],*y=it[_y];
		MakeToRoot(x);
		Access(y),Splay(y);
		y->Son[0]=x->Fa=null;
		PushUp(y);
	}
	Node* GetMax(int _x,int _y){
		Node *x=it[_x],*y=it[_y];
		MakeToRoot(x);
		Access(y),Splay(y);
		return y->Max;
	}
}

int n,m,T,Last[N];
ll Ans[N];
struct Edge{
	int x,y,z,l,r,id;
}E[N];

typedef pair<int,int> pii;
typedef pair<int,pii> piii;
stack<piii>s;
void Recover(int x){
	while(s.size()>x){
		piii tmp=s.top();
		s.pop();
		if(tmp.first==1)LCT::Cut(tmp.second.first,tmp.second.second);	
		else LCT::Link(tmp.second.first,tmp.second.second);
	}
}

void CDQ(int l,int r,ll d,vector<Edge>e){
	using namespace LCT;
	int mid=l+r>>1,now=::s.size();
	vector<Edge>v1,v2;
	for(vector<Edge>::iterator it=e.begin();it!=e.end();it++){
		if(it->l==l&&it->r==r){
			if(!Bridge(it->x,it->y)){
				Link(it->x,it->id);
				Link(it->y,it->id);
				d+=it->z;
				::s.push(piii(1,pii(it->x,it->id)));
				::s.push(piii(1,pii(it->y,it->id)));
			}
			else{
				Node* t=GetMax(it->x,it->y);
				if(t->val>it->z){
					Cut(t->id,t->x);
					Cut(t->id,t->y);
					Link(it->id,it->x);
					Link(it->id,it->y);
					d+=it->z-t->val;
					::s.push(piii(2,pii(t->id,t->x)));
					::s.push(piii(2,pii(t->id,t->y)));
					::s.push(piii(1,pii(it->id,it->x)));
					::s.push(piii(1,pii(it->id,it->y)));
				}
			}
		}
		else if(it->r<=mid)v1.push_back(*it);
		else if(it->l>mid)v2.push_back(*it);
		else v1.push_back((Edge){it->x,it->y,it->z,it->l,mid,it->id}),
			 v2.push_back((Edge){it->x,it->y,it->z,mid+1,it->r,it->id});
	}
	if(l==r)Ans[l]=d;
	else CDQ(l,mid,d,v1),CDQ(mid+1,r,d,v2);
	Recover(now);
}
vector<Edge>v;
int main(){
	int i,j,k,x,y,z;
	n=_R(),m=_R(),T=_R();
	for(i=1;i<=m;i++){
		E[i].x=_R(),E[i].y=_R(),E[i].z=_R();
		Last[i]=i;
		E[i].l=1,E[i].r=T;
	}
	for(i=1;i<=T;i++){
		x=_R(),y=_R();
		E[Last[x]].r=i-1;
		E[i+m]=E[Last[x]];
		Last[x]=i+m;
		E[i+m].l=i,E[i+m].r=T,E[i+m].z=y;
	}
	LCT::Init(n+m+T);
	for(i=1;i<=m+T;i++)
		if(E[i].l<=E[i].r){
			E[i].id=n+v.size()+1;
			x=E[i].id;
			pool[x].id=E[i].id;
			pool[x].x=E[i].x;
			pool[x].y=E[i].y;
			pool[x].val=E[i].z;
			v.push_back(E[i]);
		}
	CDQ(1,T,0,v);
	for(i=1;i<=T;i++)printf("%lld\n",Ans[i]);
}
