/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dojannin <dojannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 15:04:10 by dojannin          #+#    #+#             */
/*   Updated: 2023/04/21 20:50:06 by dojannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/include.h"

/*
    Mimi
    Déplacement de la fonction lexer dans le dossier/.c dédié ./src/lexer/lexer.c
    simplement par claireté et norme

*/


t_token	*recuperator(void)
{
	t_token	*tmp;

	tmp = g_data.token;
	while (tmp)
	{
		if (tmp->t_type == 9)
		{
			if (tmp->next && tmp->next->t_type == 3)
				tmp->next->t_type = 10;
		}
		tmp = tmp->next;
	}
	return (NULL);
}


t_token	*modificator(void)
{
	//TRANSFORME LES WORD EN EOF SI PRESENCE HERE_DOC PREALABLE
	t_token	*tmp;

	tmp = g_data.token;
	while (tmp)
	{
		if (tmp->t_type == 9)
		{
			if (tmp->next)
			{
				if (tmp->next->t_type != 0 && tmp->next->t_type != 1
					&& tmp->next->t_type != 2 && tmp->next->t_type != 9)
					tmp->next->t_type = 10;
			}
		}
		tmp = tmp->next;
	}
	return (NULL);
}

void	destroyer(int start, int i)
{
	//DETRUIT LES TOKENS ENTRE START ET I
	t_token *tmp;
	int		compare;

	tmp = g_data.token;
	compare = 0;
	while (compare < i)
	{
		if (compare >= start && compare < i)	
		{
			tmp = delete_token(tmp, compare);
			compare = compare - 1;
			i = i - 1;
			start = start - 1;
		}
		compare++;
	}
	g_data.token = tmp;
}

int	det_squote(char *str)
{
	int	i;
	int	stock;
	int	res;
	int	flag;

	(norm(), i = 0, stock = 0, res = 0, flag = 0);
	while (str[i])
	{
		if (str[i] == '"' && flag == 1)
			flag = 0;
		if (str[i] == '"')
			flag = 1;
		if (str[i] == '\'' && flag != 1)
			return (1);
		i++;
	}
	return (0);
}

int 	det_dquote(char *str)
{
	int	i;
	int	stock;
	int	res;
	int	flag;

	printf("entre dquote\n");
	(norm(), i = 0, stock = 0, res = 0, flag = 0);
	while (str[i])
	{
		if (str[i] == '\'' && flag == 1)
			flag = 0;
		if (str[i] == '\'')
			flag = 1;
		if (str[i] == '"' && flag != 1)
			return (1);
		i++;
	}
	return (0);
}

void	case_dquote(t_token *tmp, char *stock, char *res, int start, int i, int j, int pos)
{
	char	*rest;
	
	rest = NULL;
	stock = tmp->value;
	(void)start;
	printf("stock dans dquote = %s\n", stock);
	printf("i = %d\n", i);
	while (stock[i] && stock[i] != '"')
		i++;
	if (stock[i + 1])
		i = i + 1;
	j = i;
	printf("1\n");
	while (stock[j] && stock[j] != '"')
		j++;
	printf("2\n");
	if (j == (int)ft_strlen(stock))
		res = ft_strjoin(ft_strsub(stock, 0, i - 1), ft_strsub(stock, i, j));
	else
	{
		if (j + 1 == (int)ft_strlen(stock))
			res = ft_strjoin(ft_strsub(stock, 0, i - 1), ft_strsub(stock, i, j - i));
		else
			res = ft_strjoin(ft_strsub(stock, 0, i - 1), ft_strsub(stock, i, j - 2));
	}
	if (res[ft_strlen(res) - 1] == '"')
	{
		printf("4\n");
		j = j + 1;
		if (res[ft_strlen(res) - 1] == '"')
			rest = ft_strsub(res, 0, ft_strlen(res) - 1);
		else
			rest = ft_strjoin(res, ft_strsub(stock, j, ft_strlen(stock) - j));
	}
	if (rest != NULL)
	{
		if (pos == 0)
			ft_token_addf(&g_data.token, ft_token_new(WORD, rest));
		else
			ft_token_add(&g_data.token, ft_token_new(WORD, rest));
		tmp = g_data.token;
	}
	else
	{
		if (pos == 0)
			ft_token_addf(&g_data.token, ft_token_new(WORD, res));
		else
			ft_token_add(&g_data.token, ft_token_new(WORD, res));
		tmp = g_data.token;
	}
	if (pos == 0)
		delete_token(g_data.token, pos + 1);
	else
		delete_token(g_data.token, pos);
	return ;
	// printf("b\n");
	// char	*rest;

	// rest = NULL;
	// stock = tmp->value;
	// while (stock[i] && stock[i] != '"')
	// 	i++;
	// if (stock[i + 1])
	// 	i = i + 1;
	// j = i;
	// while (stock[j] && stock[j] != '"')
	// 	j++;
	// // res = ft_strsub(stock, 0, i);
	// printf("ft_strsub(stock, 0, i) = %s\n", ft_strsub(stock, 0, i - 1));
	// printf("ft_strsub(stock, i, j)) = %s\n", ft_strsub(stock, i, j - 2));
	// res = ft_strjoin(ft_strsub(stock, 0, i - 1), ft_strsub(stock, i, j - 2));
	// if (stock[j] != '\0')
	// {
	// 	rest = ft_strjoin(res, ft_strsub(stock, j + 1, ft_strlen(stock) - 1));
	// 	printf("resttt = %s\n", rest);
	// }
	// printf("c\n");
	// printf("res touplait = %s\n", res);
	// printf("pos = %d\n", pos);
	// if (start == 0)
	// 	ft_token_addf(&g_data.token, ft_token_new(WORD, res));
	// else
	// 	ft_token_add(&g_data.token, ft_token_new(WORD, res));
	// tmp = g_data.token;
	// if (pos == 0)
	// 	delete_token(g_data.token, pos + 1);
	// else
	// 	delete_token(g_data.token, pos);
	// return ;
}

void	case_squote_term(t_token *tmp, char *stock, char *res, int start, int i, int j, int pos)
{
	char	*rest;

	rest = NULL;
	stock = tmp->value;
	(void)start;
	printf("s_Quote = %s\n", tmp->value);
	printf("i = %d\n", i);
	// i = 0;
	// j = 0;
	while (stock[i] && stock[i] != '\'')
		i++;
	if (stock[i + 1])
		i = i + 1;
	j = i;
	printf("j %d\n", j);
	while (stock[j] && stock[j] != '\'')
		j++;
	// if (j == (int)ft_strlen(stock)
	if (j == (int)ft_strlen(stock))
		res = ft_strjoin(ft_strsub(stock, 0, i - 1), ft_strsub(stock, i, j));
	else
	{
		if (j + 1 == (int)ft_strlen(stock))
			res = ft_strjoin(ft_strsub(stock, 0, i - 1), ft_strsub(stock, i, j - i));
		else
			res = ft_strjoin(ft_strsub(stock, 0, i - 1), ft_strsub(stock, i, j - 2));
	}
	if (res[ft_strlen(res) - 1] == '\'')
	{
		j = j + 1;
		if (res[ft_strlen(res) - 1] == '\'')
			rest = ft_strsub(res, 0, ft_strlen(res) - 1);
		else
			rest = ft_strjoin(res, ft_strsub(stock, j, ft_strlen(stock) - j));
	}
	if (rest != NULL)
	{
		if (pos == 0)
			ft_token_addf(&g_data.token, ft_token_new(WORD, rest));
		else
			ft_token_add(&g_data.token, ft_token_new(WORD, rest));
		tmp = g_data.token;
	}
	else
	{
		if (pos == 0)
			ft_token_addf(&g_data.token, ft_token_new(WORD, res));
		else
			ft_token_add(&g_data.token, ft_token_new(WORD, res));
		tmp = g_data.token;
	}
	if (pos == 0)
		delete_token(g_data.token, pos + 1);
	else
		delete_token(g_data.token, pos);
	return ;
}

int	other_term(t_token *tmp, char *stock, char *res, int start, int i, int j, int pos)
{
	if (det_squote(tmp->value) == 1 || det_dquote(tmp->value) == 1)
	{
		if (det_dquote(tmp->value) == 1)
			case_dquote(tmp, stock, res, start, i, j, pos);
		else if (det_squote(tmp->value) == 1)
			case_squote_term(tmp, stock, res, start, i, j, pos);
		return (1);
	}
	if (!tmp->next)
		return (0);
	else
	{
		printf("la\n");
		tmp = tmp->next;
		pos++;
		return (2);
	}
}

void	split_res_main( t_token *tmp, char *res, char *stock, int i)
{
	printf("res = |%s|\n", res);
	if (res[0] == '-')
	{
		printf("yeepp\n");
		ft_token_add(&g_data.token, ft_token_new(OPTION, res));
		afftoken(g_data.token, "lui");
	}
	else
	{
		while (res[i] != '-' && res[i])
			i++;
		if (i != (int)ft_strlen(res))
		{
			printf("on a det un truc\n");
			stock = ft_strsub(res, 0, i);
			printf("stock = %s\n", stock);
			ft_token_addf(&g_data.token, ft_token_new(WORD, stock));
			stock = ft_strsub(res, i, ft_strlen(res) - 1);
			ft_token_add(&g_data.token, ft_token_new(WORD, stock));
		}
		else
		{
			printf("WSSSHH\n");
			ft_token_addf(&g_data.token, ft_token_new(WORD, res));
			printf("Sprs\n");
		}
	}
	tmp = g_data.token;
	return ;
}

char	*help_some_quotes(t_token *tmp, char *res, int *i)
{
	printf("yes\n");
	char	*stock;

	stock = tmp->value;
	while (((ft_strlen(tmp->value) == 3) || (ft_strlen(tmp->value) == 1 && tmp->t_type == 3)
		|| (stock[ft_strlen(stock) - 1] != '\'' && tmp->t_type == 4)) && tmp)
	{
		*i = *i + 1;
		printf("la\n");
		if (tmp->next)
			tmp = tmp->next;
		else
			break ;
		stock = tmp->value;

	}
	res = malloc(sizeof(char) * (*i + 1));
	printf("la2\n");
	tmp = g_data.token;
	while (tmp && ((ft_strlen(tmp->value) != 3 && tmp->t_type != 4 && tmp->t_type != 5)
		&& (ft_strlen(tmp->value) != 1 || tmp->t_type != 3)))
		tmp = tmp->next;
	printf("la333\n");
	*i = 0;
	printf("tmp - > value = %s\n", tmp->value);
	while (((ft_strlen(tmp->value) == 3) || (ft_strlen(tmp->value) == 1 && tmp->t_type == 3)
		|| (stock[ft_strlen(stock) - 1] != '\'' && tmp->t_type == 5)) && tmp)
	{
		if (ft_strlen(tmp->value) == 1 && tmp->t_type == 3)
		{
			res[*i] = tmp->value[0];
		}
		else
			res[*i] = tmp->value[1];
		*i = *i + 1;
		if (tmp->next == NULL)
			break ;
		tmp = tmp->next;
	}
	res[*i] = '\0';
	printf("la333\n");
	return (res);
}

void	some_quotes(t_token *tmp, char *stock, char *res, int start, int i)
{
	char	*tricky;

	tricky = NULL;
	printf("main_case\n");
	// if (ft_strlen(tmp->value) == 3)
	// {
		if (start == 0)
			start = i;
		res = help_some_quotes(tmp, res, &i);
		printf("i = %d\n", i);
		printf("Start = %d\n", start);
	
	//	RAJOUTER LA DESTRUCTION DES AUTRES
		if (ft_strlen(res) == 1 && res[0] == '-')
		{
			if (tmp->next)
			{
				tricky = ft_strjoin(res, tmp->next->value);
				i++;
			}
		}
		afftoken(g_data.token, "la\n");
		if (start == 0)
		{
			printf("tu te fais avoir\n");
			destroyer(start, i);
		}
		destroyer(start, i + 1);
		printf("RESSSSS = %s\n", res);
		printf("i = %d\n", start);
		i = 0;
		printf("res stp = %s\n", res);
		printf("tricky = %s\n", tricky);
		if (tricky != NULL)
		{
			printf("laaa\n");
			split_res_main(tmp, tricky, stock, i);
		}
		else
			split_res_main(tmp, res, stock, i);
	// }
	printf("finito\n");
}

t_token	*terminator(void)
{
	t_token	*tmp;
	char	*res;
	char	*stock;
	int		i;
	int		start;
	int		j;
	int		pos;
	

	j = 0;
	i = 0;
	pos = 0;
	start = 0;
	stock = NULL;
	tmp = g_data.token;
	res = NULL;
	while (tmp)
	{
		printf("DET_QUOTTe(tmp) = %d\n", det_squote(tmp->value));
		printf("t_type = %d\n", tmp->t_type);
		if (tmp->t_type != 4 && tmp->t_type != 5)
		{
			printf("entre\n");
			printf("tmp->value - %s\n", tmp->value);
			if (other_term(tmp, stock, res, start, i, j, pos) == 0)
				break ;
			// if (help_terminator(tmp, stock, res, start, i, j, pos) != 2)
				tmp = g_data.token;
			// i = i - 1;
		}
		else if (tmp->t_type == 4 || tmp->t_type == 5)
		{
			printf("tmp->t_typr = %s\n", tmp->value);
			printf("ft_strlen(tmp->value) = %zu\n", ft_strlen(tmp->value));
			some_quotes(tmp, stock, res, start, i);
			printf("et sortido\n");
			tmp = g_data.token;
			// i = i - 1;
		}
		if (tmp->next)
			tmp = tmp->next;
		else
			return (g_data.token);
		char c;
		read(0, &c, 1);
		pos++;
		i++;
	}
	return (g_data.token);
}

t_token	*reunificator()
{
	t_token	*tmp;
	char	*stock = NULL;
	int		i;
	int		start;
	char	*res;

	res = NULL;
	i = 0;
	start = 0;
	tmp = g_data.token;
	while (tmp)
	{
		stock = tmp->value;
		if (ft_strlen(stock) == 1 && tmp->value[0] == '-')
		{
			tmp = tmp->next;
			stock = tmp->value;
			while (stock[i])
				i++;
			res = malloc(sizeof(char) * i + 2);
			i = 0;
			res[0] = '-';
			while (stock[i])
			{
				res[i + 1] = stock[i];
				i++;
			}
			res[i + 1] = '\0';
			tmp = g_data.token;
			while (tmp)
			{
				if (ft_strlen(tmp->value) == 1 && tmp->value[0] == '-')
				{	
					destroyer(start, i + 1);
					tmp = g_data.token;
				}
				if (!tmp && !tmp->next)
					break;
				tmp = tmp->next;
				i++;
			}
			ft_token_add(&g_data.token, ft_token_new(OPTION, res));
		}
		if (!tmp || !tmp->next || tmp->next == NULL)
			break ;
		tmp = tmp->next;
		start++;
	}
	return (g_data.token);
}

void	ft_tab_delete(char **tab)
{
	// char	*tmp;
	int		i;

	i = 0;
	while (tab[i] != NULL)
	{
		// printf("tab[i] = %s\n", tab[i]);
		// tmp = tab[i];
		// tab[i] = tab[i + 1];
		free(tab[i]);
		i++;
	}
	free(tab);
}


t_list	*ft_lexer(char *str)
{
	int		i;
	t_list	*list;
	char	**tab;

	i = 0;
	list = NULL;
	printf("al\n");
	tab = ft_split(str);
	printf("al\n");

	printf("tab[0] = %s\n", tab[0]);
	if (!tab || tab[0] == NULL)
	{
		// printf("Error : malloc failed() in ft_lexer.\na");
		return (NULL);
	}
	while (tab[i])
	{
		ft_lstadd(&list, ft_lstnew(tab[i]));
		i++;
	}
	afflist(list, "lexer");
	tokenizateur(list);
	recuperator();
	modificator();
	afflist(list, "lexer");
	if (terminator() == NULL)
		return (NULL);
	// if (reunificator() == NULL)
	// 	return (NULL);
	free(tab);
	printf("fin lexer\n");
	afftoken(g_data.token, "fin kexer");
	return (list);
}
