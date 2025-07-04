#########################################
#				VARIABLES				#
#########################################

NAME = philo

# Compilation
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3

# Directories
D_SRCS = srcs
D_INCS = incs
D_OBJS = objs

# Source Files
FILES 	= 	init_utils.c \
			init.c \
			main.c

SRCS 	= 		$(addprefix $(D_SRCS)/, $(FILES))

# Include Files
INCS = -I ./$(D_INCS)

# Object Files
OBJS 	= 	$(patsubst $(D_SRCS)/%.c, $(D_OBJS)/%.o, $(SRCS))

#########################################
#				   RULES				#
#########################################

.PHONY : all
all: $(D_OBJS) $(NAME)

$(D_OBJS)/%.o: $(D_SRCS)/%.c Makefile incs/philo.h
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@ 


$(D_OBJS):
	mkdir -p $(D_OBJS)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

.PHONY : clean
clean:
	@echo "clean objs from /$(NAME)"
	@rm -rf $(D_OBJS)

.PHONY : fclean
fclean: 
	@$(MAKE) --no-print-directory clean
	@echo "clean $(NAME) from /$(NAME)"
	@rm -f $(NAME)

.PHONY : re
re:
	@$(MAKE) --no-print-directory fclean
	@$(MAKE) --no-print-directory all