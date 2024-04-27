#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

//ham doc file
void docfile(const char *file, float a[][100], int *n){
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

 //hien thi menu
void menu(){
        printf("  -------MENU-------\n");
        printf("1. DOC MA TRAN TU FILE\n");
        printf("2. XUAT MA TRAN RA MAN HINH\n");
        printf("3. TINH TONG VA TICH 2 MA TRAN\n");
        printf("4. DOI 2 COT MA TRAN\n");
        printf("5. LUU MA TRAN VAO FILE \n");
        printf("6. KET THUC CHUONG TRINH\n");
        printf("  ------------------");
        printf("\nVUI LONG CHON : \0.t");
}

//check sai du lieu
void check(int *choose){
    int check;
    for(;;){
        check = scanf("%d", choose);
        while(getchar() != '\n');
        if(check != 1){
                printf("\nGia tri vua nhap khong hop le!\n");
                printf("\nVui long nhap lai: ");
                continue;
                }
        else break;
            }
}

//ham MAIN /*   */
int main() {

        FILE *f;
        char file[100], name[10];
        int p, q, choose, chck, count, m = 0, n = 0, cal = 0;
        float a[100][100], b[100][100], sum[100][100], plus[100][100];

    menu:
        menu();
        check(&choose);
        switch(choose){
//
            case 1:
                while(1) {
                    printf("\nNhap file chua ma tran A: ");
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

                while(1) {
                    printf("\nNhap file chua ma tran B: ");
                    scanf("%s", file);
                    f = fopen(file, "r");

                    if(f == NULL) {
                        printf("File 2 khong ton tai! \n");
                        continue;
                        }

                    docfile(file, b, &m);
                    xuat(b, m);
                    break;
                }

                printf("\n Nhan phim bat ky de quay lai menu! ");
                getch();
                break;
//
            case 2:
                count = 0;
                if (n != 0){
                    printf("CAC MA TRAN CO THE CHON \n");
                    printf("%d. MA TRAN A\n", ++count);
                    printf("%d. MA TRAN B\n", ++count);
                    if(cal==1){
                        printf("%d. MA TRAN TONG \n", ++count);
                        printf("%d. MA TRAN TICH \n", ++count);
                    }
                }
                if (n == 0 && m == 0){
                    printf ("BO NHO KHONG CO MA TRAN NAO!\n");
                    printf("\nNhan phim bat ky de quay lai menu! ");
                    getch();
                    break;
                }
                printf("CHON MA TRAN MUON XUAT: ");

            check1:
                check(&choose);
                if(choose >= 1 && choose <= count){}
                else {
                    printf("Khong hop le!\n Vui long nhap lai: ");
                    goto check1;
                }

                switch(choose){
                    case 1: xuat(a, n);    break;
                    case 2: xuat(b, m);    break;
                    case 3: xuat(sum, n);  break;
                    default: xuat(plus, n);break;
                }
                printf("\n Nhan phim bat ky de quay lai menu! ");
                getch();
                break;
//
            case 3:
                if (n == 0 && m == 0){
                    printf ("BO NHO KHONG CO MA TRAN NAO!\n");
                    printf("\nNhan phim bat ky de quay lai menu! ");
                    getch();
                    break;
                }
                printf("\nMa tran A: \n");
                xuat(a, n);
                printf("\nMa tran B: \n");
                xuat(b, m);
                if(m != n){
                    printf("\nHai ma tran khong cung bac!");
                    printf("\nNhan phim bat ki de quay lai!");
                    getch();
                    break;
                }
                tinhtongtich(a, b, n, plus, sum);
                printf("\nMa tran tong C:\n");
                xuat(sum, n);
                printf("Ma tran tich D:\n");
                xuat(plus, n);

                cal = 1;
                printf("\nNhan phim bat ky de quay lai menu! ");
                getch();
                break;
//
            case 4:
            count = 0;
                if (n != 0){
                    printf("CAC MA TRAN CO THE CHON \n");
                    printf("%d. MA TRAN A\n", ++count);
                    printf("%d. MA TRAN B\n", ++count);
                    if(cal == 1){
                        printf("%d. MA TRAN TONG \n", ++count);
                        printf("%d. MA TRAN TICH \n", ++count);
                    }
                }
                if (n == 0&&m == 0){
                    printf ("BO NHO KHONG CO MA TRAN NAO!\n");
                    printf("\nNhan phim bat ky de quay lai menu! ");
                    getch();
                    break;
                }
                chck = 0;
                printf(" CHON MA TRAN MUON DOI: ");
            check2:
                check(&choose);
                if(choose >= 1 && choose <= count){}
                else {
                    printf("\nKhong hop le!\n Vui long nhap lai: ");
                    goto check2;
                    }

                for(;;){

                    printf("\nNhap 2 cot muon doi cua ma tran tich: ");
                    chck = scanf("%d %d", &p, &q);
                    while(getchar() != '\n');

                    if(chck != 2){
                        printf("\nGia tri vua nhap khong phai so nguyen!\n");
                        continue;
                        }

                    if((q < 1 || q > n) || (p < 1 || p > n)){
                        printf("\nSo cot phai tu 1 den %d, vui long nhap lai 2 cot!\n",n);
                        continue;
                        }
                    else break;
                }

                switch(choose){

                case 1:
                    printf("\nMa tran A: ");
                    xuat(a, n);
                    swap(a, n, p, q);
                    printf("Ma tran A sau khi doi cot:\n");
                    xuat(a, n);
                    break;

                case 2:
                    printf("\nMa tran B: ");
                    xuat(b, m);
                    swap(b, m, p, q);
                    printf("Ma tran B sau khi doi cot:\n");
                    xuat(b, m);
                    break;

                case 3:
                    printf("\nMa tran tong: ");
                    xuat(sum, n);
                    swap(sum, n, p, q);
                    printf("Ma tran tong sau khi doi cot:\n");
                    xuat(sum, n);
                    break;

                default:
                    printf("\nMa tran tich: ");
                    xuat(plus, n);
                    swap(plus, n, p, q);
                    printf("Ma tran tich sau khi doi cot:\n");
                    xuat(plus, n);
                    break;
                }

                printf("\n Nhan phim bat ky de quay lai menu! ");
                getch();
                break;
//
            case 5:
            count = 0;
                if (n != 0){
                    printf("CAC MA TRAN CO THE CHON \n");
                    printf("%d. MA TRAN A\n",++count);
                    printf("%d. MA TRAN B\n",++count);
                    if(cal == 1){
                        printf("%d. MA TRAN TONG \n",++count);
                        printf("%d. MA TRAN TICH \n",++count);
                    }
                }
                if (n == 0 && m == 0){
                    printf ("\nBO NHO KHONG CO MA TRAN NAO!\n");
                    printf("\nNhan phim bat ky de quay lai menu! ");
                    getch();
                    break;
                }

            check3:
                check(&choose);
                if(choose >= 1 && choose <= count){}
                else {
                    printf("Khong hop le!\n Vui long nhap lai: ");
                    goto check3;
                    }

                printf("TAO HOAC NHAP TEN LUU DU LIEU: ");
                scanf("%s", file);
                f = fopen(file, "w");

                switch(choose){
                case 1:   ghifile(file,a,n);break;
                case 2:  ghifile(file,b,n);break;
                case 3: ghifile(file,sum,n);break;
                default: ghifile(file,plus,n);break;
                }
                printf("\nMa tran da duoc luu!");
                printf("\nNhan phim bat ky de quay lai menu! ");
                getch();
                break;
//
            case 6: exit(0);

            default:

                printf("\nKHONG HOP LE, NHAN BAT KY DE NHAP LAI! ");
                getch();
                break;

        }

        system("cls");
        goto menu;

        fclose(f);

        return 0;
}
