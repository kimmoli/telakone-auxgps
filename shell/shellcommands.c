#include "hal.h"
#include "shell.h"
#include "shellcommands.h"

char uartShellHistoryBuffer[SHELL_MAX_HIST_BUFF];

const ShellCommand commands[] =
{
    { "status",  cmd_status },
    { "out",     cmd_out },
    { "blink",   cmd_blink },
    { "ping",    cmd_ping },
    { "diic",    cmd_diic },
    { "piic",    cmd_piic },
    { "env",     cmd_env },
    { "dm",      cmd_dmb },
    { "dmb",     cmd_dmb },
    { "dmw",     cmd_dmw },
    { "date",    cmd_date },
    { "reboot",  cmd_reboot },
    {NULL, NULL}
};

const ShellConfig shell_cfg_uart =
{
    (BaseSequentialStream *)&SD6,
    commands,
    uartShellHistoryBuffer,
    SHELL_MAX_HIST_BUFF
};
