#include <stdio.h>
#include <malloc.h>
#include "hashmap.h"
#include "intlist.h"
#include "tree.h"
#include "linkedlist.h"
#include <string.h>

#define bitset(byte,nbit)   ((byte) |=  (1<<(nbit)))
#define bitclear(byte,nbit) ((byte) &= ~(1<<(nbit)))
#define bitcheck(byte,nbit) ((byte) &   (1<<(nbit)))

struct ching {
    int value;
    int freq;
} typedef ching;

struct chang {
    unsigned char *array;
    char value;
} typedef chang;

char *code(char *input) {

}

// C program for Huffman Coding
#include <stdio.h>
#include <stdlib.h>

// This constant can be avoided by explicitly
// calculating height of Huffman Tree
#define MAX_TREE_HT 100

typedef unsigned char uchar;

// A Huffman tree node
struct MinHeapNode {
    struct MinHeapNode *left, *right;
    // One of the input characters
    unsigned char data;

    // Frequency of the character

    // Left and right child of this node
    unsigned freq;
};

// A Min Heap: Collection of
// min-heap (or Huffman tree) nodes
struct MinHeap {

    // Current size of min heap
    unsigned size;

    // capacity of min heap
    unsigned capacity;

    // Array of minheap node pointers
    struct MinHeapNode** array;
};

void encode_preorder_traversal(struct MinHeapNode * root, char * serialized_string, int * serialized_string_idx)
{
    if(root)
    {
        char * tmp_str = (char *)malloc(sizeof(char) * 10);
        int tmp_str_len = strlen(tmp_str);

        memcpy(&serialized_string[*serialized_string_idx], tmp_str, tmp_str_len);
        *serialized_string_idx += tmp_str_len;
        serialized_string[*serialized_string_idx] = ',';
        *serialized_string_idx += 1;

        free(tmp_str);

        encode_preorder_traversal(root->left, serialized_string, serialized_string_idx);
        encode_preorder_traversal(root->right, serialized_string, serialized_string_idx);
    }
    else
    {
        serialized_string[*serialized_string_idx] = '#';
        *serialized_string_idx += 1;
        serialized_string[*serialized_string_idx] = ',';
        *serialized_string_idx += 1;
    }
    return;
}

/** Encodes a tree to a single string. */
char* serialize(struct MinHeapNode* root)
{
    char * serialized_string = (char *)malloc(sizeof(char) * (10001 * 10));
    int serialized_string_idx = 0;

    encode_preorder_traversal(root, serialized_string, &serialized_string_idx);
    serialized_string[serialized_string_idx] = '\0';
    return serialized_string;
}

struct TreeNode * decode_preorder_traversal(struct MinHeapNode ** root, char * data, int * index)
{
    if(data[*index] != '\0')
    {
        if(data[*index] == '#')
        {
            *index += 2;
            return NULL;;
        }


        int val;
        char * tmp_str = (char *)malloc(sizeof(char) * 10);
        int tmp_str_idx = 0;
        while(data[*index] != ',')
        {
            tmp_str[tmp_str_idx++] = data[*index];
            *index += 1;
        }
        *index += 1;
        tmp_str[tmp_str_idx] = '\0';

        val = atoi(tmp_str);
        struct MinHeapNode * new_node = (struct MinHeapNode *)malloc(sizeof(struct MinHeapNode));
        new_node->data = val;
        new_node->left = NULL;
        new_node->right = NULL;

        if(*root == NULL)
        {
            *root = new_node;
        }

        new_node->left = decode_preorder_traversal(root, data, index);
        new_node->right = decode_preorder_traversal(root, data, index);
        return new_node;
    }
    return NULL;
}

/** Decodes your encoded data to tree. */
struct MinHeapNode* deserialize(char* data)
{
    struct MinHeapNode * root = NULL;

    int index = 0;
    decode_preorder_traversal(&root, data, &index);
    return root;
}

// A utility function allocate a new
// min heap node with given character
// and frequency of the character
struct MinHeapNode* newNode(char data, unsigned freq)
{
    struct MinHeapNode* temp = (struct MinHeapNode*)malloc(
            sizeof(struct MinHeapNode));

    temp->left = temp->right = NULL;
    temp->data = data;
    temp->freq = freq;

    return temp;
}

// A utility function to create
// a min heap of given capacity
struct MinHeap* createMinHeap(unsigned capacity)

{

    struct MinHeap* minHeap
            = (struct MinHeap*)malloc(sizeof(struct MinHeap));

    // current size is 0
    minHeap->size = 0;

    minHeap->capacity = capacity;

    minHeap->array = (struct MinHeapNode**)malloc(
            minHeap->capacity * sizeof(struct MinHeapNode*));
    return minHeap;
}

// A utility function to
// swap two min heap nodes
void swapMinHeapNode(struct MinHeapNode** a,
                     struct MinHeapNode** b)

{

    struct MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

// The standard minHeapify function.
void minHeapify(struct MinHeap* minHeap, int idx)

{

    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size
        && minHeap->array[left]->freq
           < minHeap->array[smallest]->freq)
        smallest = left;

    if (right < minHeap->size
        && minHeap->array[right]->freq
           < minHeap->array[smallest]->freq)
        smallest = right;

    if (smallest != idx) {
        swapMinHeapNode(&minHeap->array[smallest],
                        &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

// A utility function to check
// if size of heap is 1 or not
int isSizeOne(struct MinHeap* minHeap)
{

    return (minHeap->size == 1);
}

// A standard function to extract
// minimum value node from heap
struct MinHeapNode* extractMin(struct MinHeap* minHeap)

{

    struct MinHeapNode* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];

    --minHeap->size;
    minHeapify(minHeap, 0);

    return temp;
}

// A utility function to insert
// a new node to Min Heap
void insertMinHeap(struct MinHeap* minHeap,
                   struct MinHeapNode* minHeapNode)

{

    ++minHeap->size;
    int i = minHeap->size - 1;

    while (i
           && minHeapNode->freq
              < minHeap->array[(i - 1) / 2]->freq) {

        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }

    minHeap->array[i] = minHeapNode;
}

// A standard function to build min heap
void buildMinHeap(struct MinHeap* minHeap)

{

    int n = minHeap->size - 1;
    int i;

    for (i = (n - 1) / 2; i >= 0; --i)
        minHeapify(minHeap, i);
}

// A utility function to print an array of size n
void printArr(unsigned char arr[], int n)
{
    int i;
    for (i = 0; i < n; i++)
        printf("%d", arr[i]);

    printf("\n");
}

void printArrChar(unsigned char arr[], int n)
{
    int i;
    for (i = 0; i < n; i++)
        printf("%c", arr[i]);

    printf("\n");
}

// Utility function to check if this node is leaf
int isLeaf(struct MinHeapNode* root)

{
    return !(root->left) && !(root->right);
}

// Creates a min heap of capacity
// equal to size and inserts all character of
// data[] in min heap. Initially size of
// min heap is equal to capacity
struct MinHeap* createAndBuildMinHeap(char data[],
                                      int freq[], int size)

{

    struct MinHeap* minHeap = createMinHeap(size);

    for (int i = 0; i < size; ++i)
        minHeap->array[i] = newNode(data[i], freq[i]);

    minHeap->size = size;
    buildMinHeap(minHeap);

    return minHeap;
}

unsigned char bitArray(unsigned char *list) {
    unsigned char ret = 0;
    for(int i = 0 ;i  < 8 ; i++) {
        if(list[i] == 1) {
            bitset(ret,i);
        }
    }
    return ret;
}

ints *bitCoding(ints *list) {
    uchar* re = (uchar*) calloc(list->length,1);
    ints* ret = intsMake();
    ret->length = (list->length/8)+1;
    for(int i = 0 ;i  < ret->length ; i++) {
        for(int f = 0 ; f < 8 ; f++) {
            if (list->array[i * 8 + f] == 1) {
                bitset(ret->array[i], f);
            }
        }
    }
    ret->bytes = list->length;
    return ret;
}

// The main function that builds Huffman tree
struct MinHeapNode* buildHuffmanTree(char data[],
                                     int freq[], int size)

{
    struct MinHeapNode *left, *right, *top;

    // Step 1: Create a min heap of capacity
    // equal to size. Initially, there are
    // modes equal to size.
    struct MinHeap* minHeap
            = createAndBuildMinHeap(data, freq, size);

    // Iterate while size of heap doesn't become 1
    while (!isSizeOne(minHeap)) {

        // Step 2: Extract the two minimum
        // freq items from min heap
        left = extractMin(minHeap);
        right = extractMin(minHeap);

        // Step 3: Create a new internal
        // node with frequency equal to the
        // sum of the two nodes frequencies.
        // Make the two extracted node as
        // left and right children of this new node.
        // Add this node to the min heap
        // '$' is a special value for internal nodes, not
        // used
        top = newNode('$', left->freq + right->freq);

        top->left = left;
        top->right = right;

        insertMinHeap(minHeap, top);
    }

    // Step 4: The remaining node is the
    // root node and the tree is complete.
    return extractMin(minHeap);
}

// Prints huffman codes from the root of Huffman Tree.
// It uses arr[] to store codes
void printCodes(struct MinHeapNode* root, unsigned char arr[],
                int top,chang *ret)

{
    // Assign 0 to left edge and recur
    if (root->left) {
        arr[top] = 0;
        printCodes(root->left,arr,top+1,ret);
    }

    // Assign 1 to right edge and recur
    if (root->right) {
        arr[top] = 1;
        printCodes(root->right,arr,top+1,ret);
    }

    // If this is a leaf node, then
    // it contains one of the input
    // characters, print the character
    // and its code from arr[]
    if (isLeaf(root)) {
        printf("%c: ",root->data);
        printArr(arr,top);
        arr[top] = 0;
        chang rets;
        rets.value = root->data;
        unsigned char *thing = (unsigned char*) malloc(8);
        for(int i = 0 ; i < 8 ; i++) {
            if (i >= top) {
                thing[i] = 9;
            }
            else {thing[i] = arr[i];}
        }
        rets.array = thing;
        ret[bitArray(arr)] = rets;
    }
}

// The main function that builds a
// Huffman Tree and print codes by traversing
// the built Huffman Tree
struct MinHeapNode* HuffmanCodes(char data[], int freq[], int size,chang *ret,unsigned char *arr)

{
    // Construct Huffman Tree
    struct MinHeapNode* root = buildHuffmanTree(data, freq, size);

    // Print Huffman codes using
    // the Huffman tree built above
    int top = 0;
    printCodes(root, arr, top,ret);
    return root;
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
    sortArray(ret,b-2);
    return ret;
}

int getLength(ching **list) {
    int ret = 0;
    while(list[ret] != NULL) {
        ret++;
    }
    return ret-1;
}

ints *getId(slot *map,unsigned char key) {
    unsigned char *ids = (unsigned char*)getInt(key,map);
    int i = 7;
    while(ids[i] == 9) {
        i--;
    }
    i++;
    unsigned char *l = (unsigned char *)calloc(i,1);
    for(int f = 0; f < i ; f++) {
        l[f] =ids[f];
    }
    ints *ret = (ints*)malloc(sizeof(ints));
    ret->array = l;
    ret->length = i;
    return ret;
}

ints *concat(ints *a,ints *b) {
    for(int i = 0 ;i < b->length ; i++) {
        intsAdd(a,b->array[i]);
    }
    return a;
}

struct MinHeapNode* tree;


ints *codeBody(char *original) {
    unsigned char arr[MAX_TREE_HT];
    chang *ret  = (chang*)calloc(MAX_TREE_HT,sizeof(chang));
    ching **list = getList(original);
    int length = getLength(list);
    char *values = (char*)calloc(length,1);
    int *freqs = (char*)calloc(length,4);
    for(int i = 0 ; i < length ; i++) {
        values[i] = list[i]->value;
        freqs[i] = list[i]->freq;
    }
    tree = HuffmanCodes(values,freqs,length,ret,arr);
    int huflength = MAX_TREE_HT-1;
    while(ret[huflength].array == NULL) {
        huflength--;
    }
    slot *map = createHashmap();
    for(int i = 0 ; i < huflength+1 ; i++) {
        if(ret[i].value != NULL && ret[i].array != NULL) {
            map = insertInt(map, ret[i].value, ret[i].array);
        }
    }
    int i = 1;
    ints *l = getId(map, original[0]);
    while(original[i] != '\0') {
        l = concat(l,getId(map, original[i]));
        i++;
    }
    ints *final = bitCoding(l);
    return final;
}

ints *turnToBinary(ints *input) {
    ints* ret = (ints*) calloc(1,sizeof(ints));
    ret->array = (unsigned char*) calloc(input->length*8,sizeof(unsigned char));
    ret->length = input->bytes;
    for(int i = 0 ; i  < input->length ; i++) {
        for(int f = 0 ; f < 8 ; f++) {
            if(bitcheck(input->array[i],f) != 0) {
                ret->array[i * 8 + f] = 1;
            }
            else {
                ret->array[i * 8 + f] = 0;
            }
        }
    }
    return ret;
}

char decodeFromTree(struct MinHeapNode* root,ints* code,int* place) {
    char ret;
    if(isLeaf(root)) {
        ret = root->data;
        return ret;
    }
    if(code->array[*place] == 0) {
        (*place)++;
        return decodeFromTree(root->left,code,place);
    }
    if(code->array[*place] == 1) {
        (*place)++;
        return decodeFromTree(root->right,code,place);
    }
}

ints* getChar(struct MinHeapNode *root, ints* code) {
    ints *ret = intsMake();
    for(int i = 0 ; i < code->length ;) {
        intsAdd(ret,decodeFromTree(root,code,&i));
    }
    intsAdd(ret,0);
    return ret;
}

FILE* encodeStringHuf(char* original) {
    ints *f = codeBody(original);
    FILE *ptr = fopen("file.huf","wb+");
    short *exp = (short*) malloc(sizeof(short));
    (*exp) = f->length*8;
    short *length = (short*) malloc(sizeof(short));
    (*length) = f->bytes;
    fwrite(exp,sizeof(short),1,ptr);
    fwrite(length,sizeof(short),1,ptr);
    fwrite((f->array),sizeof(char),f->length,ptr);
    char *tre = serialize(tree);
    int i = 0;
    while(tre[i] != 0) {i++;}
    fwrite(tre,sizeof(char),i,ptr);
    rewind(ptr);
    return ptr;
}

FILE* encodeHuf(FILE* input) {
    fseek(input,0L,SEEK_END);
    int lengtht = ftell(input);
    char* original = (char*) calloc(lengtht,1);
    rewind(input);
    fread(original,1,lengtht,input);
    return encodeStringHuf(original);
}

unsigned char* decodeStringHuf(FILE* ptr) {
    short expret;
    short lengthret;
    rewind(ptr);
    fread(&expret,sizeof(short),1,ptr);
    fread(&lengthret,sizeof(short),1,ptr);
    unsigned char *arr = (unsigned char*) calloc(expret/8,sizeof(char));
    fread(arr,sizeof(char),expret/8,ptr);
    ints* list = intsMake();
    list->array = arr;
    list->length = expret/8;
    list->bytes = lengthret;
    long int cur = ftell(ptr);
    fseek(ptr, 0L, SEEK_END);
    long int end = ftell(ptr);
    long treeSize =  end-cur;
    char* treechars = (char*)calloc(treeSize,1);
    fseek(ptr,cur,SEEK_SET);
    fread(treechars,1,treeSize,ptr);
    printf("%s\n",treechars);
    printf("%s",serialize(tree));
    struct MinHeapNode* root = (struct MinHeapNode*) malloc(sizeof(struct MinHeapNode));
    root = deserialize(treechars);
    return getChar(root,turnToBinary(list))->array;
}

int main(int argc, char* argv[]) {
    char *original = "go go gophers";
    FILE* originalFile = fopen("hello.txt","w+");
    fwrite(original,1,strlen(original)+1,originalFile);

    FILE* ptr = encodeHuf(originalFile);
    unsigned char* ret = decodeStringHuf(ptr);
    printf("%s()", ret);
    free(ret);
    return 0;
}

