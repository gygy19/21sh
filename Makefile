# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/03/25 15:18:38 by jguyet            #+#    #+#              #
#    Updated: 2016/03/30 10:16:32 by jguyet           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 21sh

C_INCLUDE_PATH += org/21sh/includes/

LIBFT_PATH =	./libft/

LIBFT_NAME =	libft.a

FINAL_FLAGS = -ltermcap -ggdb

OBJ_PATH =	obj/21sh\
			obj/21sh/console/\
			obj/21sh/console/edition/\
			obj/21sh/console/signal/\
			obj/21sh/console/print/\
			obj/21sh/console/parser/\
			obj/21sh/console/edition/\
			obj/21sh/console/process/\
			obj/21sh/entity/\
			obj/21sh/console/tree/\
			obj/21sh/console/exec/\
			obj/21sh/variable/env/\
			obj/21sh/variable/path/\
			obj/21sh/directory/\
			obj/21sh/console/window/


CFLAGS += -Wall -Wextra -Werror
CFLAGS += $(foreach d, $(C_INCLUDE_PATH), -I $d)

SRCS = 	org/21sh/console/edition/edition.c\
		org/21sh/console/edition/history.c\
		org/21sh/console/signal/sig.c\
		org/21sh/console/loading.c\
		org/21sh/console/parser/parse_exec.c\
		org/21sh/console/parser/parse_cmd.c\
		org/21sh/console/print/print_error.c\
		org/21sh/entity/tools_two.c\
		org/21sh/entity/tools.c\
		org/21sh/console/process/console_process.c\
		org/21sh/console/process/process_keys.c\
		org/21sh/console/window/size.c\
		org/21sh/console/edition/edit_multiline.c\
		org/21sh/console/edition/move_cursor.c\
		org/21sh/console/edition/remove_character.c\
		org/21sh/console/print/tputs_putchar.c\
		org/21sh/console/parser/parse_simple_quote.c\
		org/21sh/console/parser/parse_back.c\
		org/21sh/console/parser/parse_double_quote.c\
		org/21sh/console/parser/parse_braces.c\
		org/21sh/console/parser/parse_error_minor.c\
		org/21sh/console/parser/parse_back_quote.c\
		org/21sh/console/parser/split_process.c\
		org/21sh/console/tree/tree.c\
		org/21sh/console/tree/tree_two.c\
		org/21sh/console/parser/parse_aggregation.c\
		org/21sh/console/process/process_one_dir.c\
		org/21sh/console/exec/exec_pipe.c\
		org/21sh/console/exec/exec_dir.c\
		org/21sh/console/exec/exec_default.c\
		org/21sh/console/edition/tab_search.c\
		org/21sh/console/edition/tab_stars.c\
		org/21sh/console/edition/parse_key.c\
		org/21sh/console/edition/ft_key.c\
		org/21sh/console/exec/ft_flux.c\
		org/21sh/console/tree/tree_three.c\
		org/21sh/console/parser/parse_dirdir.c\
		org/21sh/variable/path/ft_path.c\
		org/21sh/variable/env/ft_env_tools.c\
		org/21sh/variable/env/ft_env.c\
		org/21sh/directory/ft_cd.c\
		org/21sh/directory/ft_cd_two.c\
		org/21sh/directory/utils.c\
		org/21sh/main.c


OBJS = $(patsubst org/%.c,obj/%.o,$(SRCS))

CP = cp

RM = rm -f

LIBFT_FLAG =	-L$(LIBFT_PATH) -lft

LIBFT = $(addprefix $(LIBFT_PATH),$(LIBFT_NAME))

all: RT libft $(NAME)

RT:
	@mkdir -p obj
	@mkdir -p $(OBJ_PATH)

$(OBJS): | obj

obj/%.o: org/%.c
	@$(CC) -c $(CFLAGS) -ggdb $< -o $@
	@echo "Loading   [\033[36m" $(notdir $(@:.o=.c)) "\033[00m]             \033[A"

$(NAME): $(OBJS)
	@$(CC) $(LIBFT_FLAG) $(CFLAGS) $(FINAL_FLAGS) -o $@ $^
	@echo "\nCompiling" [ $(NAME) ] "\033[32mSUCCESS\033[00m"

libft:	$(LIBFT)

$(LIBFT):
	@make -C $(LIBFT_PATH)

clean:
	@$(RM) $(OBJS)
	@make -C $(LIBFT_PATH) clean
	@echo "Cleaning " [ $(NAME) ] "..." "\033[35mOK\033[00m"

fclean: clean
	@$(RM) $(NAME)
	@$(RM) -rf obj
	@make -C $(LIBFT_PATH) fclean

re: fclean all

.PHONY: all clean fclean re
