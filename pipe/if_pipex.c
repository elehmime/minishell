/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 22:25:15 by marvin            #+#    #+#             */
/*   Updated: 2024/06/17 22:25:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// < prenom.txt cat | grep F | grep V > a
// pipex de base ./pipex file1 cmd1 cmd2 cmd3 file2 == < file1 cmd1 | cmd2 | cmd3 ... | cmdn > file2
// heredoc  ./pipex here_doc LIMITER cmd cmd1 file == cmd << LIMITER | cmd1 >> file

void print_tab(char **tab)
{
    int i = 0;
    while (tab[i])
    {
        printf("cmd[%d] = %s\n", i, tab[i]);
        i++;
    }
}

int check_pipex_value(t_pipex *pipex)
{
    if (pipex->pipe_count < 1)
        return (NO);
    if (pipex->cmd_count < 2)
        return (NO);
    if (!pipex->cmd[1] || pipex->cmd[1][0] == '\0')
        pipex->cmd[1] = ft_strdup("NoIn");
    pipex->cmd[pipex->cmd_count] = ft_strdup(pipex->out);
    return (YES);
}

void    ft_free_pipe(t_pipex *pipex)
{
    ft_free_tab(pipex->cmd);
    free(pipex->out);
}

void while_ifpipex(t_token *token, t_pipex *pipex)
{
    while (token)
    {
        if (token->type == 1)
            pipex->pipe_count++;
        if (token->type == 0)
        {
            pipex->cmd[pipex->cmd_count] = ft_strdup(token->word);
            if (token->next)
            {
                while (token->next && token->next->type == 0)
                {
                    char *temp = pipex->cmd[pipex->cmd_count];
                    pipex->cmd[pipex->cmd_count] = ft_strjoin(pipex->cmd[pipex->cmd_count], " ");
                    free(temp);
                    temp = pipex->cmd[pipex->cmd_count];
                    pipex->cmd[pipex->cmd_count] = ft_strjoin(pipex->cmd[pipex->cmd_count], token->next->word);
                    free(temp);
                    token = token->next;
                }
            }
            pipex->cmd_count++;
        }
        if (token->type == 4) // in
            pipex->cmd[1] = ft_strdup(token->word);
        if (token->type == 5) // in heredoc
        {
            pipex->cmd[1] = ft_strdup("here_doc");
            pipex->cmd[2] = ft_strdup(token->word);
        }
        if (token->type == 2 || token->type == 3) // out > et >>
            pipex->out = ft_strdup(token->word);
        token = token->next;
    }
}

int count_cmd(t_token *token, t_pipex *pipex)
{
    int total_cmds = 0;
    while (token)
    {
        if (token->type == 0)
        {
            while (token->next && token->next->type == 0)
            {
                if (token->next)
                    token = token->next;
                else
                    break;
            }
            total_cmds++;
        }
        if (token->type == 5)
        {
            pipex->cmd_count++;
            total_cmds = total_cmds + 2;
        }
        token = token->next;
    }
    return (total_cmds);
}

int if_pipex(t_data *data, t_token *token, t_pipex *pipex)
{
    int total_cmds;

    pipex->cmd_count = 2;
    pipex->pipe_count = 0;
    pipex->out = NULL;
    total_cmds = count_cmd(token, pipex);
    pipex->cmd = malloc(sizeof(char *) * (total_cmds + 4)); // +4 pour "./pipex_bonus", fichier d'entrée, et NULL
    if (!pipex->cmd)
        return (NO);
    pipex->cmd[0] = ft_strdup("./pipex_bonus");
    pipex->cmd[1] = NULL;
    while_ifpipex(token, pipex);
    if (!pipex->out)
        pipex->out = ft_strdup("NoOut");
    pipex->cmd[pipex->cmd_count] = ft_strdup(pipex->out); // ajouter la sortie
    pipex->cmd[pipex->cmd_count + 1] = NULL; // NULL terminer la commande
    if (check_pipex_value(pipex) == YES)
    {
        pipex_main(ft_tablen(pipex->cmd), pipex->cmd, data->env_maj);
        ft_free_pipe(pipex);
        return (YES);
    }
    ft_free_pipe(pipex);
    return (NO);
}
