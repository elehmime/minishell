/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 11:30:57 by marvin            #+#    #+#             */
/*   Updated: 2024/02/12 11:30:57 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	wait_child(t_pipedata *data, int ac)
{
	int	i;

	i = 0;
	while (i < ac - 4)
	{
		waitpid(data->pid_tab[i], NULL, 0);
		i++;
	}
}

void	process1(t_pipedata *data, char **env, int ac, char **av)
{
	char	*cmd;

	init_in(data, av);
	init_out(data, av, ac);
	cmd = get_path_pipex(data->cmds[data->nbfork], env, data);
	if (!cmd) 
	{
		free(data->cmds);
		free(cmd);
		free(data->pid_tab);
		exit(0);
	}
	check_param(data->cmds[data->nbfork], data);
	execve(cmd, data->param, env);
}

int	pipex_init(int argc, char **av, t_pipedata *data) // exit err
{
	int	i;

	i = 0;
	data->nbfork = 0;
	if (take_cmds(data, av, argc) == 1)
		return (1);
	data->pid_tab = malloc(sizeof(pid_t) * (argc - 3));
	if (!data->pid_tab)
	{
		exit_err(data, 0, "Error, Malloc Pid tab");
		return (1);
	}
	while (i < argc - 3)
		data->pid_tab[i++] = 0;
	if (check_open_file(data, argc, av) == 1)
		return (1);
	pipe(data->pipe_impair);
	pipe(data->pipe_pair);
	return (0);
}

int	pipex_main(int argc, char **argv, char **envp)
{
	t_pipedata	data;
	char	**av;
	int		ac;

	av = check_av(argv, argc);
	if (is_heredoc(argv) == 1)
		ac = pipex_heredoc(argv, argc);
	else
		ac = argc;
	if (pipex(&data, ac, av, envp) == 1)
		return (0);
	ft_close(&data);
	wait_child(&data, ac);
	free_all(&data, argv, av);
	return (0);
}

int	pipex(t_pipedata *data, int ac, char **av, char **envp) // exit err
{
	pid_t	pid;

	data->saved_stdout = dup(STDOUT_FILENO);
	data->NoIn = 0;
	data->NoOut = 0;
	if (ft_strcmp(av[1], "NoIn") == 0)
 		data->NoIn = 1;
	if (ft_strcmp(av[ac - 1], "NoOut") == 0)
		data->NoOut = 1;
	if (pipex_init(ac, av, data) == 1)
		return (1);
	while ((data->nbfork) < (ac - 3))
	{
		pid = fork();
		if (pid == -1)
			exit_err(data, 2, "Erreur, fork"); // dernier exit err a gere
		else if (pid == 0)
			process1(data, envp, ac, av);
		else
			parent(data, pid);
		data->nbfork++;
	}
	return (0);
}
