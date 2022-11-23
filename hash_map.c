#include "hash_map.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct hash_map *hash_map_init(size_t size)
{
    struct hash_map *n_node = malloc(sizeof(struct hash_map));
    if (!n_node)
        return NULL;
    n_node->size = size;
    struct pair_list **pl = calloc(size, sizeof(struct pair_list));
    if (!pl)
        return NULL;
    n_node->data = pl;
    return n_node;
}
bool hash_map_insert(struct hash_map *hash_map, const char *key, char *value,
                     bool *updated)
{
    *updated = false;
    if (hash_map == NULL)
        return false;
    if (hash_map->size == 0)
        return false;
    size_t index = hash(key) % hash_map->size;
    struct pair_list *hi = malloc(sizeof(struct pair_list));
    if (hi == NULL)
        return false;
    struct pair_list *pl = hash_map->data[index];
    while (pl != NULL)
    {
        if (!strcmp(key, pl->key))
        {
            pl->value = value;
            *updated = true;
            free(hi);
            return true;
        }
        pl = pl->next;
    }
    pl = hash_map->data[index];
    hi->key = key;
    hi->value = value;
    hi->next = pl;
    hash_map->data[index] = hi;
    return true;
}
void hash_map_free(struct hash_map *hash_map)
{
    if (hash_map == NULL)
        return;
    size_t i = 0;
    while (i < hash_map->size)
    {
        struct pair_list *temp = hash_map->data[i];
        while (temp != NULL)
        {
            struct pair_list *temp1 = temp->next;
            free(temp);
            temp = temp1;
        }
        i++;
    }
    free(hash_map->data);
    free(hash_map);
}
