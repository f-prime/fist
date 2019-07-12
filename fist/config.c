#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "dstring.h"

static void config_set_default(struct config *config) {
    config->host = dcreate(CONFIG_DEFAULT_HOST);
    config->max_phrase_length = CONFIG_DEFAULT_MAX_PHRASE_LEN;
    config->port = CONFIG_DEFAULT_PORT;
    config->save_period = CONFIG_DEFAULT_SAVE_PERIOD;
    config->so_backlog = CONFIG_DEFAULT_SO_BACKLOG;
}

static void config_parse_int(const char *val, int *target) {
    // TODO: Check for errors?
    // TODO: Sanity check values?
    *target = atoi(val);
}

void config_free(struct config *config) {
    dfree(config->host);
    free(config);
}

struct config *config_parse(const char *path)
{
    struct config *config;
    FILE *f;
    char line[256];
    unsigned int line_num = 0;

    if(!path) {
        path = CONFIG_DEFAULT_PATH;
    }

    config = calloc(1, sizeof(struct config));
    if(!config) {
        perror("calloc");
        return NULL;
    }

    config_set_default(config);

    f = fopen(path, "r");
    if(!f) {
        fprintf(stderr, "config_parse: Failed to open '%s'\n", path);
        return config;
    }

    while(fgets(line, sizeof(line), f)) {
        char *saveptr;
        char *tokens[3];
        int num_tokens = 0;
        line_num++;

        while(num_tokens < 3) {
            char *token = strtok_r(num_tokens ? NULL : line, " \r\n", &saveptr);
            if(!token) {
                break;
            }
            tokens[num_tokens++] = token;
        }

        if(num_tokens == 0)
            continue;
        if(num_tokens != 2) {
            fprintf(stderr, "config_parse: %s:%u: Bad line\n", path, line_num);
            continue;
        }

        dstring key = dcreate(tokens[0]);
        dstring value = dcreate(tokens[1]);

        if(dequalsc(key, "Host")) {
            config->host = dcreate(dtext(value));
        } else if(dequalsc(key, "MaxPhraseLength")) {
            config_parse_int(tokens[1], &config->max_phrase_length);
        } else if(dequalsc(key, "Port")) {
            config_parse_int(tokens[1], &config->port);
        } else if(dequalsc(key, "SavePeriod")) {
            config_parse_int(tokens[1], &config->save_period);
        } else if(dequalsc(key, "SoBacklog")) {
            config_parse_int(tokens[1], &config->so_backlog);
        } else {
            fprintf(stderr, "config_parse: %s:%u: Unknown config key '%s'\n", path, line_num,
                    tokens[0]);
        }

        dfree(key);
        dfree(value);
    }

    fclose(f);

    return config;
}
