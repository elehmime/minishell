/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ellehmim <ellehmim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 15:52:33 by farouk            #+#    #+#             */
/*   Updated: 2024/06/14 18:47:10 by ellehmim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int check_quotes(char *line)
{
    int i = 0;
    char j;
    while (line[i])
    {
        if (line[i] == '\'' || line[i] == '"')
        {
            j = line[i];
            i++;
            while (line[i])
            {
                if (line[i] == j)
                    break;
                i++;
            }
            if (line[i] != j)
                return(1);
        }
        i++;
    }
    return(0); 
}


void negatif_string(char *line)
{
    int i;

    i = 0;
    while (line && line[i])
    {
        if (ft_strchr(QUOTES, line[i]))
        {
            char c  = line[i++];
            while (line[i] && line[i] != c)
            {
                line[i] = -line[i];
                i++;
            }
        }
        i++;
    }
}
void positif_string(char *line)
{
    int i = 0;
    while (line && line[i])
    {
        if (line[i] < 0)
            line[i] = -line[i];
        i++;
    }
}

int parsing(char *line, char **env, t_data *data)
{
	if (check_quotes(line))
        return (1);
	data->dest = expend(line, env);
	negatif_string(data->dest);
    //printf("data->dest neg: %s\n", data->dest);
	if (syntax(data->dest))
		return (2);
    find_command(data->dest, data);
	return (0);
}
