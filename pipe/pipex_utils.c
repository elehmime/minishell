/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 11:38:34 by marvin            #+#    #+#             */
/*   Updated: 2024/02/12 11:38:34 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	take_cmds(t_pipedata *data, char **av, int argc) // exit err
{
	int	i;
	int	j;
	int	n_cmds;

	i = 2;
	j = 0;
	n_cmds = argc - 3;
	data->cmds = malloc(sizeof(char *) * n_cmds);
	if (!data->cmds)
	{
		exit_err(data, 1, "Erreur, malloc cmd");
		return (1);
	}
	while (j < n_cmds)
	{
		data->cmds[j] = av[i];
		i++;
		j++;
	}
	return (0);
}

char	*getenv_path_pipex(char *name, char **env)
{
	int		i;
	int		j;
	char	*sub;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		sub = ft_substr(env[i], 0, j);
		if (ft_strcmp(sub, name) == 0)
		{
			free(sub);
			return (env[i] + j + 1);
		}
		free(sub);
		i++;
	}
	return (NULL);
}

char	*get_path_pipex(char *cmd, char **env, t_pipedata *data)
{
	char	*exec;
	char	**allpath;
	char	**s_cmd;

	int (i) = -1;
	if (cmd[0] == '/')
	{
		if (check_cmd_path(cmd) == 1)
			return (cmd);
	}
	allpath = ft_split(getenv_path_pipex("PATH", env), ':');
	s_cmd = ft_split(cmd, ' ');
	while (allpath[++i])
	{
		data->path_part = ft_strjoin(allpath[i], "/");
		exec = ft_strjoin(data->path_part, s_cmd[0]);
		free(data->path_part);
		if (access(exec, F_OK | X_OK) == 0)
			return (ft_free_tab_pipex(s_cmd), exec);
		free(exec);
	}
	ft_free_tab_pipex(allpath);
	ft_free_tab_pipex(s_cmd);
	return (NULL);
}

int	check_param(char *cmd, t_pipedata *data)
{
	data->param = ft_split(cmd, ' ');
	return (0);
}

void	ft_close(t_pipedata *data)
{
	close(data->pipe_impair[0]);
	close(data->pipe_impair[1]);
	close(data->pipe_pair[1]);
	close(data->pipe_pair[0]);
	if (data->NoIn == 0)
		close(data->fd_infile);
}
