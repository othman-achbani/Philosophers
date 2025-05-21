SRCS = parsing_utils.c  philo.c 

RM	= rm -rf
CFLAGS = -Wall -Wextra -Werror -pthread
CC = cc
OBJF = $(SRCS:.c=.o)
NAME = philo

RESET		=	'\033[0m'
GREEN		=	'\033[32m'
GRAY		=	'\033[2;37m'
ITALIC		=	'\033[3m'

.c.o 	:
			@echo $(ITALIC)$(GREEN) "     - Compiling the file /$<..." $(RESET)
			@$(CC) $(CFLAGS) -c $< -o $@

all  	:$(NAME)

$(NAME) : $(OBJF)
			@echo $(ITALIC)$(GREEN) "     - all the philosophers are sitting on the table" $(RESET)
			@$(CC) $(CFLAGS) $(OBJF) -o $(NAME)

clean	: 
			@echo $(ITALIC)$(GRAY) "     - deleting the object files..." $(RESET)
			@$(RM) $(OBJF)

fclean	: clean
			@echo $(ITALIC)$(GRAY) "     - deleting the executable files..." $(RESET)
			@$(RM) $(NAME)

re		: fclean all

.PHONY	: all clean fclean re bonus 
.SECONDARY: