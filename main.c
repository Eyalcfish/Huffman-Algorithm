#include <stdio.h>
#include <malloc.h>

struct intList {
    int *array;
    int length;
    int bytes;
} typedef ints;

ints *intsMake() {
    ints *ret = (ints*)malloc(sizeof(ints));
    ret->array = (int*)malloc(sizeof(int));
    ret->length = 0;
    ret->bytes = 4;
    return ret;
}

ints *intsAdd(ints* list,int a) {
    list->array = (int*) realloc(list->array,sizeof(int)*(list->length+1));
    list->array[list->length] = a;
    list->length++;
    list->bytes = list->length*4;
    return list;
}

void printList(ints* list) {
    printf("-----------------\n");
    for(int i = 0 ; i < list->length ; i++) {
        printf("%d\n",list->array[i]);
    }
    printf("-----------------\n");
}

int main() {
    ints *list = intsMake();
    list = intsAdd(list,1);
    list = intsAdd(list,6);
    list = intsAdd(list,1);
    list = intsAdd(list,3);
    list = intsAdd(list,5);
    printList(list);
    printf("Hello, World!\n");
    free(list);
    return 0;
}
