/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_tokenizateur.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dojannin <dojannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 19:06:54 by dojannin          #+#    #+#             */
/*   Updated: 2023/04/17 19:14:23 by dojannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/include.h"

t_token	*ft_token_new(int type, char *value)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (new == NULL)
		return (NULL);
	new->t_type = type;
	new->value = value;
	new->next = NULL;
	return (new);
}

t_token	*ft_token_add(t_token **alst, t_token *new)
{
	t_token	*tmp;

	tmp = *alst;
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	else
		*alst = new;
	return (new);
}

t_token	*delete_token(t_token *head, int position)
{
	int		i;
	t_token	*new_head;
	t_token	*current;
	t_token	*next_node;

	(norm(), i = 0, new_head = NULL, current = NULL, next_node = NULL);
	if (head == NULL)
		return (head);
	if (position == 0)
	{
		if (head->next)
			new_head = head->next;
		free(head);
		return (new_head);
	}
	current = head;
	while (current != NULL && i < position - 1)
	{
		current = current->next;
		i++;
	}
	if (current == NULL || current->next == NULL)
		return (head);
	next_node = current->next->next;
	free(current->next);
	current->next = next_node;
	return (head);
}

void	ft_token_addf(t_token **alst, t_token *new)
{
	if (alst == NULL || new == NULL)
		return ;
	new->next = *alst;
	*alst = new;
}

void	ft_token_delete(t_token **l)
{
	t_token	*tmp;

	tmp = (*l);
	while ((*l) != NULL)
	{
		tmp = (*l);
		(*l) = (*l)->next;
		free(tmp);
	}
	free(*l);
}
