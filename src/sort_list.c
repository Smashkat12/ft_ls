/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorulan <kmorulan@student.wethinkcode.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 09:26:45 by kmorulan          #+#    #+#             */
/*   Updated: 2019/09/10 14:02:14 by kmorulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void		merge_sort(t_pathinfo **direntry_l, t_flag *flags)
{
	t_pathinfo	*head;
	t_pathinfo	*a;
	t_pathinfo	*b;

	head = *direntry_l;
	if (!head || !head->next) //if the direntry list is empty or just has one entry.
		return ;
	split(head, &a, &b);
	merge_sort(&a, flags); //this recursion will end when the list only has one element in it.
	merge_sort(&b, flags); //this recursion will end when the list only has one element in it.
	*direntry_l = lex_sort(a, b, flags);
}
t_pathinfo		*lex_sort(t_pathinfo *a, t_pathinfo *b, t_flag *flags)
{
	t_pathinfo	*result;

	result = NULL;
	if (!a)
		return (b);
	if (!b)
		return (a);
	if (flags->t || flags->l)
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
int			timecmp(t_pathinfo *a, t_pathinfo *b, t_flag *flags)
{
	if (flags->c)
		return (b->statinfo.st_ctimespec.tv_nsec - a->statinfo.st_ctimespec.tv_nsec); //last file status change (chmod, chown etc...)
	if (flags->u)
		return (b->statinfo.st_atime - a->statinfo.st_atime); //time of last access
	if (b->statinfo.st_mtime == a->statinfo.st_mtime)
		return (b->statinfo.st_mtimespec.tv_nsec - a->statinfo.st_mtimespec.tv_nsec);
	else
		return (b->statinfo.st_mtime - a->statinfo.st_mtime);
}
t_pathinfo		*lex_sort2(t_pathinfo *a, t_pathinfo *b)
{
	t_pathinfo	*result;

	result = NULL;
	if (!a)
		return (b);
	if (!b)
		return (a);
	if (ft_strcmp(a->pathname , b->pathname) < 0) //if a < b else a > b
	{
		result = a; // result will hold the small dir entry
		result->next = lex_sort2(a->next, b); // the next will be the possible small and so on until direntry_l fully sorted
	}
	else
	{
		result = b;
		result->next = lex_sort2(a, b->next);
	}
	return (result); //return sorted list
}
void		sort_list(t_pathinfo **direntry_l, t_flag *flags)
{
	if (flags->f)
		return ;
	merge_sort(direntry_l, flags);
	if (flags->r)
		rev_list(direntry_l);
}

void		rev_list(t_pathinfo **direntry_l)
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
void		split(t_pathinfo *head, t_pathinfo **a, t_pathinfo **b)
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
