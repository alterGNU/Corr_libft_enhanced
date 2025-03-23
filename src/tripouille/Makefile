TIMEOUT_US				= 1000000

.DEFAULT_GOAL			= a
UTILS					= utils/sigsegv.cpp utils/color.cpp utils/check.cpp utils/gnl.cpp utils/leaks.cpp
TESTS_PATH				= tests/
SHELL					= bash


LIBFT_A					= $(shell find ../../.. -name 'libft.a' 2>/dev/null | head -n 1)

MANDATORY				= mandatory
1MANDATORY				= $(addprefix 1, $(MANDATORY))
42MANDATORY				= $(addprefix 42, $(MANDATORY))
10MMANDATORY			= $(addprefix 10M, $(MANDATORY))


BONUS					= bonus
1MBONUS					= $(addprefix m1, $(BONUS))
42MBONUS				= $(addprefix m42, $(BONUS))
10MMBONUS				= $(addprefix m10M, $(BONUS))

1BONUS					= $(addprefix 1, $(BONUS))
42BONUS					= $(addprefix 42, $(BONUS))
10MBONUS				= $(addprefix 10M, $(BONUS))

CFLAGS					= -g3 -Wall -Wextra -Werror
CPPFLAGS				= -g3 -ldl -std=c++11 -I utils/ -I.. -Wno-everything

UNAME = $(shell uname -s)
ifeq ($(UNAME), Linux)
    VALGRIND = valgrind -q --leak-check=full
endif

$(1MANDATORY): 1%:
	@clang++ -D BUFFER_SIZE=1 -gdwarf-4 -D TIMEOUT_US=$(TIMEOUT_US) $(CPPFLAGS) $(UTILS) $(TESTS_PATH)$*.cpp $(LIBFT_A) -o gnlTest && $(VALGRIND) ./gnlTest < files/alternate_line_nl_with_nl && rm -f gnlTest
$(42MANDATORY): 42%:
	@clang++ -D BUFFER_SIZE=42 -gdwarf-4 -D TIMEOUT_US=$(TIMEOUT_US) $(CPPFLAGS) $(UTILS) $(TESTS_PATH)$*.cpp $(LIBFT_A) -o gnlTest && $(VALGRIND) ./gnlTest < files/alternate_line_nl_with_nl && rm -f gnlTest
$(10MMANDATORY): 10M%:
	@clang++ -D BUFFER_SIZE=10000000 -gdwarf-4 -D TIMEOUT_US=$(TIMEOUT_US) $(CPPFLAGS) $(UTILS) $(TESTS_PATH)$*.cpp $(LIBFT_A) -o gnlTest && $(VALGRIND) ./gnlTest < files/alternate_line_nl_with_nl && rm -f gnlTest


$(1BONUS): 1%:
	@clang++ -D BUFFER_SIZE=1 -gdwarf-4 -D TIMEOUT_US=$(TIMEOUT_US) $(CPPFLAGS) $(UTILS) $(TESTS_PATH)$*.cpp $(LIBFT_A) -o gnlTest && $(VALGRIND) ./gnlTest < files/alternate_line_nl_with_nl && rm -f gnlTest
$(42BONUS): 42%:
	@clang++ -D BUFFER_SIZE=42 -gdwarf-4 -D TIMEOUT_US=$(TIMEOUT_US) $(CPPFLAGS) $(UTILS) $(TESTS_PATH)$*.cpp $(LIBFT_A) -o gnlTest && $(VALGRIND) ./gnlTest < files/alternate_line_nl_with_nl && rm -f gnlTest
$(10MBONUS): 10M%:
	@clang++ -D BUFFER_SIZE=10000000 -gdwarf-4 -D TIMEOUT_US=$(TIMEOUT_US) $(CPPFLAGS) $(UTILS) $(TESTS_PATH)$*.cpp $(LIBFT_A) -o gnlTest && $(VALGRIND) ./gnlTest < files/alternate_line_nl_with_nl && rm -f gnlTest

$(1MBONUS): m1%:
	@clang++ -D BUFFER_SIZE=1 -gdwarf-4 -D TIMEOUT_US=$(TIMEOUT_US) $(CPPFLAGS) $(UTILS) $(TESTS_PATH)$(MANDATORY).cpp $(LIBFT_A) -o gnlTest && $(VALGRIND) ./gnlTest < files/alternate_line_nl_with_nl && rm -f gnlTest
$(42MBONUS): m42%:
	@clang++ -D BUFFER_SIZE=42 -gdwarf-4 -D TIMEOUT_US=$(TIMEOUT_US) $(CPPFLAGS) $(UTILS) $(TESTS_PATH)$(MANDATORY).cpp $(LIBFT_A) -o gnlTest && $(VALGRIND) ./gnlTest < files/alternate_line_nl_with_nl && rm -f gnlTest
$(10MMBONUS): m10M%:
	@clang++ -D BUFFER_SIZE=10000000 -gdwarf-4 -D TIMEOUT_US=$(TIMEOUT_US) $(CPPFLAGS) $(UTILS) $(TESTS_PATH)$(MANDATORY).cpp $(LIBFT_A) -o gnlTest && $(VALGRIND) ./gnlTest < files/alternate_line_nl_with_nl && rm -f gnlTest

mandatory_start:
	@tput setaf 4 && echo [Mandatory]

bonus_start:
	@tput setaf 3 && printf "[Static = " && cat ../*bonus.c | grep -E 'static.*;' | wc -l | tr -d '\n' | xargs /bin/echo -n && printf "]\n"
	@tput setaf 5 && /bin/echo [Bonus]

m: mandatory_start $(1MANDATORY) $(42MANDATORY) $(10MMANDATORY) cleanMandatory
b: bonus_start $(1MBONUS) $(42MBONUS) $(10MMBONUS) $(1BONUS) $(42BONUS) $(10MBONUS) cleanBonus
a: m b

fclean clean cleanMandatory cleanBonus:
	@rm -rf gnlTest*

.PHONY:	mandatory_start m bonus_start b a fclean clean cleanMandatory cleanBonus
