#include<stdio.h>
#include<algorithm>
using namespace std;
typedef pair<int,int> pii;
const int N=400005,Inf=1e9;

int n,K;
int Tote,Last[N],Next[N],End[N],Len[N];
int Minn,Root,tot,Ans[N],Size[N];
pii S[N];
bool Vis[N];

void Ins(int x,int y,int z){
    End[++Tote]=y;
    Len[Tote]=z;
    Next[Tote]=Last[x];
    Last[x]=Tote;
}

void GetSize(int x,int fa){
    int i,u;
    Size[x]=1;
    for(i=Last[x];i;i=Next[i]){
        u=End[i];
        if(u!=fa&&!Vis[u]){
            GetSize(u,x);
            Size[x]+=Size[u];
        }
    }
}
void GetRoot(int x,int tot,int fa){
    int i,u,Maxx=tot-Size[x];
    for(i=Last[x];i;i=Next[i]){
        u=End[i];
        if(u!=fa&&!Vis[u]){
            Maxx=max(Maxx,Size[u]);
            GetRoot(u,tot,x);
        }
    }
    if(Maxx<Minn)Minn=Maxx,Root=x;
}
void Pre(int x){
    Minn=Inf;
    GetSize(x,0);
    GetRoot(x,Size[x],0);
}
void GetD(int x,int dis,int dep,int fa){
    S[++tot].first=dis,S[tot].second=dep;
    for(int i=Last[x];i;i=Next[i])
        if(End[i]!=fa&&!Vis[End[i]])GetD(End[i],dis+Len[i],dep+1,x);
}
void GetAns(int x,int Dis,int Dep,int ty){
    tot=0;
    GetD(x,Dis,Dep,0);
    sort(S+1,S+tot+1);
    for(int i=1,j=tot;i<=tot&&i<=j;i++){
        while(i<j&&S[i].first+S[j].first>K)j--;
        while(S[i].first+S[j].first==K)
            Ans[S[i].second+S[j].second]+=ty,
            j--;
    }
}
void Dfs(int x){
    int i,u;
    Vis[x]=1;
    GetAns(x,0,0,1);
    for(i=Last[x];i;i=Next[i]){
        u=End[i];
        if(!Vis[u]){
            GetAns(u,Len[i],1,-1);
            Pre(u);
            Dfs(Root);
        }
    }
}
int main(){
    int i,j,k,x,y,z;
    scanf("%d%d",&n,&K);
    for(i=1;i<n;i++){
        scanf("%d%d%d",&x,&y,&z);
        x++,y++;
        Ins(x,y,z),Ins(y,x,z);
    }
    Pre(1);
    Dfs(Root);
    for(i=1;i<=n;i++)
        if(Ans[i]){
            printf("%d\n",i);
            return 0;
        }
    puts("-1");
}