/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabatist <vabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 10:26:05 by vabatist          #+#    #+#             */
/*   Updated: 2025/02/12 12:53:47 by vabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	handle_error_invalid_server_id(int pid)
{
	ft_printf("[ERROR]: invalid server_id. Failed to send signal to PID %d\n",
		pid);
	exit(EXIT_FAILURE);
}

static void	send_signals(int pid, char *message)
{
	int	letter;
	int	i;

	letter = 0;
	while (message[letter])
	{
		i = -1;
		while (++i < 8)
		{
			if (((unsigned char)(message[letter] >> (7 - i)) & 1) == 0)
				kill(pid, SIGUSR1);
			else if (((unsigned char)(message[letter] >> (7 - i)) & 1) == 1)
				kill(pid, SIGUSR2);
			usleep(50);
		}
		letter++;
	}
	i = 0;
	while (i++ < 8)
	{
		if (kill(pid, SIGUSR1) == -1)
			handle_error_invalid_server_id(pid);
		usleep(50);
	}
}

static void	print_usage_and_errors(int argc)
{
	if (argc == 1)
	{
		ft_printf("\nTo send a message, use the following format:\n");
		ft_printf("./client PID \"YOUR MESSAGE\"\n");
		ft_printf("\nTo shutdown server, use the following format:\n");
		ft_printf("./client PID \"exit\"\n\n");
	}
	else
	{
		ft_printf("[ERROR]: Too much or too few arguments.\n");
		ft_printf("Make sure to enter arguments as follow:\n");
		ft_printf("./client PID \"YOUR MESSAGE\"\n");
	}
}

int	main(int argc, char **argv)
{
	char	*message;
	int		server_id;

	if (argc == 1 || argc != 3)
	{
		print_usage_and_errors(argc);
		return (0);
	}
	server_id = ft_atoi(argv[1]);
	if (server_id <= 0)
	{
		ft_printf("[ERROR]: invalid server_id\n");
		return (0);
	}
	message = argv[2];
	if (message[0] == 0)
	{
		ft_printf("You haven't sent any text. Please write something \n");
		return (0);
	}
	send_signals(server_id, message);
	return (0);
}
