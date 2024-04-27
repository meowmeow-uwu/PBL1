#include <stdio.h>
#include <string.h>
int main(){
    FILE *f;
    char name[50];
    f=fopen("E:\\file.txt","w");
    if (f==NULL)
         {printf("File ko ton tai");
            return 1;
            }
    else printf("\nMo file thanh cong");
    int i;
    for (i=0;i<strlen(name);i++)
    fputc(name[i],f);
    char address[50];
    fflush(f);
    printf("\nNhap dia chi: ");
    gets(address);
    fputs(address,f);
    fputs("\n",f);
    printf("\nGhi file thanh cong");
    fclose(f);
return 0;
}
