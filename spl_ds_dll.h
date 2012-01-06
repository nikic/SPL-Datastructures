#ifndef SPL_DS_DLL_H
#define SPL_DS_DLL_H 1

/* DLL structures */
typedef struct _spl_ds_dll_element {
    zval                       *zval;
    struct _spl_ds_dll_element *next;
    struct _spl_ds_dll_element *prev;
} spl_ds_dll_element;

typedef struct _spl_ds_dll {
    spl_ds_dll_element *first;
    spl_ds_dll_element *last;
    long                count;
} spl_ds_dll;

/* Internal DLL API */
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

/* PHP object wrapper around DLL */
typedef struct _spl_ds_dll_object {
    zend_object  std;
    spl_ds_dll  *list;
} spl_ds_dll_object;

#define SPL_DS_DLL_GET_LIST() \
    ((spl_ds_dll_object *) zend_object_store_get_object(getThis() TSRMLS_CC))->list

/* PHP object handlers */
void spl_ds_dll_object_free_storage(spl_ds_dll_object *obj TSRMLS_DC);
void spl_ds_dll_object_clone_storage(spl_ds_dll_object *obj_orig, spl_ds_dll_object **obj_clone_ptr);

#endif
