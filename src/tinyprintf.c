#include "tinyprintf.h"

static size_t my_strlen(const char *s)
{
    size_t count = 0;
    while (*s != '\0')
    {
        count++;
        s++;
    }
    return count;
}

static void rev(char *s)
{
    int l = 0;
    int r = my_strlen(s) - 1;
    char t;

    while (l < r)
    {
        t = s[l];
        s[l] = s[r];
        s[r] = t;

        l++;
        r--;
    }
}

static char *my_utoa_base(unsigned int n, char *s, const char *base)
{
    if (n == 0)
    {
        char *save = s;
        *s = *base;
        s++;
        *s = '\0';
        return save;
    }

    char *save = s;
    int b = my_strlen(base) - 1;
    int divide = b + 1;

    while (n != 0)
    {
        unsigned int q = n / divide;
        unsigned int r = n % divide;
        *s = base[r];
        n = q;
        s++;
    }
    *s = '\0';
    rev(save);
    return save;
}

static char *my_itoa_base(int n, char *s, const char *base)
{
    if (n == 0)
    {
        char *save = s;
        *s = *base;
        s++;
        *s = '\0';
        return save;
    }
    int neg = 0;
    if (n < 0)
    {
        neg = 1;
        n *= -1;
    }
    char *save = s;
    int b = my_strlen(base) - 1;
    int divide = b + 1;
    while (n != 0)
    {
        int q = n / divide;
        int r = n % divide;
        *s = base[r];
        n = q;
        s++;
    }
    if (neg)
    {
        *s = '-';
        s++;
    }
    *s = '\0';
    rev(save);
    return save;
}

static int print_string(char *s)
{
    int res = 0;
    while (*s != '\0')
    {
        res++;
        putchar(*s);
        s++;
    }
    return res;
}

static int case_percentage(int res)
{
    putchar('%');
    return res + 1;
}

static int case_d(va_list argsInfo, int res)
{
    int arg = va_arg(argsInfo, int);
    char s[1000];
    my_itoa_base(arg, s, "0123456789");
    res += print_string(s);
    return res;
}

static int case_s(va_list argsInfo, int res)
{
    char *arg = va_arg(argsInfo, char *);
    if (arg == NULL)
    {
        res += print_string("(null)");
        return res;
    }
    else
    {
        res += print_string(arg);
        return res;
    }
}

static int case_o(va_list argsInfo, int res)
{
    unsigned int arg = va_arg(argsInfo, unsigned int);
    char s[1000];
    my_utoa_base(arg, s, "01234567");
    res += print_string(s);
    return res;
}

static int case_u(va_list argsInfo, int res)
{
    unsigned int arg = va_arg(argsInfo, unsigned int);
    char s[1000];
    my_utoa_base(arg, s, "0123456789");
    res += print_string(s);
    return res;
}

static int case_c(va_list argsInfo, int res)
{
    char arg = va_arg(argsInfo, int);
    putchar(arg);
    res++;
    return res;
}

static int case_x(va_list argsInfo, int res)
{
    unsigned int arg = va_arg(argsInfo, unsigned int);
    char s[1000];
    my_utoa_base(arg, s, "0123456789abcdef");
    res += print_string(s);
    return res;
}

static int convert_and_print(const char *format, int res, va_list argsInfo)
{
    if (*(format + 1) == '\0')
    {
        putchar(*format);
        return res + 1;
    }
    switch (*(format + 1))
    {
    case '%':
        res = case_percentage(res);
        break;
    case 'd':
        res = case_d(argsInfo, res);
        break;
    case 'u':
        res = case_u(argsInfo, res);
        break;
    case 's':
        res = case_s(argsInfo, res);
        break;
    case 'c':
        res = case_c(argsInfo, res);
        break;
    case 'o':
        res = case_o(argsInfo, res);
        break;
    case 'x':
        res = case_x(argsInfo, res);
        break;
    default:
        putchar('%');
        putchar(*(format + 1));
        res += 2;
    }
    return res;
}

int tinyprintf(const char *format, ...)
{
    int res = 0;
    va_list argsInfo;
    va_start(argsInfo, format);
    while (*format != '\0')
    {
        switch (*format)
        {
        case '%':
            res = convert_and_print(format, res, argsInfo);
            if (*(format + 1) == '\0')
            {
                format++;
            }
            else
            {
                format += 2;
            }
            break;
        default:
            putchar(*format);
            res++;
            format++;
            break;
        }
    }
    va_end(argsInfo);
    return res;
}
