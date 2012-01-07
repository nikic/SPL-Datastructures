#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_spl_ds.h"
#include "spl_ds_collection.h"
#include "spl_ds_dll.h"

zend_class_entry *spl_ds_ce_Stack;
zend_object_handlers spl_ds_handlers_Stack;

zend_object_value spl_ds_stack_create_handler(zend_class_entry *class_type TSRMLS_DC)
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
    retval.handlers = &spl_ds_handlers_Stack;

    return retval;
}

SPL_DS_METHOD(Stack, peek)
{
    spl_ds_dll *list;
    zval *item;

    if (zend_parse_parameters_none() == FAILURE) {
        return;
    }

    list = SPL_DS_DLL_GET_LIST();

    if (spl_ds_dll_is_empty(list)) {
        //zend_throw_exception(x, "Can't peek an empty stack", 0 TSRMLS_CC);
        return;
    }

    item = spl_ds_dll_get_last(list);
    RETURN_ZVAL(item, 1, 1);
}

SPL_DS_METHOD(Stack, pop)
{
    spl_ds_dll *list;
    zval *item;

    if (zend_parse_parameters_none() == FAILURE) {
        return;
    }

    list = SPL_DS_DLL_GET_LIST();

    if (spl_ds_dll_is_empty(list)) {
        //zend_throw_exception(x, "Can't pop an empty stack", 0 TSRMLS_CC);
        return;
    }

    item = spl_ds_dll_remove_last(list);
    RETURN_ZVAL(item, 1, 1);
}

SPL_DS_METHOD(Stack, push)
{
    zval *item;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &item) == FAILURE) {
        return;
    }

    spl_ds_dll_add_last(SPL_DS_DLL_GET_LIST(), item);
}

ZEND_BEGIN_ARG_INFO(spl_ds_arg_info_Stack_void, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(spl_ds_arg_info_Stack_push, 0, 0, 1)
    ZEND_ARG_INFO(0, item)
ZEND_END_ARG_INFO()

const zend_function_entry spl_ds_methods_Stack[] = {
    SPL_DS_ME(Stack, peek,    spl_ds_arg_info_Stack_void)
    SPL_DS_ME(Stack, pop,     spl_ds_arg_info_Stack_void)
    SPL_DS_ME(Stack, push,    spl_ds_arg_info_Stack_push)
    SPL_DS_ME(DLL,   clear,   spl_ds_arg_info_Stack_void)
    SPL_DS_ME(DLL,   isEmpty, spl_ds_arg_info_Stack_void)
    SPL_DS_ME(DLL,   toArray, spl_ds_arg_info_Stack_void)
    SPL_DS_ME(DLL,   count,   spl_ds_arg_info_Stack_void)
    PHP_FE_END
};

PHP_MINIT_FUNCTION(spl_ds_stack)
{
    SPL_DS_REGISTER_CLASS(Stack, spl_ds_stack_create_handler);
    zend_class_implements(spl_ds_ce_Stack TSRMLS_CC, 1, spl_ds_ce_Collection);

    memcpy(
        &spl_ds_handlers_Stack,
        zend_get_std_object_handlers(),
        sizeof(zend_object_handlers)
    );
    spl_ds_handlers_Stack.clone_obj = zend_objects_store_clone_obj;

    return SUCCESS;
}
