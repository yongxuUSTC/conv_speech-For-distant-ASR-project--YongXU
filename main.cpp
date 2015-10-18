#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <io.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "fft_1.h"
using namespace std;


void main(int argc,char *argv[])
{
	double maxV(double *p, int p_len);
	short maxW(short *p, int p_len);

	if (argc <4)
	{
		cout << "usage: conv_speech.exe clean_speech.raw h.raw out.raw"<<endl;
	}

	FILE *fp=fopen(argv[1],"rb");
	FILE *fp_h=fopen(argv[2],"rb");
	FILE *fp1=fopen(argv[3],"wb");
	//const char *file_name="wav_clean.raw";
	//const char *file_name_h="h.raw";
	//FILE *fp,*fp_h,*fp1;

	//char file_name[100];
	//cin>>(file_name);

	//char file_name_h[100];
	//cin>>(file_name_h);

//get file length
FILE* file = fopen(argv[1], "rb"); 
int N_clean=0;
if (file)  
{  
int size = filelength(fileno(file)); 
N_clean=size/2;////16bit, 2 bit
//cout<<"length= ";
//cout<<size<<endl;  
fclose(file);  
} 

//get h file length
FILE* file_h = fopen(argv[2], "rb"); 
int N_h=0;
if (file_h)  
{  
int size = filelength(fileno(file_h)); 
N_h=size/2;////16bit, 2 bit
//cout<<"length= ";
//cout<<size<<endl;  
fclose(file_h);  
} 

	fp=fopen(argv[1],"rb");
	if (fp==NULL)
	{
	printf("\n error on open this RAW file!\n");
	}

		fp_h=fopen(argv[2],"rb");
	if (fp_h==NULL)
	{
	printf("\n error on open this h file!\n");
	}

	fp1=fopen(argv[3],"wb");
	//printf ("start to get double value 1\n");
	//short speech1[160000]={0};////10 s wav length
	//short speech2[160000]={0};
	short *speech1=new short [N_clean];
	short *speech2=new short [N_h];
	short *out=(short *)malloc(N_clean*sizeof(short));
	double *d1=(double *)malloc(N_clean*sizeof(double));
	double *d2=(double *)malloc(N_h*sizeof(double));

	// read and then write
	fread(speech1,sizeof(short),N_clean,fp);
	fread(speech2,sizeof(short),N_h,fp_h);
	//printf ("start to get double value\n");

	//short max_c=maxW(speech1,N_clean);
	for (int j=0;j<N_clean;j++)
	{
	d1[j]=(speech1[j]);
	//d1[j]=ToDouble(speech1[j]);
	//d1[j] = floor(speech1[j]/60 + .5) * 60;
	}

	//short max_h=maxW(speech2,N_h);
	for (int j=0;j<N_h;j++)
	{
	d2[j]=(speech2[j]);// should not use (double) speech2[i], or it will lead to different results
	//d2[j]=ToDouble(speech2[j]);
      //d2[j] = floor( speech2[j]/60 + .5) * 60;
	}

	/*cout<<d2[0]<<endl;
	cout<<d2[38]<<endl;
	cout<<d2[39]<<endl;
	cout<<d2[40]<<endl;
	cout<<d2[41]<<endl;
	cout<<d2[90]<<endl;
	cout<<d2[91]<<endl;*/
	int p_len=N_clean+N_h-1;
	double *p=(double *)malloc(p_len*sizeof(double));
	p=conv(d1,N_clean,d2,N_h);
	double max_p=.0;
	max_p=maxV(p,p_len);//get the abosolute maximum value of p

	for (int j=0;j<N_clean;j++)
	{
	out[j]=(short)((p[j]/max_p)*32767);
	}

	fwrite(out,sizeof(short),N_clean,fp1);
	//cout<<p[0]<<endl;
	//cout<<p[1]<<endl;
	//cout<<p[202]<<endl;
	//cout<<out[3000]<<endl;

	free(out);
   free(p);
   free(d1);
   free(speech1);
   free(speech2);
   free(d2);
	fclose (fp1);
		fclose (fp);
		fclose (fp_h);
}

double maxV(double *p, int p_len)
{
double temp;
temp=fabs(p[0]);
 for (int i=1;i<p_len;i++)
 {
  
  if(fabs(p[i])>temp)
   temp=fabs(p[i]);    
 }
 return temp;

}

short maxW(short *p, int p_len)
{
short temp;
temp=abs(p[0]);
 for (int i=1;i<p_len;i++)
 {
  
  if(abs(p[i])>temp)
   temp=abs(p[i]);    
 }
 return temp;

}
