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

    return list;
}

void spl_ds_dll_clear(spl_ds_dll *list)
{
    while (list->first != NULL) {
        spl_ds_dll_element *current = list->first;
        list->first = current->next;

        zval_ptr_dtor(&current->data);

        efree(current);
    }
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
            spl_ds_dll_add_last(clone, current->data);
            
            current = current->next;
        } while (current != NULL);
    }

    return clone;
}

zend_bool spl_ds_dll_is_empty(spl_ds_dll *list)
{
    return list->last == NULL;
}

void spl_ds_dll_add_last(spl_ds_dll *list, zval *item)
{
    spl_ds_dll_element *element = emalloc(sizeof(spl_ds_dll_element));

    Z_ADDREF_P(item);
    element->data = item;

    element->next = NULL;
    element->prev = list->last;

    if (element->prev != NULL) {
        element->prev->next = element;
    }

    list->last = element;

    if (list->first == NULL) {
        list->first = element;
    }
}

zval *spl_ds_dll_get_last(spl_ds_dll *list)
{
    if (list->last == NULL) {
        return NULL;
    }

    Z_ADDREF_P(list->last->data);

    return list->last->data;
}

zval *spl_ds_dll_remove_last(spl_ds_dll *list)
{
    zval *retval;
    spl_ds_dll_element *last = list->last;

    if (last == NULL) {
        return NULL;
    }

    retval = last->data;

    list->last = last->prev;

    if (last->prev != NULL) {
        last->prev->next = NULL;
    }

    if (list->first == last) {
        list->first = NULL;
    }

    efree(last);

    return retval;
}
