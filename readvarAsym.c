#include <stdio.h>
#define  M 12
#define N 10
main()
{
  char array[M][N]={0};
  FILE *fptr;
  char c;
  char file_name[20];
  int i,j;
  
  printf("Type in the name of the file containing the Field\n");
  scanf("%s",file_name);
  fptr=fopen(file_name,"r");
  for (i=0; i<M; i++)
   for (j=0; j<N; j++){
     c=fgetc(fptr); 
     while ( !((c == '1')||(c =='0')) ) c=fgetc(fptr);
     array[i][j]=c;
   }
  fclose(fptr);

  for (i=0; i<M; i++)
   for (j=0; j<N; j++)  {
    if (j == 0) printf("\n");                
    printf("%c  ",array[i][j]);
   }
  printf("\n");

}    
