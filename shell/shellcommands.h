#ifndef TK_SHELLCOMMANDS_H
#define TK_SHELLCOMMANDS_H

#include "hal.h"
#include "shell.h"

#define SHELL_WA_SIZE   THD_WORKING_AREA_SIZE(2048)

#if 0
extern void cmd_status(BaseSequentialStream *chp, int argc, char *argv[]);
#endif
extern void cmd_diic(BaseSequentialStream *chp, int argc, char *argv[]);
extern void cmd_piic(BaseSequentialStream *chp, int argc, char *argv[]);
extern void cmd_probe(BaseSequentialStream *chp, int argc, char *argv[]);
extern void cmd_reboot(BaseSequentialStream *chp, int argc, char *argv[]);
extern void cmd_dmw(BaseSequentialStream *chp, int argc, char *argv[]);
extern void cmd_dmb(BaseSequentialStream *chp, int argc, char *argv[]);
extern void cmd_env(BaseSequentialStream *chp, int argc, char *argv[]);
extern void cmd_out(BaseSequentialStream *chp, int argc, char *argv[]);
extern void cmd_gps(BaseSequentialStream *chp, int argc, char *argv[]);
extern void cmd_date(BaseSequentialStream *chp, int argc, char *argv[]);
extern void cmd_ping(BaseSequentialStream *chp, int argc, char *argv[]);
extern void cmd_send(BaseSequentialStream *chp, int argc, char *argv[]);

extern const ShellCommand commands[];
extern const ShellConfig shell_cfg_uart;

#endif // TK_SHELLCOMMANDS_H
