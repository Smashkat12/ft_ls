/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorulan <kmorulan@student.wethinkcode.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 06:00:50 by kmorulan          #+#    #+#             */
/*   Updated: 2019/09/12 17:25:53 by kmorulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

t_size	init_size(void)
{
	t_size	size;

	size.nlink = 0;
	size.pw_name = 0;
	size.gr_name = 0;
	size.st_size = 0;
	size.major = 0;
	size.minor = 0;
	size.device = 0;
	size.f_name = 0;
	size.w_cols = getwincols();
	return (size);
}

int			getwincols(void)
{
	struct	winsize	size;

	if(!(ioctl(STDOUT_FILENO,TIOCGWINSZ, &size)))
		return(size.ws_col);
	return (-1);
}

static void 	set_major_minor(t_size *size,t_pathinfo *direntry_l)
{
	int			temp;

	temp = major(direntry_l->statinfo.st_rdev);
	if (temp > size->major)
		size->major = temp;
	temp = minor(direntry_l->statinfo.st_rdev);
	if (temp > size->minor)
		size->minor = temp;
	size->device = 1;
}

static void			set_digit_len(t_size *size)
{
	size->nlink = get_digit_len(size->nlink);
	size->major = get_digit_len(size->major);
	size->minor = get_digit_len(size->minor);
	size->st_size = get_digit_len(size->st_size);
	if (size->device)
	{
		size->st_size = BIGEST(size->major + size->minor + 2, size->st_size);
	}
}

int				get_digit_len(int64_t nbr)
{
	int			num_index;

	if (nbr) //if the number is not 0;
	{
		num_index = 0; // index starts at 0
	}
	else
	{
		num_index = 1; // else start at 1
	}
	while (nbr)
	{
		nbr = nbr / 10;
		num_index++;
	}
	return (num_index);
}

t_size		set_size(t_pathinfo *direntry_l)
{
	t_size	size;
	int		temp;

	size = init_size();
	while (direntry_l)
	{
		if (direntry_l->statinfo.st_nlink > size.nlink)
			size.nlink = direntry_l->statinfo.st_nlink;
		temp = ft_strlen(getpwuid(direntry_l->statinfo.st_uid)->pw_name); //getpwuid returns pointer to struct passwd func defined in PWD.h
		if (temp > size.pw_name)
			size.pw_name = temp;
		temp = ft_strlen(getgrgid(direntry_l->statinfo.st_gid)->gr_name); //getgrgip retruns pointer to struct group; func defined in GRP.h
		if (temp > size.gr_name)
			size.gr_name = temp;
		if (direntry_l->statinfo.st_size > size.st_size)
			size.st_size = direntry_l->statinfo.st_size;
		temp = ft_strlen(direntry_l->pathname);
		if (temp > size.f_name)
			size.f_name = temp;
		if (S_ISBLK(direntry_l->statinfo.st_mode) || S_ISCHR(direntry_l->statinfo.st_mode))
			set_major_minor(&size, direntry_l);
		direntry_l = direntry_l->next;
	}
	set_digit_len(&size);
	return (size);
}