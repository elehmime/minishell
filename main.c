/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ellehmim <ellehmim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 11:43:52 by ellehmim          #+#    #+#             */
/*   Updated: 2024/06/11 11:43:52 by ellehmim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

/*1 = pipe
2 = >
3 = >>
4 = <
5 = <<
0 = comande classique*/

// voir pour les redirection comme cat < prenom.txt > aaa 
// voir avec farouk pour le sig_management pdt les prompt comme here_doc
// faire le exit
// regler toutes les erreur valgrind
// faire $?

void	check_to_send(t_data *data, char **env)
{
	t_pipex	pipex;

	data->redirout = 0;
	data->redirin = 0;
	data->continue_while = 0;
	if (if_pipex(data, data->token, &pipex) == YES)
		return ;
	while(data->token)
	{
		check_redirection_in(data);
		check_redirection_out(data);
		if (data->token->type == 0)
		{
			if (exec_cmd(data, env) != 2)
				waitpid(data->pid, NULL, 0);
		}
		reset_redir(data);
		if (data->continue_while == NO)
				break;
		if(data->token->next)
			data->token = data->token->next;
	}
}

int body(char *line, char **env, t_data *data)
{
	if (parsing(line, env, data))
		return (1);
	print_token_list(data->token);
	if (line[0] != '\0')
		add_history(line);
	check_to_send(data, env);
	free(line);
	free_token_list(data->token);
	return (0);
}

int	minishell_start(t_data *data, char **env)
{
    char *line;
	
    print_welcome();
	signal(SIGINT, sig_management);
	signal(SIGQUIT, sig_management);
    while (1)
	{
		line = readline("Minishell $");
		if (!line)
			break ;
		if (!*line)
			continue ;
		if (body(line, env, data))
			printf("erreur syntax\n");
    }
    return (0);
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	t_data	data;

	env_cpy(&data, env);
	minishell_start(&data, env);
	return (0);
}