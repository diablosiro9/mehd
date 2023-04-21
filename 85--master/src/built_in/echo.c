/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dojannin <dojannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 21:21:13 by imac21            #+#    #+#             */
/*   Updated: 2023/04/19 16:05:22 by dojannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/include.h"


int	ft_isquote(int c)
{
	if (c == '"' || c == 39)
		return (1);
	return (0);
}

int	ft_isequal(int c)
{
	if (c == '=')
		return (1);
	return (0);
}

int	ft_iswspace(char c)
{
	while (c == ' ' || c == '\f' || c == '\n'
		|| c == '\r' || c == '\t' || c == '\v')
		return (1);
	return (0);
}

void	help_echo(t_token *tmp, size_t *i, int *flag)
{
	if (tmp->value == NULL)
		return ;
	if (ft_strlen(tmp->value) == 3 && tmp->value[ft_strlen(tmp->value) - 1] == ' ')
	{
		if (tmp->next)
			tmp = tmp->next;
		else
		{
			*flag = 2;
			return ;
		}
		*flag = -1;
	}
	if (ft_strlen(tmp->value) > 3)
		return ;
	while (!ft_strncmp(tmp->value, "-n", ft_strlen("-n")))
	{
		if (tmp->next)
			tmp = tmp->next;
		else
		{
			*flag = 2;
			return ;
		}
		*flag = -1;
		while (g_data.cmd[*i] && ft_iswspace(g_data.cmd[*i]) != 1)
			*i += 1;
		while (g_data.cmd[*i] && ft_iswspace(g_data.cmd[*i]) == 1)
			*i += 1;
	}
}

int	echo_dollar(t_token **tmp)
{
	char	*stock = NULL;
	char	*test = NULL;
	int		i = 0;

	if ((*tmp)->t_type == 4)
	{
		stock = (*tmp)->value;
		if (stock[1] == '$' && stock[2] == '?')
		{
			printf("LA\n");
		}
		if (stock[1] == '$')
		{
			test = search_env_content_do(g_data.env, &stock[2]);
			if (test == NULL)
				return (0);
			return (1);
		}
		if (stock[i] == '"')
		{
			while (stock[i] == '"')
				i++;
			test = search_env_content_do(g_data.env, &stock[i]);
			if (test == NULL)
				return (0);
			return (1);
		}
	}
	return (0);
}

int	case_quote(char *cmd, t_token **tmp, size_t *i, int redir)
{
	char	*stock = NULL;
	// char	*rest = NULL;
	int		flag = 0;
	int		stop = 0;
	int		j = 0;
	int		delim = ft_strlen((*tmp)->value) - 1;
	
	(void)cmd;
	if ((*tmp)->t_type == 4 || (*tmp)->t_type == 5)
	{
		stock = (*tmp)->value;
		if ((*tmp)->t_type == 4)
		{
			while (delim > 0 && (stock[delim] == '\'' || stock[delim] == '"'))
				delim--;
			if (stock[delim + 1] == '\'')
				delim--;
			while (stock[j])
			{
				if (stock[j] == '$')
				{
					// rest = ft_substr(stock, delim + 1, ft_strlen(stock) - 4);
					flag = 2;
					stock = search_env_content_do(g_data.env, ft_substr(stock, j, delim));
					if (stock == NULL)
						break ;
					// 	return (1);
					flag = 2;
				}
				j++;
			}
		}
		j = 0;
		if (flag != 2)
		{
			stock = &(*tmp)->value[1];
			flag = ft_strlen((*tmp)->value);
			while (flag != 0 && (stock[flag - 1] != '\'' && stock[flag - 1] != '"'))
				flag--;
			if (flag == (int)ft_strlen((*tmp)->value))
				stock[flag] = '\0';
			stock[flag - 1] = '\0';
		}
		if (flag == 2)
		{
			cmd = (*tmp)->value;
			while (cmd[j] == '"')
				j++;
			while (cmd[j] != '$')
			{
				ft_putchar_fd(cmd[j], redir);
				j++;
			}
			if (cmd[j] == '$')
				j++;
			while (cmd[j] >= 65 && cmd[j] <= 90)
				j++;
		}
		if (stock != NULL)
		{
			ft_putstr_fd(stock, redir);
			while (cmd[j] >= 65 && cmd[j] <= 90)
				j++;
			while (cmd[j] != '\0' && cmd[j] != '"')
			{
				ft_putchar_fd(cmd[j++], redir);
			}
			stop = 1;
			if ((*tmp)->next)
				(*tmp) = (*tmp)->next;
			*i = *i + 1;
		}
	}
	if (stop != 1)
	{
		// printf("toin\n");
		// ft_putstr_fd((*tmp)->value, redir);
	}
	if ((*tmp)->next)
		(*tmp) = (*tmp)->next;
	else
		return (1);
	return (0);
}

int	case_squote(char *cmd, t_token **tmp, size_t *i, int redir)
{
	char	*stock = NULL;
	// char	*rest = NULL;
	// int		flag = 0;
	int		stop = 0;
	int		j = 0;
	int		delim = ft_strlen((*tmp)->value) - 1;
	
	(void)cmd;
	if ((*tmp)->t_type == 5)
	{
		stock = (*tmp)->value;
		if ((*tmp)->t_type == 5)
		{
			while (delim > 0 && stock[delim] == '\'')
				delim--;
			if (stock[delim + 1] == '\'')
				delim--;
			stock = ft_strsub(stock, 1, delim + 1);
		}
		j = 0;
		if (stock != NULL)
		{
			ft_putstr_fd(stock, redir);
			stop = 1;
			*i = *i + 1;
		}
	}
	if ((*tmp)->next)
		(*tmp) = (*tmp)->next;
	else
		return (1);
	return (0);
}

int	case_option(char *cmd, t_token **tmp, size_t *i, int redir)
{
	int		idx;
	char	*stock;

	idx = 0;
	stock = (*tmp)->value;
	(void)i;
	(void)cmd;
	if (ft_strlen(stock) >= 2)
	{
		if (stock[idx] == '-')
			idx++;
		while (stock[idx])
		{
			if (stock[idx] != 'n')
			{
				ft_putstr_fd((*tmp)->value, redir);
			}
			idx++;
		}
	}
	return (1);
}

int	case_string(char *cmd, t_token **tmp, size_t *i, int redir)
{
	int	idx = 0;
	// printf("entre case string\n");
	while ((*tmp)->value[idx] && ft_iswspace((*tmp)->value[idx]) != 1)
		ft_putchar_fd((*tmp)->value[idx++], redir);
	if ((*tmp)->next)
		(*tmp) = (*tmp)->next;
	else
		return (1);
	while (cmd[*i] && ft_isquote(cmd[*i]) != 1 && ft_iswspace(cmd[*i]) != 1
		&& ft_isprint(cmd[*i]) > 1 && cmd[*i] != '=')
		*i += 1;
	if (cmd[*i] == '=')
		*i += 1;
	return (0);
}

int	main_echo(char *cmd, t_token **tmp, size_t *i, int redir, int *flag)
{
	int	f_round = 0;
	if (*flag == -1)
		(*tmp) = (*tmp)->next;
	while ((*tmp))
	{
		if (ft_strcmp(cmd, "echo $?") == 0)
		{
			printf("echo $? = %d\n", g_data.exit);
			return (0);
		}
		if ((*tmp)->t_type == 4)
		{
			if (case_quote(cmd, tmp, i, redir) == 1)
				return (1);
		}
		else if ((*tmp)->t_type == 5)
		{
			if (case_squote(cmd, tmp, i, redir) == 1)
				return (1);
		}
		else if ((*tmp)->t_type == 7)
		{
			if (case_option(cmd, tmp, i, redir) == 1)
				return (1);
		}
		else if ((*tmp)->t_type == 3 && (*tmp)->t_type != 4 && (*tmp)->t_type != 5)
		{
			if (f_round != 0)
			// if ((*tmp)->t_type != 7)
				ft_putchar_fd(' ', redir);
			if (case_string(cmd, tmp, i, redir) == 1)
				return (1);
		}
		else if (((*tmp)->t_type == 8 || (*tmp)->t_type == 6) && (*tmp)->t_type != 4 && (*tmp)->t_type != 5)
		{
			if (case_string(cmd, tmp, i, redir) == 1)
				return (1);
		}
		f_round = 1;
        // printf("milieu loop\n");
    }
	// if ((*tmp)->t_type == 6
	return (0);
}

int	ft_echo(int redir)
{
	t_token 	*tmp;
	char		*cmd;
	size_t			i;
	int			flag;

	flag = 1;
	i = 0;
	tmp = g_data.token;
    cmd = g_data.cmd;
	if (redir == -1)
		redir = 1;
    while (i < ft_strlen("echo"))
		i += 1;
	if (tmp->next)
		tmp = tmp->next;
	else
	{
		flag = 1;
		ft_putchar_fd('\n', redir);
		return (1);
	}
	help_echo(tmp, &i, &flag);
	if (flag == 2)
		return (1);
	main_echo(cmd, &tmp, &i, redir, &flag);
	if (flag == 1)
		ft_putchar_fd('\n', redir);
	return (1);
}
