#include "syscalls.h"

// create dummy syscalls as we don't need them but the linker still needs them.
void _close(void) {}
void _lseek(void) {}
void _read(void) {}
void _write(void) {}
void _kill(void) {}
void _isatty(void) {}
void _getpid(void) {}
void _fstat(void) {}
