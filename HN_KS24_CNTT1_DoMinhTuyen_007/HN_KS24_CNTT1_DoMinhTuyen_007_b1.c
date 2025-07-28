#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct {
    int id;
    char customer[50];
    int status;
    float total;
} Order;
typedef struct DoubleNode {
    Order order;
    struct DoubleNode *next;
    struct DoubleNode *prev;
} DoubleNode;
typedef struct SingleNode {
    Order order;
    struct SingleNode *next;
} SingleNode;
DoubleNode *doubleHead = NULL;
SingleNode *singleHead = NULL;
DoubleNode *createDoubleNode(Order order) {
    DoubleNode *node = (DoubleNode *)malloc(sizeof(DoubleNode));
    node->order = order;
    node->next = NULL;
    node->prev = NULL;
    return node;
}
SingleNode *createSingleNode(Order order) {
    SingleNode *node = (SingleNode *)malloc(sizeof(SingleNode));
    node->order = order;
    node->next = NULL;
    return node;
}
Order createOrder() {
    Order order;
    printf("Enter ID: ");
    scanf("%d", &order.id);
    printf("Enter Name: ");
    fflush(stdin);
    fgets(order.customer, sizeof(order.customer), stdin);
    order.customer[strcspn(order.customer, "\n")] = 0;
    order.status = 0;
    printf("Enter Total: ");
    scanf("%f", &order.total);
    return order;
}
DoubleNode *insertDoubleNodeAtEnd(DoubleNode *head, Order order) {
    DoubleNode *newNode = createDoubleNode(order);
    if (head == NULL)
        return newNode;
    DoubleNode *curr = head;
    while (curr->next != NULL)
        curr = curr->next;
    curr->next = newNode;
    newNode->prev = curr;
    return head;
}
SingleNode *insertSingleNodeAtEnd(SingleNode *head, Order order) {
    SingleNode *newNode = createSingleNode(order);
    if (head == NULL)
        return newNode;
    SingleNode *curr = head;
    while (curr->next != NULL)
        curr = curr->next;
    curr->next = newNode;
    return head;
}
void printDoubleList(DoubleNode *head) {
    if (head == NULL) {
        printf("Khong co don chua giao\n");
        return;
    }
    DoubleNode *curr = head;
    while (curr != NULL) {
        printf("ID: %d\n", curr->order.id);
        printf("Name: %s\n", curr->order.customer);
        printf("Status: %d\n", curr->order.status);
        printf("Total: %.2f\n", curr->order.total);
        printf("--------------------\n");
        curr = curr->next;
    }
}
void printSingleList(SingleNode *head) {
    if (head == NULL) {
        printf("Khong co don da giao\n");
        return;
    }
    SingleNode *curr = head;
    while (curr != NULL) {
        printf("ID: %d\n", curr->order.id);
        printf("Name: %s\n", curr->order.customer);
        printf("Status: %d\n", curr->order.status);
        printf("Total: %.2f\n", curr->order.total);
        printf("--------------------\n");
        curr = curr->next;
    }
}
DoubleNode *deleteDoubleNodeById(DoubleNode *head) {
    int id;
    printf("Enter delete ID: ");
    scanf("%d", &id);
    if (head == NULL) {
        printf("Danh sach rong.\n");
        return head;
    }
    DoubleNode *curr = head;
    while (curr != NULL && curr->order.id != id)
        curr = curr->next;

    if (curr == NULL) {
        printf("ID not found\n");
        return head;
    }

    if (curr == head) {
        head = curr->next;
        if (head != NULL)
            head->prev = NULL;
    } else {
        curr->prev->next = curr->next;
        if (curr->next != NULL)
            curr->next->prev = curr->prev;
    }

    free(curr);
    printf("Xoa thanh cong.\n");
    return head;
}
void updateOrder(DoubleNode *head) {
    int id;
    printf("Enter update ID: ");
    scanf("%d", &id);
    DoubleNode *curr = head;
    while (curr != NULL && curr->order.id != id)
        curr = curr->next;
    if (curr == NULL) {
        printf("ID not found.\n");
        return;
    }
    printf("Nhap ten moi: ");
    fflush(stdin);
    fgets(curr->order.customer, sizeof(curr->order.customer), stdin);
    curr->order.customer[strcspn(curr->order.customer, "\n")] = 0;
    printf("Nhap tong tien moi: ");
    scanf("%f", &curr->order.total);
    printf("Cap nhat thanh cong.\n");
}
void updateOrderStatus() {
    int id;
    printf("Enter ID to mark as delivered: ");
    scanf("%d", &id);
    DoubleNode *curr = doubleHead;
    while (curr != NULL && curr->order.id != id)
        curr = curr->next;

    if (curr == NULL) {
        printf("ID not found.\n");
        return;
    }

    Order order = curr->order;
    order.status = 1;

    if (curr == doubleHead) {
        doubleHead = curr->next;
        if (doubleHead != NULL)
            doubleHead->prev = NULL;
    } else {
        curr->prev->next = curr->next;
        if (curr->next != NULL)
            curr->next->prev = curr->prev;
    }
    free(curr);
    singleHead = insertSingleNodeAtEnd(singleHead, order);
    printf("Da danh dau don hang da giao.\n");
}
void sortDoubleListByTotal() {
    if (doubleHead == NULL || doubleHead->next == NULL) return;

    for (DoubleNode *i = doubleHead; i->next != NULL; i = i->next) {
        for (DoubleNode *j = i->next; j != NULL; j = j->next) {
            if (i->order.total > j->order.total) {
                Order temp = i->order;
                i->order = j->order;
                j->order = temp;
            }
        }
    }
    printf("Da sap xep theo tong tien.\n");
}
void searchOrderById(int id) {
    DoubleNode *currD = doubleHead;
    while (currD != NULL) {
        if (currD->order.id == id) {
            printf("Tim thay trong danh sach chua giao:\n");
            printf("ID: %d | Name: %s | Status: %d | Total: %.2f\n",
                   currD->order.id, currD->order.customer, currD->order.status, currD->order.total);
            return;
        }
        currD = currD->next;
    }

    SingleNode *currS = singleHead;
    while (currS != NULL) {
        if (currS->order.id == id) {
            printf("Tim thay trong danh sach da giao:\n");
            printf("ID: %d | Name: %s | Status: %d | Total: %.2f\n",
                   currS->order.id, currS->order.customer, currS->order.status, currS->order.total);
            return;
        }
        currS = currS->next;
    }

    printf("Khong tim thay don hang co ID: %d\n", id);
}
int main() {
    int choice;
    do {
        printf("\n====== MENU ======\n");
        printf("1. Them don hang moi\n");
        printf("2. Hien thi danh sach don hang\n");
        printf("3. Xoa don hang\n");
        printf("4. Cap nhat thong tin don hang\n");
        printf("5. Danh dau don hang da giao\n");
        printf("6. Sap xep don hang theo tong tien\n");
        printf("7. Tim kiem don hang theo ID\n");
        printf("8. Thoat\n");
        printf("Your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: {
                Order order = createOrder();
                doubleHead = insertDoubleNodeAtEnd(doubleHead, order);
                break;
            }
            case 2:
                printf("\n--- Don hang CHUA GIAO ---\n");
                printDoubleList(doubleHead);
                printf("\n--- Don hang DA GIAO ---\n");
                printSingleList(singleHead);
                break;
            case 3:
                doubleHead = deleteDoubleNodeById(doubleHead);
                break;
            case 4:
                updateOrder(doubleHead);
                break;
            case 5:
                updateOrderStatus();
                break;
            case 6:
                sortDoubleListByTotal();
                break;
            case 7: {
                int id;
                printf("Nhap ID can tim: ");
                scanf("%d", &id);
                searchOrderById(id);
                break;
            }
            case 8:
                printf("Ket thuc chuong trinh.\n");
                break;
            default:
                printf("Lua chon khong hop le!\n");
        }
    } while (choice != 8);

    return 0;
}