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

enum findField
{
    city,
    number,
    address,
    owner,
    nhamang
};

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
void displayPosition(Position p) {
    printf("-Number: %s\n  -City: %s\n  -Unit: %s\n  -Address: %s\n", p->value.number, p->value.city, p->value.owner, p->value.address);
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
Position find(List pL, enum findField field, char *data)
{
    while (pL != NULL)
    {
        switch (field)
        {
            case city:
                if (strcmp(pL->value.city, data) == 0)
                    return pL;
                break;
            case number:
                if (strcmp(pL->value.number, data) == 0)
                    return pL;
                break;
            case address:
                if (strcmp(pL->value.address, data) == 0)
                    return pL;
                break;
            case owner:
                if (strcmp(pL->value.owner, data) == 0)
                    return pL;
                break;
            case nhamang:
                if (strcmp(pL->value.nhamang, data) == 0)
                    return pL;
                break;
            default:
                return NULL; // Trường không hợp lệ
        }
        pL = pL->next;
    }
    return NULL; // Không tìm thấy
}


Position find1() {}

Position find2() {}

Position find3() {}

// sắp xếp theo các tiêu chí, @override
void Arrange1() {}

void Arrange2() {}

void Arrange3() {}

// xóa mẫu tin
void delete(List L, char *data)
{
    Position p;
    p = find(L, city, data);
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
    char *c = "Da Nang";
    p = find(Contacts, city, c);
    displayPosition(p);
    // delete (Contacts, city);
    // printf("%s", Contacts->value.number);
    // display(Contacts);

    free(Contacts);
    return 0;
}