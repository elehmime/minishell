/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ellehmim <ellehmim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 15:41:58 by farouk            #+#    #+#             */
/*   Updated: 2024/06/14 18:51:53 by ellehmim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int    in_single_quote(char *str, int j)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == '\'')
        {
            i++;
            while(str[i] && str[i] != '\'')
            {
                if (str[i] == 36 && i == j)
                    return (1);
                i++;
            }
        }
        if (str[i] == '\"')
        {
            i++;
            while (str[i] && str[i] != '\"')
                i++;
        }
        i++;
    }
    return (0);
}

void	free_tab(char **tab)
{
	int	i;

	if (tab == NULL)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	tab = NULL;
}

void	print_error(void)
{
	printf("incorrect inpout");
	exit(0);
}

void	sig_management(int signo)
{
	if (signo == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}