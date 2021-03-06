/*
 * Řešení IJC-DU2
 * Autor: Tomáš Matuš, FIT VUT Brno
 * Login: xmatus37
 * Datum: 19.4.2021
 * Přeloženo: gcc 10.2.0
 */

#include <stdlib.h>
#include "htab.h"
#include "htab_struct.h"

bool htab_erase(htab_t * t, htab_key_t key) {
    size_t index = htab_hash_function(key) % t->arr_size;

    struct htab_item *itm = t->arr[index];
    if (itm == NULL) {
        return false;
    }
    // compare keys with first item on index
    if (strcmp(itm->pair.key, key) == 0) {
        // keys match
        t->arr[index] = itm->next;
        itm->next = NULL;
        free((char*)itm->pair.key);
        free(itm);
        t->size--;
        return true;
    } else {
        // run through linked list and search for key
        struct htab_item *prev = itm;
        for (; itm->next != NULL; itm = itm->next) {
            // compare keys
            if (strcmp(itm->pair.key, key) == 0) {
                // key in list matches
                prev->next = itm->next;
                itm->next = NULL;
                free((char*)itm->pair.key);
                free(itm);
                t->size--;
                return true;
            }
            prev = itm;
        }
    }

    // key not found
    return false;
}
