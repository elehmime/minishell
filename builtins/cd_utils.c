/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:29:04 by marvin            #+#    #+#             */
/*   Updated: 2024/05/27 14:29:04 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strcpy_oldpwd(char *src)
{
	int		i;
	int		j;
	char	*dest;

	i = 3;
	j = 0;
	dest = malloc(sizeof(char) * (ft_strlen(src) + 4));
	dest[0] = 'O';
	dest[1] = 'L';
	dest[2] = 'D';
	while (src[j])
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strcpy_pwd(char *src, char *dest)
{
	int	i;
	int	j;

	i = 4;
	j = 0;
	dest = malloc(sizeof(char) * (ft_strlen(src) + 5));
	dest[0] = 'P';
	dest[1] = 'W';
	dest[2] = 'D';
	dest[3] = '=';
	while (src[j])
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}

int		search_pwd(t_data *data, int n)
{
	int		i;
	
	i = 0;
	if(n == 0)
	{
		while (data->env_maj[i])
		{
			if (data->env_maj[i][0] == 'P' && data->env_maj[i][1] == 'W' && data->env_maj[i][2] == 'D')
				return (i);
			i++;
		}
		return (0);
	}
	else
	{
		while (data->env_maj[i])
		{
			if (data->env_maj[i][0] == 'O' && data->env_maj[i][1] == 'L' && data->env_maj[i][2] == 'D')
				return (i);
			i++;
		}
		return (0);
	}
}