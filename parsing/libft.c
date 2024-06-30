/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 16:03:56 by ellehmim          #+#    #+#             */
/*   Updated: 2024/06/10 13:55:53 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strdup(const char *src)
{
	size_t	i;
	char	*dest;

	i = 0;
	dest = malloc((ft_strlen1(src) + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

#include <stdlib.h>

char *ft_strcpy(char *dest, const char *src)
{
    char *temp;

    temp = dest;
    while ((*dest++ = *src++) != '\0');
    return (temp);
}

char *ft_strcat(char *dest, const char *src)
{
    char *temp;

    temp = dest;
    while (*dest)
        dest++;
    while ((*dest++ = *src++) != '\0');
    return (temp);
}
