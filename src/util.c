#include "util.h"

#include "uart.h"

void errorHandler(char *file, unsigned int line) {
    logUART("[ERROR]\terorr occured on line %u in file %s\r\n", line, file);
    while (1)
        ;
}
