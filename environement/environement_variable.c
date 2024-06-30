/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environement_variable.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:21:18 by marvin            #+#    #+#             */
/*   Updated: 2024/05/21 13:21:18 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_env(t_data *data)
{
	int	i;

	i = 0;
	while (i < ft_tablen(data->env_maj))
	{
		free(data->env_maj[i]);
		i++;
	}
	free(data->env_maj);
	data->env_maj = NULL;
	return;
}

void	print_export(t_data *data)
{
	int	i;

	i = 0;
	while (data->env_maj[i])
	{
		printf("declare -x %s\n", data->env_maj[i]);
		i++;
	}
}

void	variable_en_utils(t_data *data, char **new_env)
{
	ft_free_env(data);
	env_cpy(data, new_env);
	ft_free_tab(new_env);
}

void	variables_env(t_data *data) // si la VAR existe == la remplacer et pas en cree une autre
{
	char	**new_env;
	int		len_old_env;
	int		(i) = 0;

	data->env_maj = if_var_exist(data->env_maj, data->token->next->word, &i);
	if (i > 0)
		return ;
	len_old_env = ft_tablen(data->env_maj);
	new_env =  malloc(sizeof(char *) * (len_old_env + 2));
	if (!new_env)
		return ;
	while (i < len_old_env)
	{
		new_env[i] = ft_strdup(data->env_maj[i]);
		if (!new_env[i])
		{
			while (i > 0)
				free(new_env[--i]);
			free(new_env);
			new_env = NULL;
			return;
		}
		i++;
	}
	new_env[len_old_env] = ft_strdup(data->token->next->word);
	new_env[len_old_env + 1] = NULL;
	variable_en_utils(data, new_env);
}
