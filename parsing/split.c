/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 16:41:15 by farouk            #+#    #+#             */
/*   Updated: 2024/06/10 13:56:09 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	skip_quotes2(char *s, int *x, int*y)
{
	int		i;
	char	c;

	i = 0;
	c = '\0';
	while (s[i])
	{
		if (*x == -1 && ft_strchr(QUOTES, s[i]))
		{
			*x = i;
			c = s[i];
			i++;
		}
		if (s[i] == c)
		{
			*y = i;
			break ;
		}
		i++;
	}
}


int	skip_quotes(char *s, int chev, int *x, int *y)
{
	int		i;

	i = 0;
	*x = -1;
	*y = -1;
	skip_quotes2(s, x, y);
	if (chev)
		while (s[i] && ft_strchr("><", s[i]))
			i++;
	else if (s[i] && ft_strchr("|", s[i]))
		i++;
	else
		while (s[i] && !ft_strchr(">< |", s[i]))
			i++;
	return (i);
}


char *ft_strcdup(char *s, int chev, int *mot)
{
	int i;
	int n;
	int x;
	int y;
	char *new;

	i = skip_quotes(s, chev, &x, &y);
	n = 0;
	new = malloc(i + 1);
	while (n < i)
	{
		if (s[n] < 0)
            s[n] = -s[n];
		new[n] = s[n];
		if (n == x || n == y)
			new[n] = 32; 		
		n++;
	}
	new[n] = '\0';
	(*mot) += i;
	return (new);
}

char **ft_separator(char *s)
{
	int i;
	int t;
	char **tab;
	
	i = 0;
	t = 0;
	tab = malloc(sizeof(char *) * (ft_count_word(s) + 1));
	if(!tab)
		return (NULL);
	while (s[i])
	{
		while (s[i] && ft_strchr(SPACES, s[i]))
			i++;
		if (!s[i])
			break ;
		tab[t++] = ft_strcdup(&s[i], ft_strchr("><", s[i]) != NULL, &i);
	}
	tab[t] = NULL;
	return tab;
}
