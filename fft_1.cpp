#include "fft_1.h"
#include <math.h>
#include <iostream>
using namespace std;

complex * fft_1(double a[],double b[],int n,complex * p)      //一个N点的fft同时运算两个N点实序列；
{
	complex * c=new complex[n];
	int i;
	for(i=0;i<n;i++)
	{
		c[i].real=a[i];
		c[i].imag=b[i];
	}
	complex *d=dit_fft(c,n);
	complex * a1=new complex[n];
	//complex * b1=new complex[n];
	complex c1;
	c1.real=0;
	c1.imag=-1.0/2;
	a1[0]=complexr(complexadd(d[0],complexconj(d[0])),1.0/2);
	p[0]=complexmulti(c1,complexsub(d[0],complexconj(d[0])));
	for(i=1;i<n;i++)
	{
		a1[i]=complexr(complexadd(d[i],complexconj(d[n-i])),1.0/2);
		p[i]=complexmulti(c1,complexsub(d[i],complexconj(d[n-i])));
	}
	delete [] c;
	return a1;
}
//

//complex * fft_1(short a[],short b[],int n,complex * p)      //一个N点的fft同时运算两个N点实序列；
//{
//	complex * c=new complex[n];
//	int i;
//	for(i=0;i<n;i++)
//	{
//		c[i].real=a[i];
//		c[i].imag=b[i];
//	}
//	complex *d=dit_fft(c,n);
//	complex * a1=new complex[n];
//	//complex * b1=new complex[n];
//	complex c1;
//	c1.real=0;
//	c1.imag=-1.0/2;
//	a1[0]=complexr(complexadd(d[0],complexconj(d[0])),1.0/2);
//	p[0]=complexmulti(c1,complexsub(d[0],complexconj(d[0])));
//	for(i=1;i<n;i++)
//	{
//		a1[i]=complexr(complexadd(d[i],complexconj(d[n-i])),1.0/2);
//		p[i]=complexmulti(c1,complexsub(d[i],complexconj(d[n-i])));
//	}
//	delete [] c;
//	return a1;
//}
////
complex * fft_2(double a[],int n)            //一个N点的fft运算一个2N点的实序列；
{
	double * a1=new double[n/2];
	double * a2=new double[n/2];
	int i;
	for(i=0;i<n;i++)
	{
		if(i%2==0)
			a1[i/2]=a[i];
		else 
			a2[(i-1)/2]=a[i];
	}
	double f=2*3.1415926/n;
	complex c;
	complex * b2=new complex[n/2];
	complex * b1=fft_1(a1,a2,n/2,b2);
	complex * b=new complex[n];
	for(i=0;i<n/2;i++)
	{
		c.real=cos(f*i);
		c.imag=-sin(f*i);
		b[i]=complexadd(b1[i],complexmulti(c,b2[i]));
		b[i+n/2]=complexsub(b1[i],complexmulti(c,b2[i]));
	}
	delete [] a1;
	delete [] a2;
	delete [] b2;
	return b;
}
//

//complex * fft_2(short a[],int n)            //一个N点的fft运算一个2N点的实序列；
//{
//	short * a1=new short[n/2];
//	short * a2=new short[n/2];
//	int i;
//	for(i=0;i<n;i++)
//	{
//		if(i%2==0)
//			a1[i/2]=a[i];
//		else 
//			a2[(i-1)/2]=a[i];
//	}
//	double f=2*3.1415926/n;
//	complex c;
//	complex * b2=new complex[n/2];
//	complex * b1=fft_1(a1,a2,n/2,b2);
//	complex * b=new complex[n];
//	for(i=0;i<n/2;i++)
//	{
//		c.real=cos(f*i);
//		c.imag=-sin(f*i);
//		b[i]=complexadd(b1[i],complexmulti(c,b2[i]));
//		b[i+n/2]=complexsub(b1[i],complexmulti(c,b2[i]));
//	}
//	delete [] a1;
//	delete [] a2;
//	delete [] b2;
//	return b;
//}
////

int binary(int num)
{
	int i=1,j=num;
	while((j>>=1)||(i<num))
		i<<=1;
	return i;
}
//
double * conv(double a[],int length1,double b[],int length2)    //2个短序列的卷积;
{
	int L=length1;
	int M=length2;
	int t=1;
	int i;
	//for(i=0;i<200;i++)
	//{
	//	if(t>=L+M-1)
	//		break;
	//	t=t*2;
	//}
	t = binary(L+M-1);
	//int j=i;
	double * a1=new double[t];
	double * b1=new double[t];
	for(i=0;i<L;i++)
		a1[i]=a[i];
	for(;i<t;i++)
		a1[i]=0;
	for(i=0;i<M;i++)
		b1[i]=b[i];
	for(;i<t;i++)
		b1[i]=0;
	complex * q=new complex[t];
	complex * p=fft_1(a1,b1,t,q);
	complex * u=new complex[t];
	double * xout=new double[t];
	for(i=0;i<t;i++)
	{
		*(u+i)=complexmulti(p[i],q[i]);
	}
	u=idft(u,t);
	for(i=0;i<t;i++)
		xout[i]=(u+i)->real;
	delete [] a1;
	delete [] b1;
	delete [] q;
	delete [] u;
	return xout;
}
//

//short * conv(short a[],int length1,short b[],int length2)    //2个短序列的卷积;
//{
//	int L=length1;
//	int M=length2;
//	int t=1;
//	int i;
//	//for(i=0;i<10;i++)
//	//{
//	//	if(t>=L+M-1)
//	//		break;
//	//	t=t*2;
//	//}
//	t = binary(L+M-1);
//	//int j=i;
//	short * a1=new short[t];
//	short * b1=new short[t];
//	for(i=0;i<L;i++)
//		a1[i]=a[i];
//	for(;i<t;i++)
//		a1[i]=0;
//	for(i=0;i<M;i++)
//		b1[i]=b[i];
//	for(;i<t;i++)
//		b1[i]=0;
//	complex * q=new complex[t];
//	complex * p=fft_1(a1,b1,t,q);
//	complex * u=new complex[t];
//	short * xout=new short[t];
//	for(i=0;i<t;i++)
//	{
//		*(u+i)=complexmulti(p[i],q[i]);
//	}
//	u=idft(u,t);
//	for(i=0;i<t;i++)
//		xout[i]=(u+i)->real;
//	delete [] a1;
//	delete [] b1;
//	delete [] q;
//	delete [] u;
//	return xout;
//}
////

complex * idft(complex a[],int n)            //fft的逆变换；
{
	complex * p=new complex[n];
	double t=(double) 1/n;
	int i;
	for(i=0;i<n;i++)
	{
		*(p+i)=complexconj(a[i]);
	}
	p=dit_fft(p,n);
	for(i=0;i<n;i++)
		a[i]=complexr(complexconj(p[i]),t);
	p=a;
	return p;
}
//
complex * dit_fft(complex a[],int n)//dit的fft
{
	int length=0;
	int i;
	int t;
	double td,td2=2;
	//for(int i=0;i<10;i++)
	//{
	//	if(n<=t)
	//		break;
	//	t=t*2;
	//}
	t = binary(n);
	td = t;
	int j;
	j = log10 (td)/log10 (td2) ;
	length=t;
	complex * b=new complex[length];
	for(i=0;i<length;i++)
	{
		b[i].real=0;
		b[i].imag=0;
	}
	for(i=0;i<n;i++)
	{
		b[i].imag=a[i].imag;
		b[i].real=a[i].real;
	}
	nixu(b,length);//把数组a先进行逆序排列 变为数组b
	int N=length;
	double ud, n1=2;
	const double pi=8*atan(1.0);
	complex c,wn;
	bool * flag=new bool[N];
	for(i=0;i<j;i++)
	{
		for(t=0;t<N;t++)
			flag[t]=false;
		double n2 = i;
		ud=pow(n1,n2);
		int u=ud;
		double f=pi/(2*u);//求2*pi/N
		//cout<<"f="<<f<<endl;
		for(int k=0;k<N;k++)
		{
			if(flag[k]==false)
			{
				wn.real=cos(f*k);
				wn.imag=-sin(f*k);
				c=complexadd(b[k],complexmulti(b[k+u],wn));
				b[k+u]=complexsub(b[k],complexmulti(b[k+u],wn));
				b[k]=c;
				flag[k+u]=true;
			}
		}
	}
	delete [] flag;
	return b;
}//