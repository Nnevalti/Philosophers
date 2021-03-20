BOLD=\033[1m
RED=\033[0;31m
GREEN=\033[0;32m
YELLOW=\033[0;33m
BLUE=\033[0;34m
SET=\033[0m

CC						=	gcc
CFLAGS					=	-Wall -Werror -Wextra -g

PHILO_ONE				=	philo_one
PHILO_TWO				=	philo_two
PHILO_THREE				=	philo_three

INC_DIR_ONE					=	./philo_1/includes
INC_DIR_TWO					=	./philo_2/includes
INC_DIR_THREE				=	./philo_3/includes

SRCS_DIR_ONE			=	./philo_1/srcs
SRCS_DIR_TWO			=	./philo_2/srcs
SRCS_DIR_THREE			=	./philo_3/srcs

OBJS_DIR_ONE			=	./philo_1/objs
OBJS_DIR_TWO			=	./philo_2/objs
OBJS_DIR_THREE			=	./philo_3/objs

SRCS_ONE				=	philo_one.c \
							init.c \
							philo_actions.c \
							exit.c \
							utils.c

SRCS_TWO				=	philo_two.c \
							init.c \
							philo_actions.c \
							exit.c \
							utils.c

SRCS_THREE				=	philo_three.c \
							init.c \
							philo_actions.c \
							monitor.c \
							exit.c \
							utils.c

OBJS_ONE				=	$(addprefix $(OBJS_DIR_ONE)/,$(SRCS_ONE:.c=.o))
OBJS_TWO				=	$(addprefix $(OBJS_DIR_TWO)/,$(SRCS_TWO:.c=.o))
OBJS_THREE				=	$(addprefix $(OBJS_DIR_THREE)/,$(SRCS_THREE:.c=.o))

$(OBJS_DIR_ONE)/%.o		:	$(SRCS_DIR_ONE)/%.c
							$(CC) $(CFLAGS) -I $(INC_DIR_ONE) -c $< -o $@

$(OBJS_DIR_TWO)/%.o		:	$(SRCS_DIR_TWO)/%.c
							$(CC) $(CFLAGS) -I $(INC_DIR_TWO) -c $< -o $@

$(OBJS_DIR_THREE)/%.o	:	$(SRCS_DIR_THREE)/%.c
							$(CC) $(CFLAGS) -I $(INC_DIR_THREE) -c $< -o $@

all						:	$(PHILO_ONE) $(PHILO_TWO) $(PHILO_THREE)

objs					:
							mkdir -p $(OBJS_DIR_ONE) $(OBJS_DIR_TWO) $(OBJS_DIR_THREE)

$(PHILO_ONE)			:	objs $(OBJS_ONE)
							$(CC) $(OBJS_ONE) -pthread -o $(PHILO_ONE)

$(PHILO_TWO)			:	objs $(OBJS_TWO)
							$(CC) $(OBJS_TWO) -pthread -o $(PHILO_TWO)

$(PHILO_THREE)			:	objs $(OBJS_THREE)
							$(CC) $(OBJS_THREE) -pthread -o $(PHILO_THREE)


clean					:
							@rm -f $(OBJS_ONE) $(OBJS_TWO) $(OBJS_THREE)

fclean					:	clean
							@rm -rf $(OBJS_DIR_ONE) $(OBJS_DIR_TWO) $(OBJS_DIR_THREE)
							@rm -f $(PHILO_ONE) $(PHILO_TWO) $(PHILO_THREE)

re						:	fclean all

norm					:
							~/.norminette/norminette.rb $(SRCS_DIR_ONE) $(SRCS_DIR_TWO) $(SRCS_DIR_THREE)
							~/.norminette/norminette.rb $(INC_DIR_ONE) $(INC_DIR_TWO) $(INC_DIR_THREE)

.PHONY					:	all re clean fclean
