/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heatmap_display.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmira <kmira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 13:30:12 by kmira             #+#    #+#             */
/*   Updated: 2020/02/20 13:42:44 by kmira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	print_heatmap_spot(t_filler_context *context,
							int row, int col, char *color)
{
	char	spot_char;
	char	enemy_char;

	if (context->player_char == P1)
		enemy_char = P2;
	else
		enemy_char = P1;
	spot_char = ft_tolower((context->board)[row][col]);
	if (spot_char == context->player_char)
		dprintf(STDERR_FILENO, BOLDCYAN"%c", context->player_char);
	else if (spot_char == enemy_char)
		dprintf(STDERR_FILENO, ANSI_RESET""RED"%c", enemy_char);
	else
		dprintf(STDERR_FILENO, "%s#", color);
}

void	print_heatmap(t_filler_context *context)
{
	int		row;
	int		col;
	int		num;
	int		max;

	if (context->board_height > context->board_width)
		max = context->board_height;
	else
		max = context->board_width;
	row = -1;
	max = max / 2;
	while (++row < context->board_height)
	{
		col = -1;
		write(STDERR_FILENO, ANSI_RESET"\n    ", 9);
		while (++col < context->board_width)
		{
			num = (context->heatmap)[row][col] - max;
			print_heatmap_spot(context, row, col,
					colour_code(get_r(num, max),
								get_g(num, max),
								get_b(num, max)));
		}
	}
	dprintf(STDERR_FILENO, ANSI_RESET);
	dprintf(STDERR_FILENO, "\n\033[%dA"ANSI_RESET, (context->board_height) + 1);
}
