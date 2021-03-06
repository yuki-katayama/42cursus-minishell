#--------------ESCAPE CODE------------#
ifeq ($(shell uname), Linux)
	ESC_CLEAR_SCREEN		?=	\033[0;2J
	ESC_CLEAR_CURRENT_LINE	?=	\033[0;2K\r

	ESC_DEFAULT ?=	\033[0;0m
	ESC_BOLD	?=	\033[0;1m
	ESC_UNDER	?=	\033[0;4m
	ESC_REV		?=	\033[0;7m

	ESC_BLACK		?=	\033[0;30m
	ESC_RED			?=	\033[0;31m
	ESC_GREEN		?=	\033[0;32m
	ESC_YELLOW		?=	\033[0;33m
	ESC_BLUE		?=	\033[0;34m
	ESC_PURPLE		?=	\033[0;35m
	ESC_CYAN		?=	\033[0;36m
	ESC_WHITE		?=	\033[0;37m

	ESC_BACK_BLACK		?=	\033[0;40m
	ESC_BACK_RED		?=	\033[0;41m
	ESC_BACK_GREEN		?=	\033[0;42m
	ESC_BACK_YELLOW		?=	\033[0;43m
	ESC_BACK_BLUE		?=	\033[0;44m
	ESC_BACK_PURPLE		?=	\033[0;45m
	ESC_BACK_CYAN		?=	\033[0;46m
	ESC_BACK_GRAY		?=	\033[0;47m
else
	ESC_CLEAR_SCREEN		?=	\x1b[2J
	ESC_CLEAR_CURRENT_LINE	?=	\x1b[2K\r

	ESC_DEFAULT ?=	\x1b[0m
	ESC_BOLD	?=	\x1b[1m
	ESC_UNDER	?=	\x1b[4m
	ESC_REV		?=	\x1b[7m

	ESC_BLACK		?=	\x1b[30m
	ESC_RED			?=	\x1b[31m
	ESC_GREEN		?=	\x1b[32m
	ESC_YELLOW		?=	\x1b[33m
	ESC_BLUE		?=	\x1b[34m
	ESC_PURPLE		?=	\x1b[35m
	ESC_CYAN		?=	\x1b[36m
	ESC_WHITE		?=	\x1b[37m

	ESC_BACK_BLACK		?=	\x1b[40m
	ESC_BACK_RED		?=	\x1b[41m
	ESC_BACK_GREEN		?=	\x1b[42m
	ESC_BACK_YELLOW		?=	\x1b[43m
	ESC_BACK_BLUE		?=	\x1b[44m
	ESC_BACK_PURPLE		?=	\x1b[45m
	ESC_BACK_CYAN		?=	\x1b[46m
	ESC_BACK_GRAY		?=	\x1b[47m
endif

#-----------SET DIRECTORY--------#
SRCDIR	?= ./srcs
OBJDIR	?= ./objs
DPSDIR	?= ./dps
STCSDIR ?= ./stcs
INCDIR ?= ./include

#-------------SET STCS VARIABLES----------#
STCS_ENV ?= env
STCS_LEXER ?= lexer
STCS_SIGNAL ?= signal
STCS_BUILTIN ?= builtin
STCS_EXEC ?= exec
STCS_EXPANSION ?= expansion
STCS_LIBFT ?= libft
STCS_PARSER ?= parser
STCS_UTILS ?= utils
STCS_EXIT_STATUS ?= exit_status

STCSNAME ?= $(STCS_ENV) \
			$(STCS_LEXER) \
			$(STCS_SIGNAL) \
			$(STCS_BUILTIN) \
			$(STCS_EXEC) \
			$(STCS_EXPANSION) \
			$(STCS_LIBFT) \
			$(STCS_PARSER) \
			$(STCS_UTILS) \
			$(STCS_EXIT_STATUS)


STCS ?= $(addprefix $(STCSDIR)/, $(addsuffix .a, $(STCSNAME)))

#-----------SET SRCS-------------#
SRCNAME	?=	main

SRCS ?= $(addprefix $(SRCDIR)/, $(addsuffix .c, $(SRCNAME)))


#-------------SET FLAGS--------------#
CFLAGS	?= -I $(shell brew --prefix readline)/include -I $(INCDIR) -Wall -Wextra -Werror -g
ifdef DEBUG
	CFLAGS	:= -I $(shell brew --prefix readline)/include -g
endif

LDFLAGS = -lreadline -lhistory -L$(shell brew --prefix readline)/lib

SANFLAGS ?=	-g -fsanitize=address


#-------------SET OTHER VARIEBLE-----------#
NAME	?=	minishell

CC		?= gcc

RM		:=	rm -rf


OBJS	?= $(addprefix $(OBJDIR)/, $(notdir $(SRCS:.c=.o)))
DPS		?= $(addprefix $(DPSDIR)/, $(notdir $(SRCS:.o=.d)))

#------------------------------------------#

.PHONY: all
all	:	$(STCS_ENV) \
		$(STCS_LEXER) \
		$(STCS_SIGNAL) \
		$(STCS_BUILTIN) \
		$(STCS_EXEC) \
		$(STCS_EXPANSION) \
		$(STCS_LIBFT) \
		$(STCS_PARSER) \
		$(STCS_UTILS) \
		$(STCS_EXIT_STATUS) \
		$(NAME) ## Run minishell

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@$(CC) $(CFLAGS) -MMD -MP -MF $(DPSDIR)/$(notdir $(<:.c=.d)) -c $< -o $@
	@printf "$(ESC_CLEAR_CURRENT_LINE)$(ESC_YELLOW)$< ⌛"
-include $(DPS)



.PHONY: $(STCS_ENV)
$(STCS_ENV):
	@$(MAKE) -C $(SRCDIR)/$(STCS_ENV)/.

.PHONY: $(STCS_LEXER)
$(STCS_LEXER):
	@$(MAKE) -C $(SRCDIR)/$(STCS_LEXER)/.

.PHONY: $(STCS_SIGNAL)
$(STCS_SIGNAL):
	@$(MAKE) -C $(SRCDIR)/$(STCS_SIGNAL)/.

.PHONY: $(STCS_BUILTIN)
$(STCS_BUILTIN):
	@$(MAKE) -C $(SRCDIR)/$(STCS_BUILTIN)/.

.PHONY: $(STCS_EXEC)
$(STCS_EXEC):
	@$(MAKE) -C $(SRCDIR)/$(STCS_EXEC)/.

.PHONY: $(STCS_EXPANSION)
$(STCS_EXPANSION):
	@$(MAKE) -C $(SRCDIR)/$(STCS_EXPANSION)/.

.PHONY: $(STCS_LIBFT)
$(STCS_LIBFT):
	@$(MAKE) -C $(SRCDIR)/$(STCS_LIBFT)/.

.PHONY: $(STCS_PARSER)
$(STCS_PARSER):
	@$(MAKE) -C $(SRCDIR)/$(STCS_PARSER)/.

.PHONY: $(STCS_UTILS)
$(STCS_UTILS):
	@$(MAKE) -C $(SRCDIR)/$(STCS_UTILS)/.

PHONY: $(STCS_EXIT_STATUS)
$(STCS_EXIT_STATUS):
	@$(MAKE) -C $(SRCDIR)/$(STCS_EXIT_STATUS)/.

$(NAME):	$(OBJS)
			@$(CC) $(OBJS) $(CFLAGS) $(LDFLAGS) $(STCS) -o $(NAME)
			@printf "$(ESC_CLEAR_CURRENT_LINE)$(ESC_GREEN)$(NAME): All files compiled$(ESC_DEFAULT). 👍\n"

.PHONY: dir
dir :
	@-mkdir -p $(OBJDIR)
	@-mkdir -p $(DPSDIR)
	@-mkdir -p $(STCSDIR)

.PHONY: san
san	:	${OBJS} ## Run sanitize using addres
			@$(MAKE) -s -C $(LIBDIR)
			@$(CC) $(OBJS) $(SANFLAGS) $(CFLAGS) $(LDFLAGS) $(LIBDIR)/libft.a $(STCS) -o $(NAME)

.PHONY: clean
clean	: ## Remove object
			@echo "$(ESC_CLEAR_SCREEN)"
			@$(RM) $(OBJDIR)
			@$(RM) $(DPSDIR)
			@echo "$(ESC_RED)${NAME}: '"$(OBJDIR)"' '"$(DPSDIR)"' has been deleted.$(ESC_DEFAULT)🗑️"

.PHONY: fclean
fclean	:	clean ## Remove object and static
			@$(RM) $(STCSDIR)
			@$(RM) $(NAME)
			@echo "$(ESC_RED)${NAME}: '"$(NAME)"' '"$(STCSDIR)"' has been deleted. $(ESC_DEFAULT)🗑️"

.PHONY: re
re	:	fclean all ## Retry cmpiles

debug: ## Compile nothing -W flg
		@$(MAKE) --debug DEBUG=1

norm: ## Run norm
	@printf "\e[31m"; norminette $(SRCDIR) $(INCLUDES) $(LIBDIR) \
    | grep -v -e ": OK!" -v -e "Missing or invalid header. Header are being reintroduced as a mandatory part of your files. This is not yet an error." \
    && exit 1 \
    || printf "\e[32m%s\n\e[m" "Norm OK!"; printf "\e[m"

.PHONY: help
help	: ## Display this help
	@grep -E '^[a-zA-Z1-9_-]+	:.*?## .*$$' $(MAKEFILE_LIST) | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-20s\033[0m %s\n", $$1, $$2}'