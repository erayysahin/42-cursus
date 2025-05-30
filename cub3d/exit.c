/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erasahin <erasahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 12:32:35 by osarikay          #+#    #+#             */
/*   Updated: 2024/12/25 14:20:49 by erasahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "safe_allocation/s_malloc.h"
#include <stdio.h>
#include <stdlib.h>

void	program_exit(char *error, int exit_code)
{
	if (error)
		printf("Error\n%s", error);
	gc_free();
	exit(exit_code);
}
