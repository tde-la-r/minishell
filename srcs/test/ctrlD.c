/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrlD.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amolbert <amolbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 10:48:17 by amolbert          #+#    #+#             */
/*   Updated: 2024/03/06 10:55:24 by amolbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int	main()
{
	int	i;
	
	while (read(0, &i, sizeof(int)) != 0)
	{
		printf("ok\n");	
	}
	printf("ko\n");
}