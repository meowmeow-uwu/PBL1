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
    // L->prev = NULL;
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
    printf("\n");
    int count = 1;
    while (L != NULL)
    {
        printf("%d. -Number: %s\n  -City: %s\n  -Unit: %s\n  -Address: %s\n", count++, L->value.number, L->value.city, L->value.owner, L->value.address);
        L = L->next;
    }
    printf("\n");
}

void displayPosition(Position p)
{
    printf("-Number: %s\n  -City: %s\n  -Unit: %s\n  -Address: %s\n", p->value.number, p->value.city, p->value.owner, p->value.address);
}

void displayCity(List L)
{
    printf("\nCurrent cities: \n");
    int count = 1;
    while (L != NULL)
    {
        printf("%d. %s\n", count++, L->value.city);
        L = L->next;
    }
    printf("\n");
}

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

// chèn bất kỳ
void insertM() {}

void insertFirst(List *pL, struct NumberInfo num)
{
    Position newItem = malloc(sizeof(struct Node));

    // if (newItem == NULL){
    //     fprintf(stderr, "Memory allocation failed.\n");
    //     return;}

    newItem->value = num;
    newItem->next = *pL;
    newItem->prev = NULL;

    if (*pL != NULL)
    {
        (*pL)->prev = newItem;
    }
    *pL = newItem;
}

// chèn vào đầu hoặc cuối danh sách
void add(List *L, struct NumberInfo num, int choose)
{
    Position q = *L;
    switch (choose)
    {
    case 1:
        insertFirst(L, num);
        break;
    case 2: // chen cuoi danh sach
        while (q->next != NULL)
            q = q->next;
        insert(L, num, q);
        break;
    default: // NULL:))
        break;
    }
}

// tìm kiếm theo các tiêu chí
List findAll(List L, enum findField field, char *data, int *count)
{
    // printf("Result found: ");
    List resultList = create(); // Tạo danh sách kết quả mới
    Position current = L;
    Position p = NULL; // Bắt đầu từ phần tử đầu tiên
    /*thieu NULL*/
    *count = 0;

    // Duyệt qua danh sách liên kết để tìm tất cả các phần tử phù hợp
    while (current != NULL)
    {
        // Kiểm tra nếu giá trị của trường tìm kiếm khớp với dữ liệu được cung cấp
        switch (field)
        {
        case city:
            if (strcmp(current->value.city, data) == 0)
            {
                // Thêm nút phù hợp vào danh sách kết quả
                p = insert(&resultList, current->value, p);
                (*count)++;
            }
            break;
        case number:
            if (strcmp(current->value.number, data) == 0)
            {
                p = insert(&resultList, current->value, p);
                (*count)++;
            }
            break;
        case address:
            if (strcmp(current->value.address, data) == 0)
            {
                p = insert(&resultList, current->value, p);
                (*count)++;
            }
            break;
        case owner:
            if (strcmp(current->value.owner, data) == 0)
            {
                p = insert(&resultList, current->value, p);
                (*count)++;
            }
            break;
        case nhamang:
            if (strcmp(current->value.nhamang, data) == 0)
            {
                p = insert(&resultList, current->value, p);
                (*count)++;
            }
            break;
        default:
            // Xử lý trường không hợp lệ nếu cần
            break;
        }
        current = current->next; // Chuyển sang nút kế tiếp trong danh sách
    }

    return resultList; // Trả về danh sách chứa tất cả các nút phù hợp
}

Position find(List L, enum findField field, char *data)
{
    Position current = L; // Bắt đầu từ phần tử đầu tiên của danh sách

    // Duyệt qua danh sách liên kết để tìm phần tử phù hợp
    while (current != NULL)
    {
        // Kiểm tra giá trị của trường dữ liệu cụ thể
        switch (field)
        {
        case city:
            if (strcmp(current->value.city, data) == 0)
            {
                return current; // Trả về phần tử nếu tìm thấy
            }
            break;
        case number:
            if (strcmp(current->value.number, data) == 0)
            {
                return current; // Trả về phần tử nếu tìm thấy
            }
            break;
        case address:
            if (strcmp(current->value.address, data) == 0)
            {
                return current; // Trả về phần tử nếu tìm thấy
            }
            break;
        case owner:
            if (strcmp(current->value.owner, data) == 0)
            {
                return current; // Trả về phần tử nếu tìm thấy
            }
            break;
        case nhamang:
            if (strcmp(current->value.nhamang, data) == 0)
            {
                return current; // Trả về phần tử nếu tìm thấy
            }
            break;
        default:
            // Xử lý trường không hợp lệ nếu cần
            break;
        }
        current = current->next; // Chuyển sang phần tử tiếp theo trong danh sách
    }

    return NULL; // Trả về NULL nếu không tìm thấy
}

// xóa mẫu tin
void delete(List L, Position p)
{
    // Position p = find(L, number, data); // Tìm phần tử cần xóa
    if (p == NULL)
        return;
    // Kiểm tra nếu phần tử cần xóa là phần tử đầu tiên
    if (p->prev == NULL)
    {
        L->next = p->next;
    }
    else
    {
        p->prev->next = p->next;
    }
    if (p->next != NULL)
        p->next->prev = p->prev;
    free(p); // Giải phóng bộ nhớ của phần tử bị xóa
}

// list all city in Contacts
List City(List L)
{
    List City = create();
    City = NULL;
    Position q;

    if (L != NULL)
        q = insert(&City, L->value, City);
    while (L != NULL)
    {
        if (find(City, city, L->value.city) == NULL)
            q = insert(&City, L->value, q);
        L = L->next;
    }

    return City;
}

// liệt kê danh bạ từng tỉnh thành + thống kê số lượng thuê bao
void listCity(List L, int choose)
{
    List listCity = City(L);
    List findCity;
    int count;
    while (listCity != NULL)
    {
        findCity = findAll(L, city, listCity->value.city, &count);
        printf("%s: ", listCity->value.city);
        printf("%d\n", count);
        if (choose == 4)
            display(findCity);
        listCity = listCity->next;
    }
}

// sắp xếp theo các tiêu chí, @override
void Arrange1() {}

void Arrange2() {}

void Arrange3() {}

// thống kê số lượng thuê bao theo tỉnh thành
void countPhonesByCity(List L)
{
    const char *provinces[] = {
        "Ha Noi", "Ha Giang", "Cao Bang", "Bac Kan", "Tuyen Quang", "Lao Cai",
        "Dien Bien", "Lai Chau", "Son La", "Yen Bai", "Hòa Bình", "Thai Nguyen",
        "Lang Son", "Bac Giang", "Phu Tho", "Vinh Phuc", "Quang Ninh", "Bac Ninh",
        "Hai Duong", "Hung Yen", "Ha Nam", "Nam Dinh", "Thai Binh", "Ninh Binh",
        "Thanh Hoa", "Nghe An", "Ha Tinh", "Quang Binh", "Quang Tri", "Thua Thien Hue",
        "Da Nang", "Quang Nam", "Quang Ngai", "Binh Dinh", "Phu Yen", "Khanh Hoa",
        "Ninh Thuan", "Binh Thuan", "Kon Tum", "Gia Lai", "Dak Lak", "Dak Nong",
        "Lam Dong", "Binh Phuoc", "Tay Ninh", "Binh Duong", "Dong Nai", "Ba Ria - Vung Tau",
        "Long An", "Tien Giang", "Ben Tre", "Dong Thap", "An Giang", "Kien Giang",
        "Can Tho", "Hau Giang", "Soc Trang", "Tra Vinh", "Bac Lieu", "Ca Mau"};

    int counts[62] = {0}; // Mảng đếm số điện thoại cho mỗi tỉnh thành
    int i;
    Position current = L->next;
    while (current != NULL)
    {
        char *city = current->value.city;
        for (i = 0; i < 62; ++i)
        {
            if (strcmp(provinces[i], city) == 0)
            {
                counts[i]++;
                break;
            }
        }
        current = current->next;
    }

    printf("Thong ke so dien thoai theo tinh thanh:\n");
    for (i = 0; i < 62; ++i)
    {
        if (counts[i] > 0)
        {
            printf("%s: %d so dien thoai\n", provinces[i], counts[i]);
        }
    }
}

// Tìm và thông báo nếu có trùng lặp, xóa
int duplicate(List *L)
{
    List temp = *L;
    Position p = *L;
    while (p != NULL)
    {
        while (temp != NULL)
        {
            if (p->value.number == temp->value.number && p->value.city == temp->value.city)
            {
                printf("Co su trung lap:\n");
                displayPosition(p);
                displayPosition(temp);
                printf("Ban muon xoa khong?\n1. Yes\n2. No");
                int choose;
                scanf("%d", &choose);
                if (choose == 1)
                {
                    delete (*L, p);
                    delete (temp, p);
                }
            }
            temp = temp->next;
        }
        p = p->next;
    }
}

/*                  */
int main()
{
    struct NumberInfo s1 = setNumber("0328981817", "Da Nang", "Danh", "DHBK");
    struct NumberInfo s2 = setNumber("0328981817", "Da Nang", "Em", "DHBK");
    struct NumberInfo s3 = setNumber("0328981818", "Ha Noi", "Dat", "DHBK");

    List Contacts = create();
    Contacts = NULL;
    Position p;
    p = insert(&Contacts, s1, p);
    p = insert(&Contacts, s2, p);
    p = insert(&Contacts, s3, p); // Thêm số mới
    char *c = "0328981817";
    int count;

    List findby;
    // có thể dùng int choose thay cho enum trong switchcase
    findby = findAll(Contacts, number, c, &count);
    if (findby != NULL){
        printf("FOUND: ");
        display(findby);}
    else
        printf("NOT FOUND\n");

    // delete (Contacts, c);
    // display(Contacts);

    List listcity;
    listcity = City(Contacts);
    displayCity(listcity);

    // thay 1 thành 4 nếu muốn chuyển sang liệt kê danh bạ theo tỉnh thành
    printf("ham listCity: \n");
    listCity(Contacts, 1);

    printf("\nham listCity: \n");
    listCity(Contacts, 4);

    printf("\nham add: \n");
    add(&Contacts, s3, 1);
    display(Contacts);

    // unfixed
    printf("L: \n");
    // duplicate(Contacts);
    // display(Contacts);

    free(Contacts);
    free(p);
    return 0;
}
