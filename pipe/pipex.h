/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 11:34:45 by marvin            #+#    #+#             */
/*   Updated: 2024/02/12 11:34:45 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include "../libft/libft.h"
# include <stdio.h>
# include <sys/wait.h>

# define FREE_BUFFER 1

typedef struct s_pipedata
{
	int		fd_outfile;
	int		fd_infile;
	int		NoIn;
	int		NoOut;
	int		nbfork;
	int		pipe_impair[2];
	int		pipe_pair[2];
	int		*pid_tab;
	int		saved_stdout;
	char	*path_part;
	char	**cmds;
	char	**param;
}	t_pipedata;

int		pipex_main(int argc, char **argv, char **envp);
int		pipex_init(int argc, char **av, t_pipedata *data);
int		check_open_file(t_pipedata *data, int argc, char **av);
int		is_heredoc(char **av);
int		check_param(char *cmd, t_pipedata *data);
char	*get_path_pipex(char *cmd, char **env, t_pipedata *data);
char	**check_av(char **argv, int argc);
void	exit_err(t_pipedata *data, int nb, char *err_str);
int		take_cmds(t_pipedata *data, char **av, int argc);
void	ft_free_tab_pipex(char **tab);
void	process1(t_pipedata *data, char **env, int ac, char **av);
void	ft_close(t_pipedata *data);
void	init_in(t_pipedata *data, char **av);
void	init_out(t_pipedata *data, char **av, int ac);
void	parent(t_pipedata *data, pid_t pid);
void	free_all(t_pipedata *data, char **argv, char **av);
int		pipex_heredoc(char **av, int argc);
int		pipex(t_pipedata *data, int ac, char **av, char **envp);
void	open_outfile(t_pipedata *data, int argc, char **av);
int		check_cmd_path(char *cmd);

#endif