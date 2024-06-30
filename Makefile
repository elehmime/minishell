# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/23 14:33:59 by marvin            #+#    #+#              #
#    Updated: 2024/05/23 14:33:59 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


#===CONFIGURATION===
NAME = minishell

SRC =\
		main.c \
		exec.c \
		redirection/redirection.c \
		redirection/prompt_redir_in.c \
		minishell_utils.c \
		builtins/builtins.c \
		builtins/env.c \
		builtins/cd.c \
		builtins/echo.c \
		builtins/pwd.c \
		builtins/cd_utils.c \
		builtins/exit.c \
		environement/env_cpy.c \
		environement/environement_variable.c \
		environement/unset_var.c \
		environement/environement_variable_utils.c \
		parsing/parsing.c \
		parsing/parsing_utils1.c \
		parsing/parsing_utils2.c \
		parsing/split.c \
		parsing/token.c \
		parsing/type_define.c \
		parsing/expend.c \
		parsing/expend_utils.c \
		pipe/if_pipex.c \
		pipe/pipex.c \
		pipe/free.c \
		pipe/multi_pipes_utils.c \
		pipe/pipex_heredoc.c \
		pipe/pipex_utils.c \
		pipe/pipe_utils_minishell.c \


CFLAGS = -Wall -Werror -Wextra -g3
LFLAGS = -lreadline

LIBS = \
	libft/libft.a\


INCLUDES = -Ilibft/ -I./

OBJ_DIR = obj

#===AUTOMATIC VARS===

OBJ = $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(basename $(SRC))))

LIB_FLAGS = $(addprefix -L, $(dir $(LIBS))) $(addprefix -l, $(patsubst lib%.a, %, $(notdir $(LIBS))))

#===TARGETS===
all : $(NAME)

#===COMPILING===
$(OBJ_DIR) :
	$(shell mkdir -p $(OBJ_DIR))
$(OBJ_DIR)/%.o : %.c
	mkdir -p $(dir $@)
	cc $(CFLAGS) -o $@ -c $< $(INCLUDES)
$(OBJ_DIR)/%_bonus.o : bonus/%.c
	mkdir -p $(dir $@)
	cc $(CFLAGS) -o $@ -c $< $(INCLUDES)
%.a :
	make -C $(dir $@)

#===LINKING===
$(NAME_BONUS) : $(OBJ_DIR) $(LIBS)
	cc -o  $(LIB_FLAGS) $(LFLAGS)
$(NAME) : $(OBJ_DIR) $(LIBS) $(OBJ)
	cc -o $(NAME) $(OBJ) $(LIB_FLAGS) $(LFLAGS)

#===CLEAN===
clean :
	rm -rf $(OBJ_DIR) libft/*.o || true

#===FCLEAN===
fclean : clean
	rm -f $(NAME) libft/*.o libft/*.a || true

#===RE===
re : fclean all

.PHONY : re fclean clean all default bonus