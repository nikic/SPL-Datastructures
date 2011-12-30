#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_spl_ds.h"
#include "spl_ds_collection.h"
#include "spl_ds_dll.h"

zend_class_entry *spl_ds_ce_Queue;
zend_object_handlers spl_ds_handlers_Queue;

typedef struct _spl_ds_queue_object {
    zend_object  std;
    spl_ds_dll  *list;
} spl_ds_queue_object;

#define SPL_DS_QUEUE_GET_LIST() \
    ((spl_ds_queue_object *) zend_object_store_get_object(getThis() TSRMLS_CC))->list

static void spl_ds_queue_free_storage(void *object TSRMLS_DC)
{
    spl_ds_queue_object *obj = (spl_ds_queue_object *) object;

    spl_ds_dll_free(obj->list);

    zend_object_std_dtor(&obj->std TSRMLS_CC);

    efree(obj);
}

static void spl_ds_queue_clone_storage(void *object, void **target_ptr)
{
    spl_ds_queue_object *obj_orig, *obj_clone;

    obj_orig = (spl_ds_queue_object *) object;
    obj_clone = (spl_ds_queue_object *) emalloc(sizeof(spl_ds_queue_object));

    memcpy(obj_clone, obj_orig, sizeof(spl_ds_queue_object));

    obj_clone->list = spl_ds_dll_clone(obj_orig->list);

    *target_ptr = obj_clone;
}

static zend_object_value spl_ds_queue_create_handler(zend_class_entry *class_type TSRMLS_DC)
{
    zend_object_value retval;
    spl_ds_queue_object *obj;

    obj = emalloc(sizeof(spl_ds_queue_object));

    zend_object_std_init(&obj->std, class_type TSRMLS_CC);
    object_properties_init(&obj->std, class_type);

    obj->list = spl_ds_dll_create();

    retval.handle = zend_objects_store_put(obj, NULL, spl_ds_queue_free_storage, spl_ds_queue_clone_storage TSRMLS_CC);
    retval.handlers = &spl_ds_handlers_Queue;

    return retval;
}

const zend_function_entry spl_ds_methods_Queue[] = {
    PHP_FE_END
};

PHP_MINIT_FUNCTION(spl_ds_queue)
{
    SPL_DS_REGISTER_CLASS(Queue, spl_ds_queue_create_handler);

    memcpy(
        &spl_ds_handlers_Queue,
        zend_get_std_object_handlers(),
        sizeof(zend_object_handlers)
    );
    spl_ds_handlers_Queue.clone_obj = zend_objects_store_clone_obj;

    return SUCCESS;
}
