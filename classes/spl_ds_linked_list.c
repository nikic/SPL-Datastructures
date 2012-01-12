#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_spl_ds.h"
#include "spl_ds_collection.h"
#include "spl_ds_dll.h"
#include "spl/spl_exceptions.h"
#include "zend_interfaces.h"

zend_class_entry *spl_ds_ce_LinkedList;
zend_object_handlers spl_ds_handlers_LinkedList;

zend_object_value spl_ds_linked_list_create_handler(zend_class_entry *class_type TSRMLS_DC)
{
    zend_object_value retval;
    spl_ds_dll_object *obj;

    obj = emalloc(sizeof(spl_ds_dll_object));

    zend_object_std_init(&obj->std, class_type TSRMLS_CC);
    object_properties_init(&obj->std, class_type);

    obj->list = spl_ds_dll_create();

    retval.handle = zend_objects_store_put(obj, NULL,
        (zend_objects_free_object_storage_t) spl_ds_dll_object_free_storage,
        (zend_objects_store_clone_t)         spl_ds_dll_object_clone_storage
        TSRMLS_CC
    );
    retval.handlers = &spl_ds_handlers_LinkedList;

    return retval;
}

SPL_DS_METHOD(LinkedList, getFirst)
{
    spl_ds_dll *list;
    zval *item;

    if (zend_parse_parameters_none() == FAILURE) {
        return;
    }

    list = SPL_DS_DLL_GET_LIST();

    SPL_DS_DLL_ENSURE_NOT_EMPTY(list, "Can't get first element of an empty linked list");

    item = spl_ds_dll_get_first(list);
    RETURN_ZVAL(item, 1, 1);
}

SPL_DS_METHOD(LinkedList, getLast)
{
    spl_ds_dll *list;
    zval *item;

    if (zend_parse_parameters_none() == FAILURE) {
        return;
    }

    list = SPL_DS_DLL_GET_LIST();

    SPL_DS_DLL_ENSURE_NOT_EMPTY(list, "Can't get last element of an empty linked list");

    item = spl_ds_dll_get_last(list);
    RETURN_ZVAL(item, 1, 1);
}

SPL_DS_METHOD(LinkedList, pop)
{
    spl_ds_dll *list;
    zval *item;

    if (zend_parse_parameters_none() == FAILURE) {
        return;
    }

    list = SPL_DS_DLL_GET_LIST();

    SPL_DS_DLL_ENSURE_NOT_EMPTY(list, "Can't pop an empty linked list");

    item = spl_ds_dll_remove_last(list);
    RETURN_ZVAL(item, 1, 1);
}

SPL_DS_METHOD(LinkedList, push)
{
    zval *item;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &item) == FAILURE) {
        return;
    }

    spl_ds_dll_add_last(SPL_DS_DLL_GET_LIST(), item);
}

SPL_DS_METHOD(LinkedList, shift)
{
    spl_ds_dll *list;
    zval *item;

    if (zend_parse_parameters_none() == FAILURE) {
        return;
    }

    list = SPL_DS_DLL_GET_LIST();

    SPL_DS_DLL_ENSURE_NOT_EMPTY(list, "Can't shift an empty linked list");

    item = spl_ds_dll_remove_first(list);
    RETURN_ZVAL(item, 1, 1);
}

SPL_DS_METHOD(LinkedList, unshift)
{
    zval *item;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &item) == FAILURE) {
        return;
    }

    spl_ds_dll_add_first(SPL_DS_DLL_GET_LIST(), item);
}

ZEND_BEGIN_ARG_INFO(spl_ds_arg_info_void, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(spl_ds_arg_info_takesItem, 0, 0, 1)
    ZEND_ARG_INFO(0, item)
ZEND_END_ARG_INFO()

const zend_function_entry spl_ds_methods_LinkedList[] = {
    SPL_DS_ME(LinkedList, getFirst, void)
    SPL_DS_ME(LinkedList, getLast,  void)
    SPL_DS_ME(LinkedList, pop,      void)
    SPL_DS_ME(LinkedList, push,     takesItem)
    SPL_DS_ME(LinkedList, shift,    void)
    SPL_DS_ME(LinkedList, unshift,  takesItem)
    SPL_DS_ME(DLL,        clear,    void)
    SPL_DS_ME(DLL,        isEmpty,  void)
    SPL_DS_ME(DLL,        toArray,  void)
    SPL_DS_ME(DLL,        count,    void)
    SPL_DS_ME(DLL,        rewind,   void)
    SPL_DS_ME(DLL,        current,  void)
    SPL_DS_ME(DLL,        key,      void)
    SPL_DS_ME(DLL,        next,     void)
    SPL_DS_ME(DLL,        valid,    void)
    PHP_FE_END
};

PHP_MINIT_FUNCTION(spl_ds_linked_list)
{
    SPL_DS_REGISTER_CLASS(LinkedList, spl_ds_linked_list_create_handler);
    zend_class_implements(spl_ds_ce_LinkedList TSRMLS_CC, 2,
        zend_ce_iterator,
        spl_ds_ce_Collection
    );

    memcpy(
        &spl_ds_handlers_LinkedList,
        zend_get_std_object_handlers(),
        sizeof(zend_object_handlers)
    );
    spl_ds_handlers_LinkedList.clone_obj = zend_objects_store_clone_obj;

    return SUCCESS;
}
