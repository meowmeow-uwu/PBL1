#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
//ham doc file
void docfile( const char *file, float a[][100], int *n){
        FILE *f = fopen(file, "r");

    //check if n != int || n == NULL
        if (fscanf(f, "%d", n) != 1){
            printf("\nKieu du lieu khong hop le!");
            fclose(f);
            exit(1);
        }

    //check if a[i][j] != float || a[i][j] == NULL
        for (int i = 0; i < *n; i++)
            for (int j = 0; j < *n; j++)
                if (fscanf(f, "%f", &a[i][j]) != 1){
                    printf("Kieu du lieu khong hop le!");
                    fclose(f);
                    exit(1);
                }

        fclose(f);
}

//ham xuat file
void xuat(float a[][100], int n){
        printf(" \n");

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++)
                printf("%5.1f  ", a[i][j]);
            printf(" \n");
            }
        printf(" \n");
}

//ham tinh tong va tich
void tinhtongtich(float a[][100], float b[][100], int n, float plus[][100], float sum[][100]){

        for (int i = 0; i < n; i++)
            for (int k = 0; k < n; k++)
                for (int j = 0; j < n; j++)
                    plus[i][k] += a[i][j] * b[j][k];

        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                sum[i][j] = a[i][j] + b[i][j];
}

//ham doi cho cot p va q
void swap(float a[][100], int n, int p, int q){
        float temp;

        for (int i = 0; i < n; i++) {
            temp = a[i][p-1];
            a[i][p-1] = a[i][q-1];
            a[i][q-1] = temp;
            }
}

//ham ghi file
void ghifile(const char *file, float a[][100], int n){
        FILE *f = fopen(file, "a");

        //check file's existence
        if (f == NULL) {
            printf("Khong the mo file de ghi\n");
            return;
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++)
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

//ham MAIN /*   */
int main() {

        FILE *f;
        char file1[100], file2[100], file3[100];
        int n, p, q, m;
        float a[100][100], b[100][100], sum[100][100], plus[100][100];int choice,check;


    do {
        printf("Menu:\n");
        printf("1. Doc file ma tran 1\n");
        printf("2. Doc file ma tran 2\n");
        printf("3. Tinh tong va tich cua 2 ma tran\n");
        printf("4. Doi cho cot p va q\n");
        printf("5. Thoat\n");
        printf("Nhap lua chon cua ban: ");
        scanf("%d", &choice);
        fflush(stdin);

        switch (choice) {
            case 1:
                printf("Nhap file chua ma tran 1: ");
                scanf("%s", file1);
                f = fopen(file1, "r");
                if (f == NULL) {
                    printf("File 1 khong ton tai! \n");
                    continue;
                }
                docfile(file1, a, &n);
                xuat(a, n);
                fclose(f);
                break;
            case 2:
                printf("Nhap file chua ma tran 2: ");
                scanf("%s", file2);
                f = fopen(file2, "r");
                if (f == NULL) {
                    printf("File 2 khong ton tai! \n");
                    continue;
                }
                docfile(file2, b, &m);
                xuat(b, m);
                fclose(f);
                break;
            case 3:
                if (n != m) {
                    printf("Hai ma tran khac cap! ");
                    break;
                }
                printf("Tao file de luu du lieu vao: ");
                scanf("%s", file3);
                f = fopen(file3, "w");
                fclose(f);
                tinhtongtich(a, b, n, plus, sum);
                printf("Ma tran tong:\n");
                xuat(sum, n);
                printf("Ma tran tich:\n");
                xuat(plus, n);
                char tong[20] = "Ma tran tong :\n";
                ghichufile(file3, tong);
                ghifile(file3, sum, n);
                char tich[20] = "Ma tran tich: \n";
                ghichufile(file3, tich);
                ghifile(file3, plus, n);
                break;
            case 4:
            {
                check = 0;
                for (;;) {
                    printf("Nhap 2 cot muon doi cua ma tran tich: ");
                    check = scanf("%d %d", &p, &q);
                    fflush(stdin);
                    if (check != 2) {
                        printf("Gia tri vua nhap khong phai so nguyen!\n");
                        continue;
                    }
                    if ((q < 1 || q > n) || (p < 1 || p > n)) {
                        printf("So cot phai tu 1 den %d, vui long nhap lai 2 cot!\n", n);
                        continue;
                    } else
                        break;
                }
                swap(plus, n, p, q);
                printf("Ma tran tich sau khi doi cot:\n");
                xuat(plus, n);
                char tichsau[100] = "Ma tran tich sau khi bien doi\n";
                ghichufile(file3, tichsau);
                ghifile(file3, plus, n);
                break;}
            case 5:
                printf("Ket thuc chuong trinh.\n");
                break;
            default:
                printf("Lua chon khong hop le.\n");
                break;
        }
    } while (choice != 5);

    getch();
    return 0;
}

