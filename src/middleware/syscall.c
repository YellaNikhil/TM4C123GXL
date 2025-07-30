#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <stddef.h>

// Simulate end of RAM (customize if needed)
extern char _end;
char* heap_end = &_end;

void* _sbrk(ptrdiff_t incr) {
    char* prev_heap_end = heap_end;
    heap_end += incr;
    return (void*)prev_heap_end;
}

int _write(int file, char *ptr, int len) {
    // Optional: Send to UART if implemented
    return len;
}

int _read(int file, char *ptr, int len) {
    errno = ENOSYS;
    return -1;
}

int _close(int file) {
    return -1;
}

int _fstat(int file, struct stat *st) {
    st->st_mode = S_IFCHR;
    return 0;
}

int _lseek(int file, int ptr, int dir) {
    return 0;
}

int _isatty(int file) {
    return 1;
}

int _kill(int pid, int sig) {
    errno = EINVAL;
    return -1;
}

int _getpid(void) {
    return 1;
}

void _exit(int status) {
    while (1); // Hang on exit
}
