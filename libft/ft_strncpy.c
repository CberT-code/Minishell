#include "libft.h"

char            *ft_strncpy(const char *src, int n)
{
    char        *dst;
    int      i;

    if (!(dst = malloc(sizeof(char) * n + 1)))
        return (NULL);
    i = 0;
    if (n)
    {
        while (i < n && (dst[i] = src[i]))
            i++;
        while (i < n)
            dst[i++] = 0;
    }
    return (dst);
}