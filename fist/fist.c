#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hashmap.h"
#include "indexer.h"
#include "server.h"
#include "tests.h"

int main(int argc, char *argv[]) {
    if(argc == 2 && !strcmp(argv[1], "test")) {
        run_tests();
	return 0;
    }

    return start_server("127.0.0.1", 5575);
}
