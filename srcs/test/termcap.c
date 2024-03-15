/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amolbert <amolbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 09:20:04 by amolbert          #+#    #+#             */
/*   Updated: 2024/03/05 10:32:16 by amolbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <curses.h>
#include <term.h>
#include <stdio.h>

int	init_term(void)
{
	int		ret;
	char	*term_type;

	term_type = getenv("TERM");
	if (!term_type)
	{
		printf("TERM must be set.\n");
		return (-1);
	}
	ret = tgetent(NULL, term_type);
	if (ret == - 1)
	{
		printf("Could not access to the termcap database.\n");
		return (-1);
	}
	else if (ret == 0)
	{
		printf("Terminal type is not defined in termcap database.\n");
		return (-1);
	}
	return (0);
	
}

int	main(int argc, char **argv)
{
	int		ret;
	int		column_count;
	int		line_count;
	char	*af_cap;
	char	*reset_cmd;
	
	ret = init_term();

	(void)argc;
	(void)argv;

	if (ret == 0)
	{
		column_count = tgetnum("co");
		line_count = tgetnum("li");
		printf("column_count = %d\n", column_count);
		printf("line_count = %d\n", line_count);
		af_cap = tgetstr("AF", NULL);
		tputs((const char *)tparm(af_cap, COLOR_BLUE), 1, putchar);
		printf("Cool ! Maintenant j'ecris en bleu !\n");
		af_cap = tgetstr("AF", NULL);
		tputs((const char *)tparm(af_cap, COLOR_GREEN), 1, putchar);
		printf("Cool ! Maintenant j'ecris en vert !\n");
		af_cap = tgetstr("AF", NULL);
		tputs((const char *)tparm(af_cap, COLOR_RED), 1, putchar);
		printf("Cool ! Maintenant j'ecris en rouge !\n");
		af_cap = tgetstr("us", NULL);
		tputs(af_cap, 1, putchar);
		printf("Cool ! Maintenant j'ecris en souligne !\n");
		printf("lalalalla\n");
		reset_cmd = tgetstr("me", NULL);
		tputs(reset_cmd, 1, putchar);
		printf("Cool ! Maintenant j'ecris normalement !\n");
		af_cap = tgetstr("mb", NULL);
		tputs(af_cap, 1, putchar);
		printf("Cool ! Maintenant j'ecris en clignotant !\n");
		printf("Je suis la ! Je suis pas la ! !\n");
	}
	return (ret);
}
