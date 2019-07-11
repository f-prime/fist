#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static void config_set_default(struct config *config) {
    strncpy(config->host, CONFIG_DEFAULT_HOST, CONFIG_HOST_MAX);
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

int config_parse(const char *path, struct config *config) {
    FILE *f;
    char line[256];
    unsigned int line_num = 0;

    if(!path) {
        path = CONFIG_DEFAULT_PATH;
    }

    config_set_default(config);

    f = fopen(path, "r");
    if(!f) {
        fprintf(stderr, "config_parse: Failed to open '%s'\n", path);
        return 0;
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

        if(strcmp(tokens[0], "Host") == 0) {
            strncpy(config->host, tokens[1], CONFIG_HOST_MAX - 1);
        } else if(strcmp(tokens[0], "MaxPhraseLength") == 0) {
            config_parse_int(tokens[1], &config->max_phrase_length);
        } else if(strcmp(tokens[0], "Port") == 0) {
            config_parse_int(tokens[1], &config->port);
        } else if(strcmp(tokens[0], "SavePeriod") == 0) {
            config_parse_int(tokens[1], &config->save_period);
        } else if(strcmp(tokens[0], "SoBacklog") == 0) {
            config_parse_int(tokens[1], &config->so_backlog);
        } else {
            fprintf(stderr, "config_parse: %s:%u: Unknown config key '%s'\n", path, line_num,
                    tokens[0]);
        }
    }

    return 1;
}
