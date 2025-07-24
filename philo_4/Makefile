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
FILES 	= 	main.c \
			structures_initialization/data_initialization.c \
			structures_initialization/data_initialization_utils.c \
			structures_initialization/philos_initialization.c \
			threads/monitor_routine.c \
			threads/philo_routine.c \
			threads/threads_utils.c \
			utils/clean.c \
			utils/log_display.c \
			utils/time_operations.c 

SRCS 	= 		$(addprefix $(D_SRCS)/, $(FILES))

# Include Files
INCS = -I ./$(D_INCS)
HEADERS =	$(D_INCS)/structures_initialization.h \
			$(D_INCS)/structures.h \
			$(D_INCS)/threads_handling.h \
			$(D_INCS)/utils.h

# Object Files
OBJS 	= 	$(patsubst $(D_SRCS)/%.c, $(D_OBJS)/%.o, $(SRCS))

#########################################
#				   RULES				#
#########################################

.PHONY : all
all: $(D_OBJS) $(NAME)

$(D_OBJS)/%.o: $(D_SRCS)/%.c $(HEADERS) Makefile 
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@ 


$(D_OBJS):
	mkdir -p $(D_OBJS)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -lpthread $(OBJS) -o $(NAME)

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