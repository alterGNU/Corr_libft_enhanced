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
VALGRIND="valgrind --leak-check=full --track-fds=yes --error-exitcode=1"
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
B0="\033[0;34m"                                                    # ☒ START BLUE
BU="\033[4;34m"                                                    # ☒ START BLUE
BC0="\033[0;36m"                                                   # ☒ START AZURE
BCU="\033[4;36m"                                                   # ☒ START AZURE UNDERSCORED
P0="\033[0;35m"                                                    # ☒ START PINK
G0="\033[0;37m"                                                    # ☒ START GREY
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

# -[ LAUNCH_TEST_LIBFT_MANDATORY() ]--------------------------------------------------------------------------
# Launch test for all mandatory function needed for libft
launch_tests_libft_mandatory()
{
    local LOG_LIBFT_MANDA="${LOG_DIR}/libft_mandatory"
    [[ ! -d ${LOG_LIBFT_MANDA} ]] && mkdir -p ${LOG_LIBFT_MANDA}
    local DOC_LIBFT_MANDA="${LOG_LIBFT_MANDA}/files_generated"
    local nb_err=0
    for fun in ${LIBFT_MANDA[@]};do
        local test_main=$(find "${PARENT_DIR}/src" -type f -name "test_${fun}"*".c")
        echo "🔹${BCU}${fun}():${E}"
        if [[ -n "${test_main}" ]];then
            if [[ " ${HOMEMADE_FUNUSED[@]} " =~ " $fun " ]];then
                [[ ! -d ${BIN_DIR} ]] && mkdir -p ${BIN_DIR}
                exe="${BIN_DIR}/test_${fun}"
                echo -en "  - ⚙️  ${GU}Compilation:${E}"
                if [[ ! -f "${exe}" ]];then
                    local res_compile=$(${CC} ${test_main} ${LIBFT_A} -o ${exe} -lbsd > "${LOG_DIR}/${fun}.compile" 2>&1 && echo $? || echo $?)
                    if [[ "${res_compile}" -eq 0 ]];then
                        echo -en " ✅ ${V0} Successfull.${E}\n"
                    else
                        local log_comp_fail=$(print_shorter_path ${LOG_DIR}/${fun}.compile)
                        echo -en " ❌ ${R0}compilation failed.${E}\n"
                        sed 's/^/\x1b[0;31m       /' ${log_comp_fail}
                        echo "      🔸${Y0}check log file 👉 ${M0}${log_comp_fail}${E}"
                        continue
                    fi
                else
                    echo -en " ☑️  ${BC0} Not needed.\n${E}"
                fi
                if [[ -f "${exe}" ]];then
                    echo -en "  - 🚀 ${GU}Execution  :${E}"
                    if [[ -f "${PARENT_DIR}/src/tests_libft/docs/${fun}.txt" ]];then
                        [[ ! -d ${DOC_LIBFT_MANDA} ]] && mkdir -p ${DOC_LIBFT_MANDA}
                        local res_tests=$(${exe} "${PARENT_DIR}/src/tests_libft/docs" "${DOC_LIBFT_MANDA}" > "${LOG_LIBFT_MANDA}/${fun}.log" 2>&1 && echo $? || echo $?)
                    else
                        local res_tests=$(${exe} > "${LOG_LIBFT_MANDA}/${fun}.log" 2>&1 && echo $? || echo $?)
                    fi
                    nb_err=$((nb_err + res_tests))
                    if [[ ${res_tests} -eq 0 ]];then
                        echo -en " ✅ ${V0} ${res_tests} error(s) detected.${E}\n"
                    else
                        echo -en " ❌ ${R0} ${res_tests} error(s) detected\n"
                        echo "      🔸${Y0}check log file 👉 ${M0}$(print_shorter_path ${LOG_LIBFT_MANDA}/${fun}.log)${E}"
                    fi
                    echo -en "  - 🚰 ${GU}Valgrind   :${E}"
                    if [[ -f "${PARENT_DIR}/src/tests_libft/docs/${fun}.txt" ]];then
                        [[ ! -d ${DOC_LIBFT_MANDA} ]] && mkdir -p ${DOC_LIBFT_MANDA}
                        local res_val=$(${VALGRIND} ${exe} "${PARENT_DIR}/src/tests_libft/docs" "${DOC_LIBFT_MANDA}" > "${LOG_LIBFT_MANDA}/${fun}.val" 2>&1 && echo $? || echo $?)
                    else
                        local res_val=$(${VALGRIND} ${exe} > "${LOG_LIBFT_MANDA}/${fun}.val" 2>&1 && echo $? || echo $?)
                    fi
                    nb_err=$((nb_err + res_val))
                    if [[ ${res_val} -eq 0 ]];then
                        echo -en " ✅ ${V0} ${res_val} leak(s) detected.${E}\n"
                    else
                        echo -en " ❌ ${R0} ${res_val} leak(s) detected\n"
                        echo "      🔸${Y0}check log file 👉 ${M0}$(print_shorter_path ${LOG_LIBFT_MANDA}/${fun}.val)${E}"
                    fi
                else
                    echo "${R0}  - no binary ${B0}${exe}${R0} found${E}"
                fi
            else
                echo "${R0}  - Mandatory libft function ${BC0}${fun}${R0} not found in static lib ${V0}libft.a${E}"
                nb_err=$((nb_err + 1))
            fi
            else
                echo "${R0}  - Tests for ${BC0}${fun}${R0} not found"
            fi
        done
        return ${nb_err}
}

# -[ LAUNCH_TEST_LIBFT_BONUS() ]------------------------------------------------------------------------------
# Launch test for all bonus function needed for libft
launch_tests_libft_bonus()
{
    local LOG_LIBFT_BONUS="${LOG_DIR}/libft_bonus"
    [[ ! -d ${LOG_LIBFT_BONUS} ]] && mkdir -p ${LOG_LIBFT_BONUS}
    local DOC_LIBFT_BONUS="${LOG_LIBFT_BONUS}/files_generated"
    local nb_err=0
    for fun in ${LIBFT_BONUS[@]};do
        local test_main=$(find "${PARENT_DIR}/src" -type f -name "test_${fun}.c")
        echo "🔹${BCU}${fun}():${E}"
        if [[ -n "${test_main}" ]];then
            if [[ " ${HOMEMADE_FUNUSED[@]} " =~ " ${fun} " ]];then
                [[ ! -d ${BIN_DIR} ]] && mkdir -p ${BIN_DIR}
                exe="${BIN_DIR}/test_${fun}"
                echo -en "  - ⚙️  ${GU}Compilation:${E}"
                if [[ ! -f "${exe}" ]];then
                    local res_compile=$(${CC} ${test_main} ${LIBFT_A} -o ${exe} -lbsd > "${LOG_DIR}/${fun}.compile" 2>&1 && echo $? || echo $?)
                    if [[ "${res_compile}" -eq 0 ]];then
                        echo -en " ✅ ${V0} Successfull.${E}\n"
                    else
                        local log_comp_fail=$(print_shorter_path ${LOG_DIR}/${fun}.compile)
                        echo -en " ❌ ${R0}compilation failed.${E}\n"
                        sed 's/^/\x1b[0;31m       /' ${log_comp_fail}
                        echo "      🔸${Y0}check log file 👉 ${M0}${log_comp_fail}${E}"
                        continue
                    fi
                else
                    echo -en " ☑️  ${BC0} Not needed.\n${E}"
                fi
                if [[ -f "${exe}" ]];then
                    echo -en "  - 🚀 ${GU}Execution  :${E}"
                    if [[ -f "${PARENT_DIR}/src/tests_libft/docs/${fun}.txt" ]];then
                        [[ ! -d ${DOC_LIBFT_BONUS} ]] && mkdir -p ${DOC_LIBFT_BONUS}
                        local res_tests=$(${exe} "${PARENT_DIR}/src/tests_libft/docs" "${DOC_LIBFT_BONUS}" > "${LOG_LIBFT_BONUS}/${fun}.log" 2>&1 && echo $? || echo $?)
                    else
                        local res_tests=$(${exe} > "${LOG_LIBFT_BONUS}/${fun}.log" 2>&1 && echo $? || echo $?)
                    fi
                    nb_err=$((nb_err + res_tests))
                    if [[ ${res_tests} -eq 0 ]];then
                        echo -en " ✅ ${V0} ${res_tests} error(s) detected.${E}\n"
                    else
                        echo -en " ❌${R0} ${res_tests} error(s) detected\n"
                        echo "      🔸${Y0}check log file 👉 ${M0}$(print_shorter_path ${LOG_LIBFT_BONUS}/${fun}.log)${E}"
                    fi
                    echo -en "  - 🚰 ${GU}Valgrind   :${E}"
                    if [[ -f "${PARENT_DIR}/src/tests_libft/docs/${fun}.txt" ]];then
                        [[ ! -d ${DOC_LIBFT_BONUS} ]] && mkdir -p ${DOC_LIBFT_BONUS}
                        local res_val=$(${VALGRIND} ${exe} "${PARENT_DIR}/src/tests_libft/docs" "${DOC_LIBFT_BONUS}" > "${LOG_LIBFT_BONUS}/${fun}.val" 2>&1 && echo $? || echo $?)
                    else
                        local res_val=$(${VALGRIND} ${exe} > "${LOG_LIBFT_BONUS}/${fun}.val" 2>&1 && echo $? || echo $?)
                    fi
                    nb_err=$((nb_err + res_val))
                    if [[ ${res_tests} -eq 0 ]];then
                        echo -en " ✅ ${V0} ${res_val} leak(s) detected.${E}\n"
                    else
                        echo -en " ❌ ${R0} ${res_val} leak(s) detected\n"
                        echo "      🔸${Y0}check log file 👉 ${M0}$(print_shorter_path ${LOG_LIBFT_BONUS}/${fun}.val)${E}"
                    fi
                else
                    echo "${R0}  - no binary ${B0}${exe}${R0} found${E}"
                fi
            else
                echo "${R0}  - Bonus libft function ${BC0}${fun}${R0} not found in static lib ${V0}libft.a${E}"
                nb_err=$((nb_err + 1))
            fi
            else
                echo "${R0}  - Tests for ${BC0}${fun}${R0} not found"
            fi
        done
        return ${nb_err}
}

# -[ LAUNCH_TESTS_PERSO_FUN() ]-------------------------------------------------------------------------------
# Launch tests for all my personnal functions
launch_tests_perso_fun()
{
    local LOG_PERSO_FUN="${LOG_DIR}/other_functions"
    [[ ! -d ${LOG_PERSO_FUN} ]] && mkdir -p ${LOG_PERSO_FUN}
    local DOC_PERSO_FUN="${LOG_PERSO_FUN}/files_generated"
    local nb_err=0
    for fun in ${PERSO_FUN[@]};do
        local test_main=$(find "${PARENT_DIR}/src" -type f -name "test_${fun}.c")
        echo "🔹${BCU}${fun}():${E}"
        if [[ -n "${test_main}" ]];then
            [[ ! -d ${BIN_DIR} ]] && mkdir -p ${BIN_DIR}
            exe="${BIN_DIR}/test_${fun}"
            echo -en "  - ⚙️  ${GU}Compilation:${E}"
            if [[ ! -f "${exe}" ]];then
                local res_compile=$(${CC} ${test_main} ${LIBFT_A} -o ${exe} -lbsd > "${LOG_DIR}/${fun}.compile" 2>&1 && echo $? || echo $?)
                if [[ "${res_compile}" -eq 0 ]];then
                    echo -en " ✅ ${V0} Successfull.${E}\n"
                else
                    local log_comp_fail=$(print_shorter_path ${LOG_DIR}/${fun}.compile)
                    echo -en " ❌ ${R0}compilation failed.${E}\n"
                    sed 's/^/\x1b[0;31m       /' ${log_comp_fail}
                    echo "      🔸${Y0}check log file 👉 ${M0}${log_comp_fail}${E}"
                    continue
                fi
            else
                echo -en " ☑️  ${BC0} Not needed.\n${E}"
            fi
            if [[ -f "${exe}" ]];then
                echo -en "  - 🚀 ${GU}Execution  :${E}"
                if [[ -f "${PARENT_DIR}/src/tests_libft/docs/${fun}.txt" ]];then
                    [[ ! -d ${DOC_PERSO_FUN} ]] && mkdir -p ${DOC_PERSO_FUN}
                    local res_tests=$(${exe} "${PARENT_DIR}/src/tests_libft/docs" "${DOC_PERSO_FUN}" > "${LOG_PERSO_FUN}/${fun}.log" 2>&1 && echo $? || echo $?)
                else
                    local res_tests=$(${exe} > "${LOG_PERSO_FUN}/${fun}.log" 2>&1 && echo $? || echo $?)
                fi
                nb_err=$((nb_err + res_tests))
                if [[ ${res_tests} -eq 0 ]];then
                    echo -en " ✅ ${V0} ${res_tests} error(s) detected.${E}\n"
                else
                    echo -en " ❌${R0} ${res_tests} error(s) detected\n"
                    echo "      🔸${Y0}check log file 👉 ${M0}$(print_shorter_path ${LOG_PERSO_FUN}/${fun}.log)${E}"
                fi
                echo -en "  - 🚰 ${GU}Valgrind   :${E}"
                if [[ -f "${PARENT_DIR}/src/tests_libft/docs/${fun}.txt" ]];then
                    [[ ! -d ${DOC_PERSO_FUN} ]] && mkdir -p ${DOC_PERSO_FUN}
                    local res_val=$(${VALGRIND} ${exe} "${PARENT_DIR}/src/tests_libft/docs" "${DOC_PERSO_FUN}" > "${LOG_PERSO_FUN}/${fun}.val" 2>&1 && echo $? || echo $?)
                else
                    local res_val=$(${VALGRIND} ${exe} > "${LOG_PERSO_FUN}/${fun}.val" 2>&1 && echo $? || echo $?)
                fi
                nb_err=$((nb_err + res_val))
                if [[ ${res_tests} -eq 0 ]];then
                    echo -en " ✅ ${V0} ${res_val} leak(s) detected.${E}\n"
                else
                    echo -en " ❌ ${R0} ${res_val} leak(s) detected\n"
                    echo "      🔸${Y0}check log file 👉 ${M0}$(print_shorter_path ${LOG_PERSO_FUN}/${fun}.val)${E}"
                fi
            else
                echo "${R0}  - no binary ${B0}${exe}${R0} found${E}"
            fi
        else
            echo "${M0}  - No tests founded."
        fi
    done
    return ${nb_err}
}

# ============================================================================================================
# MAIN
# ============================================================================================================
# =[ CHECK IF LIBFT.A FOUNDED ]===============================================================================
[[ -z ${LIBFT_A} ]] && { script_usage "${R0}Static lib not found: No ${BC0}libft.a${R0} file inside ${M0}${LIBFT_DIR}/${R0} folder.${E}" 2; }
# =[ CREATE LOG_DIR ]=========================================================================================
[[ ! -d ${LOG_DIR} ]] && mkdir -p ${LOG_DIR}
# =[ START MESSAGE ]==========================================================================================
print_in_box -t 2 -c y "🚧${Y0} START Libft_Enhanced's Tests${E}"
# =[ CHECK NORMINETTE ]=======================================================================================
exec_anim_in_box "check42_norminette ${LIBFT_DIR}" "Check Norminette"
# =[ LST_FUNUSED ]============================================================================================
# -[ SET LISTS HOMEMADE_FUNUSED BUILTIN_FUNUSED ]-------------------------------------------------------------
if file "${LIBFT_A}" | grep -qE 'relocatable|executable|shared object|ar archive';then
    for fun in $(nm -C "${LIBFT_A}" | awk '$2 == "T" {print $3}' | sort | uniq);do
        [[ ! " ${HOMEMADE_FUNUSED[@]} " =~ " $fun " ]] && HOMEMADE_FUNUSED+=( "${fun}" )
    done
    for fun in $(nm -C "${LIBFT_A}" | awk '$2 == "U" {print $3}' | sort | uniq);do
        if [[ ! " ${HOMEMADE_FUNUSED[@]} " =~ " $fun " ]];then
            [[ ! " ${BUILTIN_FUNUSED[@]} " =~ " $fun " ]] && BUILTIN_FUNUSED+=( "${fun}" )
        fi
    done
else
    echo -e "${BC0}${LIBFT_A}${E} is not an object file\033[m"
fi
# -[ LAUNCH_TESTS_LIBFT_MANDATODY() ]-------------------------------------------------------------------------
exec_anim_in_box "launch_tests_libft_mandatory" "Tests libft mandatory functions"
last_return=${?}
TOT_FAILS=$(( TOT_FAILS + last_return ))
# -[ LAUNCH_TESTS_LIBFT_BONUS() ]-----------------------------------------------------------------------------
for fun in ${HOMEMADE_FUNUSED[@]};do
    if [[ ! " ${LIBFT_BONUS[@]} " =~ " ${fun} " ]];then
        TOT_TESTS=$(( TOT_TESTS + ${#LIBFT_BONUS[@]} ))
        exec_anim_in_box "launch_tests_libft_bonus" "Tests libft bonus functions"
        last_return=${?}
        TOT_FAILS=$(( TOT_FAILS + last_return ))
        break
    fi
done
# -[ PERSONNAL FUNCTION ]-------------------------------------------------------------------------------------
EXTRA=( "ft_printf" "get_next_line" )
PERSO_FUN=($(printf "%s\n" "${HOMEMADE_FUNUSED[@]}" | grep -vxF -f <(printf "%s\n" "${LIBFT_MANDA[@]}" "${LIBFT_BONUS[@]}" "${EXTRA[@]}")))
for fun in "${PERSO_FUN[@]}";do [[ -n "$(find "${PARENT_DIR}/src" -type f -name "test_${fun}.c")" ]] && TOT_TESTS=$(( TOT_TESTS + 1 ));done
exec_anim_in_box "launch_tests_perso_fun" "Tests personnal functions"
last_return=${?}
TOT_FAILS=$(( TOT_FAILS + last_return ))
# =[ RESUME ]=================================================================================================
short_log_dir=$(print_shorter_path ${LOG_DIR})
print_in_box -t 2 -c y \
    "🚧${Y0} RESUME Libft_Enhanced's Tests${E}" \
    "   - 🚀 ${GU}${TOT_TESTS} functions were tested:${E}" \
    "      - ✅ $(( TOT_TESTS - TOT_FAILS)) functions ${V0}PASSED${E} there tests." \
    "      - ❌ ${TOT_FAILS} functions ${R0}FAILLED${E} there tests:" \
    "   - 📂 ${GU}Log files created at:${E} ${M0}${short_log_dir}/*${E}" \
    "      - $(find ${short_log_dir} -type f | grep '.log$' | wc -l) exec log files where created." \
    "      - $(find ${short_log_dir} -type f | grep '.val$' | wc -l) valgrind log files where created." \
    "      - $(find ${short_log_dir} -type f | grep '.txt$' | wc -l) outputs files where produce by test."
