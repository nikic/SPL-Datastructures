#ifndef SPL_DS_DLL_H
#define SPL_DS_DLL_H 1

typedef struct _spl_ds_dll_element {
    zval                       *data;
    struct _spl_ds_dll_element *next;
    struct _spl_ds_dll_element *prev;
} spl_ds_dll_element;

typedef struct _spl_ds_dll {
    spl_ds_dll_element *first;
    spl_ds_dll_element *last;
    long                count;
} spl_ds_dll;

spl_ds_dll *spl_ds_dll_create();
void spl_ds_dll_clear(spl_ds_dll *list);
spl_ds_dll *spl_ds_dll_clone(spl_ds_dll *orig);
zval *spl_ds_dll_to_array(spl_ds_dll *list);
zend_bool spl_ds_dll_is_empty(spl_ds_dll *list);
long spl_ds_dll_count(spl_ds_dll *list);

void spl_ds_dll_add_last (spl_ds_dll *list, zval *item);

zval *spl_ds_dll_get_first(spl_ds_dll *list);
zval *spl_ds_dll_get_last (spl_ds_dll *list);

zval *spl_ds_dll_remove_first(spl_ds_dll *list);
zval *spl_ds_dll_remove_last (spl_ds_dll *list);

#endif
