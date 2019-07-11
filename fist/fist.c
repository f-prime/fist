#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "config.h"
#include "hashmap.h"
#include "indexer.h"
#include "server.h"
#include "tests.h"
#include "version.h"

int main(int argc, char *argv[]) {
    int c;
    const char *config_file = NULL;
    while((c = getopt(argc, argv, "tVc:")) != -1) {
        switch(c) {
        case 'c':
            config_file = optarg;
            break;
        case 't':
            run_tests();
            return 0;
        case 'V':
            printf("%s\n", VERSION);
            return 0;
        default:
            abort();
        }
    }

    struct config config;
    config_parse(config_file, &config);

    return start_server(&config);
}
