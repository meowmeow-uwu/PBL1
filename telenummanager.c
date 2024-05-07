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
    char *nhamang;
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

/*-------------------------------------------------INSERT--------------------------------------------------*/
//------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
// nhap vao mot so dien thoai moi va them vao contacts L
void viethoa(char *str) {
    int length = strlen(str);

    // Đặt chữ cái đầu tiên của chuỗi thành chữ hoa
    if (length > 0) {
        str[0] = toupper(str[0]);
    }

    // Lặp qua các ký tự của chuỗi
    for (int i = 1; i < length; i++) {
        // Nếu là khoảng trắng và ký tự sau nó là một ký tự thường,
        // thì chuyển ký tự đó thành chữ hoa
        if (isspace(str[i]) && islower(str[i + 1])) {
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

void setNumber(List L) {
    struct NumberInfo one;
    char str[100];

    printf("\nSo dien thoai: ");
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = '\0';
    one.number = strdup(str);

    printf("Nha mang: ");
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = '\0';
    viethoa(str);
    one.nhamang = strdup(str);

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
void Display(List L) {
    printf("\n");    
    int count = 1;
    Position current = L->next;
    printf("\033[0;31mSTT\033[0m |    \033[0;31mSDT\033[0m     |  \033[0;31mNHA MANG\033[0m  |      \033[0;31mCHU SO HUU\033[0m      |             \033[0;31mDIA CHI    \033[0m             |    \033[0;31mTINH THANH  \033[0m  \n");
    while (current != NULL) {
        printf("\033[1;34m%-2d \033[0m | \033[1;32m%-10s \033[0m| \033[1;32m%-10s \033[0m| \033[1;32m%-20s\033[0m | \033[1;32m%-35s\033[0m | \033[1;32m%-15s\033[0m\n",
               count++, current->value.number, current->value.nhamang,
               current->value.owner, current->value.address, current->value.city);
        current = current->next;
    }
    printf("\n");
}

void displayPosition(Position p)
{
    printf("\033[1;34m%-2d \033[0m | \033[1;32m%-10s \033[0m| \033[1;32m%-10s \033[0m| \033[1;32m%-20s\033[0m | \033[1;32m%-35s\033[0m | \033[1;32m%-15s\033[0m\n",
                p->value.number, p->value.nhamang,
               p->value.owner, p->value.address, p->value.city);
       
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
List findAll(List L, enum findField field, char *data, int *count)
{
    // printf("Result found: ");
    List resultList = create();
    Position current = L;
    Position p = NULL;
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

/*-------------------------------------------------ARRANGE--------------------------------------------------------------*/
//------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
// sắp xếp theo các tiêu chí, @override
void Arrange(List *pL, int ascending)
{
    int swapped;
    Position current, next, lastPtr = NULL;

    /* Kiểm tra danh sách có rỗng không hoặc chỉ có một phần tử */
    if (*pL == NULL || (*pL)->next == NULL)
    {
        return;
    }

    do
    {
        swapped = 0;
        current = *pL;

        while (current->next != lastPtr)
        {
            next = current->next;
            // So sánh và quyết định điều kiện dựa trên biến 'ascending'
            if ((ascending && strcmp(current->value.city, next->value.city) > 0) ||
                (!ascending && strcmp(current->value.city, next->value.city) < 0))
            {
                // Đoạn này giả sử rằng ta có hàm swapNodes để hoán đổi hai phần tử
                swapNodes(pL, current, next);
                swapped = 1;
            }
            current = next;
        }
        lastPtr = current; // cập nhật phần tử cuối cùng đã được sắp xếp
    } while (swapped);
}

/*--------------------------------------------------DELETE && DUPLICATE-------------------------------------------------*/
//-----------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------
// xóa mẫu tin
void delete(List *L, char *data)
{
    Position p = find(*L, number, data); // TÃ¬m pháº§n tá»­ cáº§n xÃ³a
    if (p == NULL)
        return;
    // Kiá»ƒm tra náº¿u pháº§n tá»­ cáº§n xÃ³a lÃ  pháº§n tá»­ Ä‘áº§u tiÃªn
    if (p->prev == NULL)
    {
        (*L)->next = p->next;
    }
    else
    {
        p->prev->next = p->next;
    }
    if (p->next != NULL)
        p->next->prev = p->prev;
    free(p); // Giáº£i phÃ³ng bá»™ nhá»› cá»§a pháº§n tá»­ bá»‹ xÃ³a
}

void delete1(List *L, Position p)
{
    if (p->prev != NULL) p->prev->next = p->next;
    if (p->next != NULL) p->next->prev = p->prev;
    if (p == *L) *L = p->next; // Nếu xóa phần tử đầu danh sách
    free(p);
}

void swapNodes(List *pL, Position first, Position second) {
    char* tempcity = first->value.city; // Giả sử là chỉ đổi tên
    first->value.city = second->value.city;
    second->value.city = tempcity;
}

// Tìm và thông báo nếu có trùng lặp, xóa
int duplicate(List *L)
{
    Position p = *L, temp;
    int foundDuplicates = 0;
    int needRestart = 0;

    Position p = *L, temp, nextTemp;

    while (p->next != NULL) { // Không cần kiểm tra nếu p là phần tử cuối cùng
        temp = p->next;
        while (temp != NULL) {
            if ((p->value.number == temp->value.number)==0 && strcmp(p->value.city, temp->value.city) == 0) {
                printf("Co su trung lap giua hai phan tu:\n");
                displayPosition(p);
                displayPosition(temp);
                printf("Ban muon xoa phan tu nao?\n1. Phan tu dau\n2. Phan tu sau\n3. Khong xoa\n");
                int choose;
                scanf("%d", &choose);
                Position toDelete = NULL;
                switch (choose) {
                    case 1:
                        toDelete = p;
                        p = p->prev; // Di chuyển p lùi lại trước khi xóa để tiếp tục duyệt
                        break;
                    case 2:
                        toDelete = temp;
                        break;
                    default:
                        break;
                }
                if (toDelete != NULL) {
                    delete1(*L, toDelete);
                    foundDuplicates = 1;
                }
            }
            temp = nextTemp;
        }
        if (p != NULL) p = p->next;
    }
    return foundDuplicates;
}

/*---------------------------------------------------FILE HANDLING------------------------------------------------------*/
//------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------
void Doc_File_Thong_Tin_So_Dien_Thoai(FILE *filein, struct NumberInfo *e) {
    char line[256];
    if (fgets(line, sizeof(line), filein) != NULL) {
        // Loại bỏ ký tự xuống dòng cuối dòng
        line[strcspn(line, "\n")] = '\0';

        char *token = strtok(line, ",");
        e->number = strdup(token);

        token = strtok(NULL, ",");
        e->nhamang = strdup(token);

        token = strtok(NULL, ",");
        e->owner = strdup(token);

        token = strtok(NULL, ",");
        e->address = strdup(token);

        token = strtok(NULL, ",");
        e->city = strdup(token);
    }
}

// Hàm đọc danh sách số điện thoại từ file
void Doc_Danh_Sach_So_Dien_Thoai(List *pL) {
    FILE *f = fopen("numberInfo.TXT", "r");
    if (f == NULL) {
        fprintf(stderr, "Khong mo duoc file\n");
        exit(EXIT_FAILURE);
    }

    struct NumberInfo e;
    while (!feof(f)) {
        Doc_File_Thong_Tin_So_Dien_Thoai(f, &e);
        if (e.number != NULL) {
            InsertFirst(*pL, e);
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
void menu(){
    printf("\n");
    printf("---------QUAN LY DANH BA DIEN THOAI CO DINH--------");
    printf("\n1. Read file\n2. Edit Contacts\n3. Show Contacts\n4. Liet ke theo tinh thanh\n5. Thong ke so luong theo tinh thanh\n6. Check so dien thoai trung lap\n");

}

void edit(){
    printf("\n1. Insert/add\n2. Search\n3. Arrange\n4. Delete\n");
}

void chen(){
    printf("\n1. Chen vao dau danh sach\n2. Chen cuoi danh sach\n3. Chen vao mot vi tri\n4. Chen co sap xep\n");
}

void search(){
    printf("\nSearch by: \n");
    printf("\n1. number\n2. city\n3. unit\n4. \n");
}

void sapxep(){
    printf("\n1. Tang dan\n2. Giam dan\n");
}

void sapxeptheo(){
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

    List findby;
    // có thể dùng int choose thay cho enum trong switchcase
    findby = findAll(Contacts, number, c, &count);
    if (findby != NULL)
    {
        printf("FOUND: ");
        display(findby);
    }
    else
        printf("NOT FOUND\n");
//
    // printf("\nHam delete: \n");
    // delete(&Contacts, c);

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
    insert(&Contacts, s4, p);
    display(Contacts);

    // 0 là giảm dần, 1 là tăng dần
    printf("Arrange: \n");
    Arrange(&Contacts, 0);
    display(Contacts);

    // unfixed
    printf("L: \n");
    duplicate(Contacts);
    display(Contacts);

    free(Contacts);
    free(p);
    return 0;
}
