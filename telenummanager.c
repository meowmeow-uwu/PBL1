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
List findAll(List L, enum findField field, char *data)
{
    printf("Result found: ");
    List resultList = create(); // Tạo danh sách kết quả mới
    Position current = L;
    Position p = NULL; // Bắt đầu từ phần tử đầu tiên
    /*thieu NULL*/

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
            }
            break;
        case number:
            if (strcmp(current->value.number, data) == 0)
            {
                p = insert(&resultList, current->value, p);
            }
            break;
        case address:
            if (strcmp(current->value.address, data) == 0)
            {
                p = insert(&resultList, current->value, p);
            }
            break;
        case owner:
            if (strcmp(current->value.owner, data) == 0)
            {
                p = insert(&resultList, current->value, p);
            }
            break;
        case nhamang:
            if (strcmp(current->value.nhamang, data) == 0)
            {
                p = insert(&resultList, current->value, p);
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
    Position current = L->next; // Bắt đầu từ phần tử đầu tiên của danh sách

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

// list all city in Contacts
List listCity1(List L)
{
    List City = create();       // Tạo danh sách mới để lưu trữ các thành phố duy nhất
    Position current = L->next; // Bắt đầu từ phần tử đầu tiên của danh sách

    // Duyệt qua danh sách liên kết để lấy các thành phố
    while (current != NULL)
    {
        // Kiểm tra xem thành phố hiện tại đã tồn tại trong danh sách thành phố chưa
        if (find(City, city, current->value.city) == NULL)
        {
            // Nếu chưa tồn tại, thêm thành phố vào danh sách thành phố
            insert(&City, current->value, NULL); // Không cần sử dụng p
        }
        current = current->next; // Chuyển sang phần tử tiếp theo trong danh sách
    }

    return City; // Trả về danh sách thành phố duy nhất
}

List City(List L)
{
    List cityList = create();          // Danh sách để lưu trữ các tỉnh thành duy nhất
    Position currentContact = L; // Bắt đầu từ phần tử đầu tiên của danh bạ

    // Duyệt qua danh sách liên kết để lấy các tỉnh thành duy nhất
    while (currentContact != NULL)
    {
        // Kiểm tra xem tỉnh thành hiện tại đã tồn tại trong danh sách tỉnh thành chưa
        if (find(cityList, city, currentContact->value.city) == NULL)
        {
            // Nếu chưa tồn tại, thêm tỉnh thành vào danh sách tỉnh thành
            insert(&cityList, currentContact->value, NULL); // Không cần sử dụng p
        }
        currentContact = currentContact->next; // Chuyển sang phần tử tiếp theo trong danh sách danh bạ
    }

    return cityList; // Trả về danh sách các tỉnh thành duy nhất
}





void listCity(List L)
{
    List cityList = City(L); // Tạo danh sách các tỉnh thành duy nhất
    display(cityList);
    // Duyệt qua danh sách các tỉnh thành duy nhất
    Position currentCity = cityList; // Bắt đầu từ phần tử đầu tiên của danh sách tỉnh thành
    while (currentCity != NULL)
    {
        printf("Danh ba cua %s:\n", currentCity->value.city);

        // Duyệt qua danh sách danh bạ để tìm các mẫu tin thuộc tỉnh thành hiện tại
        Position currentContact = L->next; // Bắt đầu từ phần tử đầu tiên của danh bạ
        while (currentContact != NULL)
        {
            if (strcmp(currentContact->value.city, currentCity->value.city) == 0)
            {
                displayPosition(currentContact); // In ra thông tin danh bạ của mỗi mẫu tin thuộc tỉnh thành hiện tại
            }
            currentContact = currentContact->next; // Chuyển sang phần tử tiếp theo trong danh sách danh bạ
        }

        currentCity = currentCity->next; // Chuyển sang phần tử tiếp theo trong danh sách các tỉnh thành
    }
}


Position find1() {}

Position find2() {}

Position find3() {}

// xóa mẫu tin
void delete(List L, char *data)
{
    Position p = find(L, number, data); // Tìm phần tử cần xóa
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

// chèn vào đầu hoặc cuối danh sách
void add() {}

// sắp xếp theo các tiêu chí, @override
void Arrange1() {}

void Arrange2() {}

void Arrange3() {}

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
    // Contacts = NULL;
    struct NumberInfo s1 = setNumber("0328981817", "Da Nang", "Danh", "DHBK");
    struct NumberInfo s2 = setNumber("0328981817", "Da Nang", "Em", "DHBK");
    struct NumberInfo s3 = setNumber("0328981818", "Ha Noi", "Dat", "DHBK");
    Position p = NULL;
    p = insert(&Contacts, s1, p);
    p = insert(&Contacts, s2, p);
    p = insert(&Contacts, s3, p); // Thêm số mới
    // display(Contacts);
    char *c = "0328981818";

    List findby;
    // có thể dùng int choose thay cho enum trong switchcase
    findby = findAll(Contacts, number, c);
    if (findby->next != NULL)
        display(findby);
    else
        printf("NOT FOUND\n");

    // findby = create();
    // listCity(Contacts);
    delete (Contacts, c);
    // printf("%s", Contacts->value.number);
    display(Contacts);

    free(Contacts);
    return 0;
}
