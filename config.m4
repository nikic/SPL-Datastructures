PHP_ARG_ENABLE(spl-datastructures,
whether to enable SPL Datastructures support,
[  --enable-spl-datastructures Enable SPL Datastructures support])

if test "$PHP_SPL_DATASTRUCTURES" = "yes"; then
  AC_DEFINE(HAVE_SPL_DATASTRUCTURES, 1, [Whether you have SPL Datastructures])
  PHP_NEW_EXTENSION(spl_datastructures, php_spl_ds.c spl_ds_dll.c classes/collection.c classes/stack.c classes/queue.c classes/linked_list.c, $ext_shared)
fi
