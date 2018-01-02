#include<stdio.h>
#include<algorithm>
#include<math.h>
#include<vector>
using namespace std;
typedef double db;
const db eps=0.0000000001;
const int N=505,M=10005;

int n,m,T;
int nlen,mlen,ntot,mtot,blktot,blksz,tot,vblk[N];
int dx[4]={0,0,1,-1},dy[4]={1,-1,0,0};
vector<int>vc[M],vr[M],blk[M],d[M],db[N];
db p[N],a[N][N];
void Gauss(){
	int x,y,i,j,k;
	for(x=1,y=1;y<=tot;x++,y++){
		for(i=x+1,j=x;i<=tot;i++)
			if(fabs(a[i][y])>fabs(a[j][y]))j=i;
		if(j!=x)for(i=y;i<=tot+1;i++)swap(a[x][i],a[j][i]);
		for(i=x+1;i<=tot;i++)
			if(fabs(a[i][y])>eps){
				db r=a[i][y]/a[x][y];
				for(k=y;k<=tot+1;k++)a[i][k]-=a[x][k]*r;
			}
	}
	for(i=tot;i>=1;i--){
		p[i]=a[i][tot+1];
		for(j=i+1;j<=tot;j++)p[i]-=a[i][j]*p[j];
		p[i]/=a[i][i];
	}
}
int main(){
	int i,j,k,x,y,p,q,b,b1,b2,u,v,s,t;
	scanf("%d%d",&n,&m);
	nlen=sqrt(n),mlen=sqrt(m);
	ntot=(n-1)/nlen+1,mtot=(m-1)/mlen+1,blktot=ntot*mtot;
	for(i=1,x=0;i<=n;i++){
		if(i%nlen==1)x++;
		for(j=1,y=0;j<=m;j++){
			if(j%mlen==1)y++;
			blk[i][j]=(x-1)*mtot+y;
		}
	}
	for(i=1;i<n;i++)
		for(j=1;j<=m;j++){
			scanf("%d",&vc[i][j]);
			if(blk[i][j]==blk[i+1][j])vblk[blk[i][j]]+=vc[i][j];
		}
	for(i=1;i<=n;i++)
		for(j=1;j<m;j++){
			scanf("%d",&vr[i][j]);
			if(blk[i][j]==blk[i][j+1])vblk[blk[i][j]]+=vr[i][j];
		}
	scanf("%d",&T);
	while(T--){
		scanf("%d%d%d%d",&u,&v,&s,&t);
		u++,v++,s++,t++;
		b1=blk[u][v],b2=blk[s][k];
		for(i=1,t=1;i<=ntot;i++)
			for(j=1;j<=mtot;j++,t++)
			if(t!=b1&&t!=b2){
				for(k=0;k<4;k++){
					p=i+dx[k],q=j+dy[k],b=(p-1)*mtot+q;
					if(p&&p<=ntot&&q&&q<=mtot&&b!=b1&&b!=b2)a[b][t]=-1.0/d[]
				}
			}
	}
}