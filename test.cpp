/*
Bài 1.
Định dạng trong file SINHVIEN.TXT như sau:
- Dòng đầu tiên là thông tin của 1 sinh viên:
+ Họ tên
+ Mã sinh viên
+ Ngày tháng năm sinh: 1 chuỗi string định dạng dd/mm/yyyy
+ Điểm trung bình học kì

VD:
SINHVIEN.TXT
Nguyen Van Teo, N15DCCN165, 09/06/1997, 9.0
Nguyen Van B, N14DCCN189, 10/07/1996, 8.9
Nguyen Van C, N13DCCN181, 08/09/1995, 9.5
Nguyen Van C, N13DCCN179, 10/12/1995, 8.0
Nguyen Van B, N14DCCN185, 18/10/1995, 9.5


Yêu cầu:
1. Đọc dữ liệu từ file SINHVIEN.TXT
2. Nhập vào tên sinh viên và in ra màn hình thông tin sinh viên có tên trùng với tên cần tìm
3. Ghi thông tin sinh viên có điểm trung bình học kì cao nhất vào file DIEMMAX.TXT
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Khai báo cấu trúc thông tin số điện thoại
struct NumberInfo
{
    char *number;
    char *nhamang;
    char *owner;
    char *address;
    char *city;
};

// Khai báo cấu trúc Node trong danh sách liên kết
struct Node
{
    struct NumberInfo value;
    struct Node *next;
    struct Node *prev;
};

typedef struct NumberInfo NumberInfo;
typedef struct Node *Node;
typedef struct Node *List;
typedef struct Node *Position;

Position InsertFirst(List L,struct NumberInfo e)
{
    Position newItem = (Node)malloc(sizeof( struct Node));
    if (newItem == NULL)
    {
        fprintf(stderr, "Khong du bo nho\n");
        exit(EXIT_FAILURE);
    }

    newItem->value = e;
    newItem->next = L->next;
    newItem->prev = L;
    if (newItem->next != NULL)
        newItem->next->prev = newItem;
    L->next = newItem;

    return newItem;
}

// Hàm đọc file - đọc thông tin một số điện thoại từ file numberInfo.TXT
void Doc_File_Thong_Tin_So_Dien_Thoai(FILE *filein, NumberInfo *e)
{
    char line[256];
    if (fgets(line, sizeof(line), filein) != NULL)
    {
        // Sử dụng strtok để tách các trường thông tin từ dòng đọc được
        char *token = strtok(line, ",");
        e->number = strdup(token); // Sao chép và lưu trữ số điện thoại

        token = strtok(NULL, ",");
        e->nhamang = strdup(token); // Sao chép và lưu trữ nhà mạng

        token = strtok(NULL, ",");
        e->owner = strdup(token); // Sao chép và lưu trữ tên chủ sở hữu

        token = strtok(NULL, ",");
        e->address = strdup(token); // Sao chép và lưu trữ địa chỉ

        token = strtok(NULL, "\n");
        e->city = strdup(token); // Sao chép và lưu trữ thành phố
    }
}


// Hàm đọc danh sách số điện thoại từ file
void Doc_Danh_Sach_So_Dien_Thoai(FILE *filein, List pL)
{
    NumberInfo e;
    while (!feof(filein))
    {
        Doc_File_Thong_Tin_So_Dien_Thoai(filein, &e);
        if (e.number != NULL)
        {
            InsertFirst(pL, e);
        }
    }
}
// Hàm chèn một số điện thoại vào đầu danh sách liên kết

// Hàm hiển thị danh sách số điện thoại
void Display(List L)
{
    printf("\nDanh sach so dien thoai:\n");
    int count = 1;
    while (L->next != NULL)
    {
        printf("%d. So dien thoai: %s\n   Nha mang: %s\n   Chu so huu: %s\n   Dia chi: %s\n   Thanh pho: %s\n",
               count++, L->next->value.number, L->next->value.nhamang,
               L->next->value.owner, L->next->value.address, L->next->value.city);
        L = L->next;
    }
    printf("\n");
}

int main()
{
    FILE *filein;
    filein = fopen("numberInfo.TXT", "r");
    if (filein == NULL)
    {
        fprintf(stderr, "Khong mo duoc file\n");
        return 1;
    }

    List pL = (Node)malloc(sizeof(struct Node));
    if (pL == NULL)
    {
        fprintf(stderr, "Khong du bo nho\n");
        fclose(filein);
        return 1;
    }
    pL->next = NULL;

    Doc_Danh_Sach_So_Dien_Thoai(filein, pL);
    Display(pL);

    // Giải phóng bộ nhớ
    while (pL != NULL)
    {
        Position temp = pL;
        pL = pL->next;
        free(temp);
    }

    fclose(filein);

    return 0;
}