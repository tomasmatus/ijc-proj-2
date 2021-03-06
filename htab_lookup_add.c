/*
 * Řešení IJC-DU2
 * Autor: Tomáš Matuš, FIT VUT Brno
 * Login: xmatus37
 * Datum: 19.4.2021
 * Přeloženo: gcc 10.2.0
 */

#include <stdlib.h>
#include <string.h>
#include "htab.h"
#include "htab_struct.h"

htab_pair_t * htab_lookup_add(htab_t * t, htab_key_t key) {
    htab_pair_t *itm = htab_find(t, key);
    if (itm != NULL) {
        return itm;
    }

    // init new item
    struct htab_item *newItm = malloc(sizeof(struct htab_item));
    if (newItm == NULL) {
        return NULL;
    }
    // allocate length of key + \0 because strlen() excludes that
    size_t keySize = strlen(key) + 1;
    newItm->pair.key = malloc(keySize);
    if (newItm->pair.key == NULL) {
        free(newItm);
        return NULL;
    }
    memcpy((char*)newItm->pair.key, key, keySize);
    newItm->next = NULL;
    newItm->pair.value = 0;

    // calculate index of new key
    size_t index = htab_hash_function(key) % t->arr_size;
    // empty index
    if (t->arr[index] == NULL) {
        t->arr[index] = newItm;
    } else {
        struct htab_item *tmp;
        tmp = t->arr[index];
        while (tmp->next != NULL) {
            tmp = tmp->next;
        }
        tmp->next = newItm;
    }
    t->size++;

    return &newItm->pair;
}
