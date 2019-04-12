/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_choose_option.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gscolera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 19:29:17 by gscolera          #+#    #+#             */
/*   Updated: 2019/04/12 15:37:37 by gscolera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	shell_too_much_options(t_shell *sh)
{
	ft_printf("There are %d possibilies", sh->options.count);
}

static void	shell_print_in_colums(t_shell *sh, t_cmplt *list)
{
	size_t	row_capacity;
	size_t	left_in_row;

	row_capacity = (g_window_size.x - 10) / sh->options.max_len;
	while (list)
	{
		left_in_row = row_capacity;
		while (list && left_in_row--)
		{
			if (sh->act_list == list)
				ft_printf("{red}%-*s{eoc}", sh->options.max_len, list->option);
			else
				ft_printf("%-*s", sh->options.max_len, list->option);
			list = list->next;
		}
		TERM_ACTION(DOWN);
	}
}

static void	shell_print_options(t_shell *sh, t_cmplt *list)
{
	TERM_ACTION(SAVEC);
	TERM_ACTION(CD);
	TERM_ACTION(DOWN);
	if (!sh->act_list || !sh->act_list->next)
		sh->act_list = sh->cmp_list;
	else
		sh->act_list = sh->act_list->next;
	if (sh->options.count > 100)
		shell_too_much_options(sh);
	else if (sh->options.len >= g_window_size.x - 10)
		shell_print_in_colums(sh, list);
	else
	{
		while (list)
		{
			if (sh->act_list == list)
				ft_printf("{red}%s  {eoc}", list->option);
			else
				ft_printf("%s ", list->option);
			list = list->next;
		}
	}
	TERM_ACTION(RSRC);
}

void		shell_choose_option(t_shell *sh, t_cmplt *list)
{
	char	buff[10];

	ft_memset(buff, 0, 10);
	shell_print_options(sh, list);
	while (g_flags & CHOOSING)
	{
		read(fileno(stdin), buff, 10);
		if (buff[0] == KEYTAB)
			shell_print_options(sh, list);
		else if (buff[0] == KEYENTER)
		{
			shell_accept_option(sh, sh->act_list);
			g_flags &= ~CHOOSING;
		}
		else if (buff[0] == KEYESC)
			g_flags &= ~CHOOSING;
		else if (ft_isprint(buff[0]))
		{
			shell_insert_char(sh, &sh->rd, buff[0]);
			g_flags &= ~CHOOSING;
		}
		ft_strclr(buff);
	}
}
