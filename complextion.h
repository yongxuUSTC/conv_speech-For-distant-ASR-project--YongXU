#include <math.h> 
struct complex
{
	double real;
	double imag;
};
//
complex complexadd(complex c1,complex c2);
//
complex complexsub(complex c1,complex c2);
//
complex complexmulti(complex c1,complex c2);
//
complex complexconj(complex c1);
//
complex complexr(complex c1,double r);
//
int convers(int t,int length);
//
void nixu(complex a[],int length);  //复数的逆序算法；
//
//void nixu2(double a[],int length);  //实数的逆序算法；