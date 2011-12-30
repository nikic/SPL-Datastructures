#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_spl_ds.h"
#include "spl/spl_iterators.h"

zend_class_entry *spl_ds_ce_Collection;

ZEND_BEGIN_ARG_INFO(spl_ds_arg_info_Collection_void, 0)
ZEND_END_ARG_INFO()

const zend_function_entry spl_ds_methods_Collection[] = {
    SPL_DS_ABSTRACT_ME(Collection, clear,   spl_ds_arg_info_Collection_void)
    SPL_DS_ABSTRACT_ME(Collection, isEmpty, spl_ds_arg_info_Collection_void)
    SPL_DS_ABSTRACT_ME(Collection, toArray, spl_ds_arg_info_Collection_void)
    PHP_FE_END
};

PHP_MINIT_FUNCTION(spl_ds_collection)
{
    SPL_DS_REGISTER_INTERFACE(Collection); 
    zend_class_implements(spl_ds_ce_Collection TSRMLS_CC, 1, spl_ce_Countable);
}
