#!/usr/bin/env bash

# ============================================================================================================
# Launch libft.a tests
# This script take no argument (for now) and will automatically:
#   - 1: check norminette for libft folder, excluding Corr_libft_enhancde folder, tests dont comply with norme
#   - 2: list all home-made fun in libft.a
#   - 3: list all build-in fun in libft.a
#   - 4: launch libft mandatory functions tests.
#   - 5: if detected at least one fun of libft_bonus part, launch test for all libft_bonus functions.
#   - 6: if detected ft_printf() in libft.a, launch tests for ft_printf() tests (bonus too, auto)
#   - 7: if detected get_next_line() in libft.a, launch tests for get_next_line() tests (bonus too, auto)
# ============================================================================================================
 
# =[ VARIABLES ]==============================================================================================
# -[ PATH/FOLDER/FILE ]---------------------------------------------------------------------------------------
SCRIPTNAME=${0##*\/}                                              # ☒ Script's name (no path)
PARENT_DIR=$(dirname $(realpath ${0}))                            # ☒ Name of parent directory
LIBFT_DIR=$(dirname ${PARENT_DIR})                                # ☒ Name of libft_enhanced (grandparent folder)
LOG_DIR="${PARENT_DIR}/log/$(date +%Y_%m_%d/%Hh%Mm%Ss)"           # ☒ Name of the log folder
BSL_DIR="${PARENT_DIR}/src/BSL"                                   # ☒ Path to BSL folder
BIN_DIR="${PARENT_DIR}/bin"                                       # ☒ Path to bin folder (test binary)
LIBFT_A=$(find ${LIBFT_DIR} -type f -name "libft.a")              # ☒ static library name libft.a 
LIBFT_INC=$(dirname $(find ${LIBFT_DIR} -type f -name "libft.h")) # ☒ Folder that contains to libft.h HEADER
# -[ COMMANDS ]-----------------------------------------------------------------------------------------------
CC="cc -Wall -Wextra -Werror -I${LIBFT_INC}"
VAL_ERR=42
VALGRIND="valgrind --leak-check=full --track-fds=yes --error-exitcode=${VAL_ERR}"
# -[ LISTS ]--------------------------------------------------------------------------------------------------
HOMEMADE_FUNUSED=( )                                              # ☒ List of user created function in libft.a
BUILTIN_FUNUSED=( )                                               # ☒ List of build-in function in libft.a
EXCLUDE_NORMI_FOLD=( "tests" "${PARENT_DIR##*\/}" )               # ☒ List of folder to be ignore by norminette
LIBFT_MANDA=( "ft_isalpha" "ft_isdigit" "ft_isalnum" "ft_isascii" "ft_isprint" "ft_strlen" "ft_memset" \
    "ft_bzero" "ft_memcpy" "ft_memmove" "ft_strlcpy" "ft_strlcat" "ft_toupper" "ft_tolower" "ft_strchr" \
    "ft_strrchr" "ft_strncmp" "ft_memchr" "ft_memcmp" "ft_strnstr" "ft_atoi" "ft_calloc" "ft_strdup" \
    "ft_substr" "ft_strjoin" "ft_strtrim" "ft_split" "ft_itoa" "ft_strmapi" "ft_striteri" "ft_putchar_fd" \
    "ft_putstr_fd" "ft_putendl_fd" "ft_putnbr_fd" )
LIBFT_BONUS=( "ft_lstnew" "ft_lstadd_front" "ft_lstsize" "ft_lstlast" "ft_lstadd_back" "ft_lstdelone" \
    "ft_lstclear" "ft_lstiter" "ft_lstmap" )
# -[ LAYOUT ]-------------------------------------------------------------------------------------------------
LEN=100                                                            # ☑ Width of the box
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
# -[ COUNT ]--------------------------------------------------------------------------------------------------
TOT_TESTS="${#LIBFT_MANDA[@]}"                                     # ☒ Count how many fun are tested
TOT_FAILS=0                                                        # ☒ Count how many fun have failed
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
    echo -e "    ${B0}‣ ${R0}2${E}: Set a list of all user-made function found in the ${B0}libft.a${E} static lib"
    echo -e "    ${B0}‣ ${R0}3${E}: Set a list of all built-in function called by ${B0}libft.a"
    echo -e "    ${B0}‣ ${R0}4${E}: Launch at least the tests for the libft (mandatory part)"
    echo -e "    ${B0}‣ ${R0}5${E}: If libft bonus fun. detected, launch the libft bonus part tests"
    echo -e "    ${B0}‣ ${R0}6${E}: If ${G0}ft_print()${E} fun. detected, launch the tests for both its mandatory & bonus part)"
    echo -e "    ${B0}‣ ${R0}7${E}: If ${G0}get_next_line()${E} fun. detected, launch the tests for both its mandatory & bonus part)"
    echo -e "    ${B0}‣ ${R0}8${E}: If any other ${G0}home-made${E} fun. is detected ${RU}AND${E} if a corresponding test is found (matching name), then it will be test too.${BU}(use for personnal function)${E}"
    echo -e "    ${B0}‣ ${R0}9${E}: Display a resume."
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
    print_box_title -t 1 -c ${color} "${boxtitle}"
    while IFS= read -r line; do
        echol -i 0 -c ${color} -t 1 "${line}"
    done < "${tmpfile}"
    print_last -t 1 -c ${color}
    return ${exit_code}
}

# -[ LAUNCH_UNITESTS() ]--------------------------------------------------------------------------------------
# Function that launch unitests for each <function_name> found in <list_name> given as arg1:
# - Take one to two arguments:
#   - arg1 (mandatory): <list_name> that contains all the <function_name> found in object to test.
#   - arg2 (optionnal): <list_name> that contains all the <function_name> that have to be found in object.
launch_unitests()
{
    # check arguments and set lists
    [[ ${#} -eq 0 || ${#} -gt 2 ]] && { echo "${R0}WRONG USAGE OF launch_unitests():wrong number of argument" && exit 2 ; }
    local -a FUN_FOUND=( )     # list of all fun found in object (==arg1)
    local -a FUN_MANDATORY=( ) # list of all fun needed, (set as arg2 if given, else is a copy of arg1)
    eval "local -a FUN_FOUND=( \"\${${1}[@]}\" )"
    [[ -n ${2} ]] && eval "local -a FUN_MANDATORY+=( \"\${${2}[@]}\" )" || eval "local -a FUN_MANDATORY+=( \"\${${1}[@]}\" )"
    [[ ${#FUN_FOUND[@]} -eq 0 ]] && { echo "${R0}WRONG USAGE OF launch_unitests():FUN_FOUND created is an empty list" && exit 2 ; }
    [[ ${#FUN_MANDATORY[@]} -eq 0 ]] && { echo "${R0}WRONG USAGE OF launch_unitests():FUN_MANDATORY created is an empty list" && exit 2 ; }
    # Create file that contains list of function by errors
    local file_fail="${LOG_DIR}/fun_fails.lst"
    local file_leak="${LOG_DIR}/fun_leaks.lst"
    local file_miss="${LOG_DIR}/fun_missing.lst"

    local nb_err=0
    for fun in ${FUN_MANDATORY[@]};do
        echo "🔹${BCU}${fun}():${E}"
        if [[ " ${FUN_FOUND[@]} " =~ " ${fun} " ]];then
            local FUN_LOG_DIR="${LOG_DIR}/${fun}"
            [[ ! -d ${FUN_LOG_DIR} ]] && mkdir -p ${FUN_LOG_DIR}
            local test_main=$(find "${PARENT_DIR}/src" -type f -name *"${fun}.c")
            if [[ -n "${test_main}" ]];then
                # STEP 1 : COMPILATION
                [[ ! -d ${BIN_DIR} ]] && mkdir -p ${BIN_DIR}
                exe="${BIN_DIR}/test_${fun}"
                echo -en " ${BC0} ⤷${E} ⚙️  ${GU}Compilation:${E}"
                if [[ ! -f "${exe}" ]];then
                    local res_compile=$(${CC} ${test_main} ${LIBFT_A} -o ${exe} -lbsd > "${LOG_DIR}/${fun}.compile" 2>&1 && echo ${?} || echo ${?})
                    if [[ "${res_compile}" -eq 0 ]];then
                        echo -en " ✅ ${V0} Successfull.${E}\n"
                        rm "${LOG_DIR}/${fun}.compile"
                    else
                        nb_err=$(( nb_err + 1 ))
                        local log_comp_fail=$(print_shorter_path ${LOG_DIR}/${fun}.compile)
                        echo -en " ❌ ${R0}Compilation failed.${E}\n"
                        sed 's/^/\x1b[0;31m       /' ${log_comp_fail}
                        echo "      🔸${Y0}check log file 👉 ${M0}${log_comp_fail}${E}"
                        continue
                    fi
                else
                    echo -en " ☑️  ${BC0} Not needed.\n${E}"
                fi
                # STEP 2 : EXECUTION
                echo -en " ${BC0} ⤷${E} 🚀 ${GU}Execution  :${E}"
                local test_txt=$(find "${PARENT_DIR}/src" -type f -name *"${fun}.txt")
                if [[ -f "${test_txt}" ]];then
                    local res_tests=$(${exe} "$(dirname "${test_txt}")" "${FUN_LOG_DIR}" > "${FUN_LOG_DIR}/${fun}.log" 2>&1 && echo ${?} || echo ${?})
                else
                    local res_tests=$(${exe} > "${FUN_LOG_DIR}/${fun}.log" 2>&1 && echo ${?} || echo ${?})
                fi
                echo "EXIT_VALUE=${res_tests}" >> "${FUN_LOG_DIR}/${fun}.log"
                if [[ ${res_tests} -eq 0 ]];then
                    echo -en " ✅ ${V0} No error detected.${E}\n"
                else
                    echo "${fun}" >> ${file_fail}
                    echo -en " ❌ ${R0} Error detected (exec return value=${res_tests})\n"
                    echo "      🔸${Y0}check log file 👉 ${M0}$(print_shorter_path ${FUN_LOG_DIR}/${fun}.log)${E}"
                    nb_err=$(( nb_err + 1 ))
                fi
                # STEP 3 : VALGRIND
                echo -en " ${BC0} ⤷${E} 🚰 ${GU}Valgrind   :${E}"
                if [[ -f "${test_txt}" ]];then
                    local res_val=$(${VALGRIND} ${exe} "$(dirname "${test_txt}")" "${FUN_LOG_DIR}" > "${FUN_LOG_DIR}/${fun}.val" 2>&1 && echo ${?} || echo ${?})
                else
                    local res_val=$(${VALGRIND} ${exe} > "${FUN_LOG_DIR}/${fun}.val" 2>&1 && echo ${?} || echo ${?})
                fi
                if [[ ${res_val} -ne ${VAL_ERR} ]];then
                    echo -en " ✅ ${V0} No leak detected.${E}\n"
                else
                    echo "${fun}" >> ${file_leak}
                    echo -en " ❌ ${R0} Leak detected (valgrind return value=${res_val})\n"
                    echo "      🔸${Y0}check log file 👉 ${M0}$(print_shorter_path ${FUN_LOG_DIR}/${fun}.val)${E}"
                    nb_err=$(( nb_err + 1 ))
                fi
            else
                echo " ${BC0} ⤷${E} ✖️  ${G0}Tests not found.${E}"
                rmdir "${FUN_LOG_DIR}" > /dev/null 2>&1
            fi
        else
            echo "${fun}" >> ${file_miss}
            echo " ${BC0} ⤷${E} ❌ ${R0}Function not found in object.${E}"
            nb_err=$(( nb_err + 1 ))
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
    local short_log_dir=$(print_shorter_path ${LOG_DIR})
    local c_com=$(find ${short_log_dir} -type f | grep '.compile$' | wc -l)
    local c_log=$(find ${short_log_dir} -type f | grep '.log$' | wc -l)
    local c_val=$(find ${short_log_dir} -type f | grep '.val$' | wc -l)
    local c_txt=$(find ${short_log_dir} -type f | grep '.txt$' | wc -l)
    local tot_tested=$(( c_com + c_log ))
    local lst_fail=( )
    for ff in $(cat ${LOG_DIR}/fun_fails.lst ${LOG_DIR}/fun_leaks.lst ${LOG_DIR}/fun_missing.lst | sort -u);do lst_fail+=( "${ff}" );done
    [[ ${res_normi} -eq 0 ]] && args+=( "  🔸 ${Y0}Norminette:${V0} ✅ PASS${E}" ) || args+=( "  🔸 ${Y0}Norminette:${R0} ❌ FAIL (${res_normi} wrong files detected)${E}" )
    if [[ ${#lst_fail[@]} -eq 0 ]];then
        args+=( "  🔸 ${Y0}${tot_tested} functions have been tested:${V0} ✅ PASS${E}" ) 
    else
        args+=( "  🔸 ${Y0}${tot_tested} functions have been tested:${E}" )
        if [[ ${c_com} -ne 0 ]];then
            args+=( "     • ${c_com} functions ${R0}FAILLED TO COMPILE${E}." )
            for f2c in $(find ${short_log_dir} -type f | grep '.compile$');do args+=( "      👉 ${f2c}");done
        fi
        args+=( \
            "     • $(( tot_tested - ${#lst_fail[@]} )) functions ${V0}PASSED${E}." \
            "     • ${#lst_fail[@]} functions ${R0}FAILLED${E}:" \
        )
        for ff in ${lst_fail[@]};do args+=( "       👉 ${BC0}${ff}()${E}" );done
    fi

    args+=( \
        "  🔸 ${Y0}Log files created at:${E} ${M0}${short_log_dir}/*${E}" \
        "     • ${c_com} ${M0}compilation log files${E} where created(*.compile ext-->failed compilation commands returns)" \
        "     • ${c_log} ${M0}exec log files${E} where created (*.log ext-->tests returns)" \
        "     • ${c_val} ${M0}valgrind log files${E} where created (*.val ext-->valgrind returns)" \
        "     • ${c_txt} ${M0}outputs files${E} where produced by the tests execution (*.txt ext-->created by test)" \
    )
    print_in_box -t 2 -c y "${args[@]}"
}

# ============================================================================================================
# MAIN
# ============================================================================================================
# =[ CHECK IF LIBFT.A FOUNDED ]===============================================================================
[[ -z ${LIBFT_A} ]] && { script_usage "${R0}Static lib not found: No ${BC0}libft.a${R0} file inside ${M0}${LIBFT_DIR}/${R0} folder.${E}" 2; }
# =[ CREATE LOG_DIR ]=========================================================================================
[[ ! -d ${LOG_DIR} ]] && mkdir -p ${LOG_DIR}
# =[ START MESSAGE ]==========================================================================================
print_in_box -t 2 -c y "🔶 ${Y0}START Libft_Enhanced's Tests${E}"
# =[ CHECK NORMINETTE ]=======================================================================================
exec_anim_in_box "check42_norminette ${LIBFT_DIR}" "Check Norminette"
res_normi=${?}
# =[ SET LISTS ]==============================================================================================
# -[ HOMEMADE AND BUILTIN LISTS ]-----------------------------------------------------------------------------
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
# =[ LAUNCH TEST FOR LIBFT MANDATORY PART ]===================================================================
exec_anim_in_box "launch_unitests HOMEMADE_FUNUSED LIBFT_MANDA" "Tests libft mandatory functions"
# =[ LAUNCH TESTS FOR LIBFT BONUS PART (IT AT LEAST ON BONUS FUNCTION FOUND ]=================================
for fun in ${HOMEMADE_FUNUSED[@]};do
    if [[ ! " ${LIBFT_BONUS[@]} " =~ " ${fun} " ]];then
        exec_anim_in_box "launch_unitests HOMEMADE_FUNUSED LIBFT_BONUS" "Tests libft bonus functions"
        break
    fi
done
# =[ LAUNCH TESTS FOR FT_PRINTF IF FOUND IN LIBFT.A ]=========================================================
#TODO
#exec_anim_in_box "launch_unitests ft_printf ft_printf" "Tests other functions"
# =[ LAUNCH TESTS FOR GET_NEXT_LINE IF FOUND IN LIBFT.A ]=====================================================
#TODO
#exec_anim_in_box "launch_unitests get_next_line get_next_line" "Tests other functions"
## =[ LAUNCH TESTS FOR OTHERS FUNCTION ]=======================================================================
PERSO_FUN=($(printf "%s\n" "${HOMEMADE_FUNUSED[@]}" | grep -vxF -f <(printf "%s\n" "${LIBFT_MANDA[@]}" "${LIBFT_BONUS[@]}" "ft_printf" "get_next_line" )))
exec_anim_in_box "launch_unitests PERSO_FUN" "Tests other functions"
# =[ RESUME ]=================================================================================================
display_resume "Libft's tests"
