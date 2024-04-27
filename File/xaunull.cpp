#include <stdio.h>

int main() {
    char c;
    char str[100];
    int i = 0;

    printf("Nhap xau ky tu: ");
    while ((c = getchar()) != '\n' && i < 99) {
        str[i] = c;
        i++;
    }
    str[i] = '\0';  // ket thuc xau

    printf("Xau da nhap: %s\n", str);

    return 0;
}
