#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include <time.h>
#include <sys/types.h>
#include <sys/resource.h>
unsigned long int cputime()
{
  struct rusage rus;

  getrusage (0, &rus);
  return rus.ru_utime.tv_sec * 1000 + rus.ru_utime.tv_usec / 1000;
}


//read a matrix from a file
void read_mat(int nl, int nc, char mat[][nc], FILE *fp)
 {
  for(int i=0;i<nl;i++)
   {
    for(int j=0;j<nc;j++)
     {
      fscanf(fp,"%c ",&mat[i][j]);
      }
   }
 }
//printing the matrix, just for testing 
//to be removed later 
void print_mat(int nl, int nc, char mat[][nc])
 {
  for(int i=0;i<nl;i++)
   {
    for(int j=0;j<nc;j++)
     {
      printf("%c ",mat[i][j]);
      }
      printf("\n");
   }
 }
//a function to generate identity matrix 
void gen_id(int nl, int nc, char id[][nc])
 {
  for(int i=0;i<nl;i++)
   {
    for(int j=0;j<nc;j++)
     {
      if(i==j)
       {
        id[i][j]=1+'0';
       }
       else
       {
        id[i][j]=0+'0';
       }
     }
  }
 }
//-----------------------------------------------Gauss-------------------------------------------------------------
// a function to exchange between lines n1 and n2
void exchange(int nl, int nc, char mat[][nc],int n1,int n2)
 {
  char temp;
  for(int i=0;i<nc;i++)
   {
    temp=mat[n1][i];
    mat[n1][i]=mat[n2][i];
    mat[n2][i]=temp;
   }
 }
//line n2= line n1 xor line n2
void xor(int nl, int nc, char mat[][nc], int n1, int n2)
 {
  for(int i=0;i<nc;i++)
   {
    mat[n2][i]=(((mat[n1][i]-'0')+(mat[n2][i]-'0'))%2)+'0';
   // printf("mat[%d][%d]-'0'=%d\n",n1,i,mat[n1][i]-'0');
   }
  }
//the gauss function 
int Gauss( int nl, int nc, char mat[][nc], char id[][nc])
 {
  int savepoint;
  for(int i=0;i<nc;i++)
   {
    for(int j=i;j<nl;j++)
     {
      //printf("mat[%d][%d]=%c\n",j,i,mat[i][j]);
      if(mat[j][i]==('1'))
       {
        savepoint=j;
        //printf("mat[%d][%d]=%c\n",j,i,mat[i][j]);
        break;
       }
      }
    //printf("savepoint =%d\n",savepoint);
    if(savepoint==nl)
     {
      return 0;
     }
    else
     {
      exchange(nl, nc, mat,savepoint,i);;
      exchange(nl, nc, id,savepoint,i);
      for(int l=0;l<nl;l++)
       {
        if((l!=i)&&(mat[l][i]==('1')))
         {
          xor( nl, nc, mat, i, l);
          xor( nl, nc, id, i, l);
         }
        }
      }
      
    }
   return 1;
  }
//------------------------------------------------------ISD----------------------------
//step1: generate a random permuation matrix
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
void perm_mat_gen(int n, char perm_mat[][n])
 {
  int perm[n];
  rand_perm(perm,n);
  for(int i=0;i<n;i++)
   {
    for(int j=0;j<n;j++)
     {
      if(perm[j]==i)
       {
        perm_mat[i][j]=1+'0';
       }
      else
       {
        perm_mat[i][j]=0+'0';
       }
      }
     }
   }
//C=H*P, the multiplication of the permuation and the parity check matrices
//multiplying two matrices together
void matrix_mul(int n,int m, char A[][n],char B[][n],char C[][n])
 {
  int temp;
  for(int i=0;i<m;i++)
   {
    for(int j=0;j<n;j++)
     {
      temp=0;
      for(int k=0;k<n;k++)
       {
        temp+=((A[i][k]-'0')*(B[k][j]-'0'));
       }
       temp=temp%2;
       C[i][j]=temp+'0';
      }

    }
   }
//step 3: finding U that satisfies UHP=Id
//getting the smaller matrix
void get_square_mat(int m, int n, char A[][m],char B[][n])
 {
  for(int i=0;i<m;i++)
   {
    for(int j=0;j<m;j++)
     {
      A[i][j]=B[i][j];
      }
    }
 }
void vect_assign(int n, int vect1[], int vect2[])
 {
  for(int i=0;i<n;i++)
   {
    vect1[i]=vect2[i];
   }
  }

//trasnpose of a matrix
void transpose_mat(int n, char M[][n])
 {
  char temp[n][n];
  for(int i=0;i<n;i++)
   {
    for(int j=0;j<n;j++)
     {
      temp[i][j]=M[i][j];
     }
   }
  for(int i=0;i<n;i++)
   {
    for(int j=0;j<n;j++)
     {
      M[i][j]=temp[j][i];
     }
    }
  }   
//Multiplication of a vector and a matrix
void vect_mat_mul( int n, int vect[], char mat[][n], int res[])
 {
  for(int i=0;i<n;i++)
   {
    res[i]=0;
    for(int j=0;j<n;j++)
     {
       res[i]+=vect[j]*(mat[j][i]-'0');
      }
     res[i]=res[i]%2;
    }
  } 
int norm_vect(int n, int vect[])
 {
  int nor=0;
  for(int i=0;i<n;i++)
   {
    nor+=vect[i];
   }
   return nor;
 }
int get_U(int n, int m, char C[][n], int norm,int vect[])
 {
  int res;//??
  char A[m][m], id[m][m];
  norm=5000;//??
  get_square_mat(m, n, A,C);
  //print_matrix(m,m,A);
  gen_id(m,m,id);
  res=Gauss(m,m,A,id);
  //res=inverse_mat(m, A);

  if(res==1)
   {
   transpose_mat(m, A);
   vect_mat_mul(m, vect,A,vect);
   norm=norm_vect(m,vect);
   }
  return norm;
 }
void ISD(int m, int n, char H[][n], int s[], int w, int ret_vect[])
 {
  int norm,vect[m],res=0,cntr=0;
  vect_assign(m,vect,s);
  char perm_mat[n][n],C[m][n];
  printf("counter=%d\n",cntr);
  do{
  perm_mat_gen(n,perm_mat);
  matrix_mul(n,m, H,perm_mat,C);
  norm=get_U(n,m,C,norm,vect);
  vect_assign(m,vect,s);
  cntr++;
  printf("counter=%d\n",cntr);
  }while((norm>w));
  for(int i=0;i<m;i++)
   {
    ret_vect[i]=vect[i];
   }
  for(int i=m;i<n;i++)
   {
    ret_vect[i]=0;
   }
   char id[n][n];
   gen_id(n,n,id);
   Gauss(n,n,perm_mat,id);
   //inverse_mat(n, perm_mat);
   vect_mat_mul(n,ret_vect,perm_mat,ret_vect);
 }
//----------------------------------------Generation of the parity check matrix and s-----------------------------------------
void generate_H(int n, int k)
 {
  FILE *fp;
  fp=fopen("PC.txt","w+");
  int d=n-k+1,counter,pos;
  fprintf(fp,"%d\n",k);
  fprintf(fp,"%d\n",n);
  for(int i=0;i<k;i++)
   {
    counter=0;
    for(int j=0;j<n;j++)
     {
       if(j<i)
         {
           fprintf(fp,"%s","0 ");
         }
       else if(counter<d)
         {
           pos=((rand()%((n-k)/2)));
           fprintf(fp,"%s", "1 ");
           counter++;
         }
          else 
           {
           fprintf(fp,"%s","0 ");
           }
        }
       fprintf(fp,"\n");
    }
    fclose(fp);
    printf("H is a %d %d %d code\n",n,k,d);
  }
void generate_s( int n, int s[], int w)
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
//-----------Main for testing-------------------------------------------------------------------
int main(int argc, char *argv[])
 {
 // if(argc!=2)
   //{
    //printf("input the name of the file containing the matrix %s\n", argv[0]);
   //}
 //FILE *fp;
 //char *s=argv[1];
 //fp=fopen(s,"r+");
 //int nl, nc;
 //fscanf(fp,"%d %d ", &nl,&nc);
 //char mat[nl][nc],id[nl][nc];
 if(argc!=4)
  {
   printf("give me n k w %s\n",argv[0]);
  }
   srand(time(NULL));
 int n=atoi(argv[1]),k=atoi(argv[2]), w=atoi(argv[3]),m=n-k;
 //the matrices and vectors
 int s[m],e[n];
 char H[m][n],id[m][m];
 generate_H(n,m);
 //gen_id(nl, nc,mat);
 FILE *fp;
 fp=fopen("PC.txt","r+");
 int t1,t2;
 fscanf(fp,"%d %d",&t1,&t2);
 read_mat(m,n,H,fp);
 fclose(fp);
 generate_s(m,s,w);
 printf("norm of s is%d\n",norm_vect(m,s));
 //print_mat(nl,nc,mat);
 //printf("\n");
 gen_id(k, k, id);
 //print_mat(nl,nc,id);
 //printf("\n");

 //printf("%d\n",Gauss( nl, nc, mat, id));
 //printf("the result\n");
 //print_mat(nl,nc,id);
 //printf("\n");
 unsigned long int start;
 start = cputime();
 ISD(m,n,H,s,w,e);
 //e is the returned vector
 printf("Computation time : %lu ms\n", cputime() - start);
  }
