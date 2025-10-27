#include <iostream>
#include <string>
using namespace std;

const int SIZE = 10;

struct Node {
    string key;  
    int value;   
    Node* next;
};

void initTable(Node* table[]) {
    for (int i = 0; i < SIZE; i++) {
        table[i] = nullptr;
    }
}

int hashFunction(string key) {
    int sum = 0;
    for (char c : key) sum += (int)c;
    return (sum % SIZE + SIZE) % SIZE;
}

void insert(Node* table[], string key, int value) {
    int index = hashFunction(key);
    Node* cur = table[index];
    while (cur != nullptr) {
        if (cur->key == key) {
            cur->value += value; 
            return;
        }
        cur = cur->next;
    }
    Node* baru = new Node;
    baru->key = key;
    baru->value = value;
    baru->next = table[index];
    table[index] = baru;
}

Node* search(Node* table[], string key) {
    int index = hashFunction(key);
    Node* cur = table[index];
    while (cur != nullptr) {
        if (cur->key == key) return cur;
        cur = cur->next;
    }
    return nullptr;
}

void removeKey(Node* table[], string key) {
    int index = hashFunction(key);
    Node* cur = table[index];
    Node* prev = nullptr;
    while (cur != nullptr) {
        if (cur->key == key) {
            if (prev == nullptr) table[index] = cur->next;
            else prev->next = cur->next;
            delete cur;
            return;
        }
        prev = cur;
        cur = cur->next;
    }
}

void display(Node* table[]) {
    cout << "\nDaftar Buku di Perpustakaan:\n";
    for (int i = 0; i < SIZE; i++) {
        cout << "Bucket " << i << ": ";
        Node* tmp = table[i];
        while (tmp != nullptr) {
            cout << "(" << tmp->key << "," << tmp->value << ") -> ";
            tmp = tmp->next;
        }
        cout << "NULL\n";
    }
}

int main() {
    Node* table[SIZE];
    initTable(table);

    insert(table, "Iron Man", 5);
    insert(table, "Avangers", 3);
    insert(table, "Study Group", 2);
    insert(table, "Antares", 2); 

    display(table);

    Node* hasil = search(table, "Antares");
    if (hasil != nullptr) {
        cout << "\nBuku 'Antares' ditemukan dengan jumlah = " << hasil->value << endl;
    } else {
        cout << "\nBuku 'Antares' tidak ditemukan\n";
    }

    removeKey(table, "Study Group");
    cout << "\nSetelah menghapus buku 'Study Group':\n";
    display(table);

    return 0;
}
