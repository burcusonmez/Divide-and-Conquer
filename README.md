# Divide-and-Conquer 分治

****************

> :cn: :kissing: I'm Darth Vader LOOOOOOL...:pig: :pig: 

## 点分治  

####  [NKOJ 3328 距离状态 ](http://oi.nks.edu.cn/zh/Problem/Details?id=3328) :white_check_mark:

模板

#### [NKOJ 3329 race](http://oi.nks.edu.cn/zh/Problem/Details?id=3329) :white_check_mark:

转化为判定某个边数是否满足条件即可，处理方式同上  

#### [NKOJ 4367 开店](http://oi.nks.edu.cn/zh/Problem/Details?id=4367) :white_check_mark:

动态点分治

构建点分治树，将每个点的子树按年龄排序，算出距离的前缀和

对于每个询问，从u节点开始往上讨论即可

时间复杂度$O(nlog^2n)$ ，空间复杂度$O(nlogn)$  

#### [NKOJ 4056 【ZJOI2007】Hide 捉迷藏](http://42.247.7.121/zh/Problem/Details/4065):white_check_mark:

每个点开两个堆，一个记子节点到上一层重心距离，一个记其子树到它的链,全局堆记答案

**关于堆的一些操作**

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

#### [NKOJ 2703 【WC2014】紫荆花之恋（强数据版）](http://oi.nks.edu.cn/zh/Problem/Details/2703):heavy_check_mark: :kiss: :fire:   

将原要求转化为Dis[i]-D[i]<=D[j]-Dis[j]

每个点开一个sbt记左边的，再开一个用作差分

给点分治树上重构即可

#### [NKOJ 2702 【WC2014】紫荆花之恋（弱数据版）](http://oi.nks.edu.cn/zh/Problem/Details/2702):white_check_mark:

#### [NKOJ 3611 【CQOI2016 Day1】不同的最小割 ](http://oi.nks.edu.cn/zh/Problem/Details/3611)

#### [NKOJ 3984 WC2010重建计划](http://oi.nks.edu.cn/zh/Problem/Details/3984) :white_check_mark:

上静态点分治，到每个重心，二分一个答案ans

将该重心子树的边减去ans，如果找出一条权之和大于零的路径，就是满足条件的

问题变为找一条长度L,U之间的大于零的路径

枚举该重心的每一颗子树，用BFS取出当前子树的点

记下之前子树中，每种路径长度的最大值

BFS取出来的点按深度递增，于是可以用单调队列维护

优化：每个重心的子树按最大深度从小到大排序，防止被”扫把图“卡

#### [NKOJ 4351【大学生赛重庆2017】A ](http://oi.nks.edu.cn/zh/Problem/Details?id=4351):white_check_mark: :fire: 

上静态点分治，fft算一下当前答案给每个点加一下，发现每个点的子节点距离都多算了2,减掉即可

注意各种初始化

#### [NKOJ 3446 【HN Training 2015 Round7】 Shopping](http://oi.nks.edu.cn/zh/Problem/Details?id=3446)

#### [NKOJ 3220 ShadowIterator再战啦啦操](http://oi.nks.edu.cn/zh/Problem/Details?id=3220) :white_check_mark:

水题，dfs两遍即可。写了个搞笑的动态点分治

#### [BZOJ 2152 聪聪可可](http://www.lydsy.com/JudgeOnline/problem.php?id=2152)

#### [NKOJ4383【FJOI2014】最短路径树问题](http://oi.nks.edu.cn/zh/Problem/Details/4383):white_check_mark:

类似重建计划



**********************************

# 分块


>%%% WJMZBMR...
>%%% VFleaking...

#### [bzoj2724 [Violet 6]蒲公英](http://www.lydsy.com/JudgeOnline/problem.php?id=2724) :white_check_mark:

区间众数

#### [bzoj3065 带插入区间第k小数](http://www.lydsy.com/JudgeOnline/problem.php?id=3065)

分块然后排序，emmmm... :fire:



___

# CDQ分治

>%%%Oblack...

#### [NKOJ3655 菊花的故事](http://42.247.7.121/zh/Problem/Details?id=3655) :kiss:

模板 :clapper:

#### [NKOJ2041 CQOI2011 动态逆序对](http://42.247.7.121/zh/Problem/Details?id=2041) :heavy_check_mark:

CDQ:

第一维删除时间，最先删的放在后面

第二维数组位置，小的在左边

第三位值

#### [NKOJ2739【Violet III】天使玩偶](http://42.247.7.121/zh/Problem/Details?id=2739)

#### [NKOJ3933 贝壳串](http://42.247.7.121/zh/Problem/Details?id=3933)

#### [NKOJ3652 Shallot](http://42.247.7.121/zh/Problem/Details?id=3652)

#### [NKOJ2936 【FJ Training 2014 Day2】城市建设](http://42.247.7.121/zh/Problem/Details?id=2936)

#### [NKOJ3931 货币兑换](http://42.247.7.121/zh/Problem/Details?id=3931)

#### [bzoj1176 [Balkan2007]Mokia](http://www.lydsy.com/JudgeOnline/problem.php?id=1176)

#### [bzoj2244 [SDOI2011]拦截导弹](http://www.lydsy.com/JudgeOnline/problem.php?id=2244)

#### [bzoj4025 二分图](http://www.lydsy.com/JudgeOnline/problem.php?id=4025)

#### [bzoj1453 [Wc]Dface双面棋盘](http://www.lydsy.com/JudgeOnline/problem.php?id=1453)

#### [bzoj3276 磁力](http://www.lydsy.com/JudgeOnline/problem.php?id=3276)

#### [bzoj1790 [Ahoi2008]Rectangle 矩形藏宝地](http://www.lydsy.com/JudgeOnline/problem.php?id=1790)

#### [bzoj3236 [Ahoi2013]作业](http://www.lydsy.com/JudgeOnline/problem.php?id=3236)

#### [bzoj4553 [Tjoi2016&Heoi2016]序列](http://www.lydsy.com/JudgeOnline/problem.php?id=4553)



---

## 整体二分

#### [NKOJ2670 动态区间第K小数](http://42.247.7.121/zh/Problem/Details?id=2670)

#### [NKOJ3932 Meteors](http://42.247.7.121/zh/Problem/Details?id=3932)

#### [NKOJ4054 [Hnoi2016 day1]网络](http://42.247.7.121/zh/Problem/Details/4054)

#### [bzoj2738 矩阵乘法](http://www.lydsy.com/JudgeOnline/problem.php?id=2738)
