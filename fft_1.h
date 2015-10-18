#include "complextion.h"

complex * dit_fft(complex a[],int n);

complex * idft(complex a[],int n);

//complex * fft_1(short a[],short b[],int n,complex * p);//一个N点的fft同时运算两个N点实序列；
//
//complex * fft_2(short a[],int n);//一个N点的fft运算一个2N点的实序列；
//
//short * conv(short a[],int length1,short b[],int length2);//2个短序列的卷积

complex * fft_1(double a[],double b[],int n,complex * p);//一个N点的fft同时运算两个N点实序列；

complex * fft_2(double a[],int n);//一个N点的fft运算一个2N点的实序列；

double * conv(double a[],int length1,double b[],int length2);//2个短序列的卷积

int binary(int num);