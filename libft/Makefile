NAME	= libft.a

LIBFT_SRC	= src/libft/
GNL_SRC	= src/get_next_line/
LIBFT_UTIL_SRC	= src/libft_utils/

LIBFT	= ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c\
ft_memmove.c ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c\
ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c\
ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c
GNL	= get_next_line_bonus.c get_next_line_utils_bonus.c
LIBFT_UTIL	= ft_realloc.c ft_strndup.c ft_strstr.c ft_strcmp.c ft_strcpy.c ft_strncpy.c ft_strcat.c ft_strncat.c

OBJS	= $(addprefix $(LIBFT_SRC), $(LIBFT:.c=.o))
OBJS	+= $(addprefix $(GNL_SRC), $(GNL:.c=.o))
OBJS	+= $(addprefix $(LIBFT_UTIL_SRC), $(LIBFT_UTIL:.c=.o))

CC		= cc
CFLAGS	= -Wall -Wextra -Werror
RM		= rm -f

$(NAME):$(OBJS)
		ar crs $(NAME) $(OBJS)

all:$(NAME)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

clean:
	$(RM) $(OBJS)

fclean:
	$(RM) $(OBJS) $(NAME)

re: fclean all
