/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_cpy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 17:08:30 by marvin            #+#    #+#             */
/*   Updated: 2024/05/27 17:08:30 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	env_cpy(t_data *data, char **env)
{
	int	i;
	int	env_len;

	i = 0;
	env_len = ft_tablen(env);
	data->env_maj = malloc(sizeof(char *) * (env_len + 1));
	if (!data->env_maj)
		return;
	while (i < env_len)
	{
		data->env_maj[i] = ft_strdup(env[i]);
		if (!data->env_maj[i])
		{
			while (i > 0)
				free(data->env_maj[--i]);
			free(data->env_maj);
			data->env_maj = NULL;
			return;
		}
		i++;
	}
	data->env_maj[env_len] = NULL;
}
