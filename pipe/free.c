/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 19:44:36 by marvin            #+#    #+#             */
/*   Updated: 2024/02/26 19:44:36 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_all(t_pipedata *data, char **argv, char **av)
{
	free(data->cmds);
	if (is_heredoc(argv) == 1)
	{
		ft_free_tab_pipex(av);
		unlink("here_doc");
	}
	free(data->pid_tab);
}

void	ft_free_tab_pipex(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	exit_err(t_pipedata *data, int nb, char *err_str)
{
	ft_printf("%s\n", err_str);
	if (nb > 0)
	{
		if (nb >= 1)
		{
			free(data->pid_tab);
			free(data->cmds);
			if (nb >= 2)
			{
				close(data->fd_outfile);
				if (nb >= 3)
				{
					free(data->cmds);
				}
			}
		}
	}
}

int	check_cmd_path_pipex(char *cmd)
{
	if (access(cmd, F_OK | X_OK) == 0)
		return (1);
	else
		return (0);
}
