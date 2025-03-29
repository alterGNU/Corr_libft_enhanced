#!/usr/bin/env bash

# ============================================================================================================
# Launch libft.a tests
# This script take options as arguments:
#  - ARGUMENTS:
#    - NO-ARGS                            🢥  Default behavior:enable all MY_UNITESTS_{LIBFT,GNL,PRINTF,OTHERS}->{MY_UNITESTS}
#    - ARGS ∈ {-h, --help}                🢥  Enable HELP option that display script usage---------------------->{MY_UNITESTS, TRIPOUILLE}
#    - ARGS ∈ {-n, --no-norm}             🢥  Desable the NORMINETTE tester------------------------------------->{MY_UNITESTS, TRIPOUILLE}
#    - ARGS ∈ {-b, --bonus}               🢥  Enable Bonus option for all tester-------------------------------->{MY_UNITESTS, TRIPOUILLE}
#    - ARGS ∈ {-a, --all}                 🢥  Enable ALL TRIPOUILLE AND MY_UNITESTS OPTION WITHOUT BONUS-------->{MY_UNITESTS, TRIPOUILLE}
#    - ARGS ∈ {-t, --tripouille}          🢥  Enable ALL TRIPOUILLE && Disable ALL MY_UNITESTS------------------>{MY_UNITESTS, TRIPOUILLE}
#    - ARGS ∈ {-l, --libft, -lft}         🢥  Enable test for LIBFT--------------------------------------------->{MY_UNITESTS, TRIPOUILLE}
#    - ARGS ∈ {-f, --ft_printf}           🢥  Enable test for FT_PRINTF----------------------------------------->{MY_UNITESTS, TRIPOUILLE}
#    - ARGS ∈ {-g, --get_next_line, -gnl} 🢥  Enable test for GET_NEXT_LINE------------------------------------->{MY_UNITESTS, TRIPOUILLE}
#    - ARGS ∈ {-o, --other}               🢥  Enable test for OTHERS FUNCTIONS FOUND---------------------------->{MY_UNITESTS}
#  - MAIN PSEUDO-CODE:
#    - 0| IN ANY CASE:
#        - 0.0| display all enabled options
#        - 0.1| display list all home-made fun in libft.a
#        - 0.2| display list all build-in fun in libft.a (ca be use to see forbidden function)
#    - 1| NORMINETTE-CHECKER:
#        - 1.1| if NORMI=1                                   🢥  launch norminette-checker, excluding Corr_libft_enhanced folder
#    - 2| TRIPOUILLE-TESTER:
#        - 2.0| if TRIPOUILLE_LIBFT=1                        🢥  launch Tripouille-libft for mandatory part
#          - if BONUS=1 OR if any libft_bonus fun. detected  🢥  launch Tripouille-libft for bonus part
#        - 2.1| if TRIPOUILLE_PRINTF=1                       🢥  launch Tripouille-ft_printf for mandatory part
#          - if BONUS=1                                      🢥  launch Tripouille-ft_printf for bonus part
#        - 2.2| if TRIPOUILLE_GNL=1                          🢥  launch Tripouille-get_next_line for mandatory part
#          - if BONUS=1                                      🢥  launch Tripouille-get_next_line for bonus part
#    - 3| MY_UNITESTS-TESTER:
#        - 3.0| if MY_UNITESTS_LIBFT=1                       🢥  launch My_unitests-libft for mandatory part
#          - if BONUS=1 OR if any libft_bonus fun. detected  🢥  launch My_unitests-libft for bonus part
#        - 3.1| if MY_UNITESTS_PRINTF=1                      🢥  launch My_unitests-ft_printf for mandatory part
#          - if BONUS=1                                      🢥  launch My_unitests-ft_printf for bonus part
#        - 3.2| if MY_UNITESTS_GNL=1                         🢥  launch My_unitests-get_next_line for mandatory part
#          - if BONUS=1                                      🢥  launch My_unitests-get_next_line for bonus part
#        - 3.3| if MY_UNITESTS_OTHERS=1                      🢥  launch My_unitests-others (personnal fun for which a matching test was found)
# ============================================================================================================
 
# =[ VARIABLES ]==============================================================================================
# -[ SCRIPT OPTIONS ]-----------------------------------------------------------------------------------------
HELP=0                                                             # ☑ set:1🢥 Display script usage
BONUS=0                                                            # ☑ set:1🢥 launch all test with bonus option
NORM=1                                                             # ☑ set:1🢥 launch NORMINETTE TESTER
MY_UNITESTS_LIBFT=0                                                # ☑ set:1🢥 launch my tester for LIBFT(DEFAULT)
MY_UNITESTS_GNL=0                                                  # ☑ set:1🢥 launch my tester for GNL(DEFAULT)
MY_UNITESTS_PRINTF=0                                               # ☑ set:1🢥 launch my tester for PRINTF(DEFAULT)
MY_UNITESTS_OTHERS=0                                               # ☑ set:1🢥 launch my tester for OTHERS_FUNCTION_FOUND(DEFAULT)
TRIPOUILLE_LIBFT=0                                                 # ☑ set:1🢥 launch Tripouille for libft()
TRIPOUILLE_GNL=0                                                   # ☑ set:1🢥 launch Tripouille for get_next_line()
TRIPOUILLE_PRINTF=0                                                # ☑ set:1🢥 launch Tripouille for ft_printf()
# -[ PATH/FOLDER/FILE ]---------------------------------------------------------------------------------------
SCRIPTNAME=${0##*\/}                                               # ☒ Script's name (no path)
PARENT_DIR=$(dirname $(realpath ${0}))                             # ☒ Name of parent directory
LIBFT_DIR=$(dirname ${PARENT_DIR})                                 # ☒ Name of libft_enhanced (grandparent folder)
LOG_DIR="${PARENT_DIR}/log/$(date +%Y_%m_%d/%Hh%Mm%Ss)"            # ☒ Name of the log folder
LOG_FAIL="${LOG_DIR}/list_errors.log"                              # ☒ File contains list of function that failed
BSL_DIR="${PARENT_DIR}/src/BSL"                                    # ☒ Path to BSL folder
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
source ${BSL_DIR}/src/check42_norminette.sh
source ${BSL_DIR}/src/print.sh
# =[ FUNCTIONS ]==============================================================================================
# -[ USAGE ]--------------------------------------------------------------------------------------------------
# Display usage with arg1 as error_msg and arg2 as exit_code
# TODO UPDATE usage to add options.
script_usage()
{
    echo -e "${RU}[Err:${2}] Wrong usage${R0}: ${1}${E}\n${BU}Usage:${R0}  \`${V0}./${SCRIPTNAME}\`${E}"
    echo -e " 🔹 ${V0}${SCRIPTNAME}${E} has as a prerequisites:"
    echo -e "    ${B0}‣ ${R0}i) ${E}: To be cloned inside the project ${M0}path/libft/${E} to be tested, with the ${M0}--recursive-submodules${E} option."
    echo -e "    ${B0}‣ ${R0}ii)${E}: The static lib ${M0}path/libft/*/${B0}libft.a${E} has to be compiled before using ${V0}./${SCRIPTNAME}${E}."
    echo -e " 🔹 ${V0}${SCRIPTNAME}${E} have multiples options:"
    echo -e "    ${B0}‣ ${M0}[-h, --help]          ${BC0}🢥  ${E}Enable HELP option that display script usage."
    echo -e "    ${B0}‣ ${M0}[-n, --no-norm]       ${BC0}🢥  ${E}Desable step NORMINETTE tester."
    echo -e "    ${B0}‣ ${M0}[-b, --bonus]         ${BC0}🢥  ${E}Enable Bonus option for all testers."
    echo -e "    ${B0}‣ ${M0}[-a, --all]           ${BC0}🢥  ${E}Enable ALL tripouille and my_unitests OPTIONS (WITHOUT BONUS)."
    echo -e "    ${B0}‣ ${M0}[-t, --tripouille]    ${BC0}🢥  ${E}Enable ONLY tripouille tester."
    echo -e "    ${B0}‣ ${M0}[-l, --libft]         ${BC0}🢥  ${E}Enable both tripouille and my_unitests testers for LIBFT."
    echo -e "    ${B0}‣ ${M0}[-f, --ft_printf]     ${BC0}🢥  ${E}Enable both tripouille and my_unitests testers for FT_PRINTF."
    echo -e "    ${B0}‣ ${M0}[-g, --get_next_line] ${BC0}🢥  ${E}Enable both tripouille and my_unitests testers for GET_NEXT_LINE."
    echo -e "    ${B0}‣ ${M0}[-o, --other]         ${BC0}🢥  ${E}Enable both tripouille and my_unitests testers for OTHERS FUNCTIONS FOUND."
    echo -e " 🔹 ${V0}${SCRIPTNAME}${E} PSEUDO-CODE:"
    echo -e "    🔹 ${GU}0) IN ANY CASE:${E}"
    echo -e "       ${B0}‣ ${GU}0.0)${E} display all enabled options"
    echo -e "       ${B0}‣ ${GU}0.1)${E} display list all home-made fun in libft.a"
    echo -e "       ${B0}‣ ${GU}0.2)${E} display list all build-in fun in libft.a (ca be use to see forbidden function)"
    echo -e "    🔹 ${GU}1) NORMINETTE-CHECKER:${E}"
    echo -e "       ${B0}‣ ${GU}1.1)${E} if NORMI=1                                   ${BC0}🢥 ${E} launch norminette-checker, excluding Corr_libft_enhanced folder"
    echo -e "    🔹 ${BU}2) TRIPOUILLE-TESTER:${E}"
    echo -e "       ${B0}‣ ${GU}2.0)${E} if TRIPOUILLE_LIBFT=1                        ${BC0}🢥 ${E} launch Tripouille-libft for mandatory part"
    echo -e "         ${B0}⮡${E} if BONUS=1 ${B0}OR${E} if any libft_bonus fun. detected  ${BC0}🢥 ${E} launch Tripouille-libft for bonus part"
    echo -e "       ${B0}‣ ${GU}2.1)${E} if TRIPOUILLE_PRINTF=1                       ${BC0}🢥 ${E} launch Tripouille-ft_printf for mandatory part"
    echo -e "         ${B0}⮡${E} if BONUS=1                                      ${BC0}🢥 ${E} launch Tripouille-ft_printf for bonus part"
    echo -e "       ${B0}‣ ${GU}2.2)${E} if TRIPOUILLE_GNL=1                          ${BC0}🢥 ${E} launch Tripouille-get_next_line for mandatory part"
    echo -e "         ${B0}⮡${E} if BONUS=1                                      ${BC0}🢥 ${E} launch Tripouille-get_next_line for bonus part"
    echo -e "    🔹 ${GU}3) MY_UNITEST-TESTER:${E}"
    echo -e "       ${B0}‣ ${GU}3.0)${E} if MY_UNITESTS_LIBFT=1                       ${BC0}🢥 ${E} launch My_unitests-libft for mandatory part"
    echo -e "         ${B0}⮡${E} if BONUS=1 ${B0}OR${E} if any libft_bonus fun. detected  ${BC0}🢥 ${E} launch My_unitests-libft for bonus part"
    echo -e "       ${B0}‣ ${GU}3.1)${E} if MY_UNITESTS_PRINTF=1                      ${BC0}🢥 ${E} launch My_unitests-ft_printf for mandatory part"
    echo -e "         ${B0}⮡${E} if BONUS=1                                      ${BC0}🢥 ${E} launch My_unitests-ft_printf for bonus part"
    echo -e "       ${B0}‣ ${GU}3.2)${E} if MY_UNITESTS_GNL=1                         ${BC0}🢥 ${E} launch My_unitests-get_next_line for mandatory part"
    echo -e "         ${B0}⮡${E} if BONUS=1                                      ${BC0}🢥 ${E} launch My_unitests-get_next_line for bonus part"
    echo -e "       ${B0}‣ ${GU}3.3)${E} if MY_UNITESTS_OTHERS=1                      ${BC0}🢥 ${E} launch My_unitests-others (personnal fun for which a matching test was found)"
    exit ${2}
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
            local test_main=$(find "${PARENT_DIR}/src" -type f -name *"${fun}.c")
            local test_txt=$(find "${PARENT_DIR}/src" -type f -name *"${fun}.txt")
            if [[ -n "${test_main}" ]];then
                # STEP 1 : COMPILATION --> IF NO BINARY OR IF SOURCES NEWER THAN BINARY
                [[ ! -d ${BIN_DIR} ]] && mkdir -p ${BIN_DIR}
                exe="${BIN_DIR}/test_${fun}"
                echo -en " ${BC0} ⤷${E} ⚙️  ${GU}Compilation:${E}"
                # cases where compilation needed: (1:no binary),(2:sources newer than binary),(3:text exist and newer than binary)
                # TODO: handle when OBJ file are newer that exe too
                if [[ ! -f "${exe}" || "${test_main}" -nt "${exe}" || ( -n "${test_txt}" && "${test_txt}" -nt "${exe}" ) ]];then
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
    local tot_tested=$(find ${short_log_dir} -mindepth 1 -maxdepth 1 -type d | wc -l )
    local lst_fail=( )
    local causes=( )
    local causes=( )
    [[ -f "${LOG_FAIL}" ]] && for ff in $(cat ${LOG_FAIL} | awk '{print $1}' | sort -u);do [[ ! " ${lst_fail[@]} " =~ " ${ff} " ]] && lst_fail+=( "${ff}" );done
    if [[ ${#lst_fail[@]} -eq 0 ]];then
        args+=( " 🔸 ${YU}${tot_tested} functions have been tested:${V0} ✅ PASS${E}" ) 
    else
        args+=( " 🔸 ${YU}${tot_tested} functions have been tested:${E}" )
        args+=( \ "   ${V0}✅ $(( tot_tested - ${#lst_fail[@]} )) functions ${V0}PASSED.${E}" \
            "    ${R0}❌ ${#lst_fail[@]} functions ${R0}FAILLED:${E}" \
        )
        for fun in "${lst_fail[@]}";do
            args+=( "      ${R0}✘ ${RU}${fun}():${E}" )
            local link1=$(awk -v f="${fun}" '$1 == f &&  $2 == "compilation" {print $3}' ${LOG_FAIL})
            local link2=$(awk -v f="${fun}" '$1 == f &&  $2 == "errors" {print $3}' ${LOG_FAIL})
            local link3=$(awk -v f="${fun}" '$1 == f &&  $2 == "leaks" {print $3}' ${LOG_FAIL})
            local link4=$(awk -v f="${fun}" '$1 == f &&  $2 == "missing" {print $3}' ${LOG_FAIL})
            [[ -n "${link1}" ]] && args+=( "      ${R0}⤷ Error occure will compilling ${M0}👉 ${link1}${E}" )
            [[ -n "${link2}" ]] && args+=( "      ${R0}⤷ Error detected ${M0}👉 ${link2}${E}" )
            [[ -n "${link3}" ]] && args+=( "      ${R0}⤷ Leaks detected ${M0}👉 ${link3}${E}" )
            [[ -n "${link4}" ]] && args+=( "      ${R0}⤷ Missing function, not found in object file.${E}" )
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
has_a=0 ; has_t=0 ; has_l=0 ; has_g=0 ; has_p=0 ; has_b=0 ; has_h=0; has_n=0; has_o=0
for args in "$@";do
    shift
    case "${args}" in
        --[Aa]ll | -[Aa]) has_a=1 ;;
        --[Tt]ripouille | -[Tt]) has_t=1 ;;
        --[Li]bft | -[Ll][Ff][Tt] | -[Ll]) has_l=1 ;;
        --[Gg]et[Nn]ext[Ll]ine | --[Gg]et_[Nn]ext_[Ll]ine | -[Gg][Nn][Ll] | -[Gg]) has_g=1 ;;
        --ft_printf | --printf | --print | -[Pp] ) has_p=1 ;;
        --[Bb]onus | -[Bb] ) has_b=1 ;;
        --[Hh]elp | -[Hh] ) has_h=1 ;;
        --[Nn]o-[Nn]orm | -[Nn] ) has_n=1 ;;
        --[Oo]ther | --[Oo]thers | -[Oo] ) has_o=1 ;;
        *) script_usage "Error: Unknown option '${args}'" 1 ;;
    esac
done
# -[ CHECK FORBIDDEN OPTIONS COMBINATION ]--------------------------------------------------------------------
[[ ( ${has_h} -eq 1 ) && ( ${NB_ARG} -gt 1 ) ]] && script_usage "--help option can not be paired with other option" 3
[[ ( ${has_a} -eq 1 ) && ( ${ARG_COUNT} -gt 2 || ( ${ARG_COUNT} -eq 2 && ${has_b} -eq 0 && ${has_n} -eq 0 )) ]] && script_usage "--all option can only be paired with --bonus option" 3
[[ ( ${has_t} -eq 1 ) && ( ${ARG_COUNT} -gt 2 || ( ${ARG_COUNT} -eq 2 && ${has_b} -eq 0 && ${has_n} -eq 0 )) ]] && script_usage "--tripouille option can only be paired with --bonus option" 3
[[ ${ARG_COUNT} -eq 2 && ${has_b} -eq 1 && ${has_o} -eq 1 ]] && script_usage "--bonus option does not means anything for --others option" 3
# -[ SET OPTIONS VARIABLES ]----------------------------------------------------------------------------------
[[ ${has_a} -eq 1 ]] && TRIPOUILLE_LIBFT=1 && TRIPOUILLE_GNL=1 && TRIPOUILLE_PRINTF=1 && MY_UNITESTS_LIBFT=1 && MY_UNITESTS_GNL=1 && MY_UNITESTS_PRINTF=1 && MY_UNITESTS_OTHERS=1
[[ ${has_t} -eq 1 ]] && TRIPOUILLE_LIBFT=1 && TRIPOUILLE_GNL=1 && TRIPOUILLE_PRINTF=1 && MY_UNITESTS_LIBFT=0 && MY_UNITESTS_GNL=0 && MY_UNITESTS_PRINTF=0
[[ ${has_l} -eq 1 ]] && TRIPOUILLE_LIBFT=1 && MY_UNITESTS_LIBFT=1
[[ ${has_g} -eq 1 ]] && TRIPOUILLE_GNL=1 && MY_UNITESTS_GNL=1
[[ ${has_p} -eq 1 ]] && TRIPOUILLE_PRINTF=1 && MY_UNITESTS_PRINTF=1
[[ ${has_o} -eq 1 ]] && MY_UNITESTS_OTHERS=1
[[ ${has_b} -eq 1 ]] && BONUS=1
[[ ${has_h} -eq 1 ]] && HELP=1
[[ ${has_n} -eq 1 ]] && NORM=0
# =[ DISPLAY USAGE THEN STOP IF --help OPTION ]===============================================================
[[ ${HELP} -eq 1 ]] && script_usage "Help asked for" 0
# =[ SET MY_UNITEST LIBFT AS DEFAULT BEHAVIOR ]===============================================================
[[ $(( MY_UNITESTS_LIBFT + MY_UNITESTS_GNL + MY_UNITESTS_PRINTF + MY_UNITESTS_OTHERS + TRIPOUILLE_LIBFT + TRIPOUILLE_GNL + TRIPOUILLE_PRINTF )) -eq 0 ]] && MY_UNITESTS_LIBFT=1 && MY_UNITESTS_OTHERS=1;
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
    test_fun=$(find "${PARENT_DIR}/src" -type f -name *"${fun}.c")
    [[ -n "${test_fun}" ]] && PERSO_FUN_TO_TEST+=( "${fun}" )
done
# -[ SET OPTIONS LIST ]---------------------------------------------------------------------------------------
OPTIONS+=( "    🔸 ${YU}Norminette checkeur:${E}" )
[[ ${NORM} -eq 1 ]] && OPTIONS+=( "       ${V0}✓ Enable${E}" ) || OPTIONS+=( "       ${R0}✘ Desable${E}" )
if [[ $(( TRIPOUILLE_LIBFT + TRIPOUILLE_GNL + TRIPOUILLE_PRINTF )) -gt 0 ]];then
    OPTIONS+=( "    🔸 ${YU}Tripouille tester:${E}" )
    if [[ ${TRIPOUILLE_LIBFT} -eq 1 ]];then
        OPTIONS+=( "      🔸 ${YU}libft functions:${E}" "         ${V0}✓ MANDATORY part${E}" )
        if [[ ${has_b} -eq 1 ]];then
            OPTIONS+=( "         ${V0}✓ BONUS part ${G0}(asked for)${E}" )
        else
            for fun in ${HOMEMADE_FUNUSED[@]};do
                if [[ ! " ${LIBFT_BONUS[@]} " =~ " ${fun} " ]];then
                    OPTIONS+=( "         ${V0}✓ BONUS part ${G0}(detected)${E}" )
                    break
                fi
            done
        fi
    fi
    if [[ ${TRIPOUILLE_GNL} -eq 1 ]];then
        OPTIONS+=( "      🔸 ${YU}get_next_line():${E}" "         ${V0}✓ MANDATORY part${E}" )
        [[ ${has_b} -eq 1 ]] && OPTIONS+=( "         ${V0}✓ BONUS part ${G0}(asked for)${E}" )
    fi
    if [[ ${TRIPOUILLE_PRINTF} -eq 1 ]];then
        OPTIONS+=( "      🔸 ${YU}ft_printf():${E}" "         ${V0}✓ MANDATORY part${E}" )
        [[ ${has_b} -eq 1 ]] && OPTIONS+=( "         ${V0}✓ BONUS part ${G0}(asked for)${E}" )
    fi
fi
if [[ $(( MY_UNITESTS_LIBFT + MY_UNITESTS_GNL + MY_UNITESTS_PRINTF + MY_UNITESTS_OTHERS)) -gt 0 ]];then
    OPTIONS+=( "    🔸 ${YU}My_unitests tester:${E}" )
    if [[ ${MY_UNITESTS_LIBFT} -eq 1 ]];then
        OPTIONS+=( "      🔸 ${YU}libft functions:${E}" "         ${V0}✓ MANDATORY part${E}" )
        if [[ ${has_b} -eq 1 ]];then
            OPTIONS+=( "         ${V0}✓ BONUS part ${G0}(asked for)${E}" )
        else
            for fun in ${HOMEMADE_FUNUSED[@]};do
                if [[ ! " ${LIBFT_BONUS[@]} " =~ " ${fun} " ]];then
                    OPTIONS+=( "         ${V0}✓ BONUS part ${G0}(detected)${E}" )
                    break
                fi
            done
        fi
    fi
    if [[ ${MY_UNITESTS_GNL} -eq 1 ]];then
        OPTIONS+=( "      🔸 ${YU}get_next_line():${E}" "         ${V0}✓ MANDATORY part ${G0}(asked for)${E}" )
        [[ ${has_b} -eq 1 ]] && OPTIONS+=( "         ${V0}✓ BONUS part ${G0}(asked for)${E}" )
    else
        if [[ ! " ${HOMEMADE_FUNUSED[@]} " =~ " get_next_line " ]];then
            OPTIONS+=( "      🔸 ${YU}get_next_line():${E}" "         ${V0}✓ MANDATORY part ${G0}(detected)${E}" )
            [[ ${has_b} -eq 1 ]] && OPTIONS+=( "         ${V0}✓ BONUS part ${G0}(asked for)${E}" )
            break
        fi
    fi
    if [[ ${MY_UNITESTS_PRINTF} -eq 1 ]];then
        OPTIONS+=( "      🔸 ${YU}ft_printf():${E}" "         ${V0}✓ MANDATORY part ${G0}(asked for)${E}" )
        [[ ${has_b} -eq 1 ]] && OPTIONS+=( "         ${V0}✓ BONUS part ${G0}(asked for)${E}" )
    else
        if [[ ! " ${HOMEMADE_FUNUSED[@]} " =~ " ft_printf " ]];then
            OPTIONS+=( "      🔸 ${YU}ft_printf():${E}" "         ${V0}✓ MANDATORY part ${G0}(detected)${E}" )
            [[ ${has_b} -eq 1 ]] && OPTIONS+=( "         ${V0}✓ BONUS part ${G0}(asked for)${E}" )
            break
        fi
    fi
    if [[ ${MY_UNITESTS_OTHERS} -eq 1 ]];then
        OPTIONS+=( "      🔸 ${YU}${#PERSO_FUN[@]} Personnal/Other functions detected:${E}" )
        if [[ ${#PERSO_FUN_TO_TEST[@]} -eq 0 ]];then
            OPTIONS+=( "         ${R0}✘ no matching tester found${E}" )
        else
            OPTIONS+=( "         ${V0}✓ ${#PERSO_FUN_TO_TEST[@]} matching tester(s) found${E}" )
        fi
    fi
fi
# =[ 0.1 | DISPLAY ENABLED OPTIONS ]==========================================================================
print_in_box -t 2 -c y \
    "          ${Y0}  ___   _____     _     __    _____     _____   ___   ___   _____   ___  ${E}" \
    "          ${Y0} / __| |_   _|   /_\   | _ \ |_   _|   |_   _| | __| / __| |_   _| / __| ${E}" \
    "          ${Y0} \__ \   | |    / _ \  |   /   | |       | |   | _|  \__ \   | |   \__ \ ${E}" \
    "          ${Y0} |___/   |_|   /_/ \_\ |_|_\   |_|       |_|   |___| |___/   |_|   |___/ ${E}" \
    "          ${Y0}                                                                         ${E}" \
    "  🔶 ${OPTIONS[@]}"
# =[ 0.2 | DISPLAY LIST HOME-MADE FUN ]=======================================================================
# TODO
#print_in_box -t 1 -c b "🟦 ${HOMEMADE_FUNUSED[@]}"
# =[ 0.3 | DISPLAY LIST BUILD-IN FUN ]========================================================================
# TODO
#print_in_box -t 1 -c b "🟦 ${BUILTIN_FUNUSED[@]}"
# =[ 0.4 | CHECK NORMINETTE ]=================================================================================
if [[ ${NORM} -eq 1 ]];then
    exec_anim_in_box "check42_norminette ${LIBFT_DIR}" "Check Norminette"
    res_normi=${?}
fi
# =[ LAUNCH TRIPOUILLE ]======================================================================================
if [[ $(( TRIPOUILLE_LIBFT + TRIPOUILLE_GNL + TRIPOUILLE_PRINTF )) -gt 0 ]];then
    print_in_box -t 2 -c y \
        "   ${Y0}  _____         _                       _   _   _           _____              _        ${E}" \
        "   ${Y0} |_   _|  _ _  (_)  _ __   ___   _  _  (_) | | | |  ___    |_   _|  ___   ___ | |_   ___${E}" \
        "   ${Y0}   | |   | '_| | | | '_ \ / _ \ | || | | | | | | | / -_)     | |   / -_) (_-< |  _| (_-<${E}" \
        "   ${Y0}   |_|   |_|   |_| | .__/ \___/  \_,_| |_| |_| |_| \___|     |_|   \___| /__/  \__| /__/${E}" \
        "   ${Y0}                   |_|                                                                  ${E}"
fi
# -[ LIBFT ]--------------------------------------------------------------------------------------------------
if [[ ${TRIPOUILLE_LIBFT} -eq 1 ]];then
    print_in_box -t 3 -c b \
        "     ${BC0}┏┳┓  •      •┓┓    ┓•┓ ┏           ┓         ${E}" \
        "     ${BC0} ┃ ┏┓┓┏┓┏┓┓┏┓┃┃┏┓  ┃┓┣┓╋╋  ┏┳┓┏┓┏┓┏┫┏┓╋┏┓┏┓┓┏${E}" \
        "     ${BC0} ┻ ┛ ┗┣┛┗┛┗┛┗┗┗┗   ┗┗┗┛┛┗  ┛┗┗┗┻┛┗┗┻┗┻┗┗┛┛ ┗┫${E}"
    make -s -C ${PARENT_DIR}/src/tripouille/libft m
    # -[ Run BONUS-TESTER if explicitly asked ]---------------------------------------------------------------
    if [[ ${BONUS} -eq 1 ]];then 
        print_in_box -t 3 -c b \
        "     ${BC0}┏┳┓  •      •┓┓    ┓•┓ ┏   ┓        ${E}" \
        "     ${BC0} ┃ ┏┓┓┏┓┏┓┓┏┓┃┃┏┓  ┃┓┣┓╋╋  ┣┓┏┓┏┓┓┏┏${E}" \
        "     ${BC0} ┻ ┛ ┗┣┛┗┛┗┛┗┗┗┗   ┗┗┗┛┛┗  ┗┛┗┛┛┗┗┛┛${E}"
        make -s -C ${PARENT_DIR}/src/tripouille/libft b
    else
    # -[ Run BONUS-TESTER if any libft_bonus fun. founded in static library ]---------------------------------
        for fun in ${HOMEMADE_FUNUSED[@]};do
            if [[ " ${LIBFT_BONUS[@]} " =~ " ${fun} " ]];then
                print_in_box -t 3 -c b \
                    "     ${BC0}┏┳┓  •      •┓┓    ┓•┓ ┏   ┓        ${E}" \
                    "     ${BC0} ┃ ┏┓┓┏┓┏┓┓┏┓┃┃┏┓  ┃┓┣┓╋╋  ┣┓┏┓┏┓┓┏┏${E}" \
                    "     ${BC0} ┻ ┛ ┗┣┛┗┛┗┛┗┗┗┗   ┗┗┗┛┛┗  ┗┛┗┛┛┗┗┛┛${E}"
                make -s -C ${PARENT_DIR}/src/tripouille/libft b
                break
            fi
        done
    fi
fi
# -[ FT_PRINTF ]----------------------------------------------------------------------------------------------
if [[ ${TRIPOUILLE_PRINTF} -eq 1 ]];then
    if [[ " ${HOMEMADE_FUNUSED[@]} " =~ " ft_printf " ]];then
        print_in_box -t 3 -c b \
            "     ${BC0}┏┳┓  •      •┓┓    ┏┓      •   ┏  ┳┳┓     ┓         ${E}" \
            "     ${BC0} ┃ ┏┓┓┏┓┏┓┓┏┓┃┃┏┓  ┣ ╋ ┏┓┏┓┓┏┓╋╋  ┃┃┃┏┓┏┓┏┫┏┓╋┏┓┏┓┓┏${E}" \
            "     ${BC0} ┻ ┛ ┗┣┛┗┛┗┛┗┗┗┗   ┻ ┗━┣┛┛ ┗┛┗┗┛  ┛ ┗┗┻┛┗┗┻┗┻┗┗┛┛ ┗┫${E}"
        make -s -C ${PARENT_DIR}/src/tripouille/ft_printf m
        # -[     GNL_BONUS ONLY IF OPTION ACTIVATED ]-------------------------------------------------------------
        if [[ ${BONUS} -eq 1 ]];then
            print_in_box -t 3 -c b \
                "     ${BC0}┏┳┓  •      •┓┓    ┏┓      •   ┏  ┳┓       ${E}" \
                "     ${BC0} ┃ ┏┓┓┏┓┏┓┓┏┓┃┃┏┓  ┣ ╋ ┏┓┏┓┓┏┓╋╋  ┣┫┏┓┏┓┓┏┏${E}" \
                "     ${BC0} ┻ ┛ ┗┣┛┗┛┗┛┗┗┗┗   ┻ ┗━┣┛┛ ┗┛┗┗┛  ┻┛┗┛┛┗┗┛┛${E}"
                                        make -s -C ${PARENT_DIR}/src/tripouille/ft_printf b
        fi
    else
        print_in_box -t 3 -c r "${R0}ft_printf() function not found in static library${E}"
    fi
fi
# -[ GET_NEXT_LINE ]------------------------------------------------------------------------------------------
if [[ ${TRIPOUILLE_GNL} -eq 1 ]];then
    if [[ " ${HOMEMADE_FUNUSED[@]} " =~ " get_next_line " ]];then
        print_in_box -t 3 -c b \
            "     ${BC0}┏┳┓  •      •┓┓    ┏┓     ┳┓       ┓ •      ┳┳┓     ┓         ${E}" \
            "     ${BC0} ┃ ┏┓┓┏┓┏┓┓┏┓┃┃┏┓  ┃┓┏┓╋  ┃┃┏┓┓┏╋  ┃ ┓┏┓┏┓  ┃┃┃┏┓┏┓┏┫┏┓╋┏┓┏┓┓┏${E}" \
            "     ${BC0} ┻ ┛ ┗┣┛┗┛┗┛┗┗┗┗   ┗┛┗ ┗  ┛┗┗ ┛┗┗  ┗┛┗┛┗┗   ┛ ┗┗┻┛┗┗┻┗┻┗┗┛┛ ┗┫${E}"
        make -s -C ${PARENT_DIR}/src/tripouille/get_next_line m
        # -[     GNL_BONUS ONLY IF OPTION ACTIVATED ]-------------------------------------------------------------
        if [[ ${BONUS} -eq 1 ]];then
            print_in_box -t 3 -c b \
                "     ${BC0}┏┳┓  •      •┓┓    ┏┓     ┳┓       ┓ •      ┳┓       ${E}" \
                "     ${BC0} ┃ ┏┓┓┏┓┏┓┓┏┓┃┃┏┓  ┃┓┏┓╋  ┃┃┏┓┓┏╋  ┃ ┓┏┓┏┓  ┣┫┏┓┏┓┓┏┏${E}" \
                "     ${BC0} ┻ ┛ ┗┣┛┗┛┗┛┗┗┗┗   ┗┛┗ ┗  ┛┗┗ ┛┗┗  ┗┛┗┛┗┗   ┻┛┗┛┛┗┗┛┛${E}"
            make -s -C ${PARENT_DIR}/src/tripouille/get_next_line b
        fi
    else
        print_in_box -t 3 -c r "${R0}get_next_line() function not found in static library${E}"
    fi
fi
# =[ MY_UNITESTS ]============================================================================================
print_in_box -t 2 -c y \
    "           ${Y0}  __  __                _   _          _   _                _        ${E}" \
    "           ${Y0} |  \/  |  _  _   ___  | | | |  _ _   (_) | |_   ___   ___ | |_   ___${E}" \
    "           ${Y0} | |\/| | | || | |___| | |_| | | ' \  | | |  _| / -_) (_-< |  _| (_-<${E}" \
    "           ${Y0} |_|  |_|  \_, |        \___/  |_||_| |_|  \__| \___| /__/  \__| /__/${E}" \
    "           ${Y0}           |__/                                                      ${E}"
# -[ LIBFT ]--------------------------------------------------------------------------------------------------
if [[ ${MY_UNITESTS_LIBFT} -eq 1 ]];then
    exec_anim_in_box "launch_my_unitests HOMEMADE_FUNUSED LIBFT_MANDA" "Tests libft mandatory functions"
    # -[ LIBFT_BONUS if BONUS opt or if any libft_bonus fun detected in libft.a ]-----------------------------
    if [[ ${BONUS} -eq 1 ]];then 
        exec_anim_in_box "launch_my_unitests HOMEMADE_FUNUSED LIBFT_BONUS" "Tests libft bonus functions"
    else
        for fun in ${HOMEMADE_FUNUSED[@]};do
            if [[ ! " ${LIBFT_BONUS[@]} " =~ " ${fun} " ]];then
                exec_anim_in_box "launch_my_unitests HOMEMADE_FUNUSED LIBFT_BONUS" "Tests libft bonus functions"
                break
            fi
        done
    fi
fi
# -[ GET_NEXT_LINE ]------------------------------------------------------------------------------------------
# TODO
if [[ ${MY_UNITESTS_GNL} -eq 1 ]];then
    #exec_anim_in_box "launch_my_unitests HOMEMADE_FUNUSED LIBFT_MANDA" "Tests libft mandatory functions"
    exec_anim_in_box "echo \"execute test for get_next_line() mandatory part\""
    # -[ LIBFT_BONUS if BONUS opt or if any libft_bonus fun detected in libft.a ]-----------------------------
    if [[ ${BONUS} -eq 1 ]];then 
        exec_anim_in_box "echo \"execute test for get_next_line() bonus part\""
        #exec_anim_in_box "launch_my_unitests HOMEMADE_FUNUSED LIBFT_BONUS" "Tests libft bonus functions"
    fi
fi
# -[ FT_PRINTF ]----------------------------------------------------------------------------------------------
# TODO
if [[ ${MY_UNITESTS_PRINTF} -eq 1 ]];then
    #exec_anim_in_box "launch_my_unitests HOMEMADE_FUNUSED LIBFT_MANDA" "Tests libft mandatory functions"
    exec_anim_in_box "echo \"execute test for ft_printf() mandatory part\""
    # -[ LIBFT_BONUS if BONUS opt or if any libft_bonus fun detected in libft.a ]-----------------------------
    if [[ ${BONUS} -eq 1 ]];then 
        exec_anim_in_box "echo \"execute test for ft_printf() bonus part\""
        #exec_anim_in_box "launch_my_unitests HOMEMADE_FUNUSED LIBFT_BONUS" "Tests libft bonus functions"
    fi
fi
# -[ PERSONNAL FUNCTIONS ]------------------------------------------------------------------------------------
if [[ ${MY_UNITESTS_OTHERS} -eq 1 ]];then
    #exec_anim_in_box "launch_my_unitests PERSO_FUN_TO_TEST" "Tests ${#PERSO_FUN_TO_TEST[@]} personnal functions"
    exec_anim_in_box "launch_my_unitests PERSO_FUN" "Tests ${#PERSO_FUN_TO_TEST[@]}/${#PERSO_FUN[@]} of personnal functions"
fi
# -[ DISPLAY UNITESTS RESUME ]--------------------------------------------------------------------------------
# TODO
[[ $(( MY_UNITESTS_LIBFT + MY_UNITESTS_GNL + MY_UNITESTS_PRINTF + MY_UNITESTS_OTHERS)) -gt 0 ]] && display_resume "Libft's tests"
