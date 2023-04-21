/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollarz.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dojannin <dojannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:23:09 by dojannin          #+#    #+#             */
/*   Updated: 2023/04/18 13:11:02 by dojannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/include.h"

void	*find_all_dollars(void)
{
	t_token	*tmp;
	char	*cmd;
	char	*stock;

	tmp = g_data.token;
	cmd = g_data.cmd;
	stock = NULL;
	if (tmp)
	{
		while (tmp != NULL)
		{
			if (ft_strcmp(cmd, "echo $?") == 0)
				return ((void *)g_data.token->value);
			if (tmp->t_type == 6)
			{
				if (ft_strlen(tmp->value) > 1)
				
					tmp->value = search_env_content_do(g_data.env, tmp->value);
					if (tmp->value == NULL)
						tmp->value = "\n";
				else
					printf("Us_Bash: $: command not found\n");
			}
			tmp = tmp->next;
		}
	}
	return ((void *)g_data.token->value);
}
