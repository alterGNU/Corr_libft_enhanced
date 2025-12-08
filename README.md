# Corr_libft_enhanced

Corrector for the static library **libft.a** where `get_next_line()`, `ft_printf()`, and other personal functions have been added.

This corrector uses and runs [@Tripouille](https://github.com/Tripouille)'s testers for libft, get_next_line, and ft_printf functions, covering both mandatory and bonus parts.

I have also written my own tests, grouped under and referred to as **my_unitests**, which, unlike Tripouille's testers, can test 42's project functions as listed above, but also any personal function added to libft.a as long as its unit tests are added to the `src/my_unitests/` folder. (Any sub-folder works since the `find` command is used).

## Prerequisites
- The `find`, `nm`, `clang`, `cc`, `norminette`, and `valgrind` commands are required.
- The corrector must be cloned:
    - inside the **path/libft/** folder of the project to be tested.
    - with the git option `--recurse-submodules` since submodules are used.
- `path/libft/**/libft.a` must be compiled before running `./launch_tests.sh`

## Usage
- 1: **Clone the repository:**
    ```c
    git clone --recurse-submodules -j8 https://github.com/alterGNU/Corr_libft_enhanced.git
    ```
    - ⚠️ Must be cloned inside libft.
    - ⚠️ The `--recurse-submodules` option is required due to submodules.
- 2: **Compile `libft.a`** using its own Makefile: `make`
- 3: **Run the tests** (see below for available arguments):
    ```bash
    ./launch_tests.sh <ARGS>
    ```
- 4: If **my_unitests** is run, you can check its log files:
    - Log folder is created at `./log/<date>/<time>/` with all test outputs sorted by function name:
        - `./log/<date>/<time>/list_errors.log` → List of all encountered errors with format `<fun_name>\t<error_type>`
        - `./log/<date>/<time>/<fun_name>/comp_stderr.txt` → Created only when compilation failed
        - `./log/<date>/<time>/<fun_name>/exec.log` → Execution outputs (stdout && stderr)
        - `./log/<date>/<time>/<fun_name>/leaks.log` → Valgrind outputs (stdout && stderr)

## Available Script Arguments
- ⚠️ Arguments use a specific syntax: `+` is used to **ENABLE** an option, while `-` is used to **DISABLE** (except for `h` option where `-h` also enables help)
    - `+n`: Enable **Norminette_checker** option → script will launch my_unitests tests
    - `-n`: Disable **Norminette_checker** option → script will NOT launch my_unitests tests

| Argument                        | Description                                                                                                 |
| ------------------------------- | ----------------------------------------------------------------------------------------------------------- |
| (none)                          | **Default Settings**: Norminette_Checker+Forbidden_fun_checker+My_unitests+Other functions                  |
| `+a`/`-a`                       | Enable/Disable **all options**                                                                              |
| `+bi`/`-bi`                     | Enable/Disable **builtin-checker** step (checks for no forbidden functions used)                            |
| `+bo`/`-bo`                     | Enable/Disable **bonus part** (enables libft, gnl, and ft_printf bonus part checker)                        |
| `+c`                            | Enable **forced compilation** (force recompilation of unit tests even if binary exists in bin folder)       |
| `+g`/`-g`                       | Enable/Disable all testers for the **get_next_line** function (tripouille and my_unitests)                 |
| `+h` or `-h`                    | **Display help** (print script's usage)                                                                     |
| `+l`/`-l`                       | Enable/Disable all testers for **libft's functions** (tripouille and my_unitests)                           |
| `+n`/`-n`                       | Enable/Disable the **norminette-checker** (display a colored tree of folder structure)                      |
| `+o`/`-o`                       | Enable/Disable **my other unitests** (unit tests for functions not required by libft project)               |
| `+p`/`-p`                       | Enable/Disable all testers for the **ft_printf** function (tripouille and my_unitests)                      |
| `+t`/`-t`                       | Enable/Disable **tripouille** tester                                                                        |

## Script Main Steps
- **STEP 0:** Display enabled options and functions present in libft.a (home-made and built-in).
- **STEP 1:** Forbidden-function-check.
- **STEP 2:** Norminette-check.
- **STEP 3:** Run Tripouille tests (libft, printf, gnl, with bonus support).
- **STEP 4:** Run my_unitests tests (libft, printf, gnl, and other personal functions with matching tests).

## Example Option Combinations

### `./launch_tests.sh -h`
- **Display script usage (like man page)**

### `./launch_tests.sh` (DEFAULT BEHAVIOR)
- **STEP 0:** Display enabled options and functions present in libft.a (home-made and built-in).
- **STEP 1:** Forbidden-function-check
- **STEP 2:** Norminette-check
- ~~**STEP 3:** Run Tripouille tests~~
- **STEP 4:** Run my_unitests tests
    - If any libft bonus function is detected in libft.a, run **my_unitests libft bonus part** tests.
    - If `get_next_line()` is detected in libft.a, run **my_unitests get_next_line mandatory part** tests.
    - If `ft_printf()` is detected in libft.a, run **my_unitests ft_printf mandatory part** tests.

### `./launch_tests.sh -a +t +bo`
- **STEP 0:** Display enabled options and functions present in libft.a (home-made and built-in).
- ~~**STEP 1:** Forbidden-function-check~~
- ~~**STEP 2:** Norminette-check~~
- **STEP 3:** Run Tripouille tests with bonus
- ~~**STEP 4:** Run my_unitests tests~~

## Integration in libft's Makefile
- To call this tester from the libft `make` command, add two rules to libft's Makefile:
    - First rule to git clone this repo:
        ```Makefile
        clone_test_repo:
            if [ ! -d My_tester ]; then git clone --recurse-submodules -j8 https://github.com/alterGNU/Corr_libft_enhanced.git My_tester; fi
        ```
    - Second rule to launch this script with `$OPT` as its arguments:
        ```Makefile
        test: libft.a | clone_test_repo
        	@echo "$(GREEN)🔘 $(TITLE)make test$(END)"
        	@My_tester/launch_tests.sh $(OPT)
        ```
    - Of course, if you want your `make fclean` rule to remove this folder add to fclean rule:
        ```Makefile
        fclean:
            rm -rf My_tester
        ```

- Now, this tester can be cloned and launched from libft:
    - **Examples (inside libft folder):**
        - `$> make test` → run `./launch_tests.sh` without options (default behavior)
        - `$> make test OPT="-a +n"` → run `./launch_tests.sh -a +n` (only norminette_checker step)
    - **Example (outside libft folder):**
        - `$> make -C path/libft test OPT="-a +bi"` → run `./launch_tests.sh -a +bi` (only forbidden_fun_checker step)