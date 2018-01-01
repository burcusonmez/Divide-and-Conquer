#include<stdio.h>
#include<algorithm>
using namespace std;
const int N=100005;

int n,m,K;
int Tote,Len[N],Last[N],End[N],Next[N];
int tot,Ans,S[N],Size[N];
int Root,Minn;
bool Vis[N];
void Ins(int x,int y,int z){
    End[++Tote]=y;
    Len[Tote]=z;
    Next[Tote]=Last[x];
    Last[x]=Tote;
}

void GetDis(int x,int d,int fa){
    S[++tot]=d;
    for(int i=Last[x];i;i=Next[i])
        if(End[i]!=fa&&!Vis[End[i]])GetDis(End[i],d+Len[i],x);
}
void GetAns(int x,int d,int ty){
    tot=0;
    GetDis(x,d,0);
    sort(S+1,S+1+tot);
    for(int i=1,j=tot;i<=tot;i++){
        while(i<j&&S[i]+S[j]>K)j--;
        if(i>=j)break;
        Ans+=ty*(j-i);
    }
}

void GetRoot(int x,int s,int fa){
    int Maxx=0,i,u;
    Size[x]=1;
    for(i=Last[x];i;i=Next[i]){
        u=End[i];
        if(u!=fa&&!Vis[u]){
            GetRoot(u,s,x);
            Size[x]+=Size[u];
            Maxx=max(Maxx,Size[u]);
        }
    }
    Maxx=max(Maxx,s-Size[x]);
    if(Maxx<Minn)Minn=Maxx,Root=x;
}
void Dfs(int x){
    Vis[x]=1;
    GetAns(x,0,1);
    int i,u;
    for(i=Last[x];i;i=Next[i]){
        u=End[i];
        if(!Vis[u]){
            GetAns(u,Len[i],-1);
            Minn=1e9;
            GetRoot(u,Size[u],0);
            Dfs(Root);
        }
    }
}
int main(){
    int i,j,k,x,y,z;char c;
    scanf("%d%d",&n,&m);
    for(i=1;i<=m;i++){
        scanf("%d%d%d %c",&x,&y,&z,&c);
        Ins(x,y,z),Ins(y,x,z);
    }
    scanf("%d",&K);
    Minn=1e9;GetRoot(1,n,0);Dfs(Root);
    printf("%d\n",Ans);
}