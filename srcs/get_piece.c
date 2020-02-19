/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_piece.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmira <kmira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 20:29:02 by kmira             #+#    #+#             */
/*   Updated: 2020/02/19 13:46:26 by kmira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

t_piece	*make_piece(int row, int col)
{
	t_piece	*result;

	result = malloc(sizeof(*result));
	result->row_rel = row;
	result->col_rel = col;
	result->next = NULL;
	return (result);
}

void	append_piece(t_piece **piece_head, int row, int col)
{
	t_piece	*iter;

	if (*piece_head == NULL)
		*piece_head = make_piece(row, col);
	else
	{
		iter = *piece_head;
		while (iter->next != NULL)
			iter = iter->next;
		iter->next = make_piece(row, col);
	}
}

#define PIECE_ 6

char	**get_piece_board(int piece_height, int piece_width)
{
	int		row;
	char	**result;

	row = 0;
	result = malloc(sizeof(*result) * (piece_height + 1));
	while (row < piece_height)
	{
		result[row] = malloc(sizeof(**result) * (piece_width + 10));
		ft_bzero(result[row], sizeof(**result) * (piece_width + 10));
		read(STDIN_FILENO, result[row], 1);
		read(STDIN_FILENO, result[row], piece_width);
		result[row][piece_width] = '\0';
		row++;
	}
	result[row] = NULL;
	read(STDIN_FILENO, &row, 1);
	return (result);
}

void	free_piece(t_piece *piece)
{
	t_piece	*iter;
	t_piece	*release;

	iter = piece;
	while (iter != NULL)
	{
		release = iter;
		iter = iter->next;
		free(release);
	}
}

t_piece		*fill_piece(char **piece_board, int piece_height,
							int piece_width, t_piece *piece)
{
	int		row;
	int		col;
	t_piece	*piece;

	row = 0;
	piece = make_piece(0, 0);
	while (row < piece_height)
	{
		col = 0;
		while (col < piece_width)
		{
			if ((piece_board)[row][col] == '*')
				append_piece(&piece, row, col);
			col++;
		}
		row++;
	}
	return (piece);
}

t_piece	*new_piece_to_place(void)
{
	int		piece_height;
	int		piece_width;
	char	**piece_board;
	char	buff[DIGIT_LEN];
	t_piece	*piece;

	read(STDIN_FILENO, buff, PIECE_);
	piece_height = read_num();
	piece_width = read_num();
	piece_board = get_piece_board(piece_height, piece_width);
	piece = fill_piece(piece_board, piece_height, piece_width, piece);
	return (piece);
}
