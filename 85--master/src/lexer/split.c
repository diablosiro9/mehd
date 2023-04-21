/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dojannin <dojannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:49:18 by dojannin          #+#    #+#             */
/*   Updated: 2023/04/21 19:21:12 by dojannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/include.h"

// Mimi - La fonction est trop trop longue, 
//faut fractionner en plusieurs fonctions

char	**tiray_case(int *tmp, int *i, int *j, char **tab, char **str)
{
	*tmp = *i;
	while (str[0][*i] != ' ' && str[0][*i] != '\t' && str[0][*i] != '\0')
		*i = *i + 1;
	if (str[0][*i] == ' ')
		*i = *i - 1;
	tab[*j] = ft_strsub(*str, *tmp, *i);
	printf("tab[j] = %s\n", tab[*j]);
	if (str[0][*i])
		*str = *str + *i;
	else
	{
		tab[*j + 1] = 0;
		printf("toi laaaaa\n");
		return (tab);
	}
	*i = 0;
	*j = *j + 1;
	return (NULL);
}

char	**dollar_case(int *i, int *j, int *tmp, char **str, char **tab)
{
	*tmp = *i;
	while (str[0][*i] != ' ' && str[0][*i] != '\0')
		*i = *i + 1;
	tab[*j] = ft_strsub(*str, *tmp, *i - 1);
	if (str[0][*i])
		*str = *str + *i;
	else
	{
		tab[*j + 1] = 0;
		return (tab);
	}
	*i = 0;
	*j = *j + 1;
	return (NULL);
}

char	**double_quote_case(int *i, int *j, int *tmp, \
	int *flag, char **str, char **tab)
{
	*tmp = *i;
	*i = *i + 1;
	printf("tmpppp = %d\n", *tmp);
	if (str[0][*tmp] == '"')
	{
		while (str[0][*i] != '"')
		{
			if (str[0][*i] == '\0')
			{
				tab[*j] = 0;
				return (tab);
			}
			*i = *i + 1;
		}
		printf("iiiiiii = %d\n", *i);
		if (*i > 2)
			tab[*j] = ft_strsub(*str, *tmp, *i);
		else
			tab[*j] = ft_strsub(*str, *tmp, *i + 1);
		*str = *str + *i + 1;
		*i = 0;
		*tmp = 0;
		*flag = 1;
		*j = *j + 1;
	}
	return (NULL);
}

char	**simple_quote_case(int *i, int *j, int *tmp, \
	int *flag, char **str, char **tab)
{
	*tmp = *i;
	*i = *i + 1;
	printf("tmpppp = %d\n", *tmp);
	if (str[0][*tmp] == '\'')
	{
		while (str[0][*i] != '\'')
		{
			if (str[0][*i] == '\0')
			{
				tab[*j] = 0;
				return (tab);
			}
			*i = *i + 1;
		}
		printf("iiiiiii = %d\n", *i);
		if (*i > 2)
			tab[*j] = ft_strsub(*str, *tmp, *i);
		else
			tab[*j] = ft_strsub(*str, *tmp, *i + 1);
		*str = *str + *i + 1;
		*i = 0;
		*tmp = 0;
		*flag = 1;
		*j = *j + 1;
	}
	return (NULL);
}

char	**others_case(int *i, int *j, int *tmp, \
	int *flag, char **str, char **tab)
{
	int	d_quote = 0;
	*tmp = *i;
	if (str[0][*i] < 0 || str[0][*i] > 127)
	{
		tab[*j] = 0;
		return (tab);
	}
	while (str[0][*i] == ' ' && str[0][*i] == '\t')
		*i = *i + 1;
	if (str[0][*i] == '\'')
		*flag = 1;
	if (str[0][*i] != ' ')
	{
		while (str[0][*i] != ' ' && str[0][*i] != '\t' && str[0][*i] != '\0')
		{
			if (str[0][*i] == '"')
				d_quote = 1;
			*i = *i + 1;
		}
		if (d_quote == 1)
		{
			while (str[0][*i] != '\0' && str[0][*i] != '"')
				*i = *i + 1;
		}
		if ((str[0][*i] == ' ' || str[0][*i] == '\t')
			&& *flag != -1 && *flag != -2)
		{
			tab[*j] = ft_strsub(*str, *tmp, *i - 1);
		}
		else
		{
			if (*tmp != *i)
				tab[*j] = ft_strsub(*str, *tmp, *i);
			else
			{
				tab[*j] = NULL;
				return (tab);
			}
		}
		if (str[0][*i])
			*str = *str + *i;
		else
		{
			*j = *j + 1;
			tab[*j] = NULL;
			return (tab);
		}
		*i = 0;
		*tmp = 0;
		*j = *j + 1;
	}
	return (NULL);
}

char	**skip_space(int *i, int *j, char **str, char **tab)
{
	while ((str[0][*i] == ' ' || str[0][*i] == '\t') && str[0][*i])
		*i = *i + 1;
	if (str[0][*i] == '\0')
	{
		tab[*j] = NULL;
		return (tab);
	}
	*str = *str + *i;
	*i = 0;
	return (NULL);
}

char	**ft_split(char *str)
{
	int		i;
	int		j;
	int		flag;
	int		tmp;
	char	**tab;

	i = 0;
	j = 0;
	tmp = 0;
	flag = -1;
	tab = (char **)malloc(sizeof(char *) * (ft_strlen(str) + 1));
	// printf("str = %s\n", str);
	while (str[i] != '\0')
	{
		if (str[i] == ' ')
		{
			if (skip_space(&i, &j, &str, tab) != NULL)
			{
				// printf("onest la\n");
				return (tab);
			}
			flag = -2;
		}
		if (str[i] == '-')
		{
			if (tiray_case(&tmp, &i, &j, tab, &str) != NULL)
				return (tab);
		}
		else if (str[i] == '$')
		{
			if (dollar_case(&i, &j, &tmp, &str, tab) != NULL)
				return (tab);
		}
		else if (str[i] == '"')
		{
			if (double_quote_case(&i, &j, &tmp, &flag, &str, tab) != NULL)
				return (tab);
		}
		else if (str[i] == '\'')
		{
			if (simple_quote_case(&i, &j, &tmp, &flag, &str, tab) != NULL)
				return (tab);
		}
		else if (str[i] != '\'')
		{
			printf("good_One\n");
			printf("Flag = %d\n", flag);
			if (others_case(&i, &j, &tmp, &flag, &str, tab) != NULL)
			{
				printf("on returne tab\n");
				return (tab);
			}
		}
		if (flag != 1)
			i++;
		flag = 0;
	}
	tab[j] = NULL;
	return (tab);
}
