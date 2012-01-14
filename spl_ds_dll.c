#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_spl_ds.h"
#include "spl_ds_dll.h"

/**
 * Internal DLL API
 */

spl_ds_dll *spl_ds_dll_create()
{
    spl_ds_dll *list = emalloc(sizeof(spl_ds_dll));

    list->first = NULL;
    list->last  = NULL;

    list->current       = NULL;
    list->current_index = 0;

    list->count = 0;

    return list;
}

spl_ds_dll *spl_ds_dll_clone(spl_ds_dll *orig)
{
    spl_ds_dll *clone = spl_ds_dll_create();

    if (orig->first != NULL) {
        spl_ds_dll_element *current = orig->first;

        do {
            spl_ds_dll_insert_last(clone, current->zval);
            
            current = current->next;
        } while (current != NULL);
    }

    return clone;
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

zval *spl_ds_dll_to_array(spl_ds_dll *list)
{
    zval *retval;

    ALLOC_INIT_ZVAL(retval);
    array_init_size(retval, list->count);

    if (list->first != NULL) {
        spl_ds_dll_element *current = list->first;

        do {
            Z_ADDREF_P(current->zval);
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

void spl_ds_dll_insert_between(spl_ds_dll *list, zval *item, spl_ds_dll_element *prev, spl_ds_dll_element *next)
{
    spl_ds_dll_element *element = emalloc(sizeof(spl_ds_dll_element));

    Z_ADDREF_P(item);
    element->zval = item;

    element->prev = prev;
    element->next = next;

    // if prev/next exist update their next/prev pointer
    // if they don't exist it means that the inserted element is first/last
    if (prev != NULL) {
        prev->next = element;
    } else {
        list->first = element;
    }
    if (next != NULL) {
        next->prev = element;
    } else {
        list->last = element;
    }

    // keep list count in sync
    list->count++;
}

void spl_ds_dll_insert_first(spl_ds_dll *list, zval *item)
{
    spl_ds_dll_insert_between(list, item, NULL, list->first);
}

void spl_ds_dll_insert_last(spl_ds_dll *list, zval *item)
{
    spl_ds_dll_insert_between(list, item, list->last, NULL);
}

void spl_ds_dll_insert_before_current(spl_ds_dll *list, zval *item)
{
    if (list->current == NULL) {
        return;
    }

    spl_ds_dll_insert_between(list, item, list->current->prev, list->current);
}

void spl_ds_dll_insert_after_current(spl_ds_dll *list, zval *item)
{
    if (list->current == NULL) {
        return;
    }

    spl_ds_dll_insert_between(list, item, list->current, list->current->next);
}

zval *spl_ds_dll_replace_current(spl_ds_dll *list, zval *item)
{
    zval *retval;

    if (list->current == NULL) {
        return;
    }

    retval = list->current->zval;

    Z_ADDREF_P(item);
    list->current->zval = item;

    return retval;
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

zval *spl_ds_dll_get_current(spl_ds_dll *list)
{
    return spl_ds_dll_get_zval(list->current);
}

zval *spl_ds_dll_remove_element(spl_ds_dll *list, spl_ds_dll_element *element)
{
    zval *retval;

    // ensure that there actually is something to remove
    if (element == NULL) {
        return NULL;
    }

    // keep list count in sync
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

    // if element is current element advance to next element (but keep index)
    if (element == list->current) {
        list->current = element->next;
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

zval *spl_ds_dll_remove_current(spl_ds_dll *list)
{
    return spl_ds_dll_remove_element(list, list->current);
}

void spl_ds_dll_iterator_rewind(spl_ds_dll *list)
{
    list->current       = list->first;
    list->current_index = 0;
}

long spl_ds_dll_iterator_get_current_index(spl_ds_dll *list)
{
    return list->current_index;
}

zend_bool spl_ds_dll_iterator_is_valid(spl_ds_dll *list)
{
    return list->current != NULL;
}

void spl_ds_dll_iterator_move_forward(spl_ds_dll *list)
{
    if (list->current == NULL) {
        return;
    }

    list->current = list->current->next;
    list->current_index++;
}

/**
 * PHP object handlers
 */

void spl_ds_dll_object_free_storage(spl_ds_dll_object *obj TSRMLS_DC)
{
    spl_ds_dll_free(obj->list);

    zend_object_std_dtor(&obj->std TSRMLS_CC);

    efree(obj);
}

void spl_ds_dll_object_clone_storage(spl_ds_dll_object *obj_orig, spl_ds_dll_object **obj_clone_ptr)
{
    *obj_clone_ptr = (spl_ds_dll_object *) emalloc(sizeof(spl_ds_dll_object));
    memcpy(*obj_clone_ptr, obj_orig, sizeof(spl_ds_dll_object));

    (*obj_clone_ptr)->list = spl_ds_dll_clone(obj_orig->list);
}

/**
 * Shared DLL methods
 */

SPL_DS_METHOD(DLL, clear)
{
    if (zend_parse_parameters_none() == FAILURE) {
        return;
    }

    spl_ds_dll_clear(SPL_DS_DLL_GET_LIST());
}

SPL_DS_METHOD(DLL, isEmpty)
{
    if (zend_parse_parameters_none() == FAILURE) {
        return;
    }    

    RETURN_BOOL(spl_ds_dll_is_empty(SPL_DS_DLL_GET_LIST()));
}

SPL_DS_METHOD(DLL, toArray)
{
    zval *retval = spl_ds_dll_to_array(SPL_DS_DLL_GET_LIST());

    if (zend_parse_parameters_none() == FAILURE) {
        return;
    }
    
    RETURN_ZVAL(retval, 1, 1);
}

SPL_DS_METHOD(DLL, count)
{
    if (zend_parse_parameters_none() == FAILURE) {
        return;
    }

    RETURN_LONG(spl_ds_dll_count(SPL_DS_DLL_GET_LIST()));
}

SPL_DS_METHOD(DLL, rewind)
{
    if (zend_parse_parameters_none() == FAILURE) {
        return;
    }

    spl_ds_dll_iterator_rewind(SPL_DS_DLL_GET_LIST());
}

SPL_DS_METHOD(DLL, current)
{
    spl_ds_dll *list;
    zval *item;

    if (zend_parse_parameters_none() == FAILURE) {
        return;
    } 

    list = SPL_DS_DLL_GET_LIST();

    if (!spl_ds_dll_iterator_is_valid(list)) {
        return;
    }

    item = spl_ds_dll_get_current(list);
    RETURN_ZVAL(item, 1, 1);
}

SPL_DS_METHOD(DLL, key)
{
    spl_ds_dll *list;

    if (zend_parse_parameters_none() == FAILURE) {
        return;
    }

    list = SPL_DS_DLL_GET_LIST();

    if (!spl_ds_dll_iterator_is_valid(list)) {
        return;
    }

    RETURN_LONG(spl_ds_dll_iterator_get_current_index(list));
}

SPL_DS_METHOD(DLL, next)
{
    if (zend_parse_parameters_none() == FAILURE) {
        return;
    }

    spl_ds_dll_iterator_move_forward(SPL_DS_DLL_GET_LIST());
}

SPL_DS_METHOD(DLL, valid)
{
    spl_ds_dll *list;

    if (zend_parse_parameters_none() == FAILURE) {
        return;
    }

    list = SPL_DS_DLL_GET_LIST();

    RETURN_BOOL(spl_ds_dll_iterator_is_valid(list));
}
