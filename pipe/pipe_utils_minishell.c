/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils_minishell.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:57:43 by marvin            #+#    #+#             */
/*   Updated: 2024/06/26 17:57:43 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	check_open_file(t_pipedata *data, int argc, char **av)
{
	if (data->NoOut == 0)
	{
		open_outfile(data, argc, av);
		close(data->fd_outfile);
	}
	if (data->NoIn == 0)
	{
		data->fd_infile = open(av[1], O_RDONLY);
		if (data->fd_infile == -1)
		{
			exit_err(data, 1, "No such file or directory");
			return (1);
		}
		close(data->fd_infile);
	}
	return (0);
}