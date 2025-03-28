TIMEOUT_US 		= 400000 #if you timeout you can try to increase this value

.DEFAULT_GOAL	:= m
SHELL			= bash

LIBFT_A			= $(shell find ../../../.. -name 'libft.a' 2>/dev/null | head -n 1)
LIBFT_H			= $(shell find ../../../.. -name 'libft.h' 2>/dev/null | head -n 1)
INCLUDE			= $(shell dirname $(LIBFT_H))

UTILS_PATH		= utils/
UTILS			= $(addprefix $(UTILS_PATH), sigsegv.cpp color.cpp check.cpp leaks.cpp)

TESTS_PATH		= tests/
MANDATORY		= c s p d i u x upperx percent mix

BONUS			= minus 0 dot sharp space +

CC				= clang++ -std=c11 -Wno-everything
CFLAGS			= -g3 -ldl -std=c++11 -I utils/ -I$(INCLUDE) $(addprefix -I, $(shell find .. -regex ".*/.*\.h" | grep -oh ".*/"))

TEST_NUMBER := $(wordlist 2, $(words $(MAKECMDGOALS)), $(MAKECMDGOALS))
$(eval $(TEST_NUMBER):;@:)

UNAME = $(shell uname -s)
ifeq ($(UNAME), Linux)
    VALGRIND = valgrind -q --leak-check=full --track-origins=yes
endif

$(MANDATORY): %:
	@$(CC) $(CFLAGS) -gdwarf-4 -D TIMEOUT_US=$(TIMEOUT_US) $(UTILS) $(TESTS_PATH)$*_test.cpp $(LIBFT_A) -o $*_test && $(VALGRIND) ./$*_test $(TEST_NUMBER) && rm -f $*_test

$(BONUS): %:
	@$(CC) $(CFLAGS) -gdwarf-4 -D TIMEOUT_US=$(TIMEOUT_US) $(UTILS) $(TESTS_PATH)$*_test.cpp $(LIBFT_A) -o $*_test && $(VALGRIND) ./$*_test $(TEST_NUMBER) && rm -f $*_test

m: $(MANDATORY) 
b: $(BONUS)
a: m b 

clean:
	rm -rf *_test && rm -rf *_test.dSYM

fclean:
	rm -rf *_test && rm -rf *_test.dSYM

.PHONY:	m b a clean update fclean
