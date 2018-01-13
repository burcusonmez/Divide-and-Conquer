#include<stdio.h>
#include<algorithm>
#include<complex>
using namespace std;
typedef double db;
typedef complex<db> cp;
const int N=400005;
const db pi=3.14159265358;

int fft_len;
cp fft_wi[N];
void fft(cp A[],int ty){
	cp t0,t1;
	int i,j,k,m;
	for(i=0;i<fft_len;i++){
		for(j=0,k=i,m=1;m<fft_len;m<<=1,j=(j<<1)|(k&1),k>>=1);
		if(i<j)swap(A[i],A[j]);
	}
	fft_wi[0]=1;
	for(m=1;m<fft_len;m<<=1){
		t0=exp(cp(0,ty*pi/m));
		for(i=1;i<m;i++)fft_wi[i]=fft_wi[i-1]*t0;
		for(k=0;k<fft_len;k+=m<<1)
			for(i=k;i<k+m;i++){
				t0=A[i],t1=A[i+m]*fft_wi[i-k];
				A[i]=t0+t1,A[i+m]=t0-t1;
			}
	}
	if(ty==1)return;
	t0=1.0/fft_len;
	for(i=0;i<fft_len;i++)A[i]*=t0;
}
cp A[N],B[N];
int n,a[N],f[N];
void CDQ(int l,int r){
	if(l==r){
		f[l]=(f[l]+a[l])%313;
		return;
	}
	int i,mid=l+r>>1;
	CDQ(l,mid);
	for(i=l;i<=mid;i++)A[i-l]=f[i];
	for(i=mid+1;i<=r;i++)A[i-l]=0;
	for(i=0;i<=r-l;i++)B[i]=a[i];
	for(fft_len=1;fft_len<r-l+1;fft_len<<=1);
	for(i=r-l+1;i<fft_len;i++)A[i]=B[i]=0;
	fft(A,1),fft(B,1);
	for(i=0;i<fft_len;i++)A[i]*=B[i];
	fft(A,-1);
	for(i=mid+1;i<=r;i++)f[i]=(f[i]+(int)floor(A[i-l].real()+0.5))%313;
	CDQ(mid+1,r);
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]),a[i]%=313;
	CDQ(1,n);
	printf("%d",f[n]);
}