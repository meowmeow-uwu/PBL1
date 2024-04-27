#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void docfile(const char *file, float a[][100], int *n);
void xuat(float a[][100], int n);
void tinhtongtich(float a[][100], float b[][100], int n, float plus[][100], float sum[][100]);
void swap(float a[][100], int n, int p, int q);
void ghifile(const char *file, float a[][100], int n);
void ghichufile(const char *file, char *word);
/*
void fix(float n){
        FILE *f;
        f = fopen(file, "a");
        int check=0;
        while(getchar() != '\n');
        if(check != 2){
            printf("Gia tri vua nhap khong phai so nguyen!\n");
            continue;
            }
        fclose(f);
}
*/
//ham MAIN /*   */
int main() {

        FILE *f;
        char file[100], text[100];
        int m, n, p, q;
        float a[100][100], b[100][100], sum[100][100], plus[100][100];


    //doc file 1
        while(1){
            printf("Nhap file chua ma tran 1: ");
            scanf("%s", file);
            f = fopen(file, "r");

            if(f == NULL) {
                printf("File 1 khong ton tai! \n");
                continue;
            }

            docfile(file, a, &n);
            xuat(a, n);
	        break;
        }

    //doc file 2
        while(1){
            printf("Nhap file chua ma tran 2: ");
            file[0] = '\0';
            scanf("%s", file);
            f = fopen(file, "r");

            if(f == NULL){
                printf("File 2 khong ton tai! \n");
                continue;
            }

            docfile(file, b, &m);
            xuat(b, m);
            break;
        }


    //check bac cua 2 ma tran
        if (n != m){
            printf(" Hai ma tran khac cap! ");
            return 1;
        }


    //tao file doc du lieu
        printf("Tao file de luu du lieu vao: ");
        file[0] = '\0';
        scanf("%s", file);
        f = fopen(file, "w");


    //tinh tong va tich cua 2 ma tran
        tinhtongtich(a, b, n, plus, sum);
        printf("Ma tran tong:\n");
        xuat(sum, n);

        printf("Ma tran tich:\n");
        xuat(plus, n);
    
        //ghi ket qua vao file
        text[0]='\0';
        strcpy(text, "Ma tran tong: \n");
        ghichufile(file, text);
        ghifile(file, sum, n);

        text[0]='\0';
        strcpy(text, "Ma tran tich: \n");
        ghichufile(file, text);
        ghifile(file, plus, n);
    

    //doi cho cot p va q
        int check = 0;

        for(;;){
        /*         */
            printf("Nhap 2 cot muon doi cua ma tran tich: ");
            check = scanf("%d %d", &p, &q);

            while(getchar() != '\n');
            if(check != 2){
                printf("Gia tri vua nhap khong phai so nguyen!\n");
                continue;
            }

        //so cot phai tu 1 den n
            if((q<1||q>n)||(p<1||p>n)){
                printf("So cot phai tu 1 den %d, vui long nhap lai 2 cot!\n",n);
                continue;
            }
            else break;
        }

        swap(plus, n, p, q);
        printf("Ma tran tich sau khi doi cot:\n");
        xuat(plus, n);

        text[0]='\0';
        strcpy(text, "Ma tran tich sau khi bien doi: \n");
        ghichufile(file, text);
        ghifile(file, plus, n);

        fclose(f);

        return 0;
}

//ham doc file
void docfile(const char *file, float a[][100], int *n){
        FILE *f = fopen(file, "r");
        int check = 0, i, j;

    //check if n != int || n == NULL
        if (fscanf(f, "%d", n) != 1){
                printf("\nKieu du lieu khong hop le!");
                while(getchar() != '\n');
                for(;;){
                    printf("\nVui long nhap lai n: ");
                    check = scanf("%d",n);
                    while(getchar() != '\n');
                    if(check == 1)
                        break;
                    else printf("\nHay nhap 1 so nguyen: ");
                }
            }

    //check if a[i][j] != float || a[i][j] == NULL
        for (i = 0; i < *n; i++)
            for (j = 0; j < *n; j++)
                if (fscanf(f, "%f", &a[i][j]) != 1){
                    printf("\nKieu du lieu khong hop le!");
                    // while(getchar() != '\n');
                    for(;;){
                        printf("\nVui long nhap lai a[%d][%d]: ", i, j);
                        check = scanf("%f",&a[i][j]);
                        while(getchar() != '\n');
                        if(check == 1)
                            break;
                        else
                            printf("\nHay nhap 1 so thuc!");
                    }
                }

        fclose(f);
}

//ham xuat file
void xuat(float a[][100], int n){
        int i, j;
        printf(" \n");

        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++)
                printf("%5.1f  ", a[i][j]);
            printf(" \n");
            }
        printf(" \n");
}

//ham tinh tong va tich
void tinhtongtich(float a[][100], float b[][100], int n, float plus[][100], float sum[][100]){
        int i, j ,k;
        for (i = 0; i < n; i++)
            for (k = 0; k < n; k++)
                for (j = 0; j < n; j++)
                    plus[i][k] += a[i][j] * b[j][k];

        for (i = 0; i < n; i++)
            for (j = 0; j < n; j++)
                sum[i][j] = a[i][j] + b[i][j];
}

//ham doi cho cot p va q
void swap(float a[][100], int n, int p, int q){
        float temp;
        int i;

        for (i = 0; i < n; i++) {
            temp = a[i][p-1];
            a[i][p-1] = a[i][q-1];
            a[i][q-1] = temp;
            }
}

//ham ghi file
void ghifile(const char *file, float a[][100], int n){
        FILE *f = fopen(file, "a");
        int i, j;

        //check file's existence
        if (f == NULL) {
            printf("Khong the mo file de ghi\n");
            return;
        }

        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++)
                fprintf(f, "%5.1f ", a[i][j]);
            fprintf(f, "\n");
        }
        fprintf(f, "\n");

        fclose(f);
}

//ham ghi chu 1 xau vao file
void ghichufile(const char *file, char *word){

        FILE *f = fopen(file, "a");
        fprintf(f, "%s", word);
        fclose(f);
 }
