# Partition 分治

## 点分治  

#### [p3328 距离状态 ](http://oi.nks.edu.cn/zh/Problem/Details?id=3328)

模板

#### [p3329 race](http://oi.nks.edu.cn/zh/Problem/Details?id=3329)

转化为判定某个边数是否满足条件即可，处理方式同上  

#### [p4367 开店](http://oi.nks.edu.cn/zh/Problem/Details?id=4367)

动态点分治

构建点分治树，将每个点的子树按年龄排序，算出距离的前缀和

对于每个询问，从u节点开始往上讨论即可

时间复杂度$O(nlog^2n)$ ，空间复杂度$O(nlogn)$  

#### 动态点分治模板

```c++
int Root,Rt,Vis[N],Size[N],Fa[N],Dep[N];
ll Dis,Minn,FLen[N][30];	//FLen[i][j]表示i号节点到第j层的父节点的距离
vector<int>G[N];
void GetSize(int x,int fa){
	Size[x]=1;
	for(int i=Last[x],u;i;i=Next[i]){
		u=End[i];
		if(u!=fa&&!Vis[u]){
			GetSize(u,x);
			Size[x]+=Size[u];
		}
	}
}
void GetRoot(int x,int tot,int d,int fa){
	int Maxx=tot-Size[x],i,u;
	for(i=Last[x];i;i=Next[i]){
		u=End[i];
		if(u!=fa&&!Vis[u]){
			Maxx=max(Maxx,Size[u]);
			GetRoot(u,tot,d+Len[i],x);
		}
	}
	if(Maxx<Minn)Minn=Maxx,Rt=x,Dis=d;
}
void GetDis(int x,int k,int d,int fa){
	FLen[x][k]=d;
	for(int i=Last[x];i;i=Next[i])
		if(End[i]!=fa&&!Vis[End[i]])GetDis(End[i],k,d+Len[i],x);
}
void Pre(int x){
	Minn=Inf;
	GetSize(x,0);
	GetRoot(x,Size[x],0,0);
}
void GetTree(int x){
	Vis[x]=1;
	Dep[x]=Dep[Fa[x]]+1;
	GetDis(x,Dep[x],0,0);	//得到其子节点与其距离
	for(int u,i=Last[x];i;i=Next[i]){
		u=End[i];
		if(!Vis[u]){
			Pre(u);		//找出新的重心
			G[x].push_back(Rt);Fa[Rt]=x;	//与子节点连接
			GetTree(Rt);
		}
	}
}
```

