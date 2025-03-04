# Corr_libft_enhanced

Personnal corrector for **libft** project.

Use `nm` command to list all fun. of libft.a, then, when a test file exist, test this function.
- check libft mandatory and bonus part
- if added to libft.a, check `ft_printf()` mandatory and bonus part
- if added to libft.a, check `get_next_line()` mandatoy and bonus part

## Pre-requise
- `nm` command install.
- `libft.a` should have been compiled before launching `make -C Corr_libft_enhanced`

## Use
- 1: `git clone --recurse-submodules -j8 https://github.com/alterGNU/Corr_libft_enhanced.git`
    - Need to be cloned inside **libft** using `--recurse-submodules` since it as submodules
- 2: **create your libft.a**
- 3: `make -C Corr_libft_enhanced` to launch all tests.

## Details
- This project use my **BashScriptLib** repo as submodule (like a libft in bash).

- STEPS:
    - 1: check norminette (since tests do not respect the 42-norm, will exclude the Corr_libft_enhanced folder)
    - 2: list all **built-in** function founded in libft.a
    - 3: list all **home-made** function founded in libft.a
    - 4: for all **home-made** function found in libft.a, search if a test exist, then launch it.
    - 5: display resume

- For each instance of test, a folder is created where all log-file are stored.
