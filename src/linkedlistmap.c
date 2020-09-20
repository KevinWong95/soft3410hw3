#include <stdlib.h>
#include "linkedlistmap.h"

struct linkedlist_map {
    size_t size;
    struct linkedlist_map_entry* head;
    struct linkedlist_map_entry* tail;

    int (*cmp)(void*, void*);
    void (*keydel)(void*);
    void (*valdel)(void*);

};

struct linkedlist_map_entry {
    void* key;
    void* value;
    struct linkedlist_map_entry* previous;
    struct linkedlist_map_entry* next;
};

// Helper method that iterates through a linkedlist and returns the entry with the corresponding key, returning NULL if no such matching entry exists. This functionality is used in get, put, and remove, so it has been moved to a helper method.
struct linkedlist_map_entry* find_entry_with_key(struct linkedlist_map* map, void* key) {
    struct linkedlist_map_entry* current = map->head;

    while (current != NULL) {
        if (map->cmp(key, current->key) == 0) {
            return current;
        }
        current = current->next;
    }

    return NULL;
}

struct linkedlist_map* linkedlist_map_new(int (*cmp)(void*, void*), void (*keydel)(void*), void(*valdel)(void*)) {
    struct linkedlist_map* newMap = (struct linkedlist_map*) malloc(sizeof(struct linkedlist_map));
    newMap->cmp = cmp;
    newMap->keydel = keydel;
    newMap->valdel = valdel;

    newMap->size = 0;
    newMap->head = NULL;
    newMap->tail = NULL;

    return newMap;
}

void linkedlist_map_put(struct linkedlist_map* map, void* key, void* value) {
    struct linkedlist_map_entry* entry = find_entry_with_key(map, key);
    if (entry != NULL) {
        // Need to delete previous data.
        map->keydel(entry->key);
        map->valdel(entry->value);

        entry->key = key;
        entry->value = value;

        return;
    }

    // Since the key is not already in the map, create an entry and add it to the list.
    entry = (struct linkedlist_map_entry*) malloc(sizeof(struct linkedlist_map_entry));
    entry->key = key;
    entry->value = value;

    if (map->size == 0) {
        entry->previous = NULL;
        entry->next = NULL;
        map->head = entry;
        map->tail = entry;
    } else {
        entry->previous = map->tail;
        entry->next = NULL;
        map->tail->next = entry;
        map->tail = entry;
    }

    map->size += 1;
    return;
}

void* linkedlist_map_get(struct linkedlist_map* map, void* key) {

    struct linkedlist_map_entry* entry = find_entry_with_key(map, key);
    if (entry != NULL) {
        return entry->value;
    }

    return NULL;
}

void* linkedlist_map_remove(struct linkedlist_map* map, void* key) {
    struct linkedlist_map_entry* entry = find_entry_with_key(map, key);
    if (entry == NULL) {
        return NULL;
    }

    if (entry == map->head && entry == map->tail) {
        map->head = NULL;
        map->tail = NULL;
    } else if (entry == map->head) {
        map->head = entry->next;
        map->head->previous = NULL;
    } else if (entry == map->tail) {
        map->tail = entry->previous;
        map->tail->next = NULL;
    } else {
        entry->previous->next = entry->next;
        entry->next->previous = entry->previous;
    }

    map->keydel(entry->key);
    void* value = entry->value;
    free(entry);
    map->size -= 1;

    return value;
}

size_t linkedlist_map_size(struct linkedlist_map* map) {
    return map->size;
}

void linkedlist_map_destroy(struct linkedlist_map* map) {
    struct linkedlist_map_entry* current = map->head;

    while (current != NULL) {
        struct linkedlist_map_entry* next = current->next;
        
        map->keydel(current->key);
        map->valdel(current->value);
        free(current);

        current = next;
    }

    free(map);
    return;
}