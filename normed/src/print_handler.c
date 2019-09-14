/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 16:32:00 by kmorulan          #+#    #+#             */
/*   Updated: 2019/09/14 08:23:04 by kmorulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int				print_direntries(t_pathinfo *list, t_flag *flags)
{
	int			checked;

	checked = 0;
	while (list)
	{
		print_list(list, flags);
		if ((flags->one || flags->l) && list->next)
			ft_putchar('\n');
		else if (!list->next)
			list->next = NULL;
		else
			ft_putchar(' ');
		list = list->next;
		checked++;
	}
	return (checked);
}

void			free_list(t_pathinfo **list)
{
	t_pathinfo	*tmp;

	while (*list)
	{
		tmp = (*list)->next;
		free((*list)->pathname);
		free((*list)->fullpath);
		free(*list);
		*list = tmp;
	}
}

void			print_permissions(t_pathinfo *list)
{
	ft_putchar((list->statinfo.st_mode & S_IRUSR) ? 'r' : '-');
	ft_putchar((list->statinfo.st_mode & S_IWUSR) ? 'w' : '-');
	ft_putchar((list->statinfo.st_mode & S_IXUSR) ? 'x' : '-');
	ft_putchar((list->statinfo.st_mode & S_IRGRP) ? 'r' : '-');
	ft_putchar((list->statinfo.st_mode & S_IWGRP) ? 'w' : '-');
	ft_putchar((list->statinfo.st_mode & S_IXGRP) ? 'x' : '-');
	ft_putchar((list->statinfo.st_mode & S_IROTH) ? 'r' : '-');
	ft_putchar((list->statinfo.st_mode & S_IWOTH) ? 'w' : '-');
	ft_putchar((list->statinfo.st_mode & S_IXOTH) ? 'x' : '-');
	if (listxattr(list->fullpath, NULL, 0, XATTR_NOFOLLOW) > 0)
		ft_putchar('@');
	else if (acl_get_link_np(list->fullpath, ACL_TYPE_EXTENDED) != NULL)
		ft_putchar('+');
	else
		ft_putchar(' ');
}

void			print_list(t_pathinfo *direntry_l, t_flag *flags)
{
	if (flags->l)
	{
		print_type(direntry_l);
		print_permissions(direntry_l);
		print_link_count(direntry_l);
		ft_putstr(getpwuid(direntry_l->statinfo.st_uid)->pw_name);
		ft_putchar('\t');
		ft_putstr(getgrgid(direntry_l->statinfo.st_gid)->gr_name);
		ft_putchar('\t');
		if (S_ISBLK(direntry_l->statinfo.st_mode) || \
		S_ISCHR(direntry_l->statinfo.st_mode))
		{
			ft_putnbr(major(direntry_l->statinfo.st_rdev));
			ft_putstr("  \t");
			ft_putnbr(minor(direntry_l->statinfo.st_rdev));
		}
		else
			ft_putnbr(direntry_l->statinfo.st_size);
		ft_putstr("  ");
		print_date(direntry_l, flags);
		print_name(direntry_l, 0, flags);
		(S_ISLNK(direntry_l->statinfo.st_mode)) ? print_link(direntry_l) : 0;
	}
	else
		print_name(direntry_l, 1, flags);
}
