

target_sources(app PRIVATE
    src/devreg.c
    src/devreg_backend.c
    src/devreg_flash_internal.c
    src/devreg_flash_external.c
    src/devreg_shell.c
  )

#Globally visible
zephyr_include_directories(include)
zephyr_include_directories(security)