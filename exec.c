/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 21:48:09 by marvin            #+#    #+#             */
/*   Updated: 2024/06/14 21:48:09 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	if_argcmd(t_token *token)
{
	if (token->next != NULL)
	{
		if (token->type == 0 && token->next->type == 0)
			return (YES);
	}
	return (NO);
}

void	fork_exec(t_data *data, char **env)
{
	char	*cmd;
	char 	*with_arg;

	with_arg = ft_strdup(data->token->word);
	if (if_argcmd(data->token) == YES)
	{
		while (if_argcmd(data->token) == YES)
		{
			with_arg = ft_strjoin(with_arg, " ");
			with_arg = ft_strjoin(with_arg, data->token->next->word);
			if(data->token->next)
				data->token = data->token->next;
		}
	}
	check_redirection_out(data);
	if (!data->token->next)
		data->continue_while = 0;
	data->params_cmd = ft_split(with_arg, ' ');
	cmd = get_path(data->params_cmd[0], data->env_maj, data);
	if (cmd == NULL)
		exit (127);
	execve(cmd, data->params_cmd, env);
	exit (127);
}

int	exec_cmd(t_data *data, char **env)
{
	// si il y a un pipe dans la ligne alors les cmd de variable d env ne fonctione pas export, unset / VAR=...
	// si la cmd[0] = export alors prendre cmd[1] et envoyer environement variable
	// pas d espace possible dans "export VAR=     1" XXXX "export VAR=1" VVV
	if (check_builtins(data) == 0)
	{
		data->pid = fork();
		if (data->pid == -1)
			return (1);
		else if (data->pid == 0)
			fork_exec(data, env);
		else
			return (1);
	}
	return (2);
}