// Tìm và thông báo nếu có trùng lặp, xóa
int duplicate(List *L)
{
    Position p = *L, temp, nextTemp;
    int foundDuplicates = 0;

    while (p != NULL && p->next != NULL) {
        temp = p->next;
        while (temp != NULL) {
            nextTemp = temp->next; // Lưu trữ con trỏ tiếp theo của temp
            if ((p->value.number == temp->value.number)==0 && strcmp(p->value.city, temp->value.city) == 0) {
                printf("Co su trung lap giua hai phan tu:\n");
                displayPosition(p);
                displayPosition(temp);
                printf("Ban muon xoa phan tu nao?\n1. Phan tu dau\n2. Phan tu sau\n3. Khong xoa\n");
                int choose;
                scanf("%d", &choose);
                switch (choose) {
                    case 1:
                        delete1(L, p);
                        p = p->prev; // Cập nhật lại p sau khi xóa
                        if (p == NULL) p = *L; // Nếu p là null, đặt lại về đầu danh sách
                        else p = p->next; // Nếu không, tiếp tục từ phần tử tiếp theo
                        break;
                    case 2:
                        delete1(*L, temp);
                        break;
                    default:
                        break;
                }
                if (choose != 3) foundDuplicates = 1;
            }
            temp = nextTemp;
        }
        if (p != NULL) p = p->next; // Tiếp tục di chuyển p đến phần tử tiếp theo
    }
    return foundDuplicates;
}
