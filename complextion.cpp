#include <math.h>
#include <iostream>
#include "complextion.h"
//
complex complexadd(complex c1,complex c2)
{
	complex c;
	c.real=c1.real+c2.real;
	c.imag=c1.imag+c2.imag;
	return(c);
}
//
complex complexsub(complex c1,complex c2)
{
	complex c;
	c.real=c1.real-c2.real;
	c.imag=c1.imag-c2.imag;
	return(c);
}
//
complex complexmulti(complex c1,complex c2)
{
	complex c;
	c.real=c1.real*c2.real-c1.imag*c2.imag;
	c.imag=c1.real*c2.imag+c1.imag*c2.real;
	return(c);
}
//
complex complexconj(complex c1)
{
	complex c;
	c.real=c1.real;
	c.imag=-c1.imag;
	return(c);
}
//
complex complexr(complex c1,double r)
{
	complex c;
	c.real=c1.real*r;
	c.imag=c1.imag*r;
	return(c);
}
int convers(int t,int length)//直接把这个数的2进制位数传递过来，参数为p
{
	int i,p,num=0;
	int n=1;
	for(i=0;i<20;i++)
	{
		if(length<=n)
			break;
		n=n*2;
	}
	p=i;
	int *a=new int[p];
	for(i=0;i<p;i++)
		*(a+i)=0;
	i=0;
	while(t!=0)
	{
		*(a+i)=t%2;
		t=t/2;
		i++;
	}
	for(i=0;i<p;i++)
		num=*(a+i)+2*num;
	return num;
}
//
void nixu(complex a[],int length)
{
	int j=0,i;
	complex t;
	bool *b=new bool[length];
	for(i=0;i<length;i++)
		*(b+i)=false;
	for(i=0;i<length;i++)
	{
		j=convers(i,length);
		if((i!=j)&&(*(b+i)==false))
		{
			t=*(a+i);
			*(a+i)=*(a+j);
			*(a+j)=t;
		}
		*(b+j)=true;
	}
	return;
}
//
