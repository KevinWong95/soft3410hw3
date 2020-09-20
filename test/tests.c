#include "../src/linkedlistmap.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

int compareInt(void* a, void* b) {
    int* valueA = (int*)a;
    int* valueB = (int*)b;
    if (*valueA == *valueB) {
        return 0;
    } else if (*valueA < *valueB) {
        return -1;
    } else {
        return 1;
    }
}

void deleteInt(void* a) {
    free(a);
    return;
}

void testIntSimple() {
    struct linkedlist_map* myMap = linkedlist_map_new(&compareInt, &deleteInt, &deleteInt);
    int* key1 = malloc(sizeof(int));
    int* key2 = malloc(sizeof(int));
    int* key3 = malloc(sizeof(int));
    int* value1 = malloc(sizeof(int));
    int* value2 = malloc(sizeof(int));
    int* value3 = malloc(sizeof(int));
    *key1 = 3;
    *key2 = 3;
    *key3 = 5;
    *value1 = 4;
    *value2 = 7;
    *value3 = 8;

    int key2Value = 3;

    linkedlist_map_put(myMap, key1, value1);
    assert(linkedlist_map_size(myMap) == 1);
    // key2 and key1 are the same as defined by the comparator function, so this should work
    assert(*((int*)linkedlist_map_get(myMap, key2)) == 4);
    linkedlist_map_put(myMap, key2, value2);
    assert(linkedlist_map_size(myMap) == 1);
    assert(*((int*)linkedlist_map_get(myMap, key2)) == 7);
    linkedlist_map_put(myMap, key3, value3);
    assert(linkedlist_map_size(myMap) == 2);
    assert(*((int*)linkedlist_map_get(myMap, key3)) == 8);
    assert(*((int*)linkedlist_map_remove(myMap, key2)) == 7);
    assert(linkedlist_map_get(myMap, &key2Value) == NULL);
    assert(linkedlist_map_size(myMap) == 1);
    linkedlist_map_destroy(myMap);
}

void testIntLarge() {
    int index = 0;
    int numEntries = 10000;
    struct linkedlist_map* myMap = linkedlist_map_new(&compareInt, &deleteInt, &deleteInt);
    for (index = 0; index < numEntries; index++) {
        int* key = malloc(sizeof(int));
        int* value = malloc(sizeof(int));

        *key = index % (numEntries / 2);
        *value = index % (numEntries / 2) + 1;

        linkedlist_map_put(myMap, key, value);
    }
    assert(linkedlist_map_size(myMap) == numEntries / 2);

    for (index = 0; index < numEntries / 2; index++) {
        assert(*((int*)linkedlist_map_get(myMap, &index)) == (index + 1));
    }
    linkedlist_map_destroy(myMap);
}

struct SimpleStruct {
    double d;
    float f;
};

int compareSimpleStruct(void* a, void* b) {
    struct SimpleStruct* valueA = (struct SimpleStruct*)a;
    struct SimpleStruct* valueB = (struct SimpleStruct*)b;
    if (valueA->d == valueB->d) {
        if (valueA->f < valueB->f) {
            return -1;
        } else if (valueA->f > valueB->f) {
            return 1;
        }
        return 0;
    } else if (valueA->d < valueB->d) {
        return -1;
    } else {
        return 1;
    }
}

void deleteSimpleStruct(void* a) {
    free(a);
    return;
}

void testSimpleStruct() {
    struct linkedlist_map* myMap = linkedlist_map_new(&compareSimpleStruct, &deleteSimpleStruct, &deleteInt);
    struct SimpleStruct* key1 = malloc(sizeof(struct SimpleStruct));
    struct SimpleStruct* key2 = malloc(sizeof(struct SimpleStruct));
    struct SimpleStruct* key3 = malloc(sizeof(struct SimpleStruct));
    struct SimpleStruct* key4 = malloc(sizeof(struct SimpleStruct));
    key1->d = 10.0;
    key1->f = 3.1f;
    
    key2->d = 10.0;
    key2->f = 3.1f;
    
    key3->d = 10.0;
    key3->f = 3.2f;

    key4->d = -1.0;
    key4->f = 3.1f;

    int* value1 = malloc(sizeof(int));
    int* value2 = malloc(sizeof(int));
    int* value3 = malloc(sizeof(int));
    int* value4 = malloc(sizeof(int));

    *value1 = 1;
    *value2 = 2;
    *value3 = 3;
    *value4 = 4;

    linkedlist_map_put(myMap, key1, value1);
    assert(linkedlist_map_size(myMap) == 1);
    // key2 and key1 are the same as defined by the comparator function, so this should work
    assert(*((int*)linkedlist_map_get(myMap, key2)) == 1);
    linkedlist_map_put(myMap, key2, value2);
    assert(linkedlist_map_size(myMap) == 1);
    assert(*((int*)linkedlist_map_get(myMap, key2)) == 2);
    linkedlist_map_put(myMap, key3, value3);
    assert(linkedlist_map_size(myMap) == 2);
    assert(*((int*)linkedlist_map_get(myMap, key3)) == 3);
    assert(*((int*)linkedlist_map_remove(myMap, key2)) == 2);
    assert(linkedlist_map_size(myMap) == 1);
    linkedlist_map_put(myMap, key4, value4);
    assert(*((int*)linkedlist_map_get(myMap, key4)) == 4);
    assert(linkedlist_map_size(myMap) == 2);
    linkedlist_map_destroy(myMap);
}