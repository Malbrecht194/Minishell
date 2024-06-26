#================ COMPILATOR ================#
CC = cc
#=================== FLAGS ==================#
FLAGS = -Wall -Wextra -Werror -g 
#=================== NAME ===================#
NAME = minishell
#============ MINISHELL SOURCES =============#
SRCS = main.c \
	utils.c \
	access.c \
	signals.c \
	get_prompt.c \
	check_args.c \
	builtins/cd.c \
	builtins/pwd.c \
	builtins/env.c \
	builtins/exit.c \
	builtins/echo.c \
	builtins/unset.c \
	builtins/export.c \
	format_readline/format_rl.c \
	format_readline/expand_env.c \
	format_readline/utils_expand.c \
	lexor/lexor.c \
	lexor/lexor_utils.c \
	lexor/tchris_utils.c \
	lexor/lexor_init/lexor_init.c \
	lexor/lexor_init/lexor_init_utils.c \
	check_builtins/exec_cmd.c \
	check_builtins/check_cmd.c \
	check_builtins/exec_utils.c \
	check_builtins/exec_builtins.c
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
