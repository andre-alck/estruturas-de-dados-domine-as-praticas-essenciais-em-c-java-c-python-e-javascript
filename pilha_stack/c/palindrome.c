#include <stdio.h>
#include <stdlib.h>

typedef struct element {
    struct element * next;
    int value;
}
Element;

typedef struct stack {
    Element * top;
    int size;
}
Stack;

Stack * init() {
    Stack * p = malloc(sizeof(Stack));
    p -> top = NULL;
    p -> size = 0;
    return p;
}

int isEmpty(Stack * p) {
    return p -> top == NULL || p -> size == 0;
}

void empty(Stack * p) {
    while (!isEmpty(p)) {
        pop(p);
    }
}

void push(Stack * p, int value) {
    Element * e = malloc(sizeof(e));
    e -> next = p -> top;
    e -> value = value;

    p -> top = e;
    p -> size = p -> size + 1;
}

void pushValues(Stack * p, int data[], int size) {
    empty(p);

    int i;
    for (i = 0; i < size; i++) {
        push(p, data[i]);
    }
}

int pop(Stack * p) {
    if (!isEmpty(p)) {
        Element * e = p -> top;
        int v = e -> value;

        p -> top = p -> top -> next;
        p -> size = p -> size - 1;

        free(e);
        e = NULL;

        return v;
    }

    printf("Stack vazia.");
    return -1;
}

void printStatus(int is) {
    if (is) {
        printf("E palindromo.\n");
    } else {
        printf("Nao e palindromo.\n");
    }
}

void isPalindrome(Stack * p, int data[], int size) {
    int isImpar = size % 2 != 0;

    int i = 0, is = 1;

    if (isImpar) {
        for (i = 0; i <= (size / 2) - 1; i++) {
            int popped = pop(p);
            if (popped != data[i]) {
                is = 0;
                break;
            }
        }
    } else {
        while (i < size / 2) {
            int popped = pop(p);
            if (popped != data[i]) {
                is = 0;
                break;
            }
            i++;
        }
    }

    printStatus(is);
}

void actOn(Stack * p, int data[], int dataSize) {
    pushValues(p, data, dataSize);
    isPalindrome(p, data, dataSize);
}

int main() {
    Stack * p = init();

    int firstPalindrome[] = {
        1,
        2,
        3,
        2,
        1
    };
    actOn(p, firstPalindrome, sizeof(firstPalindrome) / sizeof(int));

    int justABunchOfIntegers[] = {
        3,
        5,
        6,
        7,
        8
    };
    actOn(p, justABunchOfIntegers, sizeof(justABunchOfIntegers) / sizeof(int));

    int anotherPalindrome[] = {
        1,
        2,
        2,
        1
    };
    actOn(p, anotherPalindrome, sizeof(anotherPalindrome) / sizeof(int));

    int randomNumbers[] = {
        1,
        2,
        2,
        3
    };
    actOn(p, randomNumbers, sizeof(randomNumbers) / sizeof(int));

    return 0;
}