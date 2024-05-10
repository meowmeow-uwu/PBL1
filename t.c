#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

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

int countList(List L)
{
    int count = 0;
    while (L != NULL)
    {
        ++count;
        L = L->next;
    }
    return count;
}

Position findex(List L, int index)
{
    if (index > countList(L))
        return NULL;

    Position p = L;
    int count = 1;
    while (count != index)
    {
        ++count;
        p = p->next;
    }
    return p;
}

void loaibokhoangtrang(char *str)
{
    if (str == NULL || *str == '\0')
    {
        return; // Nếu chuỗi trống hoặc con trỏ NULL, không làm gì cả
    }

    // Duyệt qua các khoảng trắng ở đầu chuỗi
    char *start = str;
    while (isspace(*start))
    {
        start++; // Di chuyển con trỏ lên phía sau nếu gặp khoảng trắng
    }

    // Di chuyển nội dung của chuỗi lên đầu
    char *dest = str;
    while (*start != '\0')
    {
        *dest++ = *start++; // Di chuyển nội dung từ start sang dest
    }
    *dest = '\0'; // Kết thúc chuỗi mới
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
        if (q == NULL)
        {
            insertFirst(L, num);
        }
        else
        {
            while (q->next != NULL)
                q = q->next;
            insert(L, num, q);
        }
        break;
    default: // NULL:))
        break;
    }
}

// chèn bất kỳ
void insertP(List *L, struct NumberInfo e, int index)
{
    Position p = findex(*L, index);
    if (p == NULL)
    {
        printf("\nElement non-exist!\n");
        return;
    }
    if (index == 1)
        insertFirst(L, e);
    else
        insert(L, e, p->prev);
}

/*-------------------------------------------------SET NUMBER-------------------------------------------------------*/
//--------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------
// create one new number element

int isAllDigits(char *str)
{
    int i, len = strlen(str);
    for (i = 0; i < len; i++)
    {
        if (!isdigit(str[i]))
        {
            return 0; // Trả về 0 nếu có ký tự không phải là chữ số
        }
    }
    return 1; // Trả về 1 nếu tất cả đều là chữ số
}

int is_Alpha(char *str)
{
    int i;
    for (i = 0; str[i]; i++)
    {
        if (!isalpha(str[i]) && str[i] != ' ')
            return 0;
    }
    return 1;
}

void set(char *str, int choose)
{
    do
    {
        str[0] = '\0';
        fgets(str, 100, stdin);
        str[strcspn(str, "\n")] = '\0';
        viethoa(str);
        if (choose == 2)
            return;
        if (!is_Alpha(str))
            printf("Should only in alphabet!\nPlease type again: ");
    } while (!is_Alpha(str));
    loaibokhoangtrang(str);
}

struct NumberInfo setNumber()
{
    struct NumberInfo one;
    char str[100];

    do
    {
        printf("\nSo dien thoai: ");
        fgets(str, sizeof(str), stdin);
        str[strcspn(str, "\n")] = '\0';
        if (!isAllDigits || strlen(str) != 10)
            printf("\nSdt phai la 1 day so gom 10 so!");
    } while (!isAllDigits(str) || strlen(str) != 10);
    one.number = strdup(str);

    printf("Chu so huu: ");
    set(str, 1);
    one.owner = strdup(str);

    printf("Dia chi: ");
    set(str, 2);
    one.address = strdup(str);

    printf("Thanh pho: ");
    set(str, 1);
    one.city = strdup(str);

    return one;
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
        printf("-Number: \t%s\n  -City: \t%s\n  -Owner: \t%s\n  -Address: \t%s\n\n", L->value.number, L->value.city, L->value.owner, L->value.address);
        return;
    }
    while (L != NULL)
    {
        printf("%d. -Number: \t%s\n  -City: \t%s\n  -Owner: \t%s\n  -Address: \t%s\n\n", count++, L->value.number, L->value.city, L->value.owner, L->value.address);
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
int compareByNumber(struct NumberInfo a, struct NumberInfo b)
{
    return strcmp(a.number, b.number);
}

int compareByCity(struct NumberInfo a, struct NumberInfo b)
{
    return strcmp(a.city, b.city);
}

int compareByOwner(struct NumberInfo a, struct NumberInfo b)
{
    return strcmp(a.owner, b.owner);
}

int compareByAddress(struct NumberInfo a, struct NumberInfo b)
{
    return strcmp(a.address, b.address);
}

void swapNodes(List *pL, Position first, Position second)
{
    struct NumberInfo temp = first->value; // Lưu trữ giá trị của nút đầu tiên
    first->value = second->value;          // Gán giá trị của nút thứ hai cho nút đầu tiên
    second->value = temp;
}

// sắp xếp theo các tiêu chí, @override
void Arrange(List *pL, int (*compare)(struct NumberInfo, struct NumberInfo), int ascending)
{
    int swapped;
    Position L, next, lastPtr = NULL;

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
            if ((ascending && compare(L->value, next->value) > 0) ||
                (!ascending && compare(L->value, next->value) < 0))
            {
                swapNodes(pL, L, next);
                swapped = 1;
            }
            L = next;
        }
        lastPtr = L;
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

void deleteP(List *L, int index)
{
    Position p = findex(*L, index);
    if (p == NULL)
    {
        printf("\nElement non-exist!\n");
        return;
    }
    delete (L, p);
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
            if (strcmp(p->value.number, temp->value.number) == 0 && strcmp(p->value.city, temp->value.city) == 0)
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
                    delete (L, temp);
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
        loaibokhoangtrang(token);
        e->number = strdup(token);

        token = strtok(NULL, ", ");
        loaibokhoangtrang(token);
        e->owner = strdup(token);

        token = strtok(NULL, ",");
        loaibokhoangtrang(token);
        e->address = strdup(token);

        token = strtok(NULL, ",");
        loaibokhoangtrang(token);
        e->city = strdup(token);
    }
}

// Hàm đọc danh sách số điện thoại từ file
void Doc_Danh_Sach_So_Dien_Thoai(List *pL)
{
    FILE *f = fopen("numberInfo.txt", "r");
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
            add(pL, e, 2);
        }
    }
    fclose(f);
}

/*---------------------------------------------------MENU INTERFACE-----------------------------------------------------------*/
//---------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------
void check(int chck, int *choice, int n)
{
    for (;;)
    {
        printf("\nYour choice: ");
        chck = scanf("%d", choice);
        getchar();
        if (!(chck == 1 && *choice >= 1 && *choice <= n))
        {
            printf("Value must be a number from 1 to %d\n!! Please choose again.\n", n);
            continue;
        }
        else
            break;
    }
}

void menu(int *choice)
{

    int chck;

    printf("\t           --------MENU--------\n");
    printf("\t  ------------------------------------\n");
    printf("\t |1. DOC FILE LAY DU LIEU             |      \n");
    printf("\t |2. HIEN THI DANH BA                 |     \n");
    printf("\t |3. CHINH SUA DANH BA                |     \n");
    printf("\t |4. TIM KIEM THEO TIEU CHI           |     \n");
    printf("\t |5. LIET KE THEO TINH THANH          |     \n");
    printf("\t |6. THONG KE SO LUONG THEO TINH THANH|     \n");
    printf("\t |7. THONG BAO NEU CO TRUNG LAP VA XOA|     \n");
    printf("\t |8. THOAT                            |     \n");
    printf("\t  ------------------------------------\n");

    check(chck, choice, 8);
}

int sapxep()
{
    printf("\n1. Tang dan\n2. Giam dan\n");
    int chck, choose;
    check(chck, &choose, 2);
    if (choose == 2)
        return 0;
    return 1;
}

void sapxeptheo(List *pL)
{
    printf("\t  --------------------------------------------\n");
    printf("\t |1. SAP XEP THEO SDT                             |     \n");
    printf("\t |2. SAP XEP THEO TINH THANH                      |     \n");
    printf("\t |3. SAP XEP THEO CHU SO HUU                      |     \n");
    printf("\t |4. SAP XEP THEO DIA CHI                         |     \n");
    printf("\t  --------------------------------------------\n");
    int chck, choose, (*f)(struct NumberInfo, struct NumberInfo);
    check(chck, &choose, 4);
    switch (choose)
    {
    case 1:
        f = compareByNumber;
        break;
    case 2:
        f = compareByCity;
        break;
    case 3:
        f = compareByOwner;
        break;
    case 4:
        f = compareByAddress;
        break;
    }
    Arrange(pL, f, sapxep());
    display(*pL, 1);
}

void chen(List *L)
{
    printf("\n1. Chen vao dau danh sach\n2. Chen cuoi danh sach\n3. Chen vao mot vi tri\n");
    int choose, chck, index, chck1;
    check(chck, &choose, 3);
    struct NumberInfo e = setNumber();
    switch (choose)
    {
    case 1:
        add(L, e, 1);
        break;
    case 2:
        add(L, e, 2);
        break;
    case 3:
        display(*L, 1);
        printf("\n\nNhap vi tri ban muon chen :  ");
        check(chck1, &index, countList(*L));
        insertP(L, e, index);
        break;
    }
    printf("Ban co muon sap xep lai danh sach khong?\n1. Yes\n2. No\n");
    check(chck, &choose, 2);
    if (choose == 1)
        sapxeptheo(L);
}

void option3(List *Contacts)

{
    int chck, chck1, choice, index;
    printf("\t  --------------------------------------------\n");
    printf("\t |1. THEM SO DIEN THOAI                           |     \n");
    printf("\t |2. SAP XEP                                      |     \n");
    printf("\t |3. XOA MOT SO DIEN THOAI                        |     \n");
    printf("\t |4. TRO VE MENU                                  |     \n");
    printf("\t  --------------------------------------------\n");

    check(chck, &choice, 4);

    switch (choice)
    {
    case 1:
        chen(Contacts);
        break;

    case 2:
        sapxeptheo(Contacts);
        break;

    case 3:
        display(*Contacts, 1);
        printf("\n\nNhap vi tri ban muon xoa :  ");
        check(chck1, &index, countList(*Contacts));
        deleteP(Contacts, index);
        printf("\n DA XOA VI TRI %d XONG!", index);
        break;

    case 4:
        return;
    }
}

void option4(List Contacts)
{
    {
        display(Contacts, 1);
        int chck;
        int choice;
        printf("\t  --------------TIM KIEM THEO--------------\n");
        printf("\t |1. SDT                                   |     \n");
        printf("\t |2. TINH THANH                            |     \n");
        printf("\t |3. DIA CHI                               |     \n");
        printf("\t |4. CHU SO HUU                            |      \n");
        printf("\t |5. TRO VE MENU                           |     \n");
        printf("\t  -----------------------------------------\n");
        check(chck, &choice, 5);
        int count;
        char str[100];
        int (*f)(struct NumberInfo, char *);
        List findby;
        if (choice == 1)
        {
            printf("VUI LONG NHAP SDT MUON TIM :");
            fgets(str, sizeof(str), stdin);
            str[strcspn(str, "\n")] = '\0';
            f = findNumber;
        }
        if (choice == 2)
        {
            printf("VUI LONG NHAP TEN TINH THANH :");
            fgets(str, sizeof(str), stdin);
            str[strcspn(str, "\n")] = '\0';
            viethoa(str);
            f = findCity;
        }
        if (choice == 3)
        {
            printf("VUI LONG NHAP TEN DIA CHI :");
            fgets(str, sizeof(str), stdin);
            str[strcspn(str, "\n")] = '\0';
            viethoa(str);
            f = findAddress;
        }
        if (choice == 4)
        {
            printf("VUI LONG NHAP TEN CHU SO HUU :");
            fgets(str, sizeof(str), stdin);
            str[strcspn(str, "\n")] = '\0';
            viethoa(str);
            f = findOwner;
        }
        if (choice == 5)
        {
            return;
        }
        findby = findAll(Contacts, f, str, &count);
        if (findby != NULL)
        {
            printf("\nFOUND: ");
            display(findby, 1);
        }
        else
            printf("\nNOT FOUND\n");
    }
}

int check_null(List L, int choose)
{
    if (L == NULL)
    {
        if (choose != 1)
            printf("Ban chua doc file!\nHay quay lai menu de doc du lieu!\n");
        return 1;
    }
    return 0;
}

int main()
{
    system("cls");
    List Contacts = create();
    Contacts = NULL;
    int choice = 1;
menu:
    menu(&choice);

    if (choice == 8)
        exit(1);
    if (choice == 1)
    {
        if (!check_null(Contacts, choice))
        {
            printf("Contacts existed!\n");
        }
        else
        {
            Doc_Danh_Sach_So_Dien_Thoai(&Contacts);
            display(Contacts, 1);
        }
    }
    else
    {
        if (check_null(Contacts, choice))
        {
        }
        else
            switch (choice)
            {
            case 2:
                display(Contacts, 1);
                break;
            case 3:
                option3(&Contacts);
                break;
            case 4:
                option4(Contacts);
                break;
            case 5:
                listCity(Contacts, 4);
                break;
            case 6:
                listCity(Contacts, 0);
                break;
            case 7:
                if (duplicate(&Contacts))
                {
                    display(Contacts, 1);
                }
                else
                    printf("\nKhong co phan tu trung lap!\n");
                break;
            }
    }
    printf("\n Nhan phim bat ky de quay lai menu...");
    getch();

    system("cls");
    goto menu;
    free(Contacts);
    return 0;
}
