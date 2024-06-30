/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:10:57 by marvin            #+#    #+#             */
/*   Updated: 2024/06/11 16:10:57 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	change_out(t_data *data, t_token *token)
{
	if (token->type == 2 || token->type == 3)
	{
		data->saved_stdout = dup(STDOUT_FILENO);
		if (token->type == 2)
			data->fd_out = open(token->word, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		else
			data->fd_out = open(token->word, O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (data->fd_out == -1)
		{
			printf("invalid output\n");
			return (0);
		}
		dup2(data->fd_out, STDOUT_FILENO);
		data->redirout = 1;
		close(data->fd_out);
		return(1);
	}
	return (0);
}

int	change_in(t_data *data, t_token *token)
{
	if (token->type == 4)
	{
		data->saved_stdin = dup(STDIN_FILENO);
		data->fd_in = open(token->word, O_RDONLY , 0644);
		if (data->fd_in == -1)
		{
			printf("invalid input\n");
			return (0);
		}
		dup2(data->fd_in, STDIN_FILENO);
		data->redirin = 1;
		close(data->fd_in);
		return (1);
	}
	return (0);
}

void	check_redirection_in(t_data *data)
{
	if (check_if_in5(data) == YES)
		return;
	if (data->token->type == 4)
	{
		change_in(data, data->token);
		if (data->token->next)
			data->token = data->token->next;
		return ;
	}
	if (data->token->prev)
	{
		if (data->token->prev->type == 4)
		{
			change_in(data, data->token->prev);
			return ;
		}
	}
	if (data->token->next && data->token->next->type == 4)
		change_in(data, data->token->next);
}

void	check_redirection_out(t_data *data)
{
	if (data->token->type == 2 || data->token->type == 3)
	{
		change_out(data, data->token);
		if (data->token->next)
			data->token = data->token->next;
		return ;
	}
	if (data->token->prev)
	{
		if (data->token->prev->type == 2 || data->token->prev->type == 3)
		{
			change_out(data, data->token->prev);
			return ;
		}
	}
	if (data->token->next && (data->token->next->type == 2 || data->token->next->type == 3))
		change_out(data, data->token->next);
}

void	reset_redir(t_data *data)
{
	if (data->redirout == 1)
		dup2(data->saved_stdout, STDOUT_FILENO);
	if (data->redirin == 1)
	{
		dup2(data->saved_stdin, STDIN_FILENO);
		if (data->is_heredoc == 1)
			unlink("here_doc");
	}
}