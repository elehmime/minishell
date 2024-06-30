/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ellehmim <ellehmim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 16:27:56 by ellehmim          #+#    #+#             */
/*   Updated: 2024/06/14 18:53:15 by ellehmim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char* ft_strncpy1(char *dest, const char *src, int n)
{
    int i;

    i = 0;
    while (i < n && src[i] != '\0')
    {
        dest[i] = src[i];
        i++;
    }
    while (i < n)
    {
        dest[i] = '\0';
        i++;
    }
    return dest;
}

char	*ft_strncat1(char *dest, const char *src, unsigned int nb)
{
	unsigned int	i;
	unsigned int	y;

	y = 0;
	i = 0;
	while (dest[i])
		i++;
	while (src[y] && y < nb)
	{
		dest[i] = src[y];
		i++;
		y++;
	}
	dest[i] = '\0';
	return (dest);
}

char* get_env_value(const char *var_name, char **env)
{
    while (*env)
    {
        if (ft_strncmp1(*env, var_name, ft_strlen1(var_name)) == 0 &&
            (*env)[ft_strlen1(var_name)] == '=')
            return &(*env)[ft_strlen1(var_name) + 1];
        env++;
    }
    return NULL;
}

void replace_var(char *dest, const char *str, int *i, int *j, char **env)
{
    int var_start;
    char var_name[BUFFER_SIZE];
    char *env_value;

    var_start = ++(*i);
    while (ft_isalnum1(str[*i]) || str[*i] == '_')
        (*i)++;
    ft_strncpy1(var_name, &str[var_start], *i - var_start);
    var_name[*i - var_start] = '\0';
    env_value = get_env_value(var_name, env);
    if (env_value)
    {
        ft_strcat1(dest, env_value);
        *j += ft_strlen1(env_value);
    }
    else
    {
        dest[(*j)++] = '$';
        ft_strncat1(dest, &str[var_start], *i - var_start);
        *j += *i - var_start;
    }
}

char	*expend(char *str, char **env)
{
    int j;
    int i;
    static char dest[BUFFER_SIZE];

    i = 0;
    j = 0;
    ft_memset1(dest, 0, BUFFER_SIZE);
    while (str[i] != '\0')
    {
        if (str[i] == '$' && in_single_quote(str, i) == 0)
            replace_var(dest, str, &i, &j, env);
        else
            dest[j++] = str[i++];
    }
    dest[j] = '\0';
    return (dest);
}
