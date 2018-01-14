# CDQ&&GB CDQ分治、整体二分

>%%%Oblack...

## CDQ分治

第一类CDQ：算出左边和右边的答案，在合并

第二类CDQ：算出左边的答案，统计对右边的影响，再处理右边 :fire:

#### [NKOJ3655 菊花的故事](http://42.247.7.121/zh/Problem/Details?id=3655) :kiss:

模板 :clapper:

#### [NKOJ2041 CQOI2011 动态逆序对](http://42.247.7.121/zh/Problem/Details?id=2041) :heavy_check_mark:

CDQ:

第一维删除时间，最先删的放在后面

第二维数组位置，小的在左边

第三位值

#### [NKOJ2739【Violet III】天使玩偶](http://42.247.7.121/zh/Problem/Details?id=2739)

#### [NKOJ3933 贝壳串](http://42.247.7.121/zh/Problem/Details?id=3933) :kiss:

方程$f[i]=\sum_{j=0}^i f[j]*a[i-j]$

fft+cdq，处理左边答案对右边的影响即可

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



## 整体二分

#### [NKOJ2670 动态区间第K小数](http://42.247.7.121/zh/Problem/Details?id=2670) :heavy_check_mark: :fireworks: :clapper: 

整体二分

二分一个mid,以时间顺序讨论，对于值小于等于mid的数和修改，用树状数组统计起来

由于是以时间顺序讨论，所以当前讨论的询问中，若满足k个，说明它的答案是小于mid的（因为树状数组里只统计了小于mid的值），将它划到左边继续讨论

对于不满足k个的，去掉小于mid的影响，放入右边讨论

对于数和修改，也按照mid进行划分

直到分治到底层，这时询问都已有了答案 :smile: :dog:

#### [NKOJ3932 Meteors](http://42.247.7.121/zh/Problem/Details?id=3932)

#### [NKOJ4054 [Hnoi2016 day1]网络](http://42.247.7.121/zh/Problem/Details/4054)

#### [bzoj2738 矩阵乘法](http://www.lydsy.com/JudgeOnline/problem.php?id=2738)
