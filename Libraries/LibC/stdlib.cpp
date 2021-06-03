#include <FSH/Types.h>

#include <stdio.h>
#include <stdlib.h>

__attribute__((__noreturn__)) void abort(void) {
#ifdef __LIBK
    printf("[Kernel] PANIC: abort()\n");
#else
    printf("abort()\n");
#endif

    while (1) {
    };
    __builtin_unreachable();
}

char* itoa(int value, char* str, int base) {
    static char digits[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    static u32 num = 0;
    static constexpr int maxlen = sizeof(int) * 8 + 1;

    auto* ret = &str[maxlen - 1];
    auto neg = value < 0 && base == 10;

    num = static_cast<u32>(value);

    *ret = '\0';

    if (neg) {
        num ^= -1;
        num++;
    } else if (base <= 1 || base > 36) {
        return ret;
    }

    do {
        *--ret = digits[num % base];
        num /= base;
    } while (num != 0);

    if (neg)
        *--ret = '-';

    return ret;
}
