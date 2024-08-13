#include <stdio.h>
#include <malloc.h>
#include "hashmap.h"
#include "intlist.h"
#include "tree.h"
#include "linkedlist.h"
#include <string.h>

struct ching {
    int value;
    int freq;
} typedef ching;

char *code(char *input) {

}

ching **sortArray(ching** list,int length) {
    for(int i = 0 ; i < length ; i++) {
        for (int f = i ; f < length ; f++) {
            if (list[i]->freq < list[f]->freq) {
                ching* var= list[i];
                list[i] = list[f];
                list[f] = var;
            }
        }
    }
    return list;
}

ching *getAmount(char *input,int i) {
    char c = input[i];
    char f = -1;
    int freq = 0;
    int length = strlen(input);
    for(i = 0 ; i  < length; i++) {
        f = input[i];
        if(f == c) {
            freq++;
        }
    }
    ching *ret = (ching*)malloc(sizeof(ching));
    ret->freq = freq;
    ret->value = c;
    return ret;
}

ching **getList(char *input) {
    slot *map = createHashmap();
    for(int i = 0 ; i < strlen(input) ; i++) {
        map = insertInt(map,input[i], getAmount(input,i));
    }
    long b = *(long*)(map[0].value) + 1;
    ching **ret = (ching**)malloc(b*sizeof(ching*));
    ret[b-1] = NULL;
    for(int i = 1 ; i < b; i++) {
        ret[i-1] = (ching*)map[i].value;
    }
    return ret;
}

int getLength(ching **list) {
    int ret = 0;
    while(list[ret] != NULL) {
        ret++;
    }
    return ret-1;
}



int main(int argc, char* argv[]) {
    ching **list = getList("go go gophers");
    int length = getLength(list);
    sortArray(list,length);
    for(int i = 0 ; i < length ; i++) {
        printf(" '%c' ",list[i]->value);
    }
    printf("\n");
    for(int i = 0 ; i < length ; i++) {
        printf("  %d  ",list[i]->freq);
    }
    free(list);
    return 0;
}