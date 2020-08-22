#include <iostream>

int doNothing() {
/* G */ int b = 50;
        int c = 100;
/* H */ return b;
}

int* getObject() {
/* C */ int a = 10;
        // int* ptr = &a;
        int* ptr = new int{40};
/* D */ return ptr;
}

int main() {
/* A */ int number = 5;
/* B */ int* pointer = getObject();
/* E */ *pointer = 20;
        new int{60};
        delete pointer;
        new int{80};
/* F */ number = doNothing();
/* I */ std::cout << *pointer << '\n';
}