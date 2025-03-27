.DEFAULT_GOAL	:= a
UTILS			= $(addprefix utils/, sigsegv.cpp color.cpp check.cpp leaks.cpp)
PARENT_DIR		= $(shell dirname $(shell pwd))
LIBFT_A			= $(shell find ../../../.. -name 'libft.a' 2>/dev/null | head -n 1)
LIBFT_H			= $(shell find ../../../.. -name 'libft.h' 2>/dev/null | head -n 1)
INCLUDE			= $(shell dirname $(LIBFT_H))
LIBFT_PATH		= $(shell dirname $(INCLUDE))
TESTS_PATH		= tests/
MANDATORY		= memset bzero memcpy memmove memchr memcmp strlen isalpha isdigit isalnum \
				isascii isprint toupper tolower strchr strrchr strncmp strlcpy strlcat strnstr \
				atoi calloc strdup substr strjoin strtrim split itoa strmapi putchar_fd putstr_fd \
				putendl_fd putnbr_fd striteri
BONUS			= lstnew lstadd_front lstsize lstlast lstadd_back lstdelone lstclear lstiter lstmap
VSOPEN			= $(addprefix vs, $(MANDATORY)) $(addprefix vs, $(BONUS))

CC		= clang++
CFLAGS	= -g3 -ldl -gdwarf-4 -std=c++11 -I utils/ -I$(INCLUDE) -no-pie
UNAME = $(shell uname -s)
ifeq ($(UNAME), Linux)
	VALGRIND = valgrind -q --leak-check=full
endif

$(MANDATORY): %: mandatory_start
	@$(CC) $(CFLAGS) $(UTILS) $(TESTS_PATH)ft_$*_test.cpp $(LIBFT_A) && $(VALGRIND) ./a.out && rm -f a.out

$(BONUS): %: bonus_start
	@$(CC) $(CFLAGS) $(UTILS) $(TESTS_PATH)ft_$*_test.cpp $(LIBFT_A) && $(VALGRIND) ./a.out && rm -f a.out

$(VSOPEN): vs%:
	@code $(TESTS_PATH)ft_$*_test.cpp

mandatory_start:
	@tput setaf 6
	make -C $(LIBFT_PATH)
	@tput setaf 4 && echo [Mandatory]

bonus_start:
	@tput setaf 6
	make bonus -C $(LIBFT_PATH)
	@tput setaf 5 && echo [Bonus]

m: $(MANDATORY)
b: $(BONUS)
a: m b 

clean:
	rm -rf a.out*

fclean:
	rm -rf a.out*

.PHONY:	mandatory_start m bonus_start b a fclean clean $(VSOPEN)
