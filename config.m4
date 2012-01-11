PHP_ARG_ENABLE(spl-datastructures,
whether to enable SPL Datastructures support,
[  --enable-spl-datastructures Enable SPL Datastructures support])

if test "$PHP_SPL_DATASTRUCTURES" = "yes"; then
  AC_DEFINE(HAVE_SPL_DATASTRUCTURES, 1, [Whether you have SPL Datastructures])
  PHP_NEW_EXTENSION(spl_datastructures, php_spl_ds.c spl_ds_dll.c classes/spl_ds_collection.c classes/spl_ds_stack.c classes/spl_ds_queue.c classes/spl_ds_linked_list.c, $ext_shared)
fi
