# Divide-ans-Conquer 分治

## 点分治  

#### [NKOJ 3328 距离状态 ](http://oi.nks.edu.cn/zh/Problem/Details?id=3328) :white_check_mark:

模板

#### [NKOJ 3329 race](http://oi.nks.edu.cn/zh/Problem/Details?id=3329) :white_check_mark:

转化为判定某个边数是否满足条件即可，处理方式同上  

#### [NKOJ 4367 开店](http://oi.nks.edu.cn/zh/Problem/Details?id=4367) :white_check_mark:

动态点分治

构建点分治树，将每个点的子树按年龄排序，算出距离的前缀和

对于每个询问，从u节点开始往上讨论即可

时间复杂度$O(nlog^2n)$ ，空间复杂度$O(nlogn)$  

##### 动态点分治模板

```c++
int Root,Rt,Vis[N],Size[N],Fa[N],Dep[N];
ll Dis,Minn,FLen[N][30];	//FLen[i][j]表示i号节点到第j层的父节点的距离
ll Sum[N];				//Sum[i]=sum{Dis[j][Dep[i]]-Dis[j][Dep[i]-1]}(j为i子节点)
						//即i子节点到i距离之和减去到i父亲距离之和
						//方便处理，在子节点上提前减掉其影响%%%Sparrow
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

#### [NKOJ 4056 【ZJOI2007】Hide 捉迷藏](http://42.247.7.121/zh/Problem/Details/4065):white_check_mark:

每个点开两个堆，一个记子节点到上一层重心距离，一个记其子树到它的链,全局堆记答案

##### 关于堆的一些操作

如果堆A是堆B[]的堆顶集合，我们修改了一个堆B[i]，怎么维护堆A？

先在堆A里删除B[i]的堆顶，操作完B[i]后，再将B[i]的堆顶加回去

```c++
void On(int x){
	if(B[x].size()>1)Ans.del(B[x].getmax());
	B[x].del(0);
	if(B[x].size()>1)Ans.push(B[x].getmax());
	for(int u=Fa[x],v=x;u;u=Fa[u],v=Fa[v]){
		if(B[u].size()>1)Ans.del(B[u].getmax());
		if(C[v].size())B[u].del(C[v].top());	//先删
		C[v].del(Dis[x][Dep[u]]);				//操作
		if(C[v].size())B[u].push(C[v].top());	//操作完后加回去
		if(B[u].size()>1)Ans.push(B[u].getmax());
	}
}
```



#### [NKOJ 3254 【ZJOI2015 Day1】幻想乡战略游戏](http://oi.nks.edu.cn/zh/Problem/Details/3254):white_check_mark:

带权重心，每次从一个点开始，计算它的权值，往它最优的子节点上走（原树的)

计算权值用动态点分治，注意不与原树搞混即可

#### [NKOJ 2703 【WC2014】紫荆花之恋（强数据版）](http://oi.nks.edu.cn/zh/Problem/Details/2703)

#### [NKOJ 2702 【WC2014】紫荆花之恋（弱数据版）](http://oi.nks.edu.cn/zh/Problem/Details/2702)

#### [NKOJ 3611 【CQOI2016 Day1】不同的最小割 ](http://oi.nks.edu.cn/zh/Problem/Details/3611)

#### [NKOJ 3984 WC2010重建计划](http://oi.nks.edu.cn/zh/Problem/Details/3984):white_check_mark:

上静态点分治，到每个重心，二分一个答案ans

将该重心子树的边减去ans，如果找出一条权之和大于零的路径，就是满足条件的

问题变为找一条长度L,U之间的大于零的路径

枚举该重心的每一颗子树，用BFS取出当前子树的点

记下之前子树中，每种路径长度的最大值

BFS取出来的点按深度递增，于是可以用单调队列维护

优化：每个重心的子树按最大深度从小到大排序，防止被”扫把图“卡

#### [NKOJ 4351【大学生赛重庆2017】A ](http://oi.nks.edu.cn/zh/Problem/Details?id=4351):white_check_mark:

上静态点分治，fft算一下当前答案给每个点加一下，发现每个点的子节点距离都多算了2,减掉即可

注意各种初始化

#### [NKOJ 3446 【HN Training 2015 Round7】 Shopping](http://oi.nks.edu.cn/zh/Problem/Details?id=3446)

#### [NKOJ 3220 ShadowIterator再战啦啦操](http://oi.nks.edu.cn/zh/Problem/Details?id=3220) :white_check_mark:

水题，dfs两遍即可。写了个搞笑的动态点分治

#### [BZOJ 2152 聪聪可可](http://www.lydsy.com/JudgeOnline/problem.php?id=2152)