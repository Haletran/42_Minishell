#/bin/sh

echo "Starting tester"
git clone https://github.com/LucasKuhn/minishell_tester.git
cd minishell_tester && ./tester builtins
