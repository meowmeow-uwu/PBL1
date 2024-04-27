#include <stdio.h>
int main(){
    int a,check;
    printf("Nhap a: ");
    for(;;){
        check=scanf("%d",&a);
        while(getchar()!='\n');
        if(check==0)
        printf("Hay nhap 1 so nguyen: ");
        else break;
    }
    return 0;
}