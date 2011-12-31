#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "spl_ds_dll.h"

spl_ds_dll *spl_ds_dll_create()
{
    spl_ds_dll *list = emalloc(sizeof(spl_ds_dll));

    list->first = NULL;
    list->last  = NULL;
    list->count = 0;

    return list;
}

void spl_ds_dll_clear(spl_ds_dll *list)
{
    while (list->first != NULL) {
        spl_ds_dll_element *current = list->first;
        list->first = current->next;

        zval_ptr_dtor(&current->zval);

        efree(current);
    }

    list->count = 0;
}

void spl_ds_dll_free(spl_ds_dll *list) {
    spl_ds_dll_clear(list);
    efree(list);
}

spl_ds_dll *spl_ds_dll_clone(spl_ds_dll *orig)
{
    spl_ds_dll *clone = spl_ds_dll_create();

    if (orig->first != NULL) {
        spl_ds_dll_element *current = orig->first;

        do {
            spl_ds_dll_add_last(clone, current->zval);
            
            current = current->next;
        } while (current != NULL);
    }

    return clone;
}

zval *spl_ds_dll_to_array(spl_ds_dll *list)
{
    zval *retval;

    ALLOC_INIT_ZVAL(retval);
    array_init_size(retval, list->count);

    if (list->first != NULL) {
        spl_ds_dll_element *current = list->first;

        do {
            add_next_index_zval(retval, current->zval);

            current = current->next;
        } while (current != NULL);
    }

    return retval;
}

zend_bool spl_ds_dll_is_empty(spl_ds_dll *list)
{
    return list->count == 0;
}

long spl_ds_dll_count(spl_ds_dll *list)
{
    return list->count;
}

void spl_ds_dll_add_last(spl_ds_dll *list, zval *item)
{
    spl_ds_dll_element *element = emalloc(sizeof(spl_ds_dll_element));

    Z_ADDREF_P(item);
    element->zval = item;

    element->next = NULL;
    element->prev = list->last;

    if (element->prev != NULL) {
        element->prev->next = element;
    }

    list->last = element;

    if (list->first == NULL) {
        list->first = element;
    }

    list->count++;
}

zval *spl_ds_dll_get_zval(spl_ds_dll_element *element)
{
    if (element == NULL) {
        return NULL;
    }

    Z_ADDREF_P(element->zval);
    return element->zval;
}

zval *spl_ds_dll_get_first(spl_ds_dll *list)
{
    return spl_ds_dll_get_zval(list->first);
}

zval *spl_ds_dll_get_last(spl_ds_dll *list)
{
    return spl_ds_dll_get_zval(list->last);
}

zval *spl_ds_dll_remove_element(spl_ds_dll *list, spl_ds_dll_element *element)
{
    zval *retval;

    // ensure that there actually is something to remove
    if (element == NULL) {
        return NULL;
    }

    list->count--;

    // remove references to element from prev and next element
    if (element->prev != NULL) {
        element->prev->next = NULL;
    }
    if (element->next != NULL) {
        element->next->prev = NULL;
    }

    // if element is first/last move the first/last pointer to next/prev
    if (element == list->first) {
        list->first = element->next;
    }
    if (element == list->last) {
        list->last = element->prev;
    }

    retval = element->zval;

    efree(element);

    return retval;
}

zval *spl_ds_dll_remove_first(spl_ds_dll *list)
{
    return spl_ds_dll_remove_element(list, list->first);
}

zval *spl_ds_dll_remove_last(spl_ds_dll *list)
{
    return spl_ds_dll_remove_element(list, list->last);
}
