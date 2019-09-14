/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_sort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 08:44:48 by kmorulan          #+#    #+#             */
/*   Updated: 2019/09/14 08:52:34 by kmorulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

t_pathinfo		*lex_sort2(t_pathinfo *a, t_pathinfo *b)
{
	t_pathinfo	*result;

	result = NULL;
	if (!a)
		return (b);
	if (!b)
		return (a);
	if (ft_strcmp(a->pathname, b->pathname) < 0)
	{
		result = a;
		result->next = lex_sort2(a->next, b);
	}
	else
	{
		result = b;
		result->next = lex_sort2(a, b->next);
	}
	return (result);
}

t_pathinfo		*lex_sort(t_pathinfo *a, t_pathinfo *b, t_flag *flags)
{
	t_pathinfo	*result;

	result = NULL;
	if (!a)
		return (b);
	if (!b)
		return (a);
	if (flags->t)
	{
		if (timecmp(a, b, flags) < 0)
		{
			result = a;
			result->next = lex_sort(a->next, b, flags);
		}
		else
		{
			result = b;
			result->next = lex_sort(a, b->next, flags);
		}
	}
	else
		result = lex_sort2(a, b);
	return (result);
}
