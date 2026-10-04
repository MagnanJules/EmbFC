#include <stddef.h>
#include <stdint.h>

#define GREETING_SIZE 64

char greeting[GREETING_SIZE];

static void crash(void)
{
    // volatile to tell the compiler to not delete this instruction
    // ending by E0 to have an access fault and not an alignment fault
    *(volatile uint32_t *)0xDEADBEE0 = 0;
}

static size_t append(size_t pos, const uint8_t *src, size_t len)
{
    for (size_t i = 0; i < len && pos < GREETING_SIZE - 1; i++)
        greeting[pos++] = (char)src[i];
    greeting[pos] = '\0';
    return pos;
}

// Crash if one of the inputs is 'A'
int hello_friends(const uint8_t *data, size_t len)
{
    size_t start = 0;
    int count = 0;

    for (size_t i = 0; i <= len; i++)
    {
        if (i < len && data[i] != ',')
            continue;

        const uint8_t *name = data + start;
        size_t name_len = i - start;

        if (name_len == 1 && name[0] == 'A')
            crash();

        size_t pos = append(0, (const uint8_t *)"Hello ", 6);
        pos = append(pos, name, name_len);
        append(pos, (const uint8_t *)"!", 1);

        count++;
        start = i + 1;
    }

    return count;
}
