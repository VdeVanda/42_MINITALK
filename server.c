/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabatist <vabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 10:27:05 by vabatist          #+#    #+#             */
/*   Updated: 2025/02/15 12:41:57 by vabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	ft_iterative_power(int base, int power)
{
	int	result;

	if (power < 0)
		return (0);
	result = 1;
	while (power > 0)
	{
		result *= base;
		power--;
	}
	return (result);
}

static char	*letter_to_string(char const *string, char const letter)
{
	int		i;
	int		j;
	char	*message;

	i = 0;
	j = 0;
	message = malloc((ft_strlen(string) + 2) * sizeof(char));
	if (!message)
		return (NULL);
	while (string[i])
		message[j++] = string[i++];
	i = 0;
	message[j++] = letter;
	message[j] = '\0';
	free((void *)(string));
	return (message);
}

static void	process_accumulated_string(char **accumulated_string,
		int char_value)
{
	*accumulated_string = letter_to_string(*accumulated_string, char_value);
	if (char_value == '\0')
	{
		if (ft_strncmp(*accumulated_string, "exit\0", 5) == 0)
		{
			ft_printf("Exiting...\n");
			free(*accumulated_string);
			exit(0);
		}
		ft_printf("%s\n", *accumulated_string);
		free(*accumulated_string);
		*accumulated_string = NULL;
	}
}

static void	signal_handler(int signum)
{
	static int	bit_counter = 0;
	static int	char_value = 0;
	static char	*accumulated_string;

	if (!accumulated_string)
		accumulated_string = ft_strdup("");
	if (signum == SIGUSR1)
		char_value += 0;
	else if (signum == SIGUSR2)
		char_value += ft_iterative_power(2, 7 - bit_counter);
	bit_counter++;
	if (bit_counter == 8)
	{
		process_accumulated_string(&accumulated_string, char_value);
		bit_counter = 0;
		char_value = 0;
	}
}

int	main(void)
{
	ft_printf("Server's PID: %d\n", getpid());
	signal(SIGUSR1, signal_handler);
	signal(SIGUSR2, signal_handler);
	while (1)
		pause();
	return (0);
}
