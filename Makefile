#================ COMPILATOR ================#
CC = cc
#=================== FLAGS ==================#
FLAGS = -Wall -Wextra -Werror -g 
#=================== NAME ===================#
NAME = minishell
#============= MINISHELL SOUCES =============#
SRCS = SRCS/main.c \
	SRCS/get_prompt.c \
	SRCS/check_args.c \
	SRCS/link_list.c \
	SRCS/link_list_utils.c \
	SRCS/link_list_utils2.c \
	SRCS/access.c \
	SRCS/utils.c \
	SRCS/format_readline/format_rl.c \
	SRCS/format_readline/expand_env.c \
	SRCS/format_readline/utils_expand.c \
	# SRCS/check_builtins/check_cmd.c\
	# SRCS/check_builtins/exec_builtins.c

#============= BUILTINS SOUCES =============#
BUILTINS = BUILTINS/echo.c \
	BUILTINS/env.c \
	BUILTINS/pwd.c \
	BUILTINS/exit.c \
	BUILTINS/cd.c \
	BUILTINS/export.c \
	BUILTINS/unset.c
	
#============= LIB SOUCES =============#
LIB = INCLUDES/minishell.h \
	INCLUDES/builtins.h\
	INCLUDES/expand.h\
	INCLUDES/lexor.h\
	INCLUDES/check_builtins.h\
#============ TRANSFORM .c TO .o ============#
OBJ = $(SRCS:.c=.o)
OBJBUILTINS = $(BUILTINS: .c=.o)
LIBFT = Libft/libft.a
OBJ_DIR = OBJ/
SRCS_DIR = SRCS/

all : $(NAME)

$(LIBFT) :
	@ $(MAKE) -C Libft all

$(OBJ_DIR)%.o : .c INCLUDES/minishell.h
	@ mkdir -p $(dir $@)
	@ $(CC) $(FLAGS) -c $< -o $@

$(NAME) : $(OBJ) $(OBJBUILTINS) $(LIBFT) 
	$(CC) $(FLAGS) -lreadline $(OBJ) $(OBJBUILTINS) $(LIBFT) -o $(NAME)

clean :
	@ $(MAKE) -C Libft clean
	rm -rf $(OBJ) $(OBJECHO) $(OBJENV) $(OBJEXIT) $(OBJPWD)

fclean :
	@ $(MAKE) -C Libft fclean
	rm -rf $(NAME) $(OBJ) $(OBJECHO) $(OBJENV) $(OBJEXIT) $(OBJPWD)

re : fclean all

.PHONY : all clean fclean re
