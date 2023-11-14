#include "shell.h"

/**
 * b_free - Function that frees a ptr and NULLs the address
 * @ptr: This is the address of the ptr to free
 * Return: 1 [freed]  | 0 [otherwise
 */

int b_free(void **ptr)
{
if (ptr && *ptr)
{
free(*ptr);
*ptr = NULL;
return (1);
}
return (0);
}
