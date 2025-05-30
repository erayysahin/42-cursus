/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erasahin <erasahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 13:18:03 by erasahin          #+#    #+#             */
/*   Updated: 2024/12/25 14:47:25 by erasahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "error.h"
#include "gnl/get_next_line.h"
#include "libft/srcs/libft.h"
#include "safe_allocation/s_malloc.h"
#include <fcntl.h>

void	map_pars(char *file, t_data *data)
{
	int		fd;
	int		i;
	int		len;
	char	*line;

	line = NULL;
	i = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		program_exit("INVALID_MAP", -1);
	len = map_size(fd, data);
	data->map_size = len;
	data->map = (char **)gc_malloc(sizeof(char *) * (len + 2));
	while (i <= len)
		data->map[i++] = (char *)gc_malloc(sizeof(char) * (data->size + 1));
	close(fd);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		program_exit("INVALID_MAP", -1);
	texture_pars(fd, data, 0, line);
	map_dup(fd, data, 0);
	close(fd);
	player_loc(data);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = gc_malloc(sizeof(t_data));
	data->key = (t_key){0};
	if (argc != 2)
		program_exit("ARGC_ERROR", -1);
	if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 4))
		program_exit("BER_ERROR", -1);
	map_pars(argv[1], data);
	create_mlx(data);
	program_exit(NULL, 0);
}
