#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char title[100];
    char author[100];
    char category[100];
    float price;
} Book;

typedef struct Node {
    Book book;
    struct Node *next;
} Node;

typedef struct Dnode {
    Book book;
    struct Dnode *next;
    struct Dnode *prev;
} Dnode;

Node *addBook(Node *head) {
    Node *newNode = (Node *) malloc(sizeof(Node));
    printf("Nhap ID sach: ");
    scanf("%d", &newNode->book.id);
    getchar();

    printf("Nhap ten sach: ");
    fgets(newNode->book.title, 100, stdin);
    newNode->book.title[strcspn(newNode->book.title, "\n")] = '\0';

    printf("Nhap ten tac gia: ");
    fgets(newNode->book.author, 100, stdin);
    newNode->book.author[strcspn(newNode->book.author, "\n")] = '\0';

    printf("Nhap the loai sach: ");
    fgets(newNode->book.category, 100, stdin);
    newNode->book.category[strcspn(newNode->book.category, "\n")] = '\0';

    printf("Nhap gia sach: ");
    scanf("%f", &newNode->book.price);
    getchar();

    newNode->next = NULL;

    if (head == NULL) {
        return newNode;
    }
    Node *temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;

    return head;
}


void printBook(Node *head) {
    Node *temp = head;
    if (head == NULL) {
        printf("Danh sach rong\n");
    }
    while (temp != NULL) {
        printf("ID: %d\n", temp->book.id);
        printf("Title: %s\n", temp->book.title);
        printf("Author: %s\n", temp->book.author);
        printf("Category: %s\n", temp->book.category);
        printf("Price: %.3f\n", temp->book.price);
        temp = temp->next;
    }
}

Node* deleteBookById(Node* head, int id) {
    if (head == NULL) {
        printf("Danh sach rong\n");
        return head;
    }
    Node* temp = head;
    Node* prev = NULL;
    while (temp != NULL && temp->book.id != id) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Khong tim thay sach ");
        return head;
    }
    if (temp == head) {
        head = head->next;
        free(temp);
        printf("Da xoa sach voi ID %d.\n", id);
        return head;
    }
    prev->next = temp->next;
    free(temp);
    printf("Da xoa sach voi ID %d.\n", id);
    return head;
}

Node* updateBook(Node* head, int id) {
    if (head == NULL) {
        printf("Danh sach rong\n");
        return head;
    }
    Node* temp = head;
    while (temp != NULL && temp->book.id != id) {
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Khong tim thay sach");
    }
    printf("Nhap ten sach: ");
    fgets(temp->book.title, 100, stdin);
    fflush(stdin);
    printf("Nhap ten tac gia: ");
    fgets(temp->book.author, 100, stdin);
    fflush(stdin);
    printf("Nhap the loai sach moi: ");
    fgets(temp->book.category, 100, stdin);
    fflush(stdin);
    printf("Nhap gia sach moi: ");
    scanf("%f", &temp->book.price);
    fflush(stdin);
    printf("Da cap nhat sach voi ID %d.\n", id);
}

void sortBook(Node* head) {
    if (head == NULL || head->next == NULL) {
        printf("Danh sach rong hoac chi co mot sach, khong can sap xep.\n");
        return;
    }
    int swapped;
    do {
        swapped = 0;
        Node* current = head;
        while (current->next != NULL) {
            if (current->book.price > current->next->book.price) {
                // Swap book data
                Book temp = current->book;
                current->book = current->next->book;
                current->next->book = temp;
                swapped = 1;
            }
            current = current->next;
        }
    } while (swapped);
}

int main() {
    int choice, id;
    char find[100];
    Node *head = NULL;
    do {
        printf("----------BOOK MANAGER----------\n");
        printf("1. Them sach \n");
        printf("2. Hien thi danh sach tat ca quyen sach \n");
        printf("3. Xoa sach \n");
        printf("4. Cap nhat thong tin mot quyen sach \n");
        printf("5. Danh dau sach da doc xong \n");
        printf("6. Sap xep sach theo gia tang dan \n");
        printf("7. Tim kiem sach theo tieu de \n");
        printf("8. Thoat chuong trinh \n");
        printf("Lua chon cua ban\n");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                head = addBook(head);
                break;
            case 2:
                printBook(head);
                break;
            case 3:
                printf("Nhap ID sach muon xoa: ");
                scanf("%d", &id);
                head = deleteBookById(head, id);
                break;
            case 4:
                printf("Nhap ID sach muon sua: ");
                scanf("%d", &id);
                head = updateBook(head, id);
                break;
            case 5:
                break;
            case 6:
                sortBook(head);
                break;
            case 7:
                break;
            case 8:
                printf("Thoat chuong trinh");
                break;
            default:
                printf("Lua chon khong hop le");
        }
    } while (choice != 8);


    return 0;
}
