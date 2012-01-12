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

    spl_ds_dll_element *current;
    long                current_index;

    long                count;
} spl_ds_dll;

/* Internal DLL API */
spl_ds_dll *spl_ds_dll_create();
void spl_ds_dll_clear(spl_ds_dll *list);
spl_ds_dll *spl_ds_dll_clone(spl_ds_dll *orig);
zval *spl_ds_dll_to_array(spl_ds_dll *list);
zend_bool spl_ds_dll_is_empty(spl_ds_dll *list);
long spl_ds_dll_count(spl_ds_dll *list);

void spl_ds_dll_add_first(spl_ds_dll *list, zval *item);
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

/* Helper macros */
#define SPL_DS_DLL_GET_LIST() \
    ((spl_ds_dll_object *) zend_object_store_get_object(getThis() TSRMLS_CC))->list

#define SPL_DS_DLL_ENSURE_NOT_EMPTY(list, msg)                               \
    if (spl_ds_dll_is_empty((list))) {                                       \
        zend_throw_exception(spl_ce_UnderflowException, (msg), 0 TSRMLS_CC); \
        return;                                                              \
    }

/* PHP object handlers */
void spl_ds_dll_object_free_storage(spl_ds_dll_object *obj TSRMLS_DC);
void spl_ds_dll_object_clone_storage(spl_ds_dll_object *obj_orig, spl_ds_dll_object **obj_clone_ptr);

/* Shared DLL methods */
SPL_DS_METHOD(DLL, clear);
SPL_DS_METHOD(DLL, isEmpty);
SPL_DS_METHOD(DLL, toArray);
SPL_DS_METHOD(DLL, count);
SPL_DS_METHOD(DLL, rewind);
SPL_DS_METHOD(DLL, current);
SPL_DS_METHOD(DLL, key);
SPL_DS_METHOD(DLL, next);
SPL_DS_METHOD(DLL, valid);

#define SPL_DS_DLL_SHARED_METHODS     \
    SPL_DS_ME(DLL, clear,   void) \
    SPL_DS_ME(DLL, isEmpty, void) \
    SPL_DS_ME(DLL, toArray, void) \
    SPL_DS_ME(DLL, count,   void) \
    SPL_DS_ME(DLL, rewind,  void) \
    SPL_DS_ME(DLL, current, void) \
    SPL_DS_ME(DLL, key,     void) \
    SPL_DS_ME(DLL, next,    void) \
    SPL_DS_ME(DLL, valid,   void)

#endif
