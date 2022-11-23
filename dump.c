#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash_map.h"

void hash_map_dump(struct hash_map *hash_map)
{
    if (hash_map == NULL)
        return;
    if (hash_map->size == 0)
        return;
    size_t i = 0;
    while (i < hash_map->size)
    {
        struct pair_list *pl = hash_map->data[i];
        while (pl != NULL)
        {
            if (!pl->next)
                printf("%s: %s\n", pl->key, pl->value);
            else
                printf("%s: %s, ", pl->key, pl->value);
            pl = pl->next;
        }
        i++;
    }
}
const char *hash_map_get(const struct hash_map *hash_map, const char *key)
{
    if (hash_map == NULL)
        return NULL;
    if (hash_map->size == 0)
        return NULL;
    size_t index = hash(key) % hash_map->size;
    struct pair_list *pl = hash_map->data[index];
    if (pl == NULL)
        return NULL;
    while (pl != NULL)
    {
        if (!strcmp(key, pl->key))
            return pl->value;
        pl = pl->next;
    }
    return NULL;
}
bool hash_map_remove(struct hash_map *hash_map, const char *key)
{
    if (hash_map == NULL)
        return false;
    if (hash_map->size == 0)
        return false;
    size_t index = hash(key) % hash_map->size;
    struct pair_list *pl = hash_map->data[index];
    if (!pl)
        return false;
    if (strcmp(key, pl->key) == 0)
    {
        hash_map->data[index] = pl->next;
        free(pl);
        return true;
    }
    while (pl->next != NULL)
    {
        if (strcmp(key, pl->next->key) == 0)
        {
            struct pair_list *pl2 = pl->next->next;
            free(pl->next);
            pl->next = pl2;
            return true;
        }
        pl = pl->next;
    }
    return false;
}
