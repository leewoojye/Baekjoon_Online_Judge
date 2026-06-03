#include <iostream>

using namespace std;

struct Node {
    int data;
    Node *next;
    Node(int x) : data(x), next(nullptr) {} // 생성자 초기화 리스트
};

void printList(Node* head) {
    Node* current = head;
    while (current != nullptr) {
        cout << current->data;
        if (current->next != nullptr) {
            cout << " -> ";
        }
        current = current->next;
    }
    cout << " -> NULL" << endl;
}

void removeDuplicates(Node* head) {
    Node* current = head;
    while (current != nullptr) {
        Node* runner = current;
        while (runner->next != nullptr) {
            if (runner->next->data == current->data) {
                Node* duplicate = runner->next;
                runner->next = runner->next->next;
                delete duplicate;
            } else {
                runner = runner->next;
            }
        }
        current = current->next;
    }
}

int main() {
    Node* head = new Node(10);
    head->next = new Node(20);
    head->next->next = new Node(30);
    head->next->next->next = new Node(20);
    head->next->next->next->next = new Node(40);
    head->next->next->next->next->next = new Node(10);

    cout << "(입력 리스트 출력)" << endl;
    printList(head);

    removeDuplicates(head);

    cout << "(중복 제거 리스트 출력)" << endl;
    printList(head);

    Node* current = head;
    while (current != nullptr) {
        Node* temp = current;
        current = current->next;
        delete temp;
    }

    return 0;
}
