/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dojannin <dojannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:19:11 by dojannin          #+#    #+#             */
/*   Updated: 2023/04/20 14:48:32 by dojannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/include.h"

int	token_size(void)
{
	t_data	ptr;
	int		i;

	i = 0;
	ptr = g_data;
	if (g_data.token)
	{
		while (g_data.token)
		{
			i++;
			g_data.token = g_data.token->next;
		}
	}
	g_data = ptr;
	return (i);
}

void	*checking_solo_name(t_token *tmp)
{
	if (token_size() == 1)
	{
		if (tmp->t_type == 4 || tmp->t_type == 5 || tmp->t_type == 6
			|| tmp->t_type == 1 || tmp->t_type == 2)
		{
			if (ft_strlen(tmp->value) < 2)
			{
				if (tmp->t_type == 6)
				{
					printf("lui\n");
					printf("minishell: $: command not found\n");
				}
				else if (tmp->t_type == 1 || tmp->t_type == 2)
					printf("minishell: syntax error near\
unexpected token 'newline'\n");
				return (NULL);
			}
		}
	}
	return (tmp);
}

void	*solo_command(void)
{
	t_token	*tmp;

	tmp = g_data.token;
	if (token_size() == 1 && tmp->t_type != 3)
	{
		if (checking_solo_name(tmp) == NULL)
			return (NULL);
		g_data.token = tmp;
	}
	return ((void *)g_data.token->value);
}

void	*manage_double(void)
{
	t_token	*tmp;

	tmp = g_data.token;
	if (token_size() > 1)
	{
		while (tmp)
		{
			if (tmp->t_type == 0 && tmp->next == NULL)
			{
				printf("minishell: Mehdi voulait\
un message d'erreur pour une '|' sans destination.\n");
				return (NULL);
			}
			if (tmp->t_type == 0 && tmp->next->t_type == 0)
			{
				printf("minishell: syntax error near unexpected token '|'\n");
				return (NULL);
			}
			tmp = tmp->next;
		}
	}
	return ((void *)g_data.token->value);
}

t_list	*token_to_list(void)
{
	t_list	*tmp;
	t_token	*stck;
	char	*stock;

	stck = g_data.token;
	tmp = NULL;
	stock = NULL;
	while (stck)
	{
		stock = ft_strdup(stck->value);
		printf("Stck->value = %s\n", stck->value);
		ft_lstadd(&tmp, ft_lstnew(stock));
		stck = stck->next;
	}
	return (tmp);
}

t_list	*ft_parsor(t_list *str)
{
	t_list	*res;

	res = NULL;
	printf("res == %s\n", str->content);
	afflist(str, "what\n");
	afftoken(g_data.token, "parsor");
	printf("fin\n");
	if (find_all_dollars() == NULL)
		return (NULL);
	if (solo_command() == NULL)
		return (NULL);
	else if (manage_double() == NULL)
		return (NULL);
	printf("tes lla en faite\n");
	afftoken(g_data.token, "parsor2");
	split_cmd_file(NULL);
	afftoken(g_data.token, "parsor3");
	res = token_to_list();
	afftoken(g_data.token, "nu");
	return (res);
}
