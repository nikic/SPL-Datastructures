#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_spl_ds.h"

zend_class_entry *spl_ds_ce_Stack;

SPL_DS_METHOD(Stack, peek)
{

}

SPL_DS_METHOD(Stack, pop)
{

}

SPL_DS_METHOD(Stack, push)
{

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
    SPL_DS_REGISTER_CLASS(Stack);

    return SUCCESS;
}
