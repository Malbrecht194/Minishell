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
	SRCS/access.c \
	SRCS/utils.c \
	SRCS/quoting.c

#============= BUILTINS SOUCES =============#
BUILTINS = BUILTINS/echo.c \
	BUILTINS/env.c \
	BUILTINS/pwd.c \
	BUILTINS/exit.c

#============ TRANSFORM .c TO .o ============#
OBJ = $(SRCS:.c=.o)
OBJBUILTINS = $(BUILTINS: .c=.o)
LIBFT = Libft/libft.a

all : $(NAME)

$(LIBFT) :
	@ $(MAKE) -C Libft all

%.o : %.c INCLUDES/minishell.h
	@ $(CC) $(FLAGS) -c $< -o $@

$(NAME) : $(OBJ) $(OBJBUILTINS) $(LIBFT) 
	$(CC) $(FLAGS) -lreadline $(OBJ) $(OBJBUILTINS) $(LIBFT) -o $(NAME)

clean :
	@ $(MAKE) -C Libft clean
	rm -rf $(OBJ) $(OBJECHO) $(OBJENV) $(OBJEXIT) $(OBJPWD)

fclean :
	@ $(MAKE) -C Libft fclean
	rm -rf $(NAME) $(OBJ) $(OBJECHO) $(OBJENV) $(OBJEXIT) $(OBJPWD) \
	BUILTINS/echo BUILTINS/env BUILTINS/exit BUILTINS/pwd

re : fclean all

.PHONY : all clean fclean re
