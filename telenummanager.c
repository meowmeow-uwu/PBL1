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

// danh sách mẫu tin
struct NumberInfo
{
    char *city;
    char *owner;
    char *address;
    char *nhamang;
    char *number;
};

typedef struct NumberInfo *numberInfo;

// danh bạ
struct Node
{
    struct Node *next;
    struct NumberInfo value;
    struct Node *prev;
};

typedef struct Node *List;
typedef struct Node *Position;

// create a list of number
List create()
{
    List L = malloc(sizeof(struct Node));
    L->next = NULL;
    L->prev = NULL;
    return L;
}

// create one new number element
struct NumberInfo setNumber(char *number, char *city, char *owner, char *address)
{
    struct NumberInfo one;

    one.number = strdup(number);
    one.city = strdup(city);
    one.owner = strdup(owner);
    one.address = strdup(address);

    return one;
}

// in danh sách thông tin tất cả danh bạ
void display(List L)
{

    int count = 1;
    while (L != NULL)
    {
        printf("%d. -Number: %s\n  -City: %s\n  -Unit: %s\n  -Address: %s\n", count++, L->value.number, L->value.city, L->value.owner, L->value.address);
        L = L->next;
    }
    printf("\n");
}

// chèn vào đầu hoặc cuối danh sách
void add() {}

// chèn vị trí bất kì
Position insert(List *pL, struct NumberInfo e, Position p)
{
    Position newItem = malloc(sizeof(struct Node));
    newItem->value = e;
    if (*pL == NULL || p == NULL)
    {
        newItem->next = NULL;
        *pL = newItem;
    }
    else
    {
        newItem->next = p->next;
        newItem->prev = p;
        p->next = newItem;
        if (newItem->next != NULL)
        {
            newItem->next->prev = newItem;
        }
    }
    return newItem;
}

// tìm kiếm theo các tiêu chí
Position find(List pL, char *city)
{
    while (pL != NULL && strcmp(pL->value.city, city) != 0)
        pL = pL->next;
    return pL;
}

Position find1() {}

Position find2() {}

Position find3() {}

// sắp xếp theo các tiêu chí, @override
void Arrange1() {}

void Arrange2() {}

void Arrange3() {}

// xóa mẫu tin
void delete(List L, char* city)
{
    Position p;
    p=find(L, city);
    if (p == NULL)
        return;
    p->prev->next = p->next;
    if (p->next != NULL)
        p->next->prev = p->prev;
}

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
    List Contacts = create();
    Contacts = NULL;
    struct NumberInfo s1 = setNumber("0328981817", "Da Nang", "Danh", "DHBK");
    struct NumberInfo s2 = setNumber("0328981818", "Ha Noi", "Dat", "DHBK");
    Position p;
    p = insert(&Contacts, s1, p);
    p = insert(&Contacts, s2, p);
    display(Contacts);
    char *city = "Da Nang";
    // delete (Contacts, city);
    // printf("%s", Contacts->value.number);
    // display(Contacts);

    free(Contacts);
    return 0;
}