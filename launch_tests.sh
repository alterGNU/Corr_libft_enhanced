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
# -[ LAYOUT ]-------------------------------------------------------------------------------------------------
LEN=100                                                    # ☑ Width of the box
# -[ COLORS ]-------------------------------------------------------------------------------------------------
E="\033[0m"                                # ☒ END color balise
N0="\033[0;30m"                            # ☒ START BLACK
R0="\033[0;31m"                            # ☒ START RED
RU="\033[4;31m"                            # ☒ START RED UNDERSCORED
V0="\033[0;32m"                            # ☒ START GREEN
M0="\033[0;33m"                            # ☒ START BROWN
Y0="\033[0;93m"                            # ☒ START YELLOW
B0="\033[0;34m"                            # ☒ START BLUE
BU="\033[4;34m"                            # ☒ START BLUE
BC0="\033[0;36m"                           # ☒ START AZURE
P0="\033[0;35m"                            # ☒ START PINK
G0="\033[0;37m"                            # ☒ START GREY
GU="\033[4;37m"                            # ☒ START GREY
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

# ============================================================================================================
# MAIN
# ============================================================================================================
echo "SCRIPTNAME=${SCRIPTNAME}"
echo "PARENT_DIR=${PARENT_DIR}"
echo "LIBFT_DIR=${LIBFT_DIR}"
echo "LOG_DIR=${LOG_DIR}"
echo "BSL_DIR=${BSL_DIR}"
check42_norminette ${PARENT_DIR}
# =[ CHECK IF LIBFT.A FOUNDED ]===============================================================================
LIBFT_A=$(find ${LIBFT_DIR} -type f -name "libft.a")
echo "LIBFT_A=${LIBFT_A}"
[[ -z ${LIBFT_A} ]] && { script_usage "${R0}Static lib not found: No ${B0}libft.a${R0} file inside ${M0}${LIBFT_DIR}/${R0} folder.${E}" 2; }
# =[ CREATE LOG_DIR ]=========================================================================================
[[ ! -d ${LOG_DIR} ]] && mkdir -p ${LOG_DIR}
