/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_define.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 19:27:55 by ellehmim          #+#    #+#             */
/*   Updated: 2024/06/13 19:12:05 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	type_define(char *s)
{
	int i;

	i = 0;
	while(s[i])
	{
		if (s[i] == '|')
			return (1);
		i++;
	}
	return (0);
}

void free_token_list(t_token *head)
{
    t_token *tmp;

    while (head)
	{
        tmp = head;
        head = head->next;
        free(tmp->word);
        free(tmp);
    }
}
