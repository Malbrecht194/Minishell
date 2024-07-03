#================ COMPILATOR ================#
CC = cc
#=================== FLAGS ==================#
FLAGS = -Wall -Wextra -Werror -gdwarf-4
#=================== NAME ===================#
NAME = minishell
#============ MINISHELL SOURCES =============#
SRCS = main.c \
	special_split.c \
	utils.c \
	get_prompt.c \
	signals.c\
	init_args.c \
	builtins/cd.c \
	builtins/pwd.c \
	builtins/env.c \
	builtins/exit.c \
	builtins/echo.c \
	builtins/unset.c \
	builtins/export/export.c \
	builtins/export/export_utils.c\
	builtins/export/export_utils_2.c\
	format_readline/format_rl.c \
	format_readline/expand_env.c \
	format_readline/utils_expand.c \
	lexor/lexor.c \
	lexor/heredoc.c \
	lexor/lexor_utils.c \
	lexor/lexor_utils_2.c \
	lexor/texec_utils.c \
	lexor/lexor_init/lexor_init.c \
	lexor/lexor_init/lexor_init_utils.c \
	exec/access.c \
	exec/exec_cmd.c \
	exec/check_cmd.c \
	exec/exec_utils.c \
	exec/exec_utils_2.c \
	exec/exec_builtins.c \
	error/error.c \
	error/error_2.c \
	error/error_utils.c
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

$(NAME) : $(LIBFT) $(OBJ)
	@ $(CC) $(OBJ) $(LIBFT) -o $(NAME) -lreadline

clean :
	@ $(MAKE) -C libft clean --no-print-directory
	@ rm -rf $(OBJ_DIR)

fclean :
	@ $(MAKE) -C libft fclean --no-print-directory
	@ rm -rf $(NAME) $(OBJ_DIR)

re : fclean all

.PHONY : all clean fclean re
