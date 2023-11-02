NAME	= minishell

SRCSDIR	= src/

SRCS = main.c free.c tokenize.c check_token.c utils.c parser.c init.c print.c

RE_SRCSDIR	= src_resaito/

RE_SRCS = exec.c search_path.c

OBJS	= $(addprefix $(SRCSDIR), $(SRCS:.c=.o))

RE_OBJS	= $(addprefix $(RE_SRCSDIR), $(RE_SRCS:.c=.o))

CC		= cc
CFLAGS	= #-Wall -Wextra -Werror
RM		= rm -f

LIBFTDIR	= libft/
LIBFTNAME	= libft.a

all:$(NAME)

$(NAME):$(OBJS) $(RE_OBJS)
	$(MAKE) -C $(LIBFTDIR)
	$(CC) $(CFLAGS) -lreadline -o $(NAME) $(OBJS) $(RE_OBJS) -L$(LIBFTDIR) -lft
.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(LIBFTDIR)$(LIBFTNAME):
	$(MAKE) -C $(LIBFTDIR)

clean:
	$(RM) $(OBJS) $(RE_OBJS)
	$(MAKE) -C $(LIBFTDIR) clean

fclean:
	$(RM) $(OBJS) $(RE_OBJS) $(NAME)
	$(MAKE) -C $(LIBFTDIR) fclean

re: fclean all
