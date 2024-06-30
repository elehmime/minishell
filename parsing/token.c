/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 17:23:14 by farouk            #+#    #+#             */
/*   Updated: 2024/06/27 00:41:36 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int r;

char    *ft_strdup1(char *src)
{
    int     i;
    int     j;
    char    *dest;

    i = 0;
    j = 0;
    dest = malloc((ft_strlen(src) + 1) * sizeof(char));
    if (!dest)
        return (NULL);
    while (src[j])
    {
        if (src[0] == 32 && i == 0)
            j++;
        dest[i] = src[j];
        i++;
        j++;
    }
    if (dest[i - 1] == 32)
        dest[i - 1] = '\0';
    dest[i] = '\0';
    return (dest);
}

t_token *new_token(char *word, int type)
{
    t_token *new;
    (void)type;
    new = (t_token *)malloc(sizeof(t_token));
    if (!new)
        return (NULL);
    new->word = ft_strdup1(word);
    if (r > 0)
    {
        new->type = r;
        r = 0;
    }
    else
        new->type = type_define(word);
    new->prev = NULL;
    new->next = NULL;
    return (new);
}

int    check_word(char *words)
{
    int i;

    i = 0;
    while (words[i])
    {
        if (words[i] == '>')
        {
            if (words[i + 1] == '>')
                return(r = 3);
            return(r = 2);
        }
        if (words[i] == '<')
        {
            if (words[i + 1] == '<')
                return(r = 5);
            return(r = 4);
        }
        i++;
    }
    return (0);
}


int loop_creat_word(char *str, t_token **current)
{
    t_token *new;

    if (check_word(str))
        return(0);
    new = new_token(str, 0);
    if (!new)
        return (-1);
    (*current)->next = new;
    new->prev = *current;
    *current = new;
    return (0);
}


t_token *create_token_list(char **words)
{
    t_token *head;
    t_token *current;
    int i;

    if (!words || !words[0])
        return (NULL);
    i = 0;
    if (check_word(words[i]))
        i++;
    head = new_token(words[i], 0); // Initialise le premier maillon
    i++;
    if (!head)
        return (NULL);
    current = head;
    r = 0;
    while (words[i])
    {
        if (loop_creat_word(words[i], &current) < 0)
            return (NULL);
        i++;

    }
    return (head);
}

void print_token_list(t_token *head)
{
    t_token *current = head;

    while (current)
    {
        printf("Word: [%s], Type: [%d]\n", current->word, current->type);
        current = current->next;
    }
}
