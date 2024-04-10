/*****************************************************************************
 * lfind.c : implement lfind
 *****************************************************************************/

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

void *lfind(const void *key, const void *base, size_t *nmemb,
            size_t size, int(*cmp)(const void *, const void *))
{
<<<<<<< HEAD
    for (size_t i = 0; i < *nmemb; ++i)
    {
        const void *elem = (const char*)base + i * size;
        if (!cmp(key, elem))
            return (void*)elem;
=======
    for (int i = 0; i < *nmemb; ++i)
    {
        const void *elem = base + i * size;
        if (!cmp(key, elem))
            return elem;
>>>>>>> 3e483547037e49f8ef828f2f0455593400968cf4
    }
    return NULL;
}
