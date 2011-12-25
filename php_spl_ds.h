#ifndef PHP_SPL_DS_H
#define PHP_SPL_DS_H 1

#define PHP_SPL_DS_VERSION "1.0"
#define PHP_SPL_DS_EXTNAME "spl_datastructures"

extern zend_module_entry spl_datastructures_module_entry;
#define phpext_spl_ds_ptr &spl_datastructures_module_entry

#define SPL_DS_NAMESPACE_PREFIX "SPL\\Datastructures\\"

#define SPL_DS_REGISTER_CLASS(name, create_handler) \
    SPL_DS_REGISTER_CLASS_EX(                       \
         spl_ds_ce_ ## name,                        \
         SPL_DS_NAMESPACE_PREFIX # name,            \
         create_handler,                            \
         spl_ds_methods_ ## name                    \
    )

#define SPL_DS_REGISTER_CLASS_EX(dst_ce, name, create_handler, methods) do { \
    zend_class_entry ce;                                                     \
    INIT_CLASS_ENTRY(ce, name, methods);                                     \
    dst_ce = zend_register_internal_class(&ce TSRMLS_CC);                    \
    dst_ce->create_object = create_handler;                                  \
} while(0)

#define SPL_DS_REGISTER_INTERFACE(name) \
    SPL_DS_REGISTER_INTERFACE_EX(       \
        spl_ds_ce_ ## name,             \
        SPL_DS_NAMESPACE_PREFIX # name, \
        spl_ds_methods_ ## name         \
    )

#define SPL_DS_REGISTER_INTERFACE_EX(dst_ce, name, methods) do { \
    zend_class_entry ce;                                         \
    INIT_CLASS_ENTRY(ce, name, methods);                         \
    dst_ce = zend_register_internal_interface(&ce TSRMLS_CC);    \
} while(0)

#define SPL_DS_ME(class, method, arg_info, flags) \
    PHP_ME(spl_ds_ ## class, method, arg_info, flags)

#define SPL_DS_ABSTRACT_ME(class, method, arg_info) \
    PHP_ABSTRACT_ME(spl_ds_ ## class, method, arg_info)

#define SPL_DS_METHOD(class, method) \
    PHP_METHOD(spl_ds_ ## class, method)

#endif
