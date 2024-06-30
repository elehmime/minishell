/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:36:52 by marvin            #+#    #+#             */
/*   Updated: 2024/05/23 11:36:52 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	env_maj_pwd(t_data *data)
{
	char	*old_pwd;
	char	newcwd[1024];
	int		i;

	i = search_pwd(data, 0);
	old_pwd = ft_strcpy_oldpwd(data->env_maj[i]);
	getcwd(newcwd, sizeof(newcwd));
	data->env_maj[i][0] = '\0';
	free(data->env_maj[i]);
	data->env_maj[i] = ft_strcpy_pwd(newcwd, data->env_maj[i]);
	i = search_pwd(data, 1);
	data->env_maj[i][0] = '\0';
	free(data->env_maj[i]);
	data->env_maj[i] = ft_strdup(old_pwd);
	free(old_pwd);
}

void	builtins_cd(int ac, t_data *data)
{
	if (ac == 1)
	{
        chdir(getenv("HOME"));
		env_maj_pwd(data);
		return ;
	}

	if (chdir(data->token->next->word) != 0)
        printf("cd: %s: No such file or directory\n", data->token->next->word);
	env_maj_pwd(data);
}
