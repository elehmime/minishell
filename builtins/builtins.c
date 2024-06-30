/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 20:16:52 by marvin            #+#    #+#             */
/*   Updated: 2024/05/20 20:16:52 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_echo(t_token *token)
{
	if ((ft_strcmp(token->word, "echo") == 0))
		return (1);
	return (0);
}

int	check_export_env(t_data *data, int len)
{
	if (ft_strcmp(data->token->word, "export") == 0)
	{
		if (len == 1)
			print_export(data);
		else
			variables_env(data);
		return (YES);
	}
	if ((ft_strcmp(data->token->word, "env") == 0) &&  token_size(data->token) == 1)
	{
		builtins_env(data);
		return (YES);
	}
	return (NO);
}

int	check_unset(t_data *data)
{
	if (ft_strcmp(data->token->word, "unset") == 0)
	{
		unset_variables(data);
		return (YES);
	}
	return (NO);
}

int	check_builtins(t_data *data)
{
	if (ft_strcmp(data->token->word, "pwd") == 0 &&  token_size(data->token) == 1)
	{
		builtins_pwd();
		return (YES);
	}
	if (check_echo(data->token) == 1)
	{
		if (builtins_echo(data->token->next) == 0)
			return (NO);
		return (YES);
	}
	if (ft_strcmp(data->token->word, "cd") == 0)
	{
		builtins_cd(token_size(data->token), data); // verfier cd .
		return (YES);
	}
	if (check_export_env(data, token_size(data->token)) == 1)
		return (YES);
	if (check_unset(data) == 1)
		return (YES);
	if (ft_strcmp(data->token->word, "exit") == 0)
		builtins_exit(data);
	return (NO);
}

