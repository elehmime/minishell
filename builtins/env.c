/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:37:13 by marvin            #+#    #+#             */
/*   Updated: 2024/05/23 11:37:13 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	builtins_env(t_data *data)
{
	int	i;

	i = 0;
	while (data->env_maj[i])
	{
		printf("%s\n", data->env_maj[i]);
		i++;
	}
}
