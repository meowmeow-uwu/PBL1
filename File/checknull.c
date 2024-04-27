#include <stdio.h>
int main(){
    FILE *f;
    int i,j,a[100][100],n;
    f=fopen("test.txt","w+");
    if(fscanf(f,"%d",&n)==0) printf("Loi nhap!");
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            {
                if(fscanf(f,"%d",&a[i][j])!=1)
                    printf("Loi du lieu!");
                if(a[i][j]==NULL)
                    printf("File thieu phan tu!");
            }
    return 0;
}