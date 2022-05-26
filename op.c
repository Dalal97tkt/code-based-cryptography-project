#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include <time.h>
#include <sys/types.h>
#include <sys/resource.h>
//-------------------------to calculate the timing--------------------------------------
unsigned long int cputime()
{
  struct rusage rus;

  getrusage (0, &rus);
  return rus.ru_utime.tv_sec * 1000 + rus.ru_utime.tv_usec / 1000;
}
//--------------------BInary multiplication----------------------------
//we want to multiply vect 1 by vect2 both are of size n
//first we define vect_P ofsize 2n-1 and initialize it to zero
void ini2zero(int size, unsigned short int vect[])
 {
  for(int i=0;i<size;i++)
   {
    vect[i]=0;
   }
 }
// we defined a necessary function that divide each element fo a vector by 2
void mod2(int size, unsigned short int vect[])
  {
  for(int i=0;i<size;i++)
   {
    vect[i]=vect[i]%2;
   }
 }
//now for the multiplication 
void multiply0 (short unsigned  vect1[], short unsigned vect2[], int size, unsigned short int  vect_P[])
 {
  int indx, i;
  ini2zero(2*size-1,vect_P);
  for(indx=0;indx<size;indx++)
   {
    for(i=0;i<size;i++)
     {
      vect_P[i+indx]+=vect1[i]*vect2[indx];
     }
   }
  mod2(2*size -1, vect_P);
 }
//------------------------------------------------division------------------------------------
//first function will give us the "degree"
int degree_s(int size, unsigned short int vect[])
 {
  int i;
  for(i=0;i<size;i++)
   {
    if(vect[i]==1)
     {
      break;
     }
   }
  return size-i;
 }
//adding zero to the divisor until we reach correct size
void padding(int ss, unsigned short int divisor[], unsigned short int divisor2[], int sb)
 {
  for(int i=0;i<ss;i++)
   {
    divisor2[i]=divisor[i];
    //printf("%hd ",divisor2[i]);
   }
  for(int i=ss;i<sb;i++)
   {
    divisor2[i]=0;
    //printf("%hd",divisor2[i]);
   }
  }
//concatenation function necessary along the way , shifts bits to the left and append the value
void concatenate(int size, unsigned short int vect[], int value)
 {
  for(int i=0;i<size-1;i++)
   {
    vect[i]=vect[i+1];
   }
  vect[size-1]=value;
 }
//shifting a vector one place to the right
void shiftr(int size, unsigned short int vect[])
 {
  int temp=vect[size-1],i;
  for(i=size-1;i>0;i--)
   {
    vect[i]=vect[i-1];
   }
  vect[0]=temp;
 }
//the division function(vect1/vect2) the remainder
void dividing( unsigned short int vect1[], int ss,int sb, unsigned short int vect2[], unsigned short int vect3[])
 {
  ini2zero(sb,vect3);
  unsigned short int vect22[sb];
  padding(ss,vect2, vect22,sb);
  printf("we entered the while loop\n");
  while(degree_s(sb, vect1)>=degree_s(ss, vect2))
   {
    printf("if\n");
    if(degree_s(sb, vect1)>=degree_s(sb,vect22))
     {
      printf("for\n");
      for(int i=0;i<sb;i++)
       {
        //printf("%d\n",vect1[i]);
        vect1[i]=(vect1[i]+vect22[i])%2;
       }
      printf("con before");
      concatenate(sb,vect3,1);
     }
     
    else
     {
      concatenate(sb, vect3,0);
     }
     printf("con after\n");
     printf("degree of dividen is %d\n",degree_s(sb,vect1));
     printf("is the problem with shiftr?\n");
     shiftr(sb,vect22);
     printf("the problem isn't with shiftr\n");
   }
 }
//---------------------------------------------------now for multiplication of 2 binary vectors of size n----------------
void trimming(int sb, int ss, unsigned short int vect1[], unsigned short int vect2[])// vect2[] contains lost of unnecessary zeros that we know of  for example 000000010 , we want it to be 0010
 {
  for(int i=0;i<ss;i++)
   {
    vect2[i]=vect1[sb-1-i];
   }
 } 
 void multiply1(unsigned short int vect1[], unsigned short int vect2[], unsigned short int vect3[], int size)
  {
   unsigned short int vectq[2*size-1];
   multiply0 (vect1, vect2,size, vectq);
   //Xn
   unsigned short int vn[size], vect4[2*size-1];
   ini2zero(size,vn);
   vn[0]=1;
   vn[size-1]=1;
   //after multiplying two vectors with each other we either have a larger dgree so we need division followed by trimming or smaller vector so we just do trimming
   if(degree_s(2*size-1,vectq)>=degree_s(size,vn))
    {
      dividing(vect3,2*size-1,size, vn, vect4);
      trimming(2*size-1,size,vectq,vect3);
    }
   else
    {
     trimming(2*size-1,size,vectq,vect3);
    }
   }
 //--------------------extended euclide to find the inverse of a binary vector----------------------------------
 int isnull(int size, unsigned short int vect[])// this function will tell us if a vector is null or not 
  {
 int i, res=1;
  for(i=0;i<size;i++)
   {
    if(vect[i]==1)
     {
      res=0;
      break;
     }
   }
  return res;
 }
 int isinv(int size, unsigned short int vect[])
  {
   int res=1;
   for(int i=0;i<size-1;i++)
    {
     if(vect[i]!=0)
      {
       res=0;
       break;
      }
    }
   if((res==1))
    {
     if(vect[size-1]=1)
      {
        res=0;
       }
     }
    return res;
   }
void vectassi(int size, unsigned short int vect1[], unsigned short int vect2[])//vect1=vect2
 {
  for(int i=0;i<size;i++)
   {
    vect1[i]=vect2[i];
   }
 }
void vectxor(int size, unsigned short int vect1[], unsigned short int vect2[])
 {
  for(int i=0;i<size;i++)
   {
    vect1[i]=(vect1[i]+vect2[i])%2;
   }
  }
void vectassiv2(int size, unsigned short int vect1[], unsigned short int newvect1[], unsigned short int quo[])
 {
 unsigned short int temp[size],temp2[size];
 vectassi(size, temp, vect1);
 vectassi(size, vect1,newvect1);
 multiply1(quo, newvect1, temp2,size);
 vectxor(size,newvect1,temp);
 }
int extended_gcd(int size, unsigned short int vect[], unsigned short int inv[])//vect1 is big
{
 unsigned short int oldr[size], r[size], olds[size],s[size],oldt[size],t[size];
 unsigned short int vn[size];
 int res=1;
   ini2zero(size,vn);
   vn[0]=1;
   vn[size-1]=1;
 vectassi(size, oldr,vn);
 vectassi(size,r, vect);
 ini2zero(size, olds);
 ini2zero(size, s);
 ini2zero(size,t);
 ini2zero(size,oldt);
 olds[size-1]=1;
 t[size-1]=1;
 unsigned short int quo[size];
 while(!isnull(size,r))
  {
  dividing(vn, size,size,vect,quo);
  vectassiv2(size,oldr, r,quo);
  vectassiv2(size,olds, s,quo);
  vectassiv2(size,oldt, t,quo);
  }
  res=isinv(size,oldr);
  vectassi(size,inv, oldt);
  return res;
 }
//-----------------------bitflipping algorithm-----------------------------------------------------------------


//-----------------------to generate the random vectors----------------------------
void generate_vect(int n, int vect[])
 {
  for(int i=0;i<n;i++)
   {
    vect[i]=rand()%2;
   }
 }
void generate_zero_vect(int n, short unsigned vect[])
 {
  for(int i=0;i<n;i++)
   {
    vect[i]=0;
   }
 }
//----------------------extra functions to help with manipulations----------------
//res=||vect||
unsigned long norm(int n, short vect[])
 {
  unsigned long res=0;
  for(int i=0;i<n;i++)
   {
    res+=vect[i];
   }
  return res;
 }
 // a function to return the bit at index ix
void int2bin(int nb, int size, short unsigned int vect[])
 {
  int i,cache=nb;
  //printf("size=%d\n",size);
  //printf("we started the function\n");
  for(i=size-1;i>=0;i--)
   {
     vect[i]=nb%2;
     //printf("vect[%d]=%d\n",i,vect[i]);
     nb/=2;
   }
   nb=cache;
   //printf("we finished\n");
 }
 //a function to determine if two vectors are equal
int are_equal(int n, short int vect1[], short int vect2[])
 {
  int res=1;
  for(int i=0;i<n;i++)
   {
    if(vect1[i]!=vect2[i])
     {
      res=0;
      break;
     }
   }
 return res;
}
// a function that takes a file as input and transform the read matrix into a vector (compact matrix form)
void file2vector(FILE *fp, unsigned long vect[])
 {
  int temp1, temp2,i, j, nb_lines, nb_col;
  fscanf(fp,"%d %d",&nb_lines,&nb_col);
  for(i=0;i<nb_lines;i++)
   {
    vect[i]=0,temp1=pow(2,nb_col-1);
    for(j=0;j<nb_col;j++)
     {
      fscanf(fp, "%d", &temp2);
      vect[i]+=(temp1*temp2);
      temp1/=2;
     }
   }
 }
//----------------------------the bitflipping code---------------------------
int Bitflipping(int n, int t, int T, unsigned short int h0[], unsigned short int h1[],unsigned short int s[], unsigned short int u[], unsigned short int v[])///
 {
  int res=1,i,j,m=2*n;
 // short u[n], v[n], syndrome[n];
  unsigned short int syndrome[n];
  //instead of defining a hige matrix, i resorted to putting it inside of a file named mat_h.txt
  FILE *fp;
  fp=fopen("mat_h.txt","w+");
  //printf("declaring u, v and H\n");
  fprintf(fp,"%d\n",n);//the first line of the file will contain the nb of lines 
  fprintf(fp,"%d\n",m);//the second line will contain the nu,ber of columns 
  //int temp[m];
  //printf("we entered the first for loop\n");
  for(i=0;i<n;i++)
   {
    u[i]=0;
    v[i]=0;
    syndrome[i]=s[i];//syndrome=s
    for(j=0;j<n;j++)
     {
    fprintf(fp,"%d ",h0[(n-i+j)%n]); // H=(rot(h0)T, rot(h1)T)
     }
    for(j=n;j<m;j++)
     {
    fprintf(fp,"%d ",h1[(-i+j)%n]);
     }
    fprintf(fp,"\n");
   }
  fclose(fp);
  //printf("we exited the first for loop\n");
  fp=fopen("mat_h.txt","r+");
  unsigned long vect_h[m];
  file2vector(fp, vect_h);
  fclose(fp);
  // to avoid operating on a huge matrix 
  unsigned long long sum_vec[m];
  unsigned short int flipped_positions[m], temp[m];
  printf("we entered the while loop\n");
  while( ((norm(n,u)!=t)||(norm(n,v)!=t))&&((norm(n,syndrome))!=0))
   {
   for(i=0;i<m;i++)
      {
       sum_vec[i]=0;
       flipped_positions[i]=0;///flipped_positions[]=0
        for(j=0;j<n;j++)
         {
          sum_vec[i]=sum_vec[i]+((syndrome[j])*((vect_h[j]>>i)&1));//sum_vect=syndrome*H
         }
	}
  for(i=0;i<m;i++)
   {
    if(sum_vec[i]>=T)
     {
      flipped_positions[i]=(flipped_positions[i]+1)%2;//positions to flip
     }
    }
    for(i=0;i<n;i++)
     {
      u[i]=(u[i]+flipped_positions[i])%2;//(u,v)xor flipped_positions
      v[i]=(v[i]+flipped_positions[n+i])%2;
     }
     for(i=0;i<n;i++)
     {
      int2bin(vect_h[i],m,temp);
      for(j=0;j<m;j++)
       {
        syndrome[i]=syndrome[i]-(temp[j]*flipped_positions[j]);//syndrome =syndrome -H *flipped positions 
       }
      syndrome[i]=syndrome[i]%2;
     }
   }
   printf("we exited the while loop\n");
   unsigned short int vect_zero[n];
   generate_zero_vect(n,vect_zero);
   for(i=0;i<n;i++)
      {
       syndrome[i]=0;
       int2bin(vect_h[i],m,temp);
       for(j=0;j<n;j++)
        {
         syndrome[i]-=temp[j]*u[j];
        }
       for(j=n;j<m;j++)
        {
         syndrome[i]-=temp[j]*v[n-j];
        }
       syndrome[i]=syndrome[i]%2;
      }
     if(!are_equal(n, vect_zero,syndrome))//edit it
      {
      res=0;
      }
  
  return res;
 }
//--------------------------------------------------the key exchange algorithm----------------------------------
void hashing ( char * name)// printing the hash value into a file
 {
  char str[128];
  FILE *fp,*p;
  fp=fopen("hash.txt","w+");
  sprintf(str,"md5sum %s",name);//tthe command is md5sum filename
  p=popen(str,"r");
  char temp;
  for(int i=0;i<32;i++)
  {
   temp=fgetc(p);
   fprintf(fp,"%d ",temp);
  }
  fclose(fp);
  pclose(p);
 }
//generating the h vectors
int true_perm( int n, int vect[],int position)
 {
  int res =1;
  for(int i=0;i<position;i++)
   {
    if(vect[i]==vect[position])
     {
      res=0;
      break;
     }
    }
   return res;
  }
//sampling a permutation at random
void rand_perm(int perm[], int n)
 {
  perm[0]=(rand()%n);
  for(int i=1;i<n;i++)
   {
    do
    {
     perm[i]=(rand()%n);
    }while(!true_perm(n,perm,i));
   }
   }
void generate_s( int n, unsigned short int s[], int w)
 {
  int pos[w],j=0;
  rand_perm(pos,w);
  for(int i=0;i<n;i++)
   {
    s[i]=0;
   }
  for(int j=0;j<w;j++)
   {
    s[pos[j]]=1;
   }
 }
void ALICE1(int n, int w)
 {
 unsigned short int h0[n];
 unsigned short int h1[n];
 unsigned short int h0inv[n];
 printf("navigating alice1\n");
 generate_s(n, h1,w);
// do{
 generate_s(n,h0,w);
 //}while(!extended_gcd(n,h0,h0inv));
 printf("we exited the while loop\n");
 unsigned short int h[n];
 multiply1(h0inv,h1,h,n);
 printf("%d\n",h[5]);
 FILE *fp;
 fp=fopen("h.txt","w+");
 for(int i=0;i<n;i++)
  {
   fprintf(fp,"%d ", h[i]);
  }
 fclose(fp);
 fp=fopen("h0.txt","w+");
 for(int i=0;i<n;i++)
  {
   fprintf(fp,"%hd ", h[i]);
  }
 fclose(fp);
 fp=fopen("h1.txt","w+");
 for(int i=0;i<n;i++)
  {
   fprintf(fp,"%hd ", h[i]);
  }
 fclose(fp);
 printf("the problem isn't with ALice 1\n");
 }
void Bob1(int t, char* s, int n)
 {
  unsigned short int e0[n],e1[n];
  int i;
  generate_s(n,e1,t);
  generate_s(n,e0,t);
    FILE *fp;
   fp=fopen("h.txt","r+");
   unsigned short int h[n];
   for(int i=0;i<n;i++)
   {
     fscanf(fp,"%hd ", &h[i]);
    }
    fclose(fp);
   unsigned short int temp[n];
   printf("before multiply1");
   multiply1(h,e1,temp,n);
   printf("after multiply 1");
   unsigned short int c1[n];
   fp=fopen("c1.txt","w+");
   for(int i=0;i<n;i++)
    {
     c1[i]=(e0[i]+temp[i])%2;
     fprintf(fp,"%d ", c1[i]);
    }
    fclose(fp);
   char * name="c1.txt";
  hashing ( name);
  
  }
  
 void ALICE2(int n, int w, int t)
 {
  FILE *fp1;
  unsigned short int temp[n], h0[n],h1[n],s[n],c1[n];
  fp1=fopen("c1.txt","r+");
  for(int i=0;i<n;i++)
   {
    fscanf(fp1,"%hd ", &c1[i]);
   }
  fclose(fp1);
   fp1=fopen("h1.txt","r+");
  for(int i=0;i<n;i++)
   {
    fscanf(fp1,"%hd ", &h1[i]);
   }
  fclose(fp1);
   fp1=fopen("h0.txt","r+");
  for(int i=0;i<n;i++)
   {
    fscanf(fp1,"%hd ", &h0[i]);
   }
  fclose(fp1);
  multiply1(h0,c1,s,n);
  unsigned short int e0[n], e1[n];
  Bitflipping(n,w,t,h0,h1,s,e0,e1);
  FILE *fp;
  fp=fopen("bla.txt","w+");
  for(int i=0;i<n;i++)
   {
    fprintf(fp,"%d ",e0[i]);
   }
  for(int i=n;i<2*n;i++)
   {
    fprintf(fp,"%d ",e1[i]);
   }
   fclose(fp);
   char *name="bla.txt";
   hashing(name);
   }
  
  
//main for testing
void printvect(int size, unsigned short int vect[])
 {
  for(int i=0;i<size;i++)
   {
    printf("%d ", vect[i]);
   }
 }
int main(int argc, char *argv[])
 {
 srand(time(NULL));//to give see to the random generator
 if(argc!=4)
  {
   printf("input n t w %s\n", argv[0]);
  }
 int n=atoi(argv[1]), t=atoi(argv[2]), w=atoi(argv[3]);
  unsigned long int start;
   start = cputime();
   printf("we started with ALice 1\n");
 ALICE1(n,w);
 printf("we finished alice 1\n");
 char *name="h.txt";
 printf("we started with Bob1\n");
 Bob1(t,name,n);
 printf("we finsihed Bob 1\n");
 
   ALICE2(n,w,t);
   printf("Computation time : %lu ms\n", cputime() - start);
 }
