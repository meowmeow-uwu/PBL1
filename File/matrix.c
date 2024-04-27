#include <stdio.h>
#include <stdlib.h>
void nhap(float a[][100], int n);
void xuat(float a[][100], int n);
void tich(float a[][100], float b[][100], int n, float plus[][100]);
void tong(float a[][100], float b[][100],int n,float sum[][100]);

    FILE *f1;

int main(){

    f1=fopen("E:\\f1.txt","r");
    if (f1==NULL) {
        printf("File khong ton tai");
        return 1;
    }
    else printf("Mo file thanh cong!\n");

    int n;
    printf("Nhap n ");
    fscanf(f1,"%d",&n);
    printf("%d\n",n);
    float a[n][n], b[n][n],sum[n][n],plus[n][n];

    nhap(a,n);
    nhap(b,n);
    xuat(a,n);
    xuat(b,n);
    //tong(a,b,n,sum);
    //xuat(sum,n);
    fclose(f1);
    return 0;
}

void nhap(float a[][100], int n){
 int i,j;
 for(i=0;i<n;i++)
    for (j=0;j<n;j++)
    fscanf(f1,"%f",&a[i][j]);
    return;
}

void xuat(float a[][100], int n){
    printf("\n");
    int i,j;
for (i=0;i<n;i++) {
    for (j=0;j<n;j++)
    printf("%f",a[i][j]);
    printf("\n"); }
    printf("\n");
    return;
}

void tich(float a[][100], float b[][100], int n, float plus[][100]){
	int i,j,k;
    for (i=0;i<n;i++)
    for (k=0;k<n;k++)
    for (j=0;j<n;j++)
        plus[i][k]=plus[i][k]+a[i][j]*b[j][k];
        return;
}

void tong(float a[][100], float b[][100], int n, float sum[][100]){
	int i,j;
for (i=0;i<n;i++)
for (j=0;j<n;j++)
    sum[i][j]=a[i][j]+b[i][j];
    return;
}
