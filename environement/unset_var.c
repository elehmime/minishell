/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 13:06:11 by marvin            #+#    #+#             */
/*   Updated: 2024/06/07 13:06:11 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_new_env(char **new_env, int j)
{
	while (j > 0)
		free(new_env[--j]);
	free(new_env);
}

int	check_var(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data->env_maj[i])
	{
		if (ft_strncmp(data->token->next->word, data->env_maj[i], ft_strlen(data->token->next->word)) == 0)
		{
			while(data->env_maj[i][j] != '=')
				j++;
			if (j == ft_strlen(data->token->next->word))
				return (YES);
		}
		i++;
	}
	return(NO);
}

void	unset_variables(t_data *data)
{
	int		(i) = 0;
	int		(j) = 0;
	int		len_old_env;
	char	**new_env;

	if (check_var(data) == NO)
		return ;
	len_old_env = ft_tablen(data->env_maj);
	new_env = malloc(sizeof(char *) * len_old_env);
	if (!new_env)
		return ;
	while (i < len_old_env)
	{
		if (ft_strncmp(data->env_maj[i], data->token->next->word,
			ft_strlen(data->token->next->word)) == 0 &&
			data->env_maj[i][ft_strlen(data->token->next->word)] == '=')
		{
			i++;
			continue ;
		}
		new_env[j] = ft_strdup(data->env_maj[i]);
		if (!new_env[j])
			return (free_new_env(new_env, j));
		i++;
		j++;
	}
	new_env[j] = NULL;
	ft_free_env(data);
	env_cpy(data, new_env);
	ft_free_tab(new_env);
}