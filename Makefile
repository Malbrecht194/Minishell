#================ COMPILATOR ================#
CC = cc
#=================== FLAGS ==================#
FLAGS = -Wall -Wextra -Werror -g 
#=================== NAME ===================#
NAME = minishell
#============ MINISHELL SOURCES =============#
SRCS = get_prompt.c \
	main.c \
	signals.c\
	check_args.c \
	link_list.c \
	link_list_utils.c \
	link_list_utils2.c \
	access.c \
	utils.c \
	builtins/echo.c \
	builtins/env.c \
	builtins/pwd.c \
	builtins/exit.c \
	builtins/cd.c \
	builtins/export.c \
	builtins/unset.c \
	format_readline/format_rl.c \
	format_readline/expand_env.c \
	format_readline/utils_expand.c 
# check_builtins/check_cmd.c\
# check_builtins/exec_builtins.c


#============ TRANSFORM .c TO .o ============#
LIBFT = libft/libft.a
OBJ_DIR = obj/
SRCS_DIR = srcs/
INCLUDE_DIR = includes
OBJ = $(addprefix $(OBJ_DIR), $(SRCS:.c=.o))

INCLUDES = -I$(INCLUDE_DIR)

all : $(NAME)

$(LIBFT) :
	@ $(MAKE) -C libft all --no-print-directory

$(OBJ_DIR)%.o : $(SRCS_DIR)%.c
	@ mkdir -p $(dir $@)
	@ $(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

$(NAME) : $(LIBFT) $(OBJ) $(OBJBUILTINS)
	@ $(CC) $(FLAGS) -lreadline $(OBJ) $(OBJBUILTINS) $(INCLUDES) $(LIBFT) -o $(NAME)

clean :
	@ $(MAKE) -C libft clean --no-print-directory
	@ rm -rf $(OBJ_DIR)

fclean :
	@ $(MAKE) -C libft fclean --no-print-directory
	@ rm -rf $(NAME) $(OBJ_DIR)

re : fclean all

.PHONY : all clean fclean re
