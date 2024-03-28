#/bin/sh

echo "Starting tester"
make fclean
make
git clone https://github.com/LucasKuhn/minishell_tester.git
cd minishell_tester && ./tester builtins
