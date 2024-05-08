#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

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

void insertFirst(List pL, struct NumberInfo num)
{
    Position newItem = malloc(sizeof(struct Node));

 
    newItem->value = num;
    newItem->next = pL->next;
    newItem->prev = pL;

    if (newItem->next != NULL)
    {
        newItem->next->prev = newItem;
    }
   
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
void insertP(List *L, struct NumberInfo e, int index)
{
    Position p = findex(*L, index);
    if (p == NULL)
    {
        printf("\nElement non-exist!\n");
        return;
    }
    if(index == 1) insertFirst(L,e);
    else
    insert(L, e, p->prev);
}

/*-------------------------------------------------SET NUMBER-------------------------------------------------------*/
//--------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------
// create one new number element


struct NumberInfo setNumber()
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
void listCity(List L, int choose) // choose=0 là thống kê,choose=1 là liệt kê.
{
    List listCity = City(L);
    List findCities;
    int count;
    while (listCity != NULL)
    {
        findCities = findAll(L, findCity, listCity->value.city, &count);
        if (choose==0)
       { printf("%s: ", listCity->value.city);
        printf("%d\n", count);}
        if (choose == 1)
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
void Arrange(List *pL, int (*compare)(struct NumberInfo, char *), int ascending) {
    int swapped;
    Position L, next, lastPtr = NULL;

    if (*pL == NULL || (*pL)->next == NULL) {
        return;
    }

    do {
        swapped = 0;
        L = *pL;

        while (L->next != lastPtr) {
            next = L->next;
            // Sử dụng con trỏ hàm để so sánh
            if ((ascending && compare(L->value, next->value.city) > 0) ||
                (!ascending && compare(L->value, next->value.city) < 0)) {
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
void duplicate(List *L,int *foundDuplicates)
{
    Position p = *L, temp, nextTemp;
    

    while (p != NULL && p->next != NULL)
    {
        temp = p->next;
        while (temp != NULL)
        {
            nextTemp = temp->next; // Lưu trữ con trỏ tiếp theo của temp
            if (p->value.number == temp->value.number)
            {
                *foundDuplicates==1;
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
            p = p->next; 
    }
   
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
    printf("\n1. Insert/add\n2. Arrange\n3. Delete\n");
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
    struct NumberInfo s1 = setNumber("0328981817", "Ca Nang", "Danh", "DHBK");
    struct NumberInfo s2 = setNumber("0328981817", "Ba Nang", "Danh", "DHBK");
    struct NumberInfo s3 = setNumber("0328981817", "Auang Binh", "Em", "DHBK");
    struct NumberInfo s4 = setNumber("0328981818", "Aa Noi", "Dat", "DHBK");

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
    display(p, 0);
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
    Arrange(&Contacts, findCity , 0);
    display(Contacts, 1);

    // unfixed
    printf("L: \n");
    if (duplicate(&Contacts))
    {
        display(Contacts, 1);
    }
    else
        printf("\nKhong co phan tu trung lap!\n");
    printf("delete\n");
    deleteP(&Contacts, 1);
    display(Contacts, 1);

    printf("index\n");
    insertP(&Contacts, s4, 1);
    display(Contacts, 1);

    free(Contacts);
    free(p);
    return 0;
}


//------------XONG HÀM MAIN,CHƯA HOÀN THÀNH OPTION 3 (THÊM, XÓA, SẮP XẾP)-----------


//
//
//void menu(int *choice){
//    float choice;
//        int chck;
//
//		printf("\t           --------MENU--------\n");
//		printf("\t  ------------------------------------\n");
//		printf("\t |1. DOC FILE LAY DU LIEU             |      \n");
//		printf("\t |2. HIEN THI DANH BA                 |     \n");
//		printf("\t |3. CHINH SUA DANH BA                |     \n");
//		printf("\t |4. TIM KIEM THEO TIEU CHI           |     \n");
//		printf("\t |5. LIET KE THEO TINH THANH          |     \n");
//		printf("\t |6. THONG KE SO LUONG THEO TINH THANH|     \n");
//		printf("\t |7. THONG BAO NEU CO TRUNG LAP VA XOA|     \n");
//		printf("\t |8. THOAT                            |     \n");
//		printf("\t  ------------------------------------\n");
//
//		for(;;)
//        {
//            printf("\nYour choice: ");
//            chck=scanf("%d", choice);
//            getchar();
//            if(!(chck==1 && *choice >= 1 && *choice <= 7)){
//                printf("Invalid input!! Please choose again.\n");
//			continue;}
//			else break;
//        }
//	}
//
//void option1()
//{
//    Doc_Danh_Sach_So_Dien_Thoai(&pL);
//    display(Contacts,1);
//
//}
//
//void option2()
//{
//    display(Contacts,1);
//}
//
//void option3()
//
//{       int chck;float choice;
//        printf("\t  --------------------------------------------\n");
//		printf("\t |1. THEM SO DIEN THOAI VAO DAU DANH BA       |     \n");
//		printf("\t |2. THEM SO DIEN THOAI VAO VI TRI BAT KY     |     \n");
//		printf("\t |3. SAP XEP THEO TINH THANH                  |     \n");
//		printf("\t |4. SAP XEP THEO NHA MANG                    |     \n");
//		printf("\t |5. SAP XEP THEO TEN CHU SO HUU              |     \n");
//		printf("\t |6. XOA MOT SO DIEN THOAI                    |\n");
//		printf("\t |7. TRO VE MENU                              |     \n");
//		printf("\t  --------------------------------------------\n");
//		for(;;)
//        {
//            printf("\nYour choice: ");
//            chck=scanf("%d",&choice);
//            getchar();
//            if(!(chck==1 && choice >= 1 && choice <= 7)){
//                printf("Invalid input!! Please choose again.\n");
//			continue;}
//			else break;
//        }
//        switch (choice){
//                case 1:{struct NumberInfo e=setnumber();insertFirst(Contacts,e);}
//                case 2:{}
//                case 3:{}
//                case 4:{}
//                case 5:{}
//                case 6:{}
//                case 7:{printf("\n Nhan phim bat ky de quay lai menu: ");getch();break;}}
//        }
//}
//
//void option4()
//{
//{       int chck;float choice;
//        printf("\t  --------------TIM KIEM THEO--------------\n");
//		printf("\t |1. SDT                                   |     \n");
//		printf("\t |2. TINH THANH                            |     \n");
//		printf("\t |3. DIA CHI                               |     \n");
//		printf("\t |4. CHU SO HUU                            |      \n");		
//		printf("\t |5. TRO VE MENU                           |     \n");
//		printf("\t  -----------------------------------------\n");
//		for(;;)
//        {
//            printf("\nYour choice: ");
//            chck=scanf("%d",&choice);
//            getchar();
//            if(!(chck==1 && choice >= 1 && choice <= 5)){
//                printf("Invalid input!! Please choose again.\n");
//			continue;}
//			else break;
//        }
//        switch (choice){
//            case 1 :{char str[100];printf("VUI LONG NHAP SDT MUON TIM :";fgets(str, sizeof(str), stdin);str[strcspn(str, "\n")] = '\0';
//                        List findby;
//                        findby = findAll(Contacts, findNumber, c, &count);
//                        if (findby != NULL)
//                                {printf("FOUND: ");display(findby,1)}
//                        else
//                        printf("NOT FOUND\n");
//                        printf("\n Nhan phim bat ky de quay lai menu: ");getch();break;}
//            case 2: {char str[100];printf("VUI LONG NHAP TEN TINH THANH :";fgets(str, sizeof(str), stdin);str[strcspn(str, "\n")] = '\0';viethoa(str);
//                        List findby;
//                        findby = findAll(Contacts, findCity, c, &count);
//                        if (findby != NULL)
//                                {printf("FOUND: ");display(findby,1)}
//                        else
//                        printf("NOT FOUND\n");
//                        printf("\n Nhan phim bat ky de quay lai menu: ");getch();break;}
//            case 3: {char str[100];printf("VUI LONG NHAP TEN DIA CHI :";fgets(str, sizeof(str), stdin);str[strcspn(str, "\n")] = '\0';viethoa(str);
//                        List findby;
//                        findby = findAll(Contacts, findAddress, c, &count);
//                        if (findby != NULL)
//                                {printf("FOUND: ");display(findby,1)}
//                        else
//                        printf("NOT FOUND\n");
//                        printf("\n Nhan phim bat ky de quay lai menu: ");getch();break;}
//            case 4:{char str[100];printf("VUI LONG NHAP TEN CHU SO HUU :";fgets(str, sizeof(str), stdin);str[strcspn(str, "\n")] = '\0';viethoa(str);
//                        List findby;
//                        findby = findAll(Contacts, findAddress, c, &count);
//                        if (findby != NULL)
//                                {printf("FOUND: ");display(findby,1)}
//                        else
//                        printf("NOT FOUND\n");
//                        printf("\n Nhan phim bat ky de quay lai menu: ");getch();break;}
//            case 5: {printf("\n Nhan phim bat ky de quay lai menu: ");getch();break;}}
//
//}
//}
//}
//
//void option5()
//{
//    listCity(Contacts,1);
//}
//
//void option6()
//{
//    listCity(Contacts,0);
//}
//
//void option7()
//{int fouduplicate=0;
//    duplicate(&Contacts,&fouduplicate);
//    if (fouduplicate==1)
//    {
//        printf("\nKHONG CO SU TRUNG LAP!!!\n");
//    }
//}
//
//int main()
//{
//    List Contacts = create();int choice;
//    menu:
//        menu(&choice);
//    switch (choice):
//        {
//            case 1: {option1();printf("\n Nhan phim bat ky de quay lai menu: ");getch();break;}
//            case 2: {option2();printf("\n Nhan phim bat ky de quay lai menu: ");getch();break;}
//            case 3: {option3();printf("\n Nhan phim bat ky de quay lai menu: ");getch();break;}
//            case 4: {option4();printf("\n Nhan phim bat ky de quay lai menu: ");getch();break;}
//            case 5: {option5();printf("\n Nhan phim bat ky de quay lai menu: ");getch();break;}
//            case 6: {option6();printf("\n Nhan phim bat ky de quay lai menu: ");getch();break;}
//            case 7: {option7();printf("\n Nhan phim bat ky de quay lai menu: ");getch();break;}
//            case 8: exit(0);
//        }
//        system("cls");
//        goto menu;
//        return 0;
//}
//
//
//


