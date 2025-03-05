#!/usr/bin/env bash

# ============================================================================================================
# Launch libft.a tests
# This script take no argument (for now) and will automatically:
#   - 1: check norminette for libft folder (excluding Corr_libft_enhancde folder, tests dont comply with normi.)
#   - 2: list all home-made fun in libft.a
#   - 3: list all build-in fun in libft.a
#   - 4: launch libft mandatory functions tests.
#   - 5: if detected, launch test for libft_bonus functions.
#   - 6: if detected, launch test for ft_printf() tests (bonus too, auto)
#   - 7: if detected, launch test for get_next_line() tests (bonus too, auto)
# ============================================================================================================
 
# =[ VARIABLES ]==============================================================================================
# -[ PATH/FOLDER/FILE ]---------------------------------------------------------------------------------------
SCRIPTNAME=${0##*\/}                                       # ☒ Script's name (no path)
PARENT_DIR=$(dirname $(realpath ${0}))                     # ☒ Name of parent directory
LIBFT_DIR=$(dirname ${PARENT_DIR})                         # ☒ Name of libft_enhanced (grandparent folder)
LOG_DIR="${PARENT_DIR}/log/$(date +%Y_%m_%d/%Hh%Mm%Ss)"    # ☒ Name of the log folder
BSL_DIR="${PARENT_DIR}/src/BSL"                            # ☒ Path to BSL folder
# -[ LISTS ]--------------------------------------------------------------------------------------------------
HOMEMADE_FUNUSED=( )                                       # ☒ List of user created function in libft.a
BUILTIN_FUNUSED=( )                                        # ☒ List of build-in function in libft.a
EXCLUDE_NORMI_FOLD=( "tests" "${PARENT_DIR##*\/}" )        # ☒ List of folder to be ignore by norminette
LIBFT_MANDA=( "ft_isalpha" "ft_isdigit" "ft_isalnum" "ft_isascii" "ft_isprint" "ft_strlen" "ft_memset" \
    "ft_bzero" "ft_memcpy" "ft_memmove" "ft_strlcpy" "ft_strlcat" "ft_toupper" "ft_tolower" "ft_strchr" \
    "ft_strrchr" "ft_strncmp" "ft_memchr" "ft_memcmp" "ft_strnstr" "ft_atoi" "ft_calloc" "ft_strdup" \
    "ft_substr" "ft_strjoin" "ft_strtrim" "ft_split" "ft_itoa" "ft_strmapi" "ft_striteri" "ft_putchar_fd" \
    "ft_putstr_fd" "ft_putendl_fd" "ft_putnbr_fd" )
LIBFT_BONUS=( "ft_lstnew" "ft_lstadd_front" "ft_lstsize" "ft_lstlast" "ft_lstadd_back" "ft_lstdelone" \
    "ft_lstclear" "ft_lstiter" "ft_lstmap" )
# -[ LAYOUT ]-------------------------------------------------------------------------------------------------
LEN=100                                                    # ☑ Width of the box
# -[ COLORS ]-------------------------------------------------------------------------------------------------
E="\033[0m"                                                # ☒ END color balise
N0="\033[0;30m"                                            # ☒ START BLACK
R0="\033[0;31m"                                            # ☒ START RED
RU="\033[4;31m"                                            # ☒ START RED UNDERSCORED
V0="\033[0;32m"                                            # ☒ START GREEN
M0="\033[0;33m"                                            # ☒ START BROWN
Y0="\033[0;93m"                                            # ☒ START YELLOW
B0="\033[0;34m"                                            # ☒ START BLUE
BU="\033[4;34m"                                            # ☒ START BLUE
BC0="\033[0;36m"                                           # ☒ START AZURE
P0="\033[0;35m"                                            # ☒ START PINK
G0="\033[0;37m"                                            # ☒ START GREY
GU="\033[4;37m"                                            # ☒ START GREY
# =[ SOURCES ]================================================================================================
source ${BSL_DIR}/src/check42_norminette.sh
source ${BSL_DIR}/src/print.sh
# =[ FUNCTIONS ]==============================================================================================
# -[ USAGE ]--------------------------------------------------------------------------------------------------
# Display usage with arg1 as error_msg and arg2 as exit_code
script_usage()
{
    echo -e "${RU}[Err:${2}] Wrong usage${R0}: ${1}${E}\n${BU}Usage:${R0}  \`${V0}./${SCRIPTNAME}\`${E}"
    echo -e " 🔹 ${V0}${SCRIPTNAME}${E} has as a prerequisites:"
    echo -e "    ${B0}‣ ${R0}i) ${E}: To be cloned inside the project ${M0}path/libft/${E} to be tested."
    echo -e "    ${B0}‣ ${R0}ii)${E}: The static lib ${M0}path/libft/*/${B0}libft.a${E} has to be compiled before using ${V0}./${SCRIPTNAME}${E}."
    echo -e " 🔹 ${V0}${SCRIPTNAME}${E} takes no arguments and will automatically:"
    echo -e "    ${B0}‣ ${R0}1${E}: Check if ${M0}libft/${E} complies with the 42-norme"
    echo -e "    ${B0}‣ ${R0}2${E}: Display a list of all function found in the ${B0}libft.a${E} static lib"
    echo -e "    ${B0}‣ ${R0}3${E}: Display a list of all built-in function called by ${B0}libft.a"
    echo -e "    ${B0}‣ ${R0}4${E}: Launch at least the tests for the libft (mandatory part)"
    echo -e "    ${B0}‣ ${R0}5${E}: If libft bonus fun. detected, launch the libft bonus part tests"
    echo -e "    ${B0}‣ ${R0}6${E}: If ${G0}ft_print()${E} fun. detected, launch the tests for both its mandatory & bonus part)"
    echo -e "    ${B0}‣ ${R0}7${E}: If ${G0}get_next_line()${E} fun. detected, launch the tests for both its mandatory & bonus part)"
    echo -e "    ${B0}‣ ${R0}8${E}: If any other ${G0}home-made${E} fun. is detected ${RU}AND${E} if a corresponding test is found (matching name), then it will be test too.${BU}(use for personnal function)${E}"
    echo -e "    ${B0}‣ ${R0}9${E}: Display a resume."
    exit ${2}
}
# -[ EXEC_ANIM_IN_BOX ]---------------------------------------------------------------------------------------
# Takes 2args: arg1:<cmd> [arg2:<title>]
# exec command passed as arg1 while displaying animation, return result in a box colored red if cmd failed, green else
exec_anim_in_box()
{
    [[ ( ${#} -gt 2 ) ]] && { echo -e "\033[1;31mWRONG USAGE of:\033[1;36mexec_anim()\033[1;31m, this function take 2 arguments max.\033[0m" && exit 3 ; }
    local frames=( 🕛  🕒  🕕  🕘 )
    local delay=0.15
    local cmd="${1}"
    [[ ${#} -eq 2 ]] && local boxtitle="${2}" || local boxtitle="${cmd}"
    local tmpfile=$(mktemp "${TMPDIR:-/tmp}/exec_anim_${cmd%% *}_XXXXXX")
    trap '[[ -f "${tmpfile}" ]] && rm -f "${tmpfile}"' EXIT RETURN
    ${1} > "${tmpfile}" 2>&1 &
    local pid=${!}
    while kill -0 ${pid} 2>/dev/null; do
        for frame in "${frames[@]}"; do printf "${frame} \033[1;40mwaiting for cmd:${1}\033[0m\r" && sleep ${delay} ; done
    done
    printf "\r\033[K" && wait ${pid}
    local exit_code=${?}
    [[ ${exit_code} -eq 0 ]] && local color="green" || local color="red"
    print_box_title -t 1 -c ${color} "${boxtitle}"
    while IFS= read -r line; do
        echol -i 0 -c ${color} -t 1 "${line}"
    done < "${tmpfile}"
    print_last -t 1 -c ${color}
    return ${exit_code}
}

# -[ LAUNCH_TEST_LIBFT_MANDATORY() ]--------------------------------------------------------------------------
# Launch test for all mandatory function needed for libft
launch_test_libft_mandatory()
{
    for fun in ${LIBFT_MANDA[@]};do
        test_main=$(find "${BSL_DIR}" -type f -name "${fun}"*.c)
        echo "fun=${fun}"
        echo "test_main=${test_main}"
        [[ -z "${test_main}" ]] && echo test found || echo test not found
    done
}

# ============================================================================================================
# MAIN
# ============================================================================================================
# =[ CHECK IF LIBFT.A FOUNDED ]===============================================================================
LIBFT_A=$(find ${LIBFT_DIR} -type f -name "libft.a")
[[ -z ${LIBFT_A} ]] && { script_usage "${R0}Static lib not found: No ${B0}libft.a${R0} file inside ${M0}${LIBFT_DIR}/${R0} folder.${E}" 2; }
# =[ CREATE LOG_DIR ]=========================================================================================
[[ ! -d ${LOG_DIR} ]] && mkdir -p ${LOG_DIR}
# =[ CHECK NORMINETTE ]=======================================================================================
exec_anim_in_box "check42_norminette ${LIBFT_DIR}" "Check Norminette"
# =[ LST_FUNUSED ]============================================================================================
# -[ SET LISTS HOMEMADE_FUNUSED BUILTIN_FUNUSED ]-------------------------------------------------------------
for obj in ${LIBFT_A};do 
    if [[ -f ${obj} ]];then
        if file "${obj}" | grep -qE 'relocatable|executable|shared object|ar archive';then
            for fun in $(nm -C "${obj}" | awk '$2 == "T" {print $3}' | sort | uniq);do
                [[ ! " ${HOMEMADE_FUNUSED[@]} " =~ " $fun " ]] && HOMEMADE_FUNUSED+=( "${fun}" )
            done
            for fun in $(nm -C "${obj}" | awk '$2 == "U" {print $3}' | sort | uniq);do
                if [[ ! " ${HOMEMADE_FUNUSED[@]} " =~ " $fun " ]];then
                    [[ ! " ${BUILTIN_FUNUSED[@]} " =~ " $fun " ]] && BUILTIN_FUNUSED+=( "${fun}" )
                fi
            done
        else
            echo -e "${B0}${obj}${E} is not an object file\033[m"
        fi
    else
        echo -e "${B0}${obj}${E} is not a file\033[m"
    fi
done
exec_anim_in_box "launch_test_libft_mandatory" "Tests libft mandatory functions"
