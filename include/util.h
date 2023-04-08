#pragma once
#include <stdint.h>

#define LEN(arr) (sizeof(arr) / sizeof(arr[0]))

typedef uint8_t byte;
typedef uint16_t word;
typedef uint32_t dword;
typedef uint64_t qword;

void errorHandler(char *file, unsigned int line);
