/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 13:18:11 by marvin            #+#    #+#             */
/*   Updated: 2024/06/28 13:18:11 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	builtins_exit(t_data *data)
{
	if (data->token->next && data->token->next->type == 0)
		data->return_cmd = ft_atoi(data->token->next->word);
	exit (0);	
}