#include "shell.h"

/**
 * _my_environment - This prints the current environment
 * @info: This structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int _my_environment(info_t *info)
{
    print_list_str(info->env);
    return (0);
}

/**
 * _getenv - This gets the value of an environ variable
 * @info: This structure contains a potential arguments. Used to maintain
 * @name: env var name
 *
 * Return: the value
 */
char *_getenv(info_t *info, const char *name)
{
    list_t *node = info->env;
    char *p;

    while (node)
    {
        p = starts_with(node->str, name);
        if (p && *p)
            return (p);
        node = node->next;
    }
    return (NULL);
}

/**
 * _my_setenv - This Initializes a new environment variable,
 * or modifies an existing one
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 *  Return: Always 0
 */
int _my_setenv(info_t *info)
{
    if (info->argc != 3)
    {
        _eputs("Incorrect number of arguements\n");
        return (1);
    }
    if (_setenv(info, info->argv[1], info->argv[2]))
        return (0);
    return (1);
}

/**
 * _my_unsetenv -This  Removes an environment variable
 * @info: This Structure containing potential arguments. Used to maintain
 *  constant function prototype.
 * Return: Always 0
 */
int _my_unsetenv(info_t *info)
{
    int i;

    if (info->argc == 1)
    {
        _eputs("Too few arguements.\n");
        return (1);
    }
    for (i = 1; i <= info->argc; i++)
        _unsetenv(info, info->argv[i]);

    return (0);
}

/**
 * calculate_env_list - this populates env linked list
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int calculate_env_list(info_t *info)
{
    list_t *node = NULL;
    size_t i;

    for (i = 0; environ[i]; i++)
        add_node_end(&node, environ[i], 0);
    info->env = node;
    return (0);
}
