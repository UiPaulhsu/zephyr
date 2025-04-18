
#include "devreg.h"

extern int devreg_flash_internal_register(void);
extern int devreg_flash_external_register(void);

enum devreg_backend_type {
    DEVREG_BACKEND_INTERNAL,
    DEVREG_BACKEND_EXTERNAL
};

int devreg_backend_select(enum devreg_backend_type type) {
    switch (type) {
    case DEVREG_BACKEND_INTERNAL:
        return devreg_flash_internal_register();
    case DEVREG_BACKEND_EXTERNAL:
        return devreg_flash_external_register();
    default:
        return -EINVAL;
    }
}
