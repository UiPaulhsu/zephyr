
#ifndef DEVREG_H_
#define DEVREG_H_

#include <zephyr/types.h>
#include <sys/types.h>
#include <errno.h>

typedef int (*devreg_read_cb)(off_t offset, void *buf, size_t len);
typedef int (*devreg_write_cb)(off_t offset, const void *buf, size_t len);
typedef int (*devreg_erase_cb)(off_t offset, size_t size);

struct devreg_api {
    devreg_read_cb  read;
    devreg_write_cb write;
    devreg_erase_cb erase;
};

int devreg_init(const struct devreg_api *api);
int devreg_read(off_t offset, void *buf, size_t len);
int devreg_write(off_t offset, const void *buf, size_t len);
int devreg_erase(off_t offset, size_t size);

#endif /* DEVREG_H_ */
