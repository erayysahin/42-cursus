/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erasahin <erasahin@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 23:12:53 by erasahin          #+#    #+#             */
/*   Updated: 2024/06/28 23:12:55 by erasahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include "libft/libft.h"

void	message_to_signal(char *message, int pid)
{
	int	bit;

	while (*message)
	{
		bit = 7;
		while (bit >= 0)
		{
			if (*message >> bit & 1)
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			usleep(100);
			bit--;
		}
		message++;
	}
}

int	main(int ac, char **av)
{
	int		pid;

	if (ac == 3)
	{
		pid = ft_atoi(av[1]);
		message_to_signal(av[2], pid);
		ft_putstr_fd("\e[0;32mSended!\n", 1);
	}
	else
	{
		ft_putstr_fd("\e[0;31mWrong Usage!\n", 1);
		ft_putstr_fd("\e[0;32mUsage: ./client <pid> <message>\n", 1);
	}
}
