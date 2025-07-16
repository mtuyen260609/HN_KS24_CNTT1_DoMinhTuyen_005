#include <stdio.h>
int main() {
    int choice;
    do {
        printf("----------TERMINAL HISTORY---------");
        printf("1. INSERT\n");
        printf("2. UNDO\n");
        printf("3. REDO\n");
        printf("4. HIEN THI\n");
        printf("5. EXIT\n");
        printf("Lua chon cua ban: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                printf("Ket thuc chuong trinh");
                break;
            default:
                printf("Lua chon khon hop le");
        }
    } while (choice != 5);
    return 0;
}