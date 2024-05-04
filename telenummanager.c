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
    // L->prev = NULL;
    return L;
}

// nhap vao mot so dien thoai moi va them vao contacts L
void setNumber(List L) {
    unsigned long m;
    char str[100];
    NumberInfo one;

    printf("So dien thoai: ");

    int chck = scanf("%lu", &m);
    getchar();
    for(;;)
    {   if (chck != 1) {printf("\nKhong hop le, vui long nhap lai!!!\n");continue;}
        else {one.number = m;break;}
    }
    printf("Nha mang: ");
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = '\0';
    one.nhamang = strdup(str);

    printf("Chu so huu: ");
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = '\0';
    one.owner = strdup(str);

    printf("Dia chi: ");
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = '\0';
    one.address = strdup(str);

    printf("Thanh pho: ");
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = '\0';
    one.city = strdup(str);

    InsertFirst(L, one);
}

// in danh sách thông tin tất cả danh bạ
void display(List L)
{
    printf("\n");
    printf("\nDanh sach so dien thoai:\n");
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
// hàm xuất danh bạ ra file
void Xuat_Danh_Sach_So_Dien_Thoai(FILE *fileout, List L)
{
    fprintf(fileout, "Danh sach so dien thoai:\n");
    while (L!= NULL)
    {
        fprintf(fileout, "%d, %s, %s, %s, %s\n",
                L->next->value.number, L->next->value.nhamang,
                L->next->value.owner, L->next->value.address, L->next->value.city);
        L = L->next;
    }
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

List copyList(List L)
{
    List copy = create();     // Tạo một danh sách mới để lưu trữ bản sao
    Position current = L;     // Con trỏ để duyệt qua danh sách gốc
    Position prevCopy = NULL; // Con trỏ đến phần tử trước của danh sách sao chép

    // Duyệt qua danh sách gốc và sao chép từng phần tử
    while (current != NULL)
    {
        // Tạo một phần tử mới để sao chép dữ liệu từ danh sách gốc
        Position newItem = malloc(sizeof(struct Node));
        if (newItem == NULL)
        {
            printf("Khong du bo nho!\n");
            return NULL;
        }
        newItem->value = current->value; // Sao chép dữ liệu từ phần tử của danh sách gốc
        newItem->next = NULL;            // Đặt con trỏ next của phần tử mới thành NULL

        // Nếu danh sách sao chép không có phần tử nào, thiết lập phần tử đầu tiên
        if (copy == NULL)
        {
            copy = newItem;
        }
        else
        {
            // Nếu danh sách sao chép đã có phần tử, chèn phần tử mới vào cuối danh sách
            prevCopy->next = newItem;
        }
        prevCopy = newItem; // Di chuyển con trỏ prevCopy đến phần tử mới

        current = current->next; // Di chuyển con trỏ trong danh sách gốc
    }

    return copy; // Trả về danh sách sao chép hoàn chỉnh
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
    List cityList = create(); // Danh sách để lưu trữ các tỉnh thành duy nhất
    Position p = L->next;
    insert(&cityList, L->value, NULL); // Bắt đầu từ phần tử đầu tiên của danh bạ

    // Duyệt qua danh sách liên kết để lấy các tỉnh thành duy nhất
    while (L != NULL)
    {
        // Kiểm tra xem tỉnh thành hiện tại đã tồn tại trong danh sách tỉnh thành chưa
        while (p->value.city == L->value.city && p != NULL)
        {
            // Nếu chưa tồn tại, thêm tỉnh thành vào danh sách tỉnh thành
            delete (cityList, L->value.city);
            p = p->next;
        }
        L = L->next; // Chuyển sang phần tử tiếp theo trong danh sách danh bạ
    }

    return cityList; // Trả về danh sách các tỉnh thành duy nhất
}

List ListCity(List L)
{
    List uniqueCityList = copyList(L); // Tạo bản sao của danh sách gốc
    Position current = uniqueCityList; // Con trỏ để duyệt qua danh sách thành phố duy nhất

    // Duyệt qua danh sách thành phố duy nhất
    while (current != NULL)
    {
        Position nextCity = current->next; // Con trỏ đến thành phố tiếp theo
        Position prevCity = current;       // Con trỏ đến thành phố trước đó

        // Duyệt qua danh sách thành phố còn lại để kiểm tra trùng lặp
        while (nextCity != NULL)
        {
            // Nếu tìm thấy thành phố trùng lặp, loại bỏ nó khỏi danh sách
            if (strcmp(nextCity->value.city, current->value.city) == 0)
            {
                Position temp = nextCity;  // Lưu trữ con trỏ đến thành phố trùng lặp
                nextCity = nextCity->next; // Di chuyển con trỏ đến thành phố tiếp theo
                prevCity->next = nextCity; // Loại bỏ thành phố trùng lặp
                free(temp);                // Giải phóng bộ nhớ của thành phố trùng lặp
            }
            else
            {
                prevCity = nextCity;       // Di chuyển con trỏ đến thành phố trước đó
                nextCity = nextCity->next; // Di chuyển con trỏ đến thành phố tiếp theo
            }
        }

        current = current->next; // Di chuyển con trỏ đến thành phố tiếp theo trong danh sách duy nhất
    }

    return uniqueCityList; // Trả về danh sách thành phố duy nhất
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

// chèn vào đầu danh sách
Position insertfirst(List pL, struct NumberInfo e)
{
    Position newItem;
    newItem = malloc(sizeof(struct Node));
    newItem->value = e;

    newItem->next = pL->next;
    newItem->prev = pL;
    pL->next = newItem;
    if (newItem->next != NULL)
        newItem->next->prev = newItem;
    return newItem;
}

// sắp xếp theo các tiêu chí, @override
void Arrange1() {} // theo alphabe up,down

void Arrange2() {}

void Arrange3() {}

// liệt kê danh bạ từng tỉnh thành
void list()
{
}

// thống kê số lượng thuê bao theo tỉnh thành
void countPhonesByCity(List L)
{
    const char *provinces[] = {
        "Ha Noi", "Ha Giang", "Cao Bang", "Bac Kan", "Tuyen Quang", "Lao Cai",
        "Dien Bien", "Lai Chau", "Son La", "Yen Bai", "Hoa Binh", "Thai Nguyen",
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
void duplicate(List L)
{
    Position current = L->next; // Bắt đầu từ phần tử đầu tiên của danh sách

    // Duyệt qua danh sách liên kết để tìm các mục trùng lặp
    while (current != NULL)
    {
        char *currentNumber = current->value.number;
        Position search = find(current->next, number, currentNumber); // Tìm mục trùng lặp

        // Nếu tìm thấy mục trùng lặp
        if (search != NULL)
        {
            printf("Duplicate found:\n");
            displayPosition(current); // In thông tin mục trùng lặp
            displayPosition(search);  // In thông tin mục trùng lặp

            Position temp = current;   // Lưu trữ con trỏ đến mục hiện tại
            current = current->next;   // Di chuyển con trỏ hiện tại đến mục tiếp theo trước khi xóa mục hiện tại
            delete (L, currentNumber); // Xóa mục trùng lặp từ danh sách
            free(temp);                // Giải phóng bộ nhớ của mục trùng lặp
        }
        else
        {
            current = current->next; // Di chuyển con trỏ hiện tại đến mục tiếp theo nếu không tìm thấy trùng lặp
        }
    }
}
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
    printf("%s", p->value.city);
    if (p == NULL)
        printf("None");
    display(Contacts);
    p = insert(&Contacts, s2, p);
    p = insert(&Contacts, s3, p); // Thêm số mới
    // display(Contacts);
    char *c = "0328981818";

    List findby;
    // có thể dùng int choose thay cho enum trong switchcase
    findby = findAll(Contacts, number, c);
    if (findby != NULL)
        display(findby);
    else
        printf("NOT FOUND\n");

    // findby = create();
    // listCity(Contacts);
    delete (Contacts, c);
    // printf("%s", Contacts->value.number);
    display(Contacts);
    printf("L: \n");
    // List cityL = ListCity(Contacts);
    duplicate(Contacts);
    display(Contacts);

    free(Contacts);
    return 0;
}
