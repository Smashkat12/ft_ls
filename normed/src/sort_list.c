/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 09:26:45 by kmorulan          #+#    #+#             */
/*   Updated: 2019/09/14 09:46:39 by kmorulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void			merge_sort(t_pathinfo **direntry_l, t_flag *flags)
{
	t_pathinfo	*head;
	t_pathinfo	*a;
	t_pathinfo	*b;

	head = *direntry_l;
	if (!head || !head->next)
		return ;
	split(head, &a, &b);
	merge_sort(&a, flags);
	merge_sort(&b, flags);
	*direntry_l = lex_sort(a, b, flags);
}

int				timecmp(t_pathinfo *a, t_pathinfo *b, t_flag *flags)
{
	if (flags->c)
	{
		return (b->statinfo.st_ctimespec.tv_nsec - \
		a->statinfo.st_ctimespec.tv_nsec);
	}
	if (flags->u)
	{
		return (b->statinfo.st_atime - a->statinfo.st_atime);
	}
	if (b->statinfo.st_mtime == a->statinfo.st_mtime)
	{
		return (b->statinfo.st_mtimespec.tv_nsec - \
		a->statinfo.st_mtimespec.tv_nsec);
	}
	else
	{
		return (b->statinfo.st_mtime - a->statinfo.st_mtime);
	}
}

void			sort_list(t_pathinfo **direntry_l, t_flag *flags)
{
	if (flags->f)
		return ;
	merge_sort(direntry_l, flags);
	if (flags->r)
		rev_list(direntry_l);
}

void			rev_list(t_pathinfo **direntry_l)
{
	t_pathinfo	*prev;
	t_pathinfo	*current;
	t_pathinfo	*next;

	prev = NULL;
	current = *direntry_l;
	while (current)
	{
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	*direntry_l = prev;
}

void			split(t_pathinfo *head, t_pathinfo **a, t_pathinfo **b)
{
	t_pathinfo	*slow;
	t_pathinfo	*fast;

	slow = head;
	fast = head->next;
	while (fast)
	{
		fast = fast->next;
		if (fast)
		{
			slow = slow->next;
			fast = fast->next;
		}
	}
	*a = head;
	*b = slow->next;
	slow->next = NULL;
	return ;
}
