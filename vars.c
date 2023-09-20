#include "shell.h"

/**
 * is_delim_chain - This tests if current char in buffer is a chain delimeter
 * @info: This is the parameter struct
 * @buf: This is the char buffer
 * @p: This is an address of current position in buf
 * Return: 1 if chain delimeter, 0 otherwise
 */
int is_delim_chain(info_t *info, char *buf, size_t *p)
{
    size_t j = *p;

    if (buf[j] == '|' && buf[j + 1] == '|')
    {
        buf[j] = 0;
        j++;
        info->cmd_buf_type = CMD_OR;
    }
    else if (buf[j] == '&' && buf[j + 1] == '&')
    {
        buf[j] = 0;
        j++;
        info->cmd_buf_type = CMD_AND;
    }
    else if (buf[j] == ';') /* is found at the end of this command */
    {
        buf[j] = 0; /* replaces semicolon with null */
        info->cmd_buf_type = CMD_CHAIN;
    }
    else
        return (0);
    *p = j;
    return (1);
}

/**
 * check_delim - This checks we should continue chaining based on last status
 * @info: This is the parameter struct
 * @buf: This is the char buffer
 * @p: This is an address of current position in buf
 * @i: This is the starting position in buf
 * @len: This is the length of buf
 * Return: Void
 */
void check_delim(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
    size_t j = *p;

    if (info->cmd_buf_type == CMD_AND)
    {
        if (info->status)
        {
            buf[i] = 0;
            j = len;
        }
    }
    if (info->cmd_buf_type == CMD_OR)
    {
        if (!info->status)
        {
            buf[i] = 0;
            j = len;
        }
    }

    *p = j;
}

/**
 * replace_alias_token - This replaces an aliases in the tokenized string
 * @info: This is the parameter struct
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias_token(info_t *info)
{
    int i;
    list_t *node;
    char *p;

    for (i = 0; i < 10; i++)
    {
        node = start_node_is(info->alias, info->argv[0], '=');
        if (!node)
            return (0);
        free(info->argv[0]);
        p = _strchr(node->str, '=');
        if (!p)
            return (0);
        p = _strdup(p + 1);
        if (!p)
            return (0);
        info->argv[0] = p;
    }
    return (1);
}

/**
 * replace_variables - This replaces vars in the tokenized string
 * @info: This is the parameter struct
 * Return: 1 if replaced, 0 otherwise
 */
int replace_variables(info_t *info)
{
    int i = 0;
    list_t *node;

    for (i = 0; info->argv[i]; i++)
    {
        if (info->argv[i][0] != '$' || !info->argv[i][1])
            continue;

        if (!_strcmp(info->argv[i], "$?"))
        {
            replace_string(&(info->argv[i]),
                           _strdup(convert_number(info->status, 10, 0)));
            continue;
        }
        if (!_strcmp(info->argv[i], "$$"))
        {
            replace_string(&(info->argv[i]),
                           _strdup(convert_number(getpid(), 10, 0)));
            continue;
        }
        node = start_node_is(info->env, &info->argv[i][1], '=');
        if (node)
        {
            replace_string(&(info->argv[i]),
                           _strdup(_strchr(node->str, '=') + 1));
            continue;
        }
        replace_string(&info->argv[i], _strdup(""));
    }
    return (0);
}

/**
 * replace_string - This replaces string
 * @old: This an address of old string
 * @new: This is the new string
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **old, char *new)
{
    free(*old);
    *old = new;
    return (1);
}
