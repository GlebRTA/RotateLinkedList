#include <iostream>
#include <string>

using namespace std;

template<typename T>
class Node {
public:
    T value;
    Node* pPrev;
    Node* pNext;

    Node(T value) {
        this->value = value;
        this->pPrev = nullptr;
        this->pNext = nullptr;
    }
};


template<typename T>
class RotateList {
protected:
    int size;
    Node<T>* first;
    Node<T>* last;

    bool isEmpty() {
        return first == nullptr;
    }

    void deleteAll() {
        Node<T>* temp = first;
        Node<T>* temp1 = nullptr;
        for (int i = 0; i < size; i++) {
            temp1 = temp;
            temp = temp->pNext;
            delete temp1;
        }
    }

public:
    RotateList() {
        size = 0;
        first = nullptr;
        last = nullptr;
    }

    ~RotateList() {
        deleteAll();
    }

    void push(T value) {
        Node<T>* temp = new Node<T>(value);

        if (isEmpty()) {
            first = temp;
            last = temp;
        }
        else {
            temp->pPrev = last;
            last->pNext = temp;
            last = temp;
            last->pNext = first;
            first->pPrev = last;
        }
        size++;
    }

    void printForward(int index = 0) {
        Node<T>* temp = first;
        for (int i = 0; i < abs(index); i++) {
            temp = temp->pNext;
        }
        cout << temp->value << " ";
    }

    void printBackward(int index = 0) {
        Node<T>* temp = last;
        for (int i = 0; i < abs(index); i++) {
            temp = temp->pPrev;
        }
        cout << temp->value << " ";
    }

    void remove(int index) {
        if (isEmpty()) {
            return;
        } else if (index == 0) {
            removeFirst();
        } else if (index == size - 1) {
            removeLast();
        } else {
            if (index < size / 2) {
                removeFromStart(index);
            } else {
                removeFromEnd(index);
            }
        }
    }

    void removeFromStart(int index) {
        Node<T>* temp = first;
        for (int i = 0; i < index; i++) {
            temp = temp->pNext;
        }
        temp->pPrev->pNext = temp->pNext;
        temp->pNext->pPrev = temp->pPrev;
        size--;
        delete temp;
    }

    void removeFromEnd(int index) {
        Node<T>* temp = last;
        for (int i = 0; i < size - index - 1; i++) {
            temp = temp->pPrev;
        }
        temp->pPrev->pNext = temp->pNext;
        temp->pNext->pPrev = temp->pPrev;
        size--;
        delete temp;
    }

    void removeFirst() {
        if (isEmpty()) {
            return;
        }
        Node<T>* temp = first;
        first = temp->pNext;
        first->pPrev = last;
        last->pNext = first;
        size--;
        delete temp;
    }

    void removeLast() {
        if (isEmpty()) {
            return;
        }
        Node<T>* temp = last;
        last = temp->pPrev;
        last->pNext = first;
        first->pPrev = last;
        size--;
        delete temp;
    }

    int getSize() {
        return size;
    }
};

template <typename T>
class Catalog: public RotateList<T> {
private:
    Node<T>* current;

public:
    Catalog() {
        this->current = nullptr;
    }

    T nextCurrent() {
        if(current == nullptr) {
            current = this->first;
        }
        else {
            current = current->pNext;
        }
        return current->value;
    }

    T prevCurrent() {
        if(current == nullptr) {
            current = this->last;
        }
        else {
            current = current->pPrev;
        }
        return current->value;
    }

    void resetCurrent() {
        current = nullptr;
    }
};


void printConditions() {
    cout << "write \"1\" to see next album\n";
    cout << "write \"2\" to see previous album\n";
    cout << "write \"3\" to exit\n";
}


int main() {

    int numOfAlbums;
    bool programLoop = true;
    int click;
    string album;

    Catalog<string> list;
    cout << "Enter number of albums\n";
    cin >> numOfAlbums;
    cin.ignore();
    for (int i = 0; i < numOfAlbums; i++) {
        cout << "Input " << i + 1 << ". album:\n";
        getline(cin, album);
        list.push(album);
    }

    printConditions();
    while (programLoop) {
        cin >> click;
        switch (click) {
            case 3:
                programLoop = false;
                break;
            case 2:
                cout << list.prevCurrent() << endl;
                break;
            case 1:
                cout << list.nextCurrent() << endl;
                break;

        }
    }

    system("pause");
}