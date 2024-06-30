/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 16:27:16 by farouk            #+#    #+#             */
/*   Updated: 2024/06/12 00:30:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_count_world2(char *line, int *i, int c, int j)
{
	j = *i;
	if (ft_strchr(SPACES, line[j]))
    {
        while (ft_strchr(SPACES, line[j]) && line[j])
            j++;
        if (ft_strchr(SPECIAL, line[j]) || ft_strchr(QUOTES, line[j])
			|| !line[j])  
            return (c);
    }
    else if (ft_strchr(SPECIAL, line[j]))
    {
        if (line[j + 1] == '>' || line[j + 1] == '<')
            j++;
        c++;
        j++;
    }
    else
    {
        while (line[j] && !ft_strchr(SPACES, line[j]) &&
			!ft_strchr(SPECIAL, line[j]) && !ft_strchr(QUOTES, line[j]))
            j++;
        c++;
    }
	*i = j - 1;
	return (c);
}

int ft_count_word(char *line)
{
    int c = 0;
    int i = 0;
	int	k;
    char j;

    if (!line)
        return (0); // a verif
    while (line[i])
    {
		k = 0;
        if (line[i] == '\'' || line[i] == '"')
        {
            j = line[i];
            i++;
            while (line[i] && line[i] != j)
                i++;
            if (line[i++] == j)
                c++;
        }
		c = ft_count_world2(line, &i, c, k);
		i++;
    }
    return (c);
}

int space(char *line, int i)
{
    char c;

	if (i < 0)
		return (-1);
	c = line[i - 1];
    while (ft_strchr(SPACES, line[i]) && line[i])
        i++;
    if (line[i] == '\0' && ft_strchr(SPECIAL, c))
        return(-1);
    if (ft_strchr(SPECIAL, c) && ft_strchr(SPECIAL, line[i]))
        return(-1);
    return(i - 1);
}

int syntax(char *line)
{
    int i;

    i = 0;
    if (line[0] == '|' || ft_strchr(SPECIAL, line[ft_strlen(line) - 1]))
        return (1);
    while (line[i])
    {
        if (line[i] == '|' && line[i + 1] == '|')
            return (1);
        else if (line[i] == '>' && (line[i + 1] == '|' || line[i + 1] == '<'))
            return (1);
        else if (line[i] == '<' && (line[i + 1] == '|' || line[i + 1] == '>'))
                return (1);
        if (line[i] == 32 || line[i] == '\n' || line[i] == '\t')
            i = space(line, i);
        if (i < 0)
            return (1);
        i++;
    }
	return (0);
}

void    find_command(char *line, t_data *data)
{
	char	**tab;

    tab = ft_separator(line);
    data->token = create_token_list(tab);
    free_tab(tab);
}
