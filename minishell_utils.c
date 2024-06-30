/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:35:06 by marvin            #+#    #+#             */
/*   Updated: 2024/05/15 15:35:06 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_welcome()
{
    ft_printf("\x1b[34m""__        _______ _     ____ ___  __  __ _____      \n" "\x1b[0m");
    ft_printf("\x1b[34m""\\ \\      / / ____| |   / ___/ _ \\|  \\/  | ____|     \n" "\x1b[0m");
    ft_printf("\x1b[34m"" \\ \\ /\\ / /|  _| | |  | |  | | | | |\\/| |  _|       \n" "\x1b[0m");
    ft_printf("\x1b[34m""  \\ V  V / | |___| |__| |__| |_| | |  | | |___      \n" "\x1b[0m");
    ft_printf("\x1b[34m""   \\_/\\_/  |_____|_____\\____\\___/|_|  |_|_____|     \n" "\x1b[0m");
    ft_printf("\x1b[0m""                  |_   _/ _ \\                       \n" "\x1b[0m");
    ft_printf("\x1b[0m""                    | || | | |                      \n" "\x1b[0m");
    ft_printf("\x1b[0m""                    | || |_| |                      \n" "\x1b[0m");
    ft_printf("\x1b[31m"" __  __ ___ _   _ __|_|_\\___/   _ _____ _     _     \n" "\x1b[0m");
    ft_printf("\x1b[31m""|  \\/  |_ _| \\ | |_ _/ ___|| | | | ____| |   | |    \n" "\x1b[0m");
    ft_printf("\x1b[31m""| |\\/| || ||  \\| || |\\___ \\| |_| |  _| | |   | |    \n" "\x1b[0m");
    ft_printf("\x1b[31m""| |  | || || |\\  || | ___) |  _  | |___| |___| |___ \n" "\x1b[0m");
    ft_printf("\x1b[31m""|_|  |_|___|_| \\_|___|____/|_| |_|_____|_____|_____| \n" "\x1b[0m");
    return ;
}

int	check_cmd_path(char *cmd)
{
	if (access(cmd, F_OK | X_OK) == 0)
		return (1);
	else
		return (0);
}

char	*get_path(char *cmd, char **env, t_data *data)
{
	char	*exec;
	char	**allpath;
	char	**s_cmd;

	int (i) = -1;
	if (cmd[0] == '/' && check_cmd_path(cmd) == 1)
		return (cmd);
	allpath = ft_split(getenv_path("PATH", env), ':');
	s_cmd = ft_split(cmd, ' ');
	while (allpath[++i])
	{
		data->path_part = ft_strjoin(allpath[i], "/");
		exec = ft_strjoin(data->path_part, s_cmd[0]);
		free(data->path_part);
		if (access(exec, F_OK | X_OK) == 0)
		{
			exec[ft_strlen(exec)] = '\0';
			return (ft_free_tab(s_cmd), exec);
		}
		free(exec);
	}
	ft_free_tab(allpath);
	ft_free_tab(s_cmd);
	printf("%s: command not found\n", cmd);
	return (NULL);
}

char	*getenv_path(char *name, char **env)
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

void	ft_free_tab(char **tab)
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

int	ft_tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

int	token_size(t_token *lst)
{
	size_t	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}