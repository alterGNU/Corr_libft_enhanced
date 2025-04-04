#!/usr/bin/env bash

# ============================================================================================================
# This script runs tests on the static library libft.a where get_next_line(), ft_print() and other personnal
# functions could have been added.
#
# To do so, it runs Tripouille's tester for libft, get_next_line and ft_printf functions, but also my own
# tester refered as My_unitests.
#
# - This script take options as arguments:
#   - NO-ARGS
#   - ARGS ∈ {-+h, --++help}                 🢥  -+Enable HELP option that display script usage
#   - ARGS ∈ {-+n, --++no-norm}              🢥  -Desable +Enable the NORM-CHECKER STEP
#   - ARGS ∈ {-+bi, --++built-in}            🢥  -Desable +Enable Display built-in found
#   - ARGS ∈ {-+bo, --++bonus}               🢥  -Desable +Enable Bonus option for all tester
#   - ARGS ∈ {-+a, --++all}                  🢥  -Desable +Enable ALL TRIPOUILLE AND MY_UNITESTS OPTION WITHOUT BONUS
#   - ARGS ∈ {-+t, --++tripouille}           🢥  -Desable +Enable ALL TRIPOUILLE && Disable ALL MY_UNITESTS
#   - ARGS ∈ {-+l, -+lft, --++libft}         🢥  -Desable +Enable tests for LIBFT
#   - ARGS ∈ {-+p, --++ft_printf}            🢥  -Desable +Enable tests for FT_PRINTF
#   - ARGS ∈ {-+g, -gnl, --++get_next_line}  🢥  -Desable +Enable tests for GET_NEXT_LINE
#   - ARGS ∈ {-+o, --++other}                🢥  -Desable +Enable tests OTHERS FUNCTIONS FOUND (USER-MADE fun)
#
# - NOTES:
#   - To test a personnal function add to libft.a, just add its unitests like:
#     ${MY_UNITESTS}/tests_<fun_name>.c and launch this script using -a or -o options:
# ============================================================================================================
 
# =[ VARIABLES ]==============================================================================================
# -[ SCRIPT OPTIONS ]-----------------------------------------------------------------------------------------
HELP=0                                                             # ☑ if set at 1🢥 Display script usage
BONUS=0                                                            # ☑ if set at 1🢥 Launch all test with bonus option
NORM=1                                                             # ☑ if set at 1🢥 Launch NORMINETTE TESTER
BUIN=1                                                             # ☒ if set at 1🢥 Display list of built-in fun used
MY_UNITESTS_LIBFT=1                                                # ☑ if set at 1🢥 Launch my tester for LIBFT(DEFAULT)
MY_UNITESTS_GNL=0                                                  # ☑ if set at 1🢥 Launch my tester for GNL(DEFAULT)
MY_UNITESTS_PRINTF=0                                               # ☑ if set at 1🢥 Launch my tester for PRINTF(DEFAULT)
MY_UNITESTS_OTHERS=1                                               # ☑ if set at 1🢥 Launch my tester for OTHERS_FUNCTION_FOUND(DEFAULT)
TRIPOUILLE_LIBFT=0                                                 # ☑ if set at 1🢥 Launch Tripouille for libft()
TRIPOUILLE_GNL=0                                                   # ☑ if set at 1🢥 Launch Tripouille for get_next_line()
TRIPOUILLE_PRINTF=0                                                # ☑ if set at 1🢥 Launch Tripouille for ft_printf()
# -[ PATH/FOLDER/FILE ]---------------------------------------------------------------------------------------
SCRIPTNAME=${0##*\/}                                               # ☒ Script's name (no path)
PARENT_DIR=$(dirname $(realpath ${0}))                             # ☒ Name of parent directory
LIBFT_DIR=$(dirname ${PARENT_DIR})                                 # ☒ Name of libft_enhanced (grandparent folder)
LOG_DIR="${PARENT_DIR}/log/$(date +%Y_%m_%d/%Hh%Mm%Ss)"            # ☒ Name of the log folder
LOG_FAIL="${LOG_DIR}/list_errors.log"                              # ☒ File contains list of function that failed
SRC_DIR="${PARENT_DIR}/src"                                        # ☒ Path to src folder
BSL="${SRC_DIR}/BSL"                                               # ☒ Path to BSL folder
MY_UNITESTS="${SRC_DIR}/my_unitests"                               # ☒ Path to my_unitests folder
TRIPOUILLE="${SRC_DIR}/tripouille"                                 # ☒ Path to tripouille folder
BIN_DIR="${PARENT_DIR}/bin"                                        # ☒ Path to bin folder (test binary)
LIBFT_A=$(find ${LIBFT_DIR} -type f -name "libft.a")               # ☒ static library name libft.a 
LIBFT_INC=$(dirname $(find ${LIBFT_DIR} -type f -name "libft.h"))  # ☒ Folder that contains to libft.h HEADER
# -[ COMMANDS ]-----------------------------------------------------------------------------------------------
CC="cc -Wall -Wextra -Werror -I${LIBFT_INC}"
VAL_ERR=42
VALGRIND="valgrind --leak-check=full --track-fds=yes --error-exitcode=${VAL_ERR}"
# -[ LAYOUT ]-------------------------------------------------------------------------------------------------
LEN=100                                                            # ☑ Width of lines (and therefore of boxes)
# -[ COLORS ]-------------------------------------------------------------------------------------------------
E="\033[0m"                                                        # ☒ END color balise
N0="\033[0;30m"                                                    # ☒ START BLACK
R0="\033[0;31m"                                                    # ☒ START RED
RU="\033[4;31m"                                                    # ☒ START RED UNDERSCORED
V0="\033[0;32m"                                                    # ☒ START GREEN
M0="\033[0;33m"                                                    # ☒ START BROWN
Y0="\033[0;93m"                                                    # ☒ START YELLOW
YU="\033[4;93m"                                                    # ☒ START YELLOW UNDERSCORED
B0="\033[0;34m"                                                    # ☒ START BLUE
BU="\033[4;34m"                                                    # ☒ START BLUE
BC0="\033[0;36m"                                                   # ☒ START AZURE
BCU="\033[4;36m"                                                   # ☒ START AZURE UNDERSCORED
P0="\033[0;35m"                                                    # ☒ START PINK
G0="\033[2;37m"                                                    # ☒ START GREY
GU="\033[4;37m"                                                    # ☒ START GREY
# -[ LISTS ]--------------------------------------------------------------------------------------------------
OPTIONS=("${YU}LIST OF ALL ACTIVATED OPTIONS:${E}" )               # ☒ List of script options enabled
HOMEMADE_FUNUSED=( )                                               # ☒ List of user created function in libft.a
BUILTIN_FUNUSED=( )                                                # ☒ List of build-in function in libft.a
PERSO_FUN=( )                                                      # ☒ List of personnal function (HOMEMADE_FUN - LIBFT_MANDA - LIBFT_BONUS - get_next_line - ft_printf)
PERSO_FUN_TO_TEST=( )                                              # ☒ List of personnal function for which a test was found
EXCLUDE_NORMI_FOLD=( "tests" "${PARENT_DIR##*\/}" )                # ☒ List of folder to be ignore by norminette
LIBFT_MANDA=( "ft_isalpha" "ft_isdigit" "ft_isalnum" "ft_isascii" "ft_isprint" "ft_strlen" "ft_memset" \
    "ft_bzero" "ft_memcpy" "ft_memmove" "ft_strlcpy" "ft_strlcat" "ft_toupper" "ft_tolower" "ft_strchr" \
    "ft_strrchr" "ft_strncmp" "ft_memchr" "ft_memcmp" "ft_strnstr" "ft_atoi" "ft_calloc" "ft_strdup" \
    "ft_substr" "ft_strjoin" "ft_strtrim" "ft_split" "ft_itoa" "ft_strmapi" "ft_striteri" "ft_putchar_fd" \
    "ft_putstr_fd" "ft_putendl_fd" "ft_putnbr_fd" )
LIBFT_BONUS=( "ft_lstnew" "ft_lstadd_front" "ft_lstsize" "ft_lstlast" "ft_lstadd_back" "ft_lstdelone" \
    "ft_lstclear" "ft_lstiter" "ft_lstmap" )
# -[ COUNT ]--------------------------------------------------------------------------------------------------
TOT_TESTS="${#LIBFT_MANDA[@]}"                                     # ☒ Count how many fun are tested
TOT_FAILS=0                                                        # ☒ Count how many fun have failed
# =[ SOURCES ]================================================================================================
source ${BSL}/src/check42_norminette.sh
source ${BSL}/src/print.sh
# =[ FUNCTIONS ]==============================================================================================
# -[ USAGE ]--------------------------------------------------------------------------------------------------
# Display usage:
# without arguments, display a default entete and return zero
# with arguments, displaye entete with arg1 as error_msg and return arg2 as the exit_value.
script_usage()
{
    local exit_value=0
    local entete="\n${BU}Usage:${R0}  \`${V0}./${SCRIPTNAME}\` ${M0}+-[h, n, a, t, bi, bo, l, f, g, o]${E}"
    if [[ ${#} -eq 2 ]];then
        local entete="${RU}[Err:${2}] Wrong usage${R0}: ${1}${E}\n${BU}Usage:${R0}  \`${V0}./${SCRIPTNAME}\` ${M0}+-[h, n, a, t, bi, bo, l, f, g, o]${E}"
        local exit_value=${2}
    fi
    echo -e "${entete}"
    echo -e " 🔹 ${BCU}STEPS:${E}"
    echo -e "    ${B0}‣ ${BC0}|STEP 0| ${GU}List-Options${E}               ${BC0} 🢥  ${E}Display the list of enabled/desabled options."
    echo -e "    ${B0}‣ ${BC0}|STEP 1| ${GU}List-Builtin${E}               ${BC0} 🢥  ${E}Display the libft buit-in functions used."
    echo -e "    ${B0}‣ ${BC0}|STEP 2| ${GU}Norme-checker${E}              ${BC0} 🢥  ${E}Run the norminette."
    echo -e "    ${B0}‣ ${BC0}|STEP 3| ${GU}Tripouille-tests${E}           ${BC0} 🢥  ${E}Run Tripouille's tester on libft functions."
    echo -e "    ${B0}‣ ${BC0}|STEP 4| ${GU}My-Unitests${E}                ${BC0} 🢥  ${E}Run unitests on minishell user-made functions."
    echo -e "    ${B0}‣ ${BC0}|STEP 5| ${GU}Display a My-unitests Resume${E}${BC0}🢥  ${E}Display a resume of failed/passed unitests."
    echo -e " 🔹 ${BU}PRE-REQUISITES:${E}"
    echo -e "    ${B0}‣ ${R0}i) ${E}: To be cloned inside the project ${M0}path/libft/${E} to be tested, with the ${M0}--recursive-submodules${E} option."
    echo -e "    ${B0}‣ ${R0}ii)${E}: The static lib ${M0}path/libft/*/${B0}libft.a${E} has to be compiled before using ${V0}./${SCRIPTNAME}${E}."
    echo -e " 🔹 ${BU}OPTIONS:${E} ${V0}+ Enable${E}, ${R0}- Desable${E} option"
    echo -e "    ${B0}‣ ${V0}+${R0}-${M0}[h] ${BC0} --> ${E}HELP                   :Display this usage."
    echo -e "    ${B0}‣ ${V0}+${R0}-${M0}[a] ${BC0} --> ${E}ALL OPTIONS            :Affect all options."
    echo -e "    ${B0}‣ ${V0}+${R0}-${M0}[bi]${BC0} --> ${E}BUILTIN      (STEP 1  ):Display Built-in fun. founded."
    echo -e "    ${B0}‣ ${V0}+${R0}-${M0}[n] ${BC0} --> ${E}NORMINETTE   (STEP 2  ):Run norminette."
    echo -e "    ${B0}‣ ${V0}+${R0}-${M0}[t] ${BC0} --> ${E}TRIPOUILLE   (STEP 3  ):Run Tripouille's testers."
    echo -e "    ${B0}‣ ${V0}+${R0}-${M0}[l] ${BC0} --> ${E}LIBFT        (STEP 3&4):Run Tripouille & My-unitest's libft testers."
    echo -e "    ${B0}‣ ${V0}+${R0}-${M0}[bo]${BC0} --> ${E}BONUS        (STEP 3&4):Enable Bonus-part evaluation option for all testers."
    echo -e "    ${B0}‣ ${V0}+${R0}-${M0}[p] ${BC0} --> ${E}FT_PRINTF    (STEP 3&4):Run Tripouille & My-unitest's ft_printf testers."
    echo -e "    ${B0}‣ ${V0}+${R0}-${M0}[g] ${BC0} --> ${E}GET_NEXT_LINE(STEP 3&4):Run Tripouille & My-unitest's get_next_line tester."
    echo -e "    ${B0}‣ ${V0}+${R0}-${M0}[o] ${BC0} --> ${E}OTHERS       (STEP 4  ):Run My_unitests for others user-made functions found."
    exit ${exit_value}
}
# -[ MAX() ]--------------------------------------------------------------------------------------------------
max()
{
    if (($1 > $2));then
        echo $1
    else
        echo $2
    fi
}
# -[ PRINT_RELATIF_PATH() ]-----------------------------------------------------------------------------------
# substract pwd from arg1 abs-path given
print_shorter_path() { echo "${1/${PWD}/.}" ; }
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
    print_box_title -t 3 -c ${color} "${boxtitle}"
    while IFS= read -r line; do
        echol -i 0 -c ${color} -t 3 "${line}"
    done < "${tmpfile}"
    print_last -t 3 -c ${color}
    return ${exit_code}
}

# -[ DISPLAY_START ]------------------------------------------------------------------------------------------
display_start()
{
    local OPTIONS=( " ${YU}LIBFT's OPTIONS:${E}" )
    [[ ${BUIN} -gt 0 ]] && OPTIONS+=( "     🔸 ${YU}STEP 1)${Y0} BUILT-IN LISTER:................${V0}✓ Enable${E}" ) || OPTIONS+=( "     🔸 ${YU}STEP 1)${Y0} BUILT-IN LISTER:................${R0}✘ Desable${E}" )
    [[ ${NORM} -gt 0 ]] && OPTIONS+=( "     🔸 ${YU}STEP 2)${Y0} NORM CHECKER:...................${V0}✓ Enable${E}" ) || OPTIONS+=( "     🔸 ${YU}STEP 2)${Y0} NORM CHECKER:...................${R0}✘ Desable${E}" )
    OPTIONS+=( "     🔸 ${YU}STEP 3)${Y0} TRIPOUILLE'S TESTER:")
    [[ ${TRIPOUILLE_LIBFT} -gt 0 ]]   && OPTIONS+=( "        ${Y0}▸ Libft tester:.........................${V0}✓ Enable${E}" ) || OPTIONS+=( "        ${Y0}▸ Libft tester:.........................${R0}✘ Desable${E}" )
    [[ ${TRIPOUILLE_GNL} -gt 0 ]]     && OPTIONS+=( "        ${Y0}▸ get_next_line tester:.................${V0}✓ Enable${E}" ) || OPTIONS+=( "        ${Y0}▸ get_next_line tester:.................${R0}✘ Desable${E}" )
    [[ ${TRIPOUILLE_PRINTF} -gt 0 ]]  && OPTIONS+=( "        ${Y0}▸ ft_printf tester:.....................${V0}✓ Enable${E}" ) || OPTIONS+=( "        ${Y0}▸ ft_printf tester:.....................${R0}✘ Desable${E}" )
    OPTIONS+=( "     🔸 ${YU}STEP 4)${Y0} MY_UNITESTS TESTER:")
    [[ ${MY_UNITESTS_LIBFT} -gt 0 ]]  && OPTIONS+=( "        ${Y0}▸ Libft tester:.........................${V0}✓ Enable${E}" ) || OPTIONS+=( "        ${Y0}▸ Libft tester:.........................${R0}✘ Desable${E}" )
    [[ ${MY_UNITESTS_GNL} -gt 0 ]]    && OPTIONS+=( "        ${Y0}▸ get_next_line tester:.................${V0}✓ Enable${E}" ) || OPTIONS+=( "        ${Y0}▸ get_next_line tester:.................${R0}✘ Desable${E}" )
    [[ ${MY_UNITESTS_PRINTF} -gt 0 ]] && OPTIONS+=( "        ${Y0}▸ ft_printf tester:.....................${V0}✓ Enable${E}" ) || OPTIONS+=( "        ${Y0}▸ ft_printf tester:.....................${R0}✘ Desable${E}" )
    [[ ${MY_UNITESTS_OTHERS} -gt 0 ]] && OPTIONS+=( "        ${Y0}▸ other user-made fun. tester:..........${V0}✓ Enable${E}" ) || OPTIONS+=( "        ${Y0}▸ other user-made fun. tester:..........${R0}✘ Desable${E}" )
    [[ ( ${MY_UNITESTS_LIBFT} -gt 0 ) || ( ${MY_UNITESTS_GNL} -gt 0 ) || ( ${MY_UNITESTS_PRINTF} -gt 0 ) || (
    ${MY_UNITESTS_OTHERS} -gt 0 ) ]] && OPTIONS+=( "     🔸 ${YU}STEP 5)${Y0} RESUME:.........................${V0}✓ Enable${E}" ) || OPTIONS+=( "     🔸 ${YU}STEP 2)${Y0} RESUME:.........................${R0}✘ Desable${E}" )
    print_in_box -t 2 -c y \
        "           ${Y0}  _     ___  ___  ___  _____       _   _        _  _             _        ${E}" \
        "           ${Y0} | |   |_ _|| _ )| __||_   _|     | | | | _ _  (_)| |_  ___  ___| |_  ___ ${E}" \
        "           ${Y0} | |__  | | | _ \| _|   | |       | |_| || ' \ | ||  _|/ -_)(_-<|  _|(_-< ${E}" \
        "           ${Y0} |____||___||___/|_|    |_|        \___/ |_||_||_| \__|\___|/__/ \__|/__/ ${E}" \
        "           ${Y0}                                                                          ${E}" \
        "  🔶 ${OPTIONS[@]}"
}

# -[ LAUNCH_MY_UNITESTS ]-------------------------------------------------------------------------------------
# Function that launch my unitests for each <function_name> found in <list_name> given as arg1 or arg2.
# Compile then Exec unitests will creating log_files then returns the numbers of errors encountred.
# - USAGE:
#   - Take one to two arguments:
#     - arg1 (mandatory): list_name of a list that contains all the <function_name> fount in object.
#       - `launch_my_unitests FUN_TO_TEST` --> will launch unitests for all function in list name: FUN_TO_TEST
#     - arg2 (optionnal): list_name of a list that contains all the <function_name> THAT HAVE TO BE FOUND in object.
#       - `launch_my_unitests LST1 LST2` --> will launch unitests for all fun in LST2 and LST1, if not in LST1=ERROR
# - LOG FILES PRODUCE:
# - ../log/<date>/<time>/${LOG_FAIL}                --> File contains list of all encountred errors, format="<fun_name>\t<error_type>"
#                                                   └-> error_type = {compilation, errors, leaks, missing}                        
# - ../log/<date>/<time>/<fun_name>/                --> Folder created for each function tested (remove if empty at the end)
# - ../log/<date>/<time>/<fun_name>/comp_stderr.txt --> File created only when compilation failed: contains compilation error messages.
# - ../log/<date>/<time>/<fun_name>/exec.log        --> File contains execution's outputs (stdout && stderr)
# - ../log/<date>/<time>/<fun_name>/leaks.log       --> File contains valgrind's outputs (stdout && stderr)
# - PSEUDO-CODE:
#   - (0): INPUT VALIDATION
#     - Check number of args given valid, else exit.
#     - Build the 2 needed arrays: FUN_FOUND (list of fun found in obj), FUN_MANDA (list of fun needed)
#       - If only arg1    --> FUN_FOUND == FUN_MANDA == ${arg1[@]}
#       - If arg1 && arg2 --> FUN_FOUND == ${arg1[@]} && FUN_MANDA == ${arg2[@]}
#     - Check if builded lists valid, else exit.
#   - (1): LOOP TROUGHT FUN_MANDA
#     - if <fun> not in FUN_FOUND --> nb_err++;
#     - else check if an unitests exist:
#        - (1.0) Create directory ../log/<date>/<time>/<fun_name>/
#        - (1.1) COMPILE if compilation needed, if compilation fail --> nb_err++ && create comp_stderr.txt
#        - (1.2) EXEC if compilation succed, redir stdout && stderr to exec.log, if exec failed --> nb_err++
#        - (1.3) VALGRIND if compilation succed, redir stdout && stderr to leaks.log, if valgrind failed --> nb_err++
#        - (1.4) If ../log/<date>/<time>/<fun_name>/ empty, remove the directory
launch_my_unitests()
{
    # INPUT VALIDATION
    [[ ${#} -eq 0 || ${#} -gt 2 ]] && { echo "${R0}WRONG USAGE OF launch_my_unitests():wrong number of argument" && exit 2 ; }
    local -a FUN_FOUND=( )     # list of all fun found in object (==arg1)
    local -a FUN_MANDA=( ) # list of all fun needed, (set as arg2 if given, else is a copy of arg1)
    eval "local -a FUN_FOUND=( \"\${${1}[@]}\" )"
    [[ -n ${2} ]] && eval "local -a FUN_MANDA+=( \"\${${2}[@]}\" )" || eval "local -a FUN_MANDA+=( \"\${${1}[@]}\" )"
    [[ ${#FUN_FOUND[@]} -eq 0 ]] && { echo "${R0}WRONG USAGE OF launch_my_unitests():FUN_FOUND created is an empty list" && exit 2 ; }
    [[ ${#FUN_MANDA[@]} -eq 0 ]] && { echo "${R0}WRONG USAGE OF launch_my_unitests():FUN_MANDA created is an empty list" && exit 2 ; }

    local nb_err=0
    for fun in ${FUN_MANDA[@]};do
        echo "🔹${BCU}${fun}():${E}"
        if [[ " ${FUN_FOUND[@]} " =~ " ${fun} " ]];then
            local FUN_LOG_DIR="${LOG_DIR}/${fun}"
            [[ ! -d ${FUN_LOG_DIR} ]] && mkdir -p ${FUN_LOG_DIR}
            local test_main=$(find "${MY_UNITESTS}" -type f -name *"${fun}.c")
            local test_txt=$(find "${MY_UNITESTS}" -type f -name *"${fun}.txt")
            if [[ -n "${test_main}" ]];then
                # STEP 1 : COMPILATION --> IF NO BINARY OR IF SOURCES NEWER THAN BINARY
                [[ ! -d ${BIN_DIR} ]] && mkdir -p ${BIN_DIR}
                exe="${BIN_DIR}/test_${fun}"
                echo -en " ${BC0} ⤷${E} ⚙️  ${GU}Compilation:${E}"
                # cases where compilation needed: (1:no binary),(2:sources newer than binary),(3:text exist and newer than binary)
                if [[ ! -f "${exe}" || "${test_main}" -nt "${exe}" || "${LIBFT_A}" -nt "${exe}" || ( -n "${test_txt}" && "${test_txt}" -nt "${exe}" ) ]];then
                    local res_compile=$(${CC} ${test_main} ${LIBFT_A} -o ${exe} -lbsd > "${FUN_LOG_DIR}/comp_stderr.log" 2>&1 && echo ${?} || echo ${?})
                    if [[ "${res_compile}" -eq 0 ]];then
                        echo -en " ✅ ${V0} Successfull.${E}\n"
                        rm "${FUN_LOG_DIR}/comp_stderr.log"
                    else
                        local log_comp_fail=$(print_shorter_path ${FUN_LOG_DIR}/comp_stderr.log)
                        nb_err=$(( nb_err + 1 ))
                        echo -e "${fun}\tcompilation\t${log_comp_fail}" >> ${LOG_FAIL}
                        echo -en " ❌ ${R0}Compilation failed.${E}\n"
                        sed 's/^/\x1b[0;31m       /' ${log_comp_fail}
                        continue
                    fi
                else
                    echo -en " ☑️  ${BC0} Not needed.\n${E}"
                fi
                # STEP 2 : EXECUTION
                echo -en " ${BC0} ⤷${E} 🚀 ${GU}Execution  :${E}"
                if [[ -f "${test_txt}" ]];then
                    local res_tests=$(${exe} "$(dirname "${test_txt}")" "${FUN_LOG_DIR}" > "${FUN_LOG_DIR}/exec.log" 2>&1 && echo ${?} || echo ${?})
                else
                    local res_tests=$(${exe} > "${FUN_LOG_DIR}/exec.log" 2>&1 && echo ${?} || echo ${?})
                fi
                echo "EXIT_VALUE=${res_tests}" >> "${FUN_LOG_DIR}/exec.log"
                if [[ ${res_tests} -eq 0 ]];then
                    echo -en " ✅ ${V0} No error detected.${E}\n"
                else
                    local exec_log_file=$(print_shorter_path ${FUN_LOG_DIR}/exec.log)
                    nb_err=$(( nb_err + 1 ))
                    echo -e "${fun}\terrors\t${exec_log_file}" >> ${LOG_FAIL}
                    echo -en " ❌ ${R0} Error detected (exec return value=${res_tests})\n"
                    echo "      🔸${Y0}check log file 👉 ${M0}${exec_log_file}${E}"
                fi
                # STEP 3 : VALGRIND
                echo -en " ${BC0} ⤷${E} 🚰 ${GU}Valgrind   :${E}"
                if [[ -f "${test_txt}" ]];then
                    local res_val=$(${VALGRIND} ${exe} "$(dirname "${test_txt}")" "${FUN_LOG_DIR}" > "${FUN_LOG_DIR}/leaks.log" 2>&1 && echo ${?} || echo ${?})
                else
                    local res_val=$(${VALGRIND} ${exe} > "${FUN_LOG_DIR}/leaks.log" 2>&1 && echo ${?} || echo ${?})
                fi
                if [[ ${res_val} -ne ${VAL_ERR} ]];then
                    echo -en " ✅ ${V0} No leak detected.${E}\n"
                else
                    local leaks_log_file=$(print_shorter_path ${FUN_LOG_DIR}/leaks.log)
                    nb_err=$(( nb_err + 1 ))
                    echo -e "${fun}\tleaks\t${leaks_log_file}" >> ${LOG_FAIL}
                    echo -en " ❌ ${R0} Leak detected (valgrind return value=${res_val})\n"
                    echo "      🔸${Y0}check log file 👉 ${M0}${leaks_log_file}${E}"
                fi
            else
                echo " ${BC0} ⤷${E} ✖️  ${G0}Tests not found.${E}"
                rmdir "${FUN_LOG_DIR}" > /dev/null 2>&1
            fi
        else
            echo -e "${fun}\tmissing\t⭙" >> ${LOG_FAIL}
            nb_err=$(( nb_err + 1 ))
            echo " ${BC0} ⤷${E} ❌ ${R0}Function not found in object.${E}"
        fi
    done
    return ${nb_err}
}
# -[ run_myunitests_gnl() ]-----------------------------------------------------------------------------------
run_myunitests_gnl()
{
    local FUN_LOG_DIR="${LOG_DIR}/gnl_manda"
    [[ ! -d ${FUN_LOG_DIR} ]] && mkdir -p ${FUN_LOG_DIR}
    local test_main=$(find "${MY_UNITESTS}" -type f -name "test_get_next_line.c")
    if [[ -n "${test_main}" ]];then
        # STEP1: COMPILATION (handle case unitests, file produce or libft.a newer than exe => recompilation)
        [[ ! -d ${BIN_DIR} ]] && mkdir -p ${BIN_DIR}
        exe="${BIN_DIR}/test_get_next_line"
        echo -en " ⚙️  ${BCU}Compilation:${E}"
        # cases where compilation needed: (1:no binary),(2:sources newer than binary),(3:text exist and newer than binary)
        if [[ ! -f "${exe}" || "${test_main}" -nt "${exe}" || "${LIBFT_A}" -nt "${exe}" || ( -n "${test_txt}" && "${test_txt}" -nt "${exe}" ) ]];then
            local res_compile=$(${CC} ${test_main} ${LIBFT_A} -o ${exe} -lbsd > "${FUN_LOG_DIR}/comp_stderr.log" 2>&1 && echo ${?} || echo ${?})
            if [[ "${res_compile}" -eq 0 ]];then
                echo -en " ✅ ${V0} Successfull.${E}\n"
                rm "${FUN_LOG_DIR}/comp_stderr.log"
            else
                local log_comp_fail=$(print_shorter_path ${FUN_LOG_DIR}/comp_stderr.log)
                nb_err=$(( nb_err + 1 ))
                echo -e "get_next_line\tcompilation\t${log_comp_fail}" >> ${LOG_FAIL}
                echo -en " ❌ ${R0}Compilation failed.${E}\n"
                sed 's/^/\x1b[0;31m       /' ${log_comp_fail}
                continue
            fi
        else
            echo -en " ☑️  ${BC0} Not needed.\n${E}"
        fi
    fi
    for my_file in $(ls ${MY_UNITESTS}/gnl/files);do
        local test_txt="${MY_UNITESTS}/gnl/files/${my_file}"
        local copy_txt="${FUN_LOG_DIR}/${my_file%\.*}.txt"
        echo -e "  🔹${BCU}file readed:${E}'${M0}${my_file}${E}'"
        # STEP 2 : EXECUTION
        echo -en "   ${BC0} ⤷${E} 🚀 ${GU}Execution  :${E}"
        ${exe} ${test_txt} > ${copy_txt}
        if [[ -f ${copy_txt} ]];then
            local diff_txt="${FUN_LOG_DIR}/${my_file%\.*}.diff"
            local res_diff=$(diff ${test_txt} ${copy_txt} > ${diff_txt} 2>&1 && echo ${?} || echo ${?})
            if [[ ${res_diff} -eq 0 ]];then
                echo -en " ✅ ${V0} Successfull.${E}\n"
                rm ${diff_txt}
            else
                local diff_log_file=$(print_shorter_path ${diff_txt})
                nb_err=$(( nb_err + 1 ))
                echo -e "get_next_line\tdiff\t${diff_log_file}" >> ${LOG_FAIL}
                echo -en " ❌ ${R0} Error detected: original_file != produced_file\n"
                echo "        🔸${Y0}check diff log file 👉 ${M0}${diff_log_file}${E}"
            fi
        else
            nb_err=$(( nb_err + 1 ))
            echo -e "get_next_line\tmissing\t${copy_txt}" >> ${LOG_FAIL}
            echo -en " ❌ ${R0} Error detected : missing file${E}\n"
        fi
        # STEP 3 : VALGRIND
        echo -en "   ${BC0} ⤷${E} 🚰 ${GU}Valgrind   :${E}"
        local leak_txt="${FUN_LOG_DIR}/leak_${my_file%\.*}.log"
        local res_val=$(${VALGRIND} ${exe} ${test_txt} > ${leak_txt} 2>&1 && echo ${?} || echo ${?})
        if [[ ${res_val} -ne ${VAL_ERR} ]];then
            echo -en " ✅ ${V0} No leak detected.${E}\n"
        else
            local leaks_log_file=$(print_shorter_path ${leak_txt})
            nb_err=$(( nb_err + 1 ))
            echo -e "get_next_line\tleaks\t${leaks_log_file}" >> ${LOG_FAIL}
            echo -en " ❌ ${R0} Leak detected (valgrind return value=${res_val})\n"
            echo "        🔸${Y0}check log file 👉 ${M0}${leaks_log_file}${E}"
        fi
    done
    return ${nb_err}
}
# -[ DISPLAY_RESUME() ]---------------------------------------------------------------------------------------
# Display the resume of test (norminette, tests results, log files produces ...)
# Take on optionnal argument, text to add between the <🔶 RESUME> and the <:>.
display_resume()
{
    [[ -n "${1}" ]] && local args=( "🔶 ${YU}RESUME ${1}:${E}" ) || local args=( "🔶 ${YU}RESUME :${E}" )
    if [[ ${NORM} -eq 1 ]];then
        [[ ${res_normi} -eq 0 ]] && args+=( " 🔸 ${YU}Norminette:${V0} ✅ PASS${E}" ) || args+=( " 🔸 ${YU}Norminette:${R0} ❌ FAIL (${res_normi} wrong files detected)${E}" )
    else
        args+=( " 🔸 ${YU}Norminette:${G0} ✖️  Test Desabled${E}" )
    fi
    local short_log_dir=$(print_shorter_path ${LOG_DIR})
    local tot_fun_tested=$(find ${short_log_dir} -mindepth 1 -maxdepth 1 -type d | wc -l )
    local lst_uniq_fail_fun=( )
    if [[ -f "${LOG_FAIL}" ]];then
        while IFS= read -r line;do
            local ff=$(echo "${line}" | awk '{print $1}')
            if [[ -n "${ff}" ]];then
                [[ ! " ${lst_uniq_fail_fun[@]} " =~ " ${ff} " ]] && lst_uniq_fail_fun+=( "${ff}" )
            fi
        done < "${LOG_FAIL}"
    fi
    if [[ ${#lst_uniq_fail_fun[@]} -eq 0 ]];then
        args+=( " 🔸 ${YU}${tot_fun_tested} function(s) have been tested:${V0} ✅ ALL PASSED${E}" ) 
    else
        args+=( " 🔸 ${YU}${tot_fun_tested} function(s) have been tested:${E}" )
        args+=( \ "   ${V0}✅ $(( tot_fun_tested - ${#lst_uniq_fail_fun[@]} )) fonction(s) ${V0}PASSED.${E}" \
            "    ${R0}❌ ${#lst_uniq_fail_fun[@]} function(s) ${R0}FAILLED:${E}" \
        )
        for fun in ${lst_uniq_fail_fun[@]};do
            args+=( "      ${R0}✘ ${RU}${fun}():${E}" )
            local link1=$(awk -v f="${fun}" '$1 == f &&  $2 == "compilation" {print $3}' ${LOG_FAIL})
            local link2=$(awk -v f="${fun}" '$1 == f &&  $2 == "errors" {print $3}' ${LOG_FAIL})
            local link3=$(awk -v f="${fun}" '$1 == f &&  $2 == "leaks" {print $3}' ${LOG_FAIL})
            local link4=$(awk -v f="${fun}" '$1 == f &&  $2 == "missing" {print $3}' ${LOG_FAIL})
            local link5=$(awk -v f="${fun}" '$1 == f &&  $2 == "diff" {print $3}' ${LOG_FAIL})
            [[ -n "${link1}" ]] && for l in ${link1}; do args+=( "        ${R0}⤷ Error occure will compilling ${M0}👉 ${l}${E}" );done
            [[ -n "${link2}" ]] && for l in ${link2}; do args+=( "        ${R0}⤷ Error detected ${M0}👉 ${l}${E}" );done
            [[ -n "${link3}" ]] && for l in ${link3}; do args+=( "        ${R0}⤷ Leaks detected ${M0}👉 ${l}${E}" );done
            [[ -n "${link4}" ]] && for l in ${link4}; do args+=( "        ${R0}⤷ Missing fun. or file.${E}" );done
            [[ -n "${link5}" ]] && for l in ${link5}; do args+=( "        ${R0}⤷ Diff. found ${M0}👉 ${l}${E}" );done
        done
    fi
    print_in_box -t 2 -c y "${args[@]}"
}

# ============================================================================================================
# MAIN
# ============================================================================================================
# =[ CHECK IF LIBFT.A FOUNDED ]===============================================================================
[[ -z ${LIBFT_A} ]] && { script_usage "${R0}Static lib not found: No ${BC0}libft.a${R0} file inside ${M0}${LIBFT_DIR}/${R0} folder.${E}" 2; }
# =[ HANDLE SCRIPTS OPTIONS ]=================================================================================
NB_ARG="${#}"
for args in "$@";do
    shift
    case "${args}" in
        --[Aa]ll | -[Aa])
            BONUS=$(max 0 $(( BONUS - 1 )))
            NORM=$(max 0 $(( NORM - 1 )))
            BUIN=$(max 0 $(( BUIN - 1 )))
            MY_UNITESTS_LIBFT=$(max 0 $(( MY_UNITESTS_LIBFT - 1 )))
            MY_UNITESTS_GNL=$(max 0 $(( MY_UNITESTS_GNL - 1 )))
            MY_UNITESTS_PRINTF=$(max 0 $(( MY_UNITESTS_PRINTF - 1 )))
            MY_UNITESTS_OTHERS=$(max 0 $(( MY_UNITESTS_OTHERS - 1 )))
            TRIPOUILLE_LIBFT=$(max 0 $(( TRIPOUILLE_LIBFT - 1 )))
            TRIPOUILLE_GNL=$(max 0 $(( TRIPOUILLE_GNL - 1 )))
            TRIPOUILLE_PRINTF=$(max 0 $(( TRIPOUILLE_PRINTF - 1 )))
            ;;
        ++[Aa]ll | +[Aa])
            BONUS=$(( BONUS + 1 ))
            NORM=$(( NORM + 1 ))
            BUIN=$(( BUIN + 1 ))
            MY_UNITESTS_LIBFT=$(( MY_UNITESTS_LIBFT + 1 ))
            MY_UNITESTS_GNL=$(( MY_UNITESTS_GNL + 1 ))
            MY_UNITESTS_PRINTF=$(( MY_UNITESTS_PRINTF + 1 ))
            MY_UNITESTS_OTHERS=$(( MY_UNITESTS_OTHERS + 1 ))
            TRIPOUILLE_LIBFT=$(( TRIPOUILLE_LIBFT + 1 ))
            TRIPOUILLE_GNL=$(( TRIPOUILLE_GNL + 1 ))
            TRIPOUILLE_PRINTF=$(( TRIPOUILLE_PRINTF + 1 ))
            ;;
        --[Tt]ripouille | -[Tt])
            TRIPOUILLE_LIBFT=$(( TRIPOUILLE_LIBFT - 1 ))
            TRIPOUILLE_GNL=$(( TRIPOUILLE_GNL - 1 ))
            TRIPOUILLE_PRINTF=$(( TRIPOUILLE_PRINTF - 1 ))
            ;;
        ++[Tt]ripouille | +[Tt])
            TRIPOUILLE_LIBFT=$(( TRIPOUILLE_LIBFT + 1 ))
            TRIPOUILLE_GNL=$(( TRIPOUILLE_GNL + 1 ))
            TRIPOUILLE_PRINTF=$(( TRIPOUILLE_PRINTF + 1 ))
            ;;
        --[Li]bft | -[Ll][Ff][Tt] | -[Ll])
            MY_UNITESTS_LIBFT=$(( MY_UNITESTS_LIBFT - 1 ))
            TRIPOUILLE_LIBFT=$(( TRIPOUILLE_LIBFT - 1 ))
            ;;
        ++[Li]bft | +[Ll][Ff][Tt] | +[Ll])
            MY_UNITESTS_LIBFT=$(( MY_UNITESTS_LIBFT + 1 ))
            TRIPOUILLE_LIBFT=$(( TRIPOUILLE_LIBFT + 1 ))
            ;;
        --[Gg]et[Nn]ext[Ll]ine | --[Gg]et_[Nn]ext_[Ll]ine | -[Gg][Nn][Ll] | -[Gg])
            TRIPOUILLE_GNL=$(( TRIPOUILLE_GNL - 1 ))
            MY_UNITESTS_GNL=$(( MY_UNITESTS_GNL - 1 ))
            ;;
        ++[Gg]et[Nn]ext[Ll]ine | ++[Gg]et_[Nn]ext_[Ll]ine | +[Gg][Nn][Ll] | +[Gg])
            TRIPOUILLE_GNL=$(( TRIPOUILLE_GNL + 1 ))
            MY_UNITESTS_GNL=$(( MY_UNITESTS_GNL + 1 ))
            ;;
        --ft_printf | --printf | --print | -[Pp] )
            TRIPOUILLE_PRINTF=$(( TRIPOUILLE_PRINTF - 1 ))
            MY_UNITESTS_PRINTF=$(( MY_UNITESTS_PRINTF - 1 ))
            ;;
        ++ft_printf | ++printf | ++print | +[Pp] )
            TRIPOUILLE_PRINTF=$(( TRIPOUILLE_PRINTF + 1 ))
            MY_UNITESTS_PRINTF=$(( MY_UNITESTS_PRINTF + 1 ))
            ;;
        --[Bb]onus | -[Bb][Oo] ) BONUS=$(( BONUS - 1 )) ;;
        ++[Bb]onus | +[Bb][Oo] ) BONUS=$(( BONUS + 1 )) ;;
        --[Bb]uil[td]-in | -[Bb][Ii] ) BUIN=$(( BUIN - 1 )) ;;
        ++[Bb]uil[td]-in | +[Bb][Ii] ) BUIN=$(( BUIN + 1 )) ;;
        [+-][+-][Hh]elp | [+-][Hh] ) HELP=$(( HELP + 1 ));;
        --[Nn]o-[Nn]orm | -[Nn] ) NORM=$(( NORM - 1 ));;
        ++[Nn]o+[Nn]orm | +[Nn] ) NORM=$(( NORM + 1 ));;
        --[Oo]ther | --[Oo]thers | -[Oo] ) MY_UNITESTS_OTHERS=$(( MY_UNITESTS_OTHERS - 1)) ;;
        ++[Oo]ther | ++[Oo]thers | +[Oo] ) MY_UNITESTS_OTHERS=$(( MY_UNITESTS_OTHERS + 1)) ;;
        *) script_usage "Error: Unknown option '${args}'" 1 ;;
    esac
done
# =[ DISPLAY USAGE THEN STOP IF --help OPTION ]===============================================================
[[ ( ${has_h} -gt 0 ) && ( ${NB_ARG} -gt 1 ) ]] && script_usage "--help option can not be paired with other option" 3
[[ ${HELP} -eq 1 ]] && script_usage
# =[ SET LISTS ]==============================================================================================
# -[ SET HOMEMADE AND BUILTIN LISTS ]-------------------------------------------------------------------------
if file "${LIBFT_A}" | grep -qE 'relocatable|executable|shared object|ar archive';then
    for fun in $(nm -C "${LIBFT_A}" | awk '$2 == "T" {print $3}' | sort | uniq);do
        [[ ! " ${HOMEMADE_FUNUSED[@]} " =~ " ${fun} " ]] && HOMEMADE_FUNUSED+=( "${fun}" )
    done
    for fun in $(nm -C "${LIBFT_A}" | awk '$2 == "U" {print $3}' | sort | uniq);do
        if [[ ! " ${HOMEMADE_FUNUSED[@]} " =~ " ${fun} " ]];then
            [[ ! " ${BUILTIN_FUNUSED[@]} " =~ " ${fun} " ]] && BUILTIN_FUNUSED+=( "${fun}" )
        fi
    done
else
    echo -e "${BC0}${LIBFT_A}${E} is not an object file\033[m"
fi
# -[ SET PERSONNAL FUNCTION DETECTED ]------------------------------------------------------------------------
PERSO_FUN+=($(printf "%s\n" "${HOMEMADE_FUNUSED[@]}" | grep -vxF -f <(printf "%s\n" "${LIBFT_MANDA[@]}" "${LIBFT_BONUS[@]}" "ft_printf" "get_next_line" )))
# -[ SET PERSONNAL FUNCTION TO TEST ]-------------------------------------------------------------------------
for fun in ${PERSO_FUN[@]};do
    test_fun=$(find "${MY_UNITESTS}" -type f -name *"${fun}.c")
    [[ -n "${test_fun}" ]] && PERSO_FUN_TO_TEST+=( "${fun}" )
done
# =[ DISPLAY_START() ]========================================================================================
display_start
## =[ 0.2 | DISPLAY LIST HOME-MADE FUN ]=======================================================================
## TODO
##print_in_box -t 1 -c b "🟦 ${HOMEMADE_FUNUSED[@]}"
## =[ 0.3 | DISPLAY LIST BUILD-IN FUN ]========================================================================
## TODO
##print_in_box -t 1 -c b "🟦 ${BUILTIN_FUNUSED[@]}"
## =[ 0.4 | CHECK NORMINETTE ]=================================================================================
#if [[ ${NORM} -eq 1 ]];then
#    exec_anim_in_box "check42_norminette ${LIBFT_DIR}" "Check Norminette"
#    res_normi=${?}
#fi
## =[ LAUNCH TRIPOUILLE ]======================================================================================
#if [[ $(( TRIPOUILLE_LIBFT + TRIPOUILLE_GNL + TRIPOUILLE_PRINTF )) -gt 0 ]];then
#    print_in_box -t 2 -c y \
#        "   ${Y0}  _____         _                       _   _   _           _____              _        ${E}" \
#        "   ${Y0} |_   _|  _ _  (_)  _ __   ___   _  _  (_) | | | |  ___    |_   _|  ___   ___ | |_   ___${E}" \
#        "   ${Y0}   | |   | '_| | | | '_ \ / _ \ | || | | | | | | | / -_)     | |   / -_) (_-< |  _| (_-<${E}" \
#        "   ${Y0}   |_|   |_|   |_| | .__/ \___/  \_,_| |_| |_| |_| \___|     |_|   \___| /__/  \__| /__/${E}" \
#        "   ${Y0}                   |_|                                                                  ${E}"
#fi
## -[ LIBFT ]--------------------------------------------------------------------------------------------------
#if [[ ${TRIPOUILLE_LIBFT} -eq 1 ]];then
#    print_in_box -t 3 -c b \
#        "     ${BC0}┏┳┓  •      •┓┓    ┓•┓ ┏           ┓         ${E}" \
#        "     ${BC0} ┃ ┏┓┓┏┓┏┓┓┏┓┃┃┏┓  ┃┓┣┓╋╋  ┏┳┓┏┓┏┓┏┫┏┓╋┏┓┏┓┓┏${E}" \
#        "     ${BC0} ┻ ┛ ┗┣┛┗┛┗┛┗┗┗┗   ┗┗┗┛┛┗  ┛┗┗┗┻┛┗┗┻┗┻┗┗┛┛ ┗┫${E}"
#    make -s -C ${TRIPOUILLE}/libft m
#    # -[ Run BONUS-TESTER if explicitly asked ]---------------------------------------------------------------
#    if [[ ${BONUS} -eq 1 ]];then 
#        print_in_box -t 3 -c b \
#        "     ${BC0}┏┳┓  •      •┓┓    ┓•┓ ┏   ┓        ${E}" \
#        "     ${BC0} ┃ ┏┓┓┏┓┏┓┓┏┓┃┃┏┓  ┃┓┣┓╋╋  ┣┓┏┓┏┓┓┏┏${E}" \
#        "     ${BC0} ┻ ┛ ┗┣┛┗┛┗┛┗┗┗┗   ┗┗┗┛┛┗  ┗┛┗┛┛┗┗┛┛${E}"
#        make -s -C ${TRIPOUILLE}/libft b
#    else
#    # -[ Run BONUS-TESTER if any libft_bonus fun. founded in static library ]---------------------------------
#        for fun in ${HOMEMADE_FUNUSED[@]};do
#            if [[ " ${LIBFT_BONUS[@]} " =~ " ${fun} " ]];then
#                print_in_box -t 3 -c b \
#                    "     ${BC0}┏┳┓  •      •┓┓    ┓•┓ ┏   ┓        ${E}" \
#                    "     ${BC0} ┃ ┏┓┓┏┓┏┓┓┏┓┃┃┏┓  ┃┓┣┓╋╋  ┣┓┏┓┏┓┓┏┏${E}" \
#                    "     ${BC0} ┻ ┛ ┗┣┛┗┛┗┛┗┗┗┗   ┗┗┗┛┛┗  ┗┛┗┛┛┗┗┛┛${E}"
#                make -s -C ${TRIPOUILLE}/libft b
#                break
#            fi
#        done
#    fi
#fi
## -[ FT_PRINTF ]----------------------------------------------------------------------------------------------
#if [[ ${TRIPOUILLE_PRINTF} -eq 1 ]];then
#    # -[ CAS1: explicitly asks-->if not found:error. ]--------------------------------------------------------
#    if [[ ${has_p} -eq 1 ]];then
#        print_in_box -t 3 -c b \
#            "     ${BC0}┏┳┓  •      •┓┓    ┏┓      •   ┏  ┳┳┓     ┓         ${E}" \
#            "     ${BC0} ┃ ┏┓┓┏┓┏┓┓┏┓┃┃┏┓  ┣ ╋ ┏┓┏┓┓┏┓╋╋  ┃┃┃┏┓┏┓┏┫┏┓╋┏┓┏┓┓┏${E}" \
#            "     ${BC0} ┻ ┛ ┗┣┛┗┛┗┛┗┗┗┗   ┻ ┗━┣┛┛ ┗┛┗┗┛  ┛ ┗┗┻┛┗┗┻┗┻┗┗┛┛ ┗┫${E}"
#        make -s -C ${TRIPOUILLE}/ft_printf m
#        if [[ ${BONUS} -eq 1 ]];then
#            print_in_box -t 3 -c b \
#                "     ${BC0}┏┳┓  •      •┓┓    ┏┓      •   ┏  ┳┓       ${E}" \
#                "     ${BC0} ┃ ┏┓┓┏┓┏┓┓┏┓┃┃┏┓  ┣ ╋ ┏┓┏┓┓┏┓╋╋  ┣┫┏┓┏┓┓┏┏${E}" \
#                "     ${BC0} ┻ ┛ ┗┣┛┗┛┗┛┗┗┗┗   ┻ ┗━┣┛┛ ┗┛┗┗┛  ┻┛┗┛┛┗┗┛┛${E}"
#            make -s -C ${TRIPOUILLE}/ft_printf b
#        fi
#    # -[ CAS2: add using -all options-->if not found, not launch and therefor not considered as an error. ]---
#    else
#        if [[ ((${has_a} -eq 1) && (" ${HOMEMADE_FUNUSED[@]} " =~ " ft_printf ")) ]];then
#            print_in_box -t 3 -c b \
#                "     ${BC0}┏┳┓  •      •┓┓    ┏┓      •   ┏  ┳┳┓     ┓         ${E}" \
#                "     ${BC0} ┃ ┏┓┓┏┓┏┓┓┏┓┃┃┏┓  ┣ ╋ ┏┓┏┓┓┏┓╋╋  ┃┃┃┏┓┏┓┏┫┏┓╋┏┓┏┓┓┏${E}" \
#                "     ${BC0} ┻ ┛ ┗┣┛┗┛┗┛┗┗┗┗   ┻ ┗━┣┛┛ ┗┛┗┗┛  ┛ ┗┗┻┛┗┗┻┗┻┗┗┛┛ ┗┫${E}"
#            make -s -C ${TRIPOUILLE}/ft_printf m
#        fi
#        if [[ ${BONUS} -eq 1 ]];then
#            print_in_box -t 3 -c b \
#                "     ${BC0}┏┳┓  •      •┓┓    ┏┓      •   ┏  ┳┓       ${E}" \
#                "     ${BC0} ┃ ┏┓┓┏┓┏┓┓┏┓┃┃┏┓  ┣ ╋ ┏┓┏┓┓┏┓╋╋  ┣┫┏┓┏┓┓┏┏${E}" \
#                "     ${BC0} ┻ ┛ ┗┣┛┗┛┗┛┗┗┗┗   ┻ ┗━┣┛┛ ┗┛┗┗┛  ┻┛┗┛┛┗┗┛┛${E}"
#            make -s -C ${TRIPOUILLE}/ft_printf b
#        fi
#    fi
#fi
## -[ GET_NEXT_LINE ]------------------------------------------------------------------------------------------
#if [[ ${TRIPOUILLE_GNL} -eq 1 ]];then
#    # -[ CAS1: explicitly asks if -g option-->if not found:error. ]-------------------------------------------
#    if [[ ${has_g} -eq 1 ]];then
#        print_in_box -t 3 -c b \
#            "     ${BC0}┏┳┓  •      •┓┓    ┏┓     ┳┓       ┓ •      ┳┳┓     ┓         ${E}" \
#            "     ${BC0} ┃ ┏┓┓┏┓┏┓┓┏┓┃┃┏┓  ┃┓┏┓╋  ┃┃┏┓┓┏╋  ┃ ┓┏┓┏┓  ┃┃┃┏┓┏┓┏┫┏┓╋┏┓┏┓┓┏${E}" \
#            "     ${BC0} ┻ ┛ ┗┣┛┗┛┗┛┗┗┗┗   ┗┛┗ ┗  ┛┗┗ ┛┗┗  ┗┛┗┛┗┗   ┛ ┗┗┻┛┗┗┻┗┻┗┗┛┛ ┗┫${E}"
#        make -s -C ${TRIPOUILLE}/get_next_line m
#        if [[ ${BONUS} -eq 1 ]];then
#            print_in_box -t 3 -c b \
#                "     ${BC0}┏┳┓  •      •┓┓    ┏┓     ┳┓       ┓ •      ┳┓       ${E}" \
#                "     ${BC0} ┃ ┏┓┓┏┓┏┓┓┏┓┃┃┏┓  ┃┓┏┓╋  ┃┃┏┓┓┏╋  ┃ ┓┏┓┏┓  ┣┫┏┓┏┓┓┏┏${E}" \
#                "     ${BC0} ┻ ┛ ┗┣┛┗┛┗┛┗┗┗┗   ┗┛┗ ┗  ┛┗┗ ┛┗┗  ┗┛┗┛┗┗   ┻┛┗┛┛┗┗┛┛${E}"
#            make -s -C ${TRIPOUILLE}/get_next_line b
#        fi
#    # -[ CAS2: add using -all options-->if not found, not launch and therefor not considered as an error. ]---
#    else
#        if [[ ((${has_a} -eq 1) && (" ${HOMEMADE_FUNUSED[@]} " =~ " get_next_line ")) ]];then
#            print_in_box -t 3 -c b \
#                "     ${BC0}┏┳┓  •      •┓┓    ┏┓     ┳┓       ┓ •      ┳┳┓     ┓         ${E}" \
#                "     ${BC0} ┃ ┏┓┓┏┓┏┓┓┏┓┃┃┏┓  ┃┓┏┓╋  ┃┃┏┓┓┏╋  ┃ ┓┏┓┏┓  ┃┃┃┏┓┏┓┏┫┏┓╋┏┓┏┓┓┏${E}" \
#                "     ${BC0} ┻ ┛ ┗┣┛┗┛┗┛┗┗┗┗   ┗┛┗ ┗  ┛┗┗ ┛┗┗  ┗┛┗┛┗┗   ┛ ┗┗┻┛┗┗┻┗┻┗┗┛┛ ┗┫${E}"
#            make -s -C ${TRIPOUILLE}/get_next_line m
#        fi
#        if [[ ${BONUS} -eq 1 ]];then
#            print_in_box -t 3 -c b \
#                "     ${BC0}┏┳┓  •      •┓┓    ┏┓     ┳┓       ┓ •      ┳┓       ${E}" \
#                "     ${BC0} ┃ ┏┓┓┏┓┏┓┓┏┓┃┃┏┓  ┃┓┏┓╋  ┃┃┏┓┓┏╋  ┃ ┓┏┓┏┓  ┣┫┏┓┏┓┓┏┏${E}" \
#                "     ${BC0} ┻ ┛ ┗┣┛┗┛┗┛┗┗┗┗   ┗┛┗ ┗  ┛┗┗ ┛┗┗  ┗┛┗┛┗┗   ┻┛┗┛┛┗┗┛┛${E}"
#            make -s -C ${TRIPOUILLE}/get_next_line b
#        fi
#    fi
#fi
## =[ MY_UNITESTS ]============================================================================================
#print_in_box -t 2 -c y \
#    "           ${Y0}  __  __                _   _          _   _                _        ${E}" \
#    "           ${Y0} |  \/  |  _  _   ___  | | | |  _ _   (_) | |_   ___   ___ | |_   ___${E}" \
#    "           ${Y0} | |\/| | | || | |___| | |_| | | ' \  | | |  _| / -_) (_-< |  _| (_-<${E}" \
#    "           ${Y0} |_|  |_|  \_, |        \___/  |_||_| |_|  \__| \___| /__/  \__| /__/${E}" \
#    "           ${Y0}           |__/                                                      ${E}"
## -[ LIBFT ]--------------------------------------------------------------------------------------------------
#if [[ ${MY_UNITESTS_LIBFT} -eq 1 ]];then
#    exec_anim_in_box "launch_my_unitests HOMEMADE_FUNUSED LIBFT_MANDA" "Tests libft mandatory functions"
#    # -[ LIBFT_BONUS if BONUS opt or if any libft_bonus fun detected in libft.a ]-----------------------------
#    if [[ ${BONUS} -eq 1 ]];then 
#        exec_anim_in_box "launch_my_unitests HOMEMADE_FUNUSED LIBFT_BONUS" "Tests libft bonus functions"
#    else
#        for fun in ${HOMEMADE_FUNUSED[@]};do
#            if [[ " ${LIBFT_BONUS[@]} " =~ " ${fun} " ]];then
#                exec_anim_in_box "launch_my_unitests HOMEMADE_FUNUSED LIBFT_BONUS" "Tests libft bonus functions"
#                break
#            fi
#        done
#    fi
#fi
## -[ GET_NEXT_LINE ]------------------------------------------------------------------------------------------
#if [[ (${has_a} -eq 1) || (${has_g} -eq 1) || (" ${HOMEMADE_FUNUSED[@]} " =~ " get_next_line ") ]];then
#    exec_anim_in_box "run_myunitests_gnl" "Run My_unitests for get_next_line()"
#    [[ ${BONUS} -eq 1 ]] && exec_anim_in_box "echo \"TODO: create run_myunitests_gnl_bonus()\"" # TODO
#fi
## -[ FT_PRINTF ]----------------------------------------------------------------------------------------------
#if [[ (${has_a} -eq 1) || (${has_p} -eq 1) || (" ${HOMEMADE_FUNUSED[@]} " =~ " ft_printf ") ]];then
#    exec_anim_in_box "echo \"TODO: create run_myunitests_ft_printf()\"" # TODO
#    [[ ${BONUS} -eq 1 ]] && exec_anim_in_box "echo \"TODO: create run_myunitests_ft_printf_bonus()\"" # TODO
#fi
## -[ PERSONNAL FUNCTIONS ]------------------------------------------------------------------------------------
#if [[ ${MY_UNITESTS_OTHERS} -eq 1 ]];then
#    exec_anim_in_box "launch_my_unitests PERSO_FUN" "Tests ${#PERSO_FUN_TO_TEST[@]}/${#PERSO_FUN[@]} of personnal functions"
#fi
## -[ DISPLAY UNITESTS RESUME ]--------------------------------------------------------------------------------
#[[ $(( MY_UNITESTS_LIBFT + MY_UNITESTS_GNL + MY_UNITESTS_PRINTF + MY_UNITESTS_OTHERS)) -gt 0 ]] && display_resume "Libft's tests"
