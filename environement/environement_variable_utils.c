/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environement_variable_utils.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ellehmim <ellehmim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 00:14:02 by ellehmim          #+#    #+#             */
/*   Updated: 2024/07/01 01:17:42 by ellehmim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int find_word(char *str, char *word)
{
    int i = 0;
    while (str[i] && str[i] == word[i] && word[i] != '=')
            i++;
    if (word[i] == '=')
        return 0;
    return 1;
}

char *replace_env(char *str, char *word)
{
    int i = 0;
    char *dest = malloc((ft_strlen(word) + 1) * sizeof(char));
    if (!dest)
        return NULL;
    while (word[i])
    {
        dest[i] = word[i];
        i++;
    }
    dest[i] = '\0';
    free(str);
    return dest;
}

char **if_var_exist(char **env, char *word, int *x)
{
    int i;

	i = 0;
    while (env[i])
    {
        if (find_word(env[i], word) == 0)
        {
            env[i] = replace_env(env[i], word);
			*x = 1;
            break;
        }
        i++;
    }
    return (env);
}