
#include <zephyr/shell/shell.h>
#include "devreg.h"

static int cmd_devreg_read(const struct shell *shell, size_t argc, char **argv) {
    if (argc < 3) return -EINVAL;
    off_t offset = strtoul(argv[1], NULL, 0);
    size_t len = strtoul(argv[2], NULL, 0);
    uint8_t buf[256];
    if (len > sizeof(buf)) len = sizeof(buf);
    if (devreg_read(offset, buf, len) < 0) return -EIO;
    for (size_t i = 0; i < len; i++) {
        shell_fprintf(shell, SHELL_NORMAL, "%02x ", buf[i]);
        if ((i + 1) % 16 == 0) shell_print(shell, "");
    }
    shell_print(shell, "");
    return 0;
}

static int cmd_devreg_write(const struct shell *shell, size_t argc, char **argv) {
    if (argc < 4) return -EINVAL;
    off_t offset = strtoul(argv[1], NULL, 0);
    uint8_t buf[256];
    size_t len = argc - 2;
    if (len > sizeof(buf)) return -EINVAL;
    for (size_t i = 0; i < len; i++) {
        buf[i] = strtoul(argv[i + 2], NULL, 16);
    }
    return devreg_write(offset, buf, len);
}

static int cmd_devreg_erase(const struct shell *shell, size_t argc, char **argv) {
    if (argc < 3) return -EINVAL;
    off_t offset = strtoul(argv[1], NULL, 0);
    size_t size = strtoul(argv[2], NULL, 0);
    return devreg_erase(offset, size);
}

SHELL_STATIC_SUBCMD_SET_CREATE(devreg_cmds,
    SHELL_CMD(read, NULL, "Read: devreg read <offset> <len>", cmd_devreg_read),
    SHELL_CMD(write, NULL, "Write: devreg write <offset> <byte0> [byte1 ...]", cmd_devreg_write),
    SHELL_CMD(erase, NULL, "Erase: devreg erase <offset> <size>", cmd_devreg_erase),
    SHELL_SUBCMD_SET_END
);

SHELL_CMD_REGISTER(devreg, &devreg_cmds, "Devreg shell commands", NULL);
