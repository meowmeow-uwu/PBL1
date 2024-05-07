#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

/*
Tên tỉnh thành: Hà Nội
Tên đơn vị: Công ty ABC
Địa chỉ: Số 123 Đường ABC, Quận XYZ, Hà Nội
Số điện thoại: 123456789
Nhà mạng : Viettel

123456789, Viettel, Công ty ABC, Số 123 Đường ABC Quận XYZ Hà Nội, Hà Nội
*/

// danh sách mẫu tin
struct NumberInfo
{
    char *number;
    char *owner;
    char *address;
    char *city;
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

/*-------------------------------------------------INSERT--------------------------------------------------*/
//------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
// nhap vao mot so dien thoai moi va them vao contacts L
void viethoa(char *str)
{
    int length = strlen(str);
    int i;

    // Đặt chữ cái đầu tiên của chuỗi thành chữ hoa
    if (length > 0)
    {
        str[0] = toupper(str[0]);
    }

    // Lặp qua các ký tự của chuỗi
    for (i = 1; i < length; i++)
    {
        // Nếu là khoảng trắng và ký tự sau nó là một ký tự thường,
        // thì chuyển ký tự đó thành chữ hoa
        if (isspace(str[i]) && islower(str[i + 1]))
        {
            str[i + 1] = toupper(str[i + 1]);
        }
    }
}

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

// chèn bất kỳ
void insertM() {}

/*-------------------------------------------------SET NUMBER-------------------------------------------------------*/
//--------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------
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

void setNumber1(List L)
{
    struct NumberInfo one;
    char str[100];

    printf("\nSo dien thoai: ");
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = '\0';
    one.number = strdup(str);

    printf("Chu so huu: ");
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = '\0';
    viethoa(str);
    one.owner = strdup(str);

    printf("Dia chi: ");
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = '\0';
    viethoa(str);
    one.address = strdup(str);

    printf("Thanh pho: ");
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = '\0';
    viethoa(str);
    one.city = strdup(str);
    //**************************************************************
    //********** nên linh hoạt bằng con trỏ hàm hoặc switch case:))
    insertFirst(L, one);
}

/*-------------------------------------------------DISPLAY----------------------------------------------------------*/
//-----------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------
// in danh sách thông tin tất cả danh bạ
void display(List L, int choose) // choose = 0 <=> in 1 Position
{
    printf("\n");
    int count = 1;
    if (!choose && L != NULL)
    {
        printf("-Number: %s\n  -City: %s\n  -Unit: %s\n  -Address: %s\n", L->value.number, L->value.city, L->value.owner, L->value.address);
        return;
    }
    while (L != NULL)
    {
        printf("%d. -Number: %s\n  -City: %s\n  -Unit: %s\n  -Address: %s\n", count++, L->value.number, L->value.city, L->value.owner, L->value.address);
        L = L->next;
    }
    printf("\n");
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

/*-------------------------------------------------FIND--------------------------------------------------------------*/
//-------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------
// tìm kiếm theo các tiêu chí
int findNumber(struct NumberInfo one, char *data)
{
    return strcmp(one.number, data);
}

int findCity(struct NumberInfo one, char *data)
{
    return strcmp(one.city, data);
}

int findAddress(struct NumberInfo one, char *data)
{
    return strcmp(one.address, data);
}

int findOwner(struct NumberInfo one, char *data)
{
    return strcmp(one.owner, data);
}

Position find(List L, int (*f)(struct NumberInfo, char *), char *data)
{
    while (L != NULL)
    {
        if (!(*f)(L->value, data))
            return L;
        L = L->next;
    }
    return NULL;
}

List findAll(List L, int (*f)(struct NumberInfo, char *), char *data, int *count)
{
    List resultList = create();
    resultList = NULL;
    Position p;
    *count = 0;

    while (L != NULL)
    {
        if (!(*f)(L->value, data))
        {
            p = insert(&resultList, L->value, p);
            (*count)++;
        }
        L = L->next;
    }

    return resultList;
}

/*-------------------------------------------------COUNT NUMBER BY CITY && LIST CITY--------------------------------------------*/
//---------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------
// list all city in Contacts
List City(List L)
{
    List City = create();
    City = NULL;
    Position q;

    if (L != NULL)
        q = insert(&City, L->value, City);
    L = L->next;
    while (L != NULL)
    {
        if (find(City, findCity, L->value.city) == NULL)
            q = insert(&City, L->value, q);
        L = L->next;
    }

    return City;
}

// liệt kê danh bạ từng tỉnh thành + thống kê số lượng thuê bao
void listCity(List L, int choose) // choose sẽ được handle trong main (switch case)
{
    List listCity = City(L);
    List findCities;
    int count;
    while (listCity != NULL)
    {
        findCities = findAll(L, findCity, listCity->value.city, &count);
        printf("%s: ", listCity->value.city);
        printf("%d\n", count);
        if (choose == 4)
            display(findCities, 1);
        listCity = listCity->next;
    }
}

/*-------------------------------------------------ARRANGE--------------------------------------------------------------*/
//------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
void swapNodes(List *pL, Position first, Position second)
{
    char *tempcity = first->value.city; // Giả sử là chỉ đổi tên
    first->value.city = second->value.city;
    second->value.city = tempcity;
}

// sắp xếp theo các tiêu chí, @override
void Arrange(List *pL, int ascending)
{
    int swapped;
    Position L, next, lastPtr = NULL;

    /* Kiểm tra danh sách có rỗng không hoặc chỉ có một phần tử */
    if (*pL == NULL || (*pL)->next == NULL)
    {
        return;
    }

    do
    {
        swapped = 0;
        L = *pL;

        while (L->next != lastPtr)
        {
            next = L->next;
            // So sánh và quyết định điều kiện dựa trên biến 'ascending'
            if ((ascending && strcmp(L->value.city, next->value.city) > 0) ||
                (!ascending && strcmp(L->value.city, next->value.city) < 0))
            {
                swapNodes(pL, L, next);
                swapped = 1;
            }
            L = next;
        }
        lastPtr = L; // cập nhật phần tử cuối cùng đã được sắp xếp
    } while (swapped);
}

/*--------------------------------------------------DELETE && DUPLICATE-------------------------------------------------*/
//-----------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------
// xóa mẫu tin
void delete(List *L, Position p)
{
    if (p == NULL)
        return;

    if ((*L) == p)
        *L = p->next;
    else
        p->prev->next = p->next;

    if (p->next != NULL)
        p->next->prev = p->prev;

    free(p);
}

// Tìm và thông báo nếu có trùng lặp, xóa
int duplicate(List *L)
{
    Position p = *L, temp, nextTemp;
    int foundDuplicates = 0;

    while (p != NULL && p->next != NULL)
    {
        temp = p->next;
        while (temp != NULL)
        {
            nextTemp = temp->next; // Lưu trữ con trỏ tiếp theo của temp
            if ((p->value.number == temp->value.number) == 0 && strcmp(p->value.city, temp->value.city) == 0)
            {
                printf("Co su trung lap giua hai phan tu:\n");
                display(p, 0);
                display(temp, 0);
                printf("Ban muon xoa phan tu nao?\n1. Phan tu dau\n2. Phan tu sau\n3. Khong xoa\n");
                int choose;
                scanf("%d", &choose);
                switch (choose)
                {
                case 1:
                    delete (L, p);
                    p = p->prev; // Cập nhật lại p sau khi xóa
                    if (p == NULL)
                        p = *L; // Nếu p là null, đặt lại về đầu danh sách
                    else
                        p = p->next; // Nếu không, tiếp tục từ phần tử tiếp theo
                    break;
                case 2:
                    delete (*L, temp);
                    break;
                default:
                    break;
                }
                if (choose != 3)
                    foundDuplicates = 1;
            }
            temp = nextTemp;
        }
        if (p != NULL)
            p = p->next; // Tiếp tục di chuyển p đến phần tử tiếp theo
    }
    return foundDuplicates;
}

/*---------------------------------------------------FILE HANDLING------------------------------------------------------*/
//------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------
void Doc_File_Thong_Tin_So_Dien_Thoai(FILE *filein, struct NumberInfo *e)
{
    char line[256];
    if (fgets(line, sizeof(line), filein) != NULL)
    {
        // Loại bỏ ký tự xuống dòng cuối dòng
        line[strcspn(line, "\n")] = '\0';

        char *token = strtok(line, ",");
        e->number = strdup(token);

        token = strtok(NULL, ",");
        e->owner = strdup(token);

        token = strtok(NULL, ",");
        e->address = strdup(token);

        token = strtok(NULL, ",");
        e->city = strdup(token);
    }
}

// Hàm đọc danh sách số điện thoại từ file
void Doc_Danh_Sach_So_Dien_Thoai(List *pL)
{
    FILE *f = fopen("numberInfo.TXT", "r");
    if (f == NULL)
    {
        fprintf(stderr, "Khong mo duoc file\n");
        exit(EXIT_FAILURE);
    }

    struct NumberInfo e;
    while (!feof(f))
    {
        Doc_File_Thong_Tin_So_Dien_Thoai(f, &e);
        if (e.number != NULL)
        {
            insertFirst(pL, e);
        }
    }
    fclose(f);
}

void checknull(struct Node *p)
{
    if (p == NULL)
        printf("NULL");
    else
        return;
}

/*---------------------------------------------------MENU INTERFACE-----------------------------------------------------------*/
//---------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------
// Cac menu lam viec
void menu()
{
    printf("\n");
    printf("---------QUAN LY DANH BA DIEN THOAI CO DINH--------");
    printf("\n1. Read file\n2. Edit Contacts\n3. Show Contacts\n4. Liet ke theo tinh thanh\n5. Thong ke so luong theo tinh thanh\n6. Check so dien thoai trung lap\n");
}

void edit()
{
    printf("\n1. Insert/add\n2. Search\n3. Arrange\n4. Delete\n");
}

void chen()
{
    printf("\n1. Chen vao dau danh sach\n2. Chen cuoi danh sach\n3. Chen vao mot vi tri\n4. Chen co sap xep\n");
}

void search()
{
    printf("\nSearch by: \n");
    printf("\n1. number\n2. city\n3. unit\n4. \n");
}

void sapxep()
{
    printf("\n1. Tang dan\n2. Giam dan\n");
}

void sapxeptheo()
{
    printf("\nSap xep theo: \n");
    printf("\n1. City\n2. \n");
}

/*                  */
int main()
{
    system("cls");
    struct NumberInfo s1 = setNumber("0328981817", "Da Nang", "Danh", "DHBK");
    struct NumberInfo s4 = setNumber("0328981817", "Da Nang", "Danh", "DHBK");
    struct NumberInfo s2 = setNumber("0328981817", "Quang Binh", "Em", "DHBK");
    struct NumberInfo s3 = setNumber("0328981818", "Ha Noi", "Dat", "DHBK");

    List Contacts = create();
    Contacts = NULL;
    Position p;
    p = insert(&Contacts, s1, p);
    p = insert(&Contacts, s2, p);
    p = insert(&Contacts, s3, p); // Thêm số mới
    char *c = "0328981817";
    int count;
    display(p, 0);
    List findby;
    // có thể dùng int choose thay cho enum trong switchcase
    findby = findAll(Contacts, findNumber, c, &count);
    if (findby != NULL)
    {
        printf("FOUND: ");
        display(findby, 1);
    }
    else
        printf("NOT FOUND\n");
    //
    printf("\nHam delete: \n");
    delete (&Contacts, p);
    display(p,0);
    // p = find(Contacts, number, c);
    // if (p != NULL) {
    //     delete1(&Contacts, p);
    //     display(Contacts); // Hiển thị danh sách sau khi xóa
    // } else {
    //     printf("Khong tim thay phan tu can xoa.\n");
    // }

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
    insert(&Contacts, s4, Contacts->next);
    display(Contacts, 1);

    // 0 là giảm dần, 1 là tăng dần
    printf("Arrange: \n");
    Arrange(&Contacts, 1);
    display(Contacts, 1);

    // unfixed
    printf("L: \n");
    if (duplicate(&Contacts))
    {
        display(Contacts, 1);
    }
    else
        printf("\nKhong co phan tu trung lap!\n");

    free(Contacts);
    free(p);
    return 0;
}
