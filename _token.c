#include "shell.h"

/********************    function 1 *************************************/

/**
 * **strtow - Func that splits a string into words
 * @str: This is the input str
 * @d: This is the delimeter str
 * Return: A ptr to an array of str | NULL on failure
 */

char **strtow(char *str, char *d)
{
    int a, b, k, m, numwords = 0;
    char **s;

    if (str == NULL || str[0] == 0)
        return (NULL);
    if (!d)
        d = " ";
    for (a = 0; str[a] != '\0'; a++)
        if (!is_separator(str[a], d) && (is_separator(str[a + 1], d) || !str[a + 1]))
            numwords++;

    if (numwords == 0)
        return (NULL);
    s = malloc((1 + numwords) * sizeof(char *));
    if (!s)
        return (NULL);
    for (a = 0, b = 0; b < numwords; b++)
    {
        while (is_separator(str[a], d))
            a++;
        k = 0;
        while (!is_separator(str[a + k], d) && str[a + k])
            k++;
        s[b] = malloc((k + 1) * sizeof(char));
        if (!s[b])
        {
            for (k = 0; k < b; k++)
                free(s[k]);
            free(s);
            return (NULL);
        }
        for (m = 0; m < k; m++)
            s[b][m] = str[a++];
        s[b][m] = 0;
    }
    s[b] = NULL;
    return (s);
}

/********************    function 2 *************************************/

/**
 * **strtow2 - Function that splits a str into words
 * @str: This is the input str
 * @d: This is the delimeter
 * Return: a ptr to an array of strs | NULL on failure
 */

char **strtow2(char *str, char d)
{
    int a, b, k, m, numwords = 0;
    char **s;

    if (str == NULL || str[0] == 0)
        return (NULL);
    for (a = 0; str[a] != '\0'; a++)
        if ((str[a] != d && str[a + 1] == d) ||
            (str[a] != d && !str[a + 1]) || str[a + 1] == d)
            numwords++;
    if (numwords == 0)
        return (NULL);
    s = malloc((1 + numwords) * sizeof(char *));
    if (!s)
        return (NULL);
    for (a = 0, b = 0; b < numwords; b++)
    {
        while (str[a] == d && str[a] != d)
            a++;
        k = 0;
        while (str[a + k] != d && str[a + k] && str[a + k] != d)
            k++;
        s[b] = malloc((k + 1) * sizeof(char));
        if (!s[b])
        {
            for (k = 0; k < b; k++)
                free(s[k]);
            free(s);
            return (NULL);
        }
        for (m = 0; m < k; m++)
            s[b][m] = str[a++];
        s[b][m] = 0;
    }
    s[b] = NULL;
    return (s);
}
