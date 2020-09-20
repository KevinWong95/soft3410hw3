#ifndef LINKEDLIST_MAP_H
#define LINKEDLIST_MAP_H

#include <stddef.h>

struct linkedlist_map_entry;
struct linkedlist_map;

struct linkedlist_map* linkedlist_map_new(int (*cmp)(void*, void*), void (*keydel)(void*), void(*valdel)(void*));
void linkedlist_map_put(struct linkedlist_map* map, void* key, void* value);
void* linkedlist_map_get(struct linkedlist_map* map, void* key);
void* linkedlist_map_remove(struct linkedlist_map* map, void* key);
size_t linkedlist_map_size(struct linkedlist_map* map);
void linkedlist_map_destroy(struct linkedlist_map* map);

#endif