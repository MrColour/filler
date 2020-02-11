# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kmira <kmira@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/07 02:00:29 by kmira             #+#    #+#              #
#    Updated: 2020/02/10 20:28:59 by kmira            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = kmira.filler

FLAGS = -Wall -Wextra -Werror
INCS = -I includes
LIBFT = srcs/libft/libft.a

FILES = \
	debug \
	get_piece \
	heatmap_color \
	heatmap_display \
	heatmap \
	update_game_state \
	initialize_game \
	main \

SRCS = $(addsuffix .c, $(addprefix srcs/, $(FILES)))

OBJS = $(addsuffix .o, $(FILES))

all: $(LIBFT) $(OBJS)
	gcc -o $(NAME) $(FLAGS) $(LIBFT) $(OBJS)

$(OBJS):
	gcc -c $(FLAGS) $(INCS) $(SRCS)

$(LIBFT):
	make -C srcs/libft/

clean:
	rm -f $(OBJS)
	make clean -C srcs/libft/

fclean: clean
	rm -f $(NAME)
# make fclean -C srcs/libft/

re: fclean all

quick: re
	make clean
	mv $(NAME) resources/players/

save: fclean
	git add .
	git commit -m "$(MSG)"
	git push
	git push https://github.com/MrColour/filler.git

play:
	./filler_vm -p1 resources/players/$(NAME) -f resources/maps/map00

map:
	./filler_vm -p1 resources/players/$(NAME) -f resources/maps/$(MAP)

.PHONY: all clean fclean re quick save
