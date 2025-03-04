# Corr_libft_enhanced

Personnal corrector for **libft** project.

Use `nm` command to list all fun. of libft.a, then, when a test file exist, test this function.
- check libft mandatory and bonus part
- if added to libft.a, check `ft_printf()` mandatory and bonus part
- if added to libft.a, check `get_next_line()` mandatoy and bonus part

## Pre-requise
- `nm` command install.
- need to be clone inside the **path/libft/** folder to be tested.
- `path/libft/**/libft.a` should have been compiled before launching `./launch_tests.sh`

## Use
- 1: `git clone --recurse-submodules -j8 https://github.com/alterGNU/Corr_libft_enhanced.git`
    - Need to be cloned inside **libft** using `--recurse-submodules` since it as submodules
- 2: **create your libft.a** using its own Makefile.
- 3: `./launch_tests.sh` to launch all tests.

## Details
- This project use my **BashScriptLib** repo as submodule (like a libft in bash).

- STEPS:
    - 1: Check if ${M0}libft/${E} complies with the 42-norme"
    - 2: Display a list of all function found in the ${B0}libft.a${E} static lib"
    - 3: Display a list of all built-in function called by ${B0}libft.a"
    - 4: Launch at least the tests for the libft (mandatory part)"
    - 5: If libft bonus fun. detected, launch the libft bonus part tests"
    - 6: If ${G0}ft_print()${E} fun. detected, launch the tests for both its mandatory & bonus part)"
    - 7: If ${G0}get_next_line()${E} fun. detected, launch the tests for both its mandatory & bonus part)"
    - 8: If any other ${G0}home-made${E} fun. is detected ${RU}AND${E} if a corresponding test is found (matching name), then it will be test too.${BU}(use for personnal function)${E}"
    - 9: Display a resume.

- Everytime `./launch_tests` is run, a log folder is created in `./log/<date>/<time>/` with all the tests outputs.
