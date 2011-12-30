#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_spl_ds.h"
#include "spl_ds_collection.h"
#include "spl_ds_stack.h"
#include "spl_ds_queue.h"

PHP_MINIT_FUNCTION(spl_datastructures)
{
    PHP_MINIT(spl_ds_collection)(INIT_FUNC_ARGS_PASSTHRU);
    PHP_MINIT(spl_ds_stack)(INIT_FUNC_ARGS_PASSTHRU);
    PHP_MINIT(spl_ds_queue)(INIT_FUNC_ARGS_PASSTHRU);

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
