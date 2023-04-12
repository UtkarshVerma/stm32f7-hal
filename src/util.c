#include "util.h"

#include "uart.h"

void error_handler(char *file, unsigned int line) {
    log_uart("[ERROR]\terorr occured on line %u in file %s\r\n", line, file);
    while (1)
        ;
}
