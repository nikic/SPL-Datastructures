#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_spl_ds.h"
#include "classes/collection.h"
#include "classes/stack.h"
#include "classes/queue.h"
#include "classes/linked_list.h"

PHP_MINIT_FUNCTION(spl_datastructures)
{
    PHP_MINIT(spl_ds_collection)(INIT_FUNC_ARGS_PASSTHRU);
    PHP_MINIT(spl_ds_stack)(INIT_FUNC_ARGS_PASSTHRU);
    PHP_MINIT(spl_ds_queue)(INIT_FUNC_ARGS_PASSTHRU);
    PHP_MINIT(spl_ds_linked_list)(INIT_FUNC_ARGS_PASSTHRU);

    return SUCCESS;
}

zend_module_entry spl_datastructures_module_entry = {
    STANDARD_MODULE_HEADER,
    PHP_SPL_DS_EXTNAME,
    NULL,
    PHP_MINIT(spl_datastructures),
    NULL,
    NULL,
    NULL,
    NULL,
    PHP_SPL_DS_VERSION,
    STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_SPL_DATASTRUCTURES
ZEND_GET_MODULE(spl_datastructures)
#endif
