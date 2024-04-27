#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*
Tên tỉnh thành: Hà Nội
Tên đơn vị: Công ty ABC
Địa chỉ: Số 123 Đường ABC, Quận XYZ, Hà Nội
Số điện thoại: 123456789
*/

const int MAX_SIZE = 1000;
typedef unsigned long long Number;
typedef int Position;

// danh sách mẫu tin
struct NumberInfo
{
    char *city;
    char *owner;
    char *address;
    char *nhamang;
    int number;
};

typedef struct NumberInfo *numberInfo;

// danh bạ
struct Node
{
    struct Node *next;
    struct NumberInfo value;
    struct Node *prev;
};

typedef struct Node* List;
typedef struct Node*Position;
numberList create(int maxsize)
{
    numberList L = malloc(sizeof(struct NumberList));
    L->maxsize = maxsize;
    L->count = 0;
    L->list = malloc(maxsize * sizeof(struct NumberInfo));
    return L;
}

//
void setNumber() {}

// in danh sách thông tin tất cả danh bạ
void display(numberList L)
{
    Position p;
    for (p = 0; p < L->count; p++)
        printf("City: %s\nUnit: %s\nAddress: %s\nNumber: %lld", L->list[p].city, L->list[p].owner, L->list[p].address, L->list[p].number);
}

// chèn vào đầu hoặc cuối danh sách
void add() {}

// chèn vị trí bất kì
void insert() {}

// tìm kiếm theo các tiêu chí
Position find() {}

Position find1() {}

Position find2() {}

Position find3() {}

// sắp xếp theo các tiêu chí, @override
void Arrange() {}

void Arrange() {}

void Arrange() {}

// xóa mẫu tin
void delete() {}

// liệt kê danh bạ từng tỉnh thành
void list()
{
}

// thống kê số lượng thuê bao theo tỉnh thành
void count() {}

// tìm và thông báo nếu có trùng lặp, xóa
void duplicate() {}

/*                  */
int main()
{

    numberList L;
    L = create(MAX_SIZE);

    return 0;
}