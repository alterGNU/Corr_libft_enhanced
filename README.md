# Corr_libft_enhanced

Corrector for the static library **libft.a** where get_next_line(), ft_printf() and other personnal functions has been added.

This corrector uses and runs [@Tripouille](https://github.com/Tripouille)'s testers for libft, get_next_line and ft_printf functions, covering both mandatory and bonus parts.

I have also written my own tests, grouped under and refers as **my_unitests**, which unlike tripouille's testers can test 42's project functions as list before, but also any personnal function add to the libft.a as long as its unitest is add to `src/my_unitests/` folder. (any sub-folder works as `find` cmd is used).

## Pre-requise
- The `nm` command must be install.
- The corrector must be cloned :
    - inside the **path/libft/** folder of the project to be tested.
    - with the git option   `--recurse-submodules` since submodules are used.
- `path/libft/**/libft.a` must be compiled before running `./launch_tests.sh`

## Usage
- 1: **Clone the repository:**
    ```c
    git clone --recurse-submodules -j8 https://github.com/alterGNU/Corr_libft_enhanced.git
    ```
    - ⚠️  Must be cloned inside libft.
    - ⚠️  The `--recurse-submodules` option is requires due to submodules.
- 2: **Compile `libft.a`** using its own Makefile: `make`
- 3: **Run the tests** (cf. below for <ARGS> values):
    ```c
    ./launch_tests.sh <ARGS>
    ```
- 4: If **My_unitests** is run, you can check its log files:
    - log folder is created at `./log/<date>/<time>/` with all the tests outputs sort by function's name:
        - `./log/<date>/<time>/list_errors.log`            --> File contains list of all encountred errors, format="<fun_name>\t<error_type>"
        - `./log/<date>/<time>/<fun_name>/comp_stderr.txt` --> File created only when compilation failed
        - `./log/<date>/<time>/<fun_name>/exec.log`        --> File contains execution's outputs (stdout && stderr)
        - `./log/<date>/<time>/<fun_name>/leaks.log`       --> File contains valgrind's outputs (stdout && stderr)

## Script arguments availlable:
| Argument                        | Description                                                                                        |
| (none)                          | Enables all My_unitests tests for libft, gnl, printf and other functions                           |
| `-h`, `--help`                  | Displays help and script usage                                                                     |
| `-n`, `--no-norm`               | Desable the norminette-checker step                                                                |
| `-b`, `--bonus`                 | Enable Bonus tests for any activated testers                                                       |
| `-a`, `--all`                   | Enable all testers (tripouille and my_unitests)                                                    |
| `-t`, `--tripouille`            | Enable ONLY tripouille tester (disable my_unitests)                                                |
| `-l`, `--libft`, `-lft`         | Enable all testers for the libft's functions (tripouille and my_unitests)                          |
| `-f`, `--ft_printf`             | Enable all testers tester for the ft_printf function (tripouille and my_unitests)                  |
| `-g`, `--get_next_line`, `-gnl` | Enable all testers tester for the get_next_line function (tripouille and my_unitests)              |
| `-o`, `--other`                 | Enable ONLY My_unitest tester for others functions found (anything but a libft+gnl+ft_printf fun.) |
 
## MAIN PSEUDO-CODE:
- **STEP 0. :** Display enabled options and functions present in libft.a (home-made and built-in).
- **STEP 1. :** Norminette-check (if enabled).
- **STEP 2. :** Run Tripouille tests (libft, printf, gnl, with bonus support if enabled).
- **STEP 3. :** Run My_unitests tests (libft, printf, gnl, other personal functions with matching tests).

## Examples:
- `./launch_tests.sh` : (DEFAULT BEHAVIOR)
    - **STEP 0.:** Display enabled options and functions present in libft.a (home-made and built-in).
    - **STEP 1.:** Run **norminette-checker**
    - **~~STEP 2.~~: Tripouille testert NOT ENABLE**
    - **STEP 3.:** Run **My_unitest libft mandatory part** unitests.
        - If any libft bonus part function is detected in libft.a, run **My_unitest libft bonus part** unitests.
        - If get_next_line() function detected in libft.a, run **My_unitest get_next_line mandatory part** unitests.
        - If ft_printf() function detected in libft.a, run **My_unitest ft_printf mandatory part** unitests.
- `./launch_tests.sh -v` : 
    - **Display script usage (~man)**
    - **~~STEP 0.~~: Desable**
    - **~~STEP 1.~~: Desable
    - **~~STEP 2.~~: Not enable**
    - **~~STEP 3.~~: Desable
- `./launch_tests.sh -n -t -b` :
    - **STEP 0.:** Display enabled options and functions present in libft.a (home-made and built-in).
    - **~~STEP 1.:~~ Desable norminette-checker** step.
    - **STEP 2.: Enable All Tripouille tester with bonus part**
        - Run **Tripouille libft mandatory AND bonus parts**
        - If ft_printf() found in static library, Run **Tripouille ft_printf mandatory and bonus part**
        - If get_next_line() found in static library, Run **Tripouille get_next_line mandatory and bonus part**
    - **~~STEP 3.:~~ Desable My-unitests** testers.
- `./launch_tests.sh -a -b` :
    - **STEP 0.:** Display enabled options and functions present in libft.a (home-made and built-in).
    - **STEP 1.:** Run **norminette-checker**
    - **STEP 2.:** Enable All  **Tripouille tester with bonus part**
        - Run **Tripouille libft mandatory AND bonus parts**
        - If ft_printf() found in static library, Run **Tripouille ft_printf mandatory and bonus part**
        - If get_next_line() found in static library, Run **Tripouille get_next_line mandatory and bonus part**
    - **STEP 3.:** Enable All  **My_unitests tester with bonus part**
        - Run **My_unitests libft mandatory AND bonus parts**
        - If ft_printf() found in static library, Run **My_unitest ft_printf mandatory and bonus part**
        - If get_next_line() found in static library, Run **My_unitest get_next_line mandatory and bonus part**
