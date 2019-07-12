#ifndef CONFIG_H
#define CONFIG_H

#include "dstring.h"

#define CONFIG_DEFAULT_HOST "127.0.0.1"
#define CONFIG_DEFAULT_MAX_PHRASE_LEN 10
#define CONFIG_DEFAULT_PATH "/usr/local/etc/fist/fist_config"
#define CONFIG_DEFAULT_PORT 5575
#define CONFIG_DEFAULT_SAVE_PERIOD 120
#define CONFIG_DEFAULT_SO_BACKLOG 10

struct config
{
    dstring host;
    int max_phrase_length;
    int port;
    int save_period;
    int so_backlog;
};

void config_free(struct config *config);

struct config *config_parse(const char *path);

#endif//CONFIG_H
