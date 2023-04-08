#include "syscalls.h"

// create dummy syscalls as we don't need them but the linker still needs them.
void _close() {}
void _lseek() {}
void _read() {}
void _write() {}
void _kill() {}
void _isatty() {}
void _getpid() {}
void _fstat() {}
