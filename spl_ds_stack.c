#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_spl_ds.h"

zend_class_entry *spl_ds_ce_Stack;
zend_object_handlers spl_ds_handlers_Stack;

typedef struct _spl_ds_stack_element {
    zval                         *data;
    struct _spl_ds_stack_element *next;
} spl_ds_stack_element;

typedef struct _spl_ds_stack_object {
    zend_object           std;
    spl_ds_stack_element *head;
} spl_ds_stack_object;

static void spl_ds_stack_free_storage(void *object TSRMLS_DC)
{
    spl_ds_stack_object *obj = (spl_ds_stack_object *) object;

    zend_object_std_dtor(&obj->std TSRMLS_CC);

    while (obj->head != NULL) {
        spl_ds_stack_element *current = obj->head;
        obj->head = current->next;

        zend_ptr_dtor(current->data);

        efree(current);
    }

    efree(obj);
}

static zend_object_value spl_ds_stack_create_handler(zend_class_entry *class_type TSRMLS_DC)
{
    zend_object_value retval;
    spl_ds_stack_object *obj;

    obj = emalloc(sizeof(spl_ds_stack_object));
    memset(obj, 0, sizeof(spl_ds_stack_object));

    zend_object_std_init(&obj->std, class_type TSRMLS_CC);
    object_properties_init(&obj->std, class_type);

    retval.handle = zend_objects_store_put(obj, NULL, spl_ds_stack_free_storage, NULL TSRMLS_CC);
    retval.handlers = &spl_ds_handlers_Stack;

    return retval;
}

SPL_DS_METHOD(Stack, peek)
{
    spl_ds_stack_object *obj;

    obj = (spl_ds_stack_object *) zend_object_store_get_object(getThis() TSRMLS_CC);

    if (obj->head == NULL) {
        //zend_throw_exception(x, "Can't peek an empty stack", 0 TSRMLS_CC);
        return;
    }

    RETURN_ZVAL(obj->head->data, 1, 0);
}

SPL_DS_METHOD(Stack, pop)
{
    spl_ds_stack_object *obj;
    spl_ds_stack_element *head;

    obj = (spl_ds_stack_object *) zend_object_store_get_object(getThis() TSRMLS_CC);

    if (obj->head == NULL) {
        //zend_throw_exception(x, "Can't pop an empty stack", 0 TSRMLS_CC);
        return;
    }

    head = obj->head;

    RETVAL_ZVAL(head->data, 1, 1);

    obj->head = head->next;
    efree(head);
}

SPL_DS_METHOD(Stack, push)
{
    zval *item;
    spl_ds_stack_object *obj;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &item) == FAILURE) {
        return;
    }

    obj = (spl_ds_stack_object *) zend_object_store_get_object(getThis() TSRMLS_CC);

    spl_ds_stack_element *element = emalloc(sizeof(spl_ds_stack_element));

    Z_ADDREF_P(item);
    element->data = item;

    element->next = obj->head;
    obj->head = element;
}

ZEND_BEGIN_ARG_INFO(spl_ds_arg_info_Stack_void, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(spl_ds_arg_info_Stack_push, 0, 0, 1)
     ZEND_ARG_INFO(0, item)
ZEND_END_ARG_INFO()

const zend_function_entry spl_ds_methods_Stack[] = {
    SPL_DS_ME(Stack, peek, spl_ds_arg_info_Stack_void, ZEND_ACC_PUBLIC)
    SPL_DS_ME(Stack, pop,  spl_ds_arg_info_Stack_void, ZEND_ACC_PUBLIC)
    SPL_DS_ME(Stack, push, spl_ds_arg_info_Stack_push, ZEND_ACC_PUBLIC)
    PHP_FE_END
};

PHP_MINIT_FUNCTION(spl_ds_stack)
{
    SPL_DS_REGISTER_CLASS(Stack, spl_ds_stack_create_handler);
    memcpy(
        &spl_ds_handlers_Stack,
        zend_get_std_object_handlers(),
        sizeof(zend_object_handlers)
    );

    return SUCCESS;
}
