#!/bin/bash

# Minishell Comprehensive Test Script (Without Exit Tests)
# Run this script from within your minishell with:
# source minishell_no_exit_tests.sh

# Colors
GREEN="\033[0;32m"
RED="\033[0;31m"
YELLOW="\033[0;33m"
BLUE="\033[0;34m"
PURPLE="\033[0;35m"
RESET="\033[0m"

# Test counter
TEST_COUNT=0
PASSED_COUNT=0
FAILED_COUNT=0

# Store the starting directory - this is crucial for tests that use cd
STARTING_DIR="$PWD"

# Create a test directory with an absolute path
TEST_DIR="$STARTING_DIR/minishell_test_dir"

# Ensure we're in the starting directory
cd "$STARTING_DIR"

# Setup test environment
setup_test_environment() {
    # Clean up any existing test directory
    rm -rf "$TEST_DIR"

    # Create test directory and files
    mkdir -p "$TEST_DIR"
    mkdir -p "$TEST_DIR/subdir"

    echo "Hello World" > "$TEST_DIR/file1.txt"
    echo "Testing" > "$TEST_DIR/file2.txt"
    echo "Content with spaces" > "$TEST_DIR/file_with_spaces.txt"
    echo "Line 1
Line 2
Line 3" > "$TEST_DIR/multiline.txt"

    echo "#!/bin/bash
echo \"Script executed with args: \$@\"
exit \${1:-0}" > "$TEST_DIR/test_script.sh"
    chmod +x "$TEST_DIR/test_script.sh"

    echo "Subdirectory file" > "$TEST_DIR/subdir/file.txt"

    # Create some read-only files and directories for permission tests
    mkdir -p "$TEST_DIR/readonly"
    echo "Read-only content" > "$TEST_DIR/readonly/file.txt"
    chmod 777 "$TEST_DIR/readonly"

    # Create empty files for specific tests
    touch "$TEST_DIR/empty_file"
    touch "$TEST_DIR/.hidden_file"
}

# Function to run a test
run_test() {
    TEST_NAME="$1"
    COMMAND="$2"
    EXPECTED_EXIT="$3"

    # Ensure we're in the starting directory before each test
    cd "$STARTING_DIR"

    TEST_COUNT=$((TEST_COUNT + 1))
    echo -e "${YELLOW}Test #$TEST_COUNT: $TEST_NAME${RESET}"
    echo -e "Command: ${BLUE}$COMMAND${RESET}"

    # Create a temp file for output and errors
    OUTPUT_FILE="$TEST_DIR/test_output_$TEST_COUNT.txt"
    ERROR_FILE="$TEST_DIR/test_error_$TEST_COUNT.txt"

    # Run the command and capture its output
    eval "$COMMAND" > "$OUTPUT_FILE" 2> "$ERROR_FILE"
    ACTUAL_EXIT=$?

    # Ensure we return to starting directory after the test
    cd "$STARTING_DIR"

    # Check if exit code matches expected
    if [ "$ACTUAL_EXIT" = "$EXPECTED_EXIT" ]; then
        echo -e "${GREEN}✓ PASSED${RESET} (Exit code: $ACTUAL_EXIT)"
        PASSED_COUNT=$((PASSED_COUNT + 1))
    else
        echo -e "${RED}✗ FAILED${RESET} (Expected exit code: $EXPECTED_EXIT, Got: $ACTUAL_EXIT)"
        FAILED_COUNT=$((FAILED_COUNT + 1))
    fi

    # Show command output
    echo -e "${BLUE}Command output:${RESET}"
    if [ -f "$OUTPUT_FILE" ]; then
        cat "$OUTPUT_FILE"
    else
        echo -e "${RED}[Output file not found]${RESET}"
    fi

    if [ -f "$ERROR_FILE" ] && [ -s "$ERROR_FILE" ]; then
        echo -e "${RED}Error output:${RESET}"
        cat "$ERROR_FILE"
    fi

    echo -e "------------------------------------------------"
}

# Setup the test environment
echo -e "${BLUE}Setting up test environment...${RESET}"
setup_test_environment

echo -e "${YELLOW}====== Basic Command Tests ======${RESET}"

# Test 1: Simple command
run_test "Simple command" "echo Hello World" 0

# Test 2: Command with options
run_test "Command with options" "echo -n Hello" 0

# Test 3: Command with path
run_test "Command with path" "ls -la \"$TEST_DIR\"" 0

# Test 4: Command not found
run_test "Command not found" "notacommand" 127

echo -e "${YELLOW}====== Built-in Command Tests ======${RESET}"

# Test 5: pwd command
run_test "pwd command" "pwd" 0

# Test 6: cd command with return to original directory
run_test "cd command" "OLDDIR=\"$PWD\" && cd \"$TEST_DIR\" && pwd && cd \"\$OLDDIR\" && pwd" 0

# Test 7: Export command
run_test "Export command" "export TEST_VAR=value && echo \$TEST_VAR" 0

# Test 8: Unset command
run_test "Unset command" "export TEST_VAR=value && echo \$TEST_VAR && unset TEST_VAR && echo \$TEST_VAR" 0

# Test 9: env command
run_test "env command" "env | grep PATH" 0

# Note: Exit command tests are removed as they would exit the shell

echo -e "${YELLOW}====== Redirection Tests ======${RESET}"

# Test 10: Output redirection
run_test "Output redirection" "echo Hello > \"$TEST_DIR/out.txt\" && cat \"$TEST_DIR/out.txt\"" 0

# Test 11: Output redirection (append)
run_test "Output append" "echo Hello > \"$TEST_DIR/append.txt\" && echo World >> \"$TEST_DIR/append.txt\" && cat \"$TEST_DIR/append.txt\"" 0

# Test 12: Input redirection
run_test "Input redirection" "cat < \"$TEST_DIR/file1.txt\"" 0

# Test 13: Input redirection from nonexistent file
run_test "Input from nonexistent file" "cat < \"$TEST_DIR/nonexistent.txt\"" 1

# Test 14: Multiple redirections
run_test "Multiple redirections" "cat < \"$TEST_DIR/file1.txt\" > \"$TEST_DIR/copy.txt\" && cat \"$TEST_DIR/copy.txt\"" 0

# Test 15: Here document
run_test "Here document" "cat << EOF
This is a heredoc test
with multiple lines
EOF" 0

echo -e "${YELLOW}====== Pipe Tests ======${RESET}"

# Test 16: Simple pipe
run_test "Simple pipe" "echo Hello World | grep Hello" 0

# Test 17: Multiple pipes
run_test "Multiple pipes" "echo Hello World | grep Hello | wc -c" 0

# Test 18: Pipe with redirections
run_test "Pipe with redirections" "echo Hello | grep Hello > \"$TEST_DIR/piped.txt\" && cat \"$TEST_DIR/piped.txt\"" 0

# Test 19: Pipe with command not found
run_test "Pipe with command not found" "echo test | notacommand" 127

echo -e "${YELLOW}====== Logical Operator Tests ======${RESET}"

# Test 20: AND operator (true case)
run_test "AND operator (true case)" "true && echo Success" 0

# Test 21: AND operator (false case)
run_test "AND operator (false case)" "false && echo 'Should not print'" 1

# Test 22: OR operator (true case)
run_test "OR operator (true case)" "true || echo 'Should not print'" 0

# Test 23: OR operator (false case)
run_test "OR operator (false case)" "false || echo Fallback" 0

# Test 24: Multiple operators
run_test "Multiple operators" "false && echo One || echo Two" 0

# Test 25: Operator precedence
run_test "Operator precedence" "true || echo One && echo Two" 0

echo -e "${YELLOW}====== Variable Tests ======${RESET}"

# Test 26: Simple variable
run_test "Simple variable" "TEST_VAR=Hello && echo \$TEST_VAR" 0

# Test 27: Variable with spaces
run_test "Variable with spaces" "TEST_VAR=\"Hello World\" && echo \$TEST_VAR" 0

# Test 28: Variable inside string
run_test "Variable inside string" "TEST_VAR=World && echo \"Hello \$TEST_VAR\"" 0

# Test 29: Variable with underscore
run_test "Variable with underscore" "_TEST_VAR=value && echo \$_TEST_VAR" 0

# Test 30: Multiple variables
run_test "Multiple variables" "VAR1=Hello && VAR2=World && echo \$VAR1 \$VAR2" 0

# Test 31: Variable with export
run_test "Variable with export" "export VAR=test && env | grep VAR=" 0

# Test 32: Undefined variable
run_test "Undefined variable" "echo \$UNDEFINED_VAR" 0

# Test 33: Variable with escaped characters
run_test "Variable with escaped characters" "VAR='special \$\"\`\\' && echo \$VAR" 0

echo -e "${YELLOW}====== Quote Tests ======${RESET}"

# Test 34: Single quotes
run_test "Single quotes" "echo 'This is a $TEST_VAR test'" 0

# Test 35: Double quotes
run_test "Double quotes" "TEST_VAR=test && echo \"This is a \$TEST_VAR test\"" 0

# Test 36: Mixed quotes
run_test "Mixed quotes" "echo \"This has 'single quotes' inside\"" 0

# Test 37: Quotes with special characters
run_test "Quotes with special characters" "echo \"*|><&\"" 0

# Test 38: Empty quotes
run_test "Empty quotes" "echo \"\" && echo ''" 0

# Test 39: Escaped quotes
run_test "Escaped quotes" "echo \"Escaped \\\"quotes\\\"\"" 0

echo -e "${YELLOW}====== Wildcard Tests ======${RESET}"

# Test 40: Simple wildcard
run_test "Simple wildcard" "echo \"$TEST_DIR\"/*.txt" 0

# Test 41: Wildcard for hidden files
run_test "Wildcard for hidden files" "echo \"$TEST_DIR\"/.*" 0

# Test 42: Escaped wildcard
run_test "Escaped wildcard" "echo \\*" 0

echo -e "${YELLOW}====== Parentheses Tests ======${RESET}"

# Test 43: Simple parentheses
run_test "Simple parentheses" "(echo Hello World)" 0

# Test 45: Unbalanced parentheses
run_test "Unbalanced parentheses" "(echo Unbalanced" 2

# Test 46: Parentheses with operators
run_test "Parentheses with operators" "(false || echo Fallback)" 0

echo -e "${YELLOW}====== Complex Tests ======${RESET}"

# Test 47: Complex command with pipes and redirections
run_test "Complex: pipes and redirections" "(cat < \"$TEST_DIR/file1.txt\" | grep Hello > \"$TEST_DIR/complex.txt\") && cat \"$TEST_DIR/complex.txt\"" 0

# Test 48: Complex command with variables and quotes
run_test "Complex: variables and quotes" "VAR1=Hello && VAR2=World && echo \"$VAR1 '$VAR2'\" > \"$TEST_DIR/vars.txt\" && cat \"$TEST_DIR/vars.txt\"" 0

# Test 49: Tilde expansion
run_test "Tilde expansion" "echo ~" 0

# Test 50: cd with no arguments (go to home)
run_test "cd with no arguments" "OLDDIR=\"$PWD\" && cd && pwd && cd \"\$OLDDIR\"" 0

# Test 51: cd with relative path
run_test "cd with relative path" "OLDDIR=\"$PWD\" && cd \"$TEST_DIR/subdir\" && pwd && cd \"\$OLDDIR\"" 0

# Test 52: cd with invalid directory
run_test "cd with invalid directory" "cd \"$TEST_DIR/nonexistent\"" 1

# Test 53: Multiple echo arguments
run_test "Multiple echo arguments" "echo one two three four five" 0

# Test 54: echo with -n option
run_test "echo with -n option" "echo -n test" 0

# Test 55: echo with escape characters
run_test "echo with escape characters" "echo escaped \\\\n chars" 0

# Test 56: Redirecting to existing file (overwrite)
run_test "Redirect to existing file" "echo First > \"$TEST_DIR/overwrite.txt\" && echo Second > \"$TEST_DIR/overwrite.txt\" && cat \"$TEST_DIR/overwrite.txt\"" 0

# Test 57: Very long command
run_test "Very long command" "echo This is a very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very long command" 0

# Test 58: Command with lots of arguments
run_test "Command with lots of arguments" "echo 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20" 0

# Test 59: Command with empty arguments
run_test "Command with empty arguments" "echo \"\" \"\" \"actual arg\" \"\"" 0

# Test 60: Empty command
run_test "Empty command" "" 0

# Test 61: Command with just spaces
run_test "Command with just spaces" "   " 0

# Test 62: Command with tabs
run_test "Command with tabs" "	echo	tabbed	command	" 0

echo -e "${YELLOW}====== Error Handling Tests ======${RESET}"

# Test 64: Command in non-existent directory
run_test "Command in non-existent directory" "\"$TEST_DIR/nonexistent/command\"" 127

# Test 65: Invalid redirection (directory)
run_test "Invalid redirection (directory)" "echo test > \"$TEST_DIR\"" 1

# Test 67: Redirect file that can't be opened
run_test "Redirect file that can't be opened" "echo test > \"$TEST_DIR/cant_open_dir/\"" 1

# Test 68: Missing command after pipe
run_test "Missing command after pipe" "echo test |" 2

echo -e "${YELLOW}====== Special Character Tests ======${RESET}"

# Test 71: Filename with spaces
run_test "Filename with spaces" "echo test > \"$TEST_DIR/file with spaces2.txt\" && cat \"$TEST_DIR/file with spaces2.txt\"" 0

# Test 72: Command with quotes in arguments
run_test "Command with quotes in arguments" "echo \"arg with \\\"quotes\\\"\"" 0

# Test 73: Command with backslashes
run_test "Command with backslashes" "echo This\\\\has\\\\backslashes" 0

echo -e "${YELLOW}====== Exit Status Tests ======${RESET}"

# Test 75: Exit status of successful command
run_test "Exit status successful" "true && echo \$?" 0

# Test 76: Exit status of failed command
run_test "Exit status failed" "false || echo \$?" 0

# Test 77: Checking exit status with &&
run_test "Exit status with &&" "false && echo Shouldnt print || echo \$?" 0

# Test 78: Checking exit status with ||
run_test "Exit status with ||" "true || echo Shouldnt print && echo \$?" 0

# Test 79: Exit status of pipeline
run_test "Exit status of pipeline" "false | true && echo \$?" 0

echo -e "${YELLOW}====== Environment Variable Tests ======${RESET}"

# Test 80: Check PATH variable
run_test "Check PATH variable" "echo \$PATH | grep -q /" 0

# Test 81: Check HOME variable
run_test "Check HOME variable" "echo \$HOME" 0

# Test 82: Check USER variable
run_test "Check USER variable" "echo \$USER" 0

# Test 83: Modify PATH temporarily
run_test "Modify PATH temporarily" "OLDPATH=\$PATH && PATH=\"$TEST_DIR\":\$PATH && PATH=\$OLDPATH && echo 'PATH restored'" 0

# Test 84: Multiple variables on one line
run_test "Multiple variables one line" "VAR1=one VAR2=two VAR3=three && echo \$VAR1 \$VAR2 \$VAR3" 0

# Test 85: Check PWD variable after cd
run_test "Check PWD variable after cd" "OLDDIR=\"$PWD\" && cd \"$TEST_DIR\" && echo \$PWD && cd \"\$OLDDIR\"" 0

echo -e "${YELLOW}====== Here Document Edge Cases ======${RESET}"

# Test 86: Here document with variables
run_test "Here document with variables" "VAR=replaced && cat << EOF
Testing \$VAR variable
EOF" 0

# Test 87: Here document without expansion
run_test "Here document without expansion" "VAR=not_replaced && cat << 'EOF'
Testing \$VAR variable
EOF" 0

# Test 88: Here document with quotes in content
run_test "Here document with quotes" "cat << EOF
\"Double quotes\" and 'single quotes'
EOF" 0

# Test 89: Here document with special characters
run_test "Here document with special characters" "cat << EOF
!@#\$%^&*()_+
<>,.?/\\|[]{}
EOF" 0

# Test 90: Here document with unusual delimiter
run_test "Here document with unusual delimiter" "cat << X_DELIMITER_X
This is a test
X_DELIMITER_X" 0

echo -e "${YELLOW}====== Extreme Edge Cases ======${RESET}"

# Test 91: Command with many arguments (using a loop)
run_test "Command with many arguments" "echo 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25" 0

# Test 93: Command with very long argument
run_test "Command with very long argument" "echo $(printf '%0.1000d' 0 | tr '0' '-')" 0

# Test 94: Multiple redirections
run_test "Multiple redirections" "echo first > \"$TEST_DIR/multi1.txt\" && echo second > \"$TEST_DIR/multi2.txt\" && cat < \"$TEST_DIR/multi1.txt\" < \"$TEST_DIR/multi2.txt\"" 0

# Test 95: Extreme pipe chain
run_test "Extreme pipe chain" "echo test | grep t | grep t | grep t | grep t | grep t" 0

# Test 96: Liam v1
run_test "Liam v1" "(echo $PWD && (ls -l | grep *.c) || echo \"No .c files found\") > output.txt && cat output.txt | wc -l" 0

# Test 97: truc de fou 2
run_test "liam v2" "echo test1 > r1 && echo test2 > r2 && < r1 < r2 ls > r3 > r4 && > r1 > r2 ls > r3 > r4 && cat r4" 0

echo -e "${YELLOW}====== Liam Random Environement Tests ======${RESET}"

run_test "Environment parsing" "echo \"$'PATH'\"" 0
run_test "Environment parsing" "echo $\"coucou\"" 0
run_test "Environment parsing" "echo \$PATH" 0
run_test "Environment parsing" "ls \$HOME/Desktop" 0
run_test "Environment parsing" "echo \"\$PATH\"\"\" coucou" 0
run_test "Environment parsing" "echo \$PATH\"coucou\"" 0
run_test "Environment parsing" "echo \"hello\"\$PWD\"coucou\"" 0
run_test "Environment parsing" "echo coucou\$PWD test\$COLORTERMlol lol\$HOME" 0
run_test "Environment parsing" "echo \"bonjour\$PATH$PWD\"" 0
run_test "Environment parsing" "echo \$PATH\"coucou\"" 0
run_test "Environment parsing" "echo \$\$\$\$\$\$\$\$" 0
run_test "Environment parsing" "echo \$12345" 0
run_test "Environment parsing" "echo \$$" 0

echo -e "${YELLOW}====== Liam Random Redirection Tests ======${RESET}"

run_test "Redirection check" "cat < test.txt" 1
run_test "Redirection check" "cat <test.txt >>hello<bonjour" 1
run_test "Redirection check" "cat \"<test.txt\"" 1
run_test "Redirection check" "echo bonjour1>test1" 0
run_test "Redirection check" "echo bonjour 1>test2" 0
run_test "Redirection check" "echo bonjour > \"     test1\"" 0
run_test "Redirection check" "echo bonjour >hey test2" 0
run_test "Redirection check" "echo bonjour >> test3" 0
run_test "Redirection check" "echo bonjour>>test3>>test4" 0
run_test "Redirection check" ">test1 >test2 echo bonjour" 0
run_test "Redirection check" ">test1>test2 echo bonjour" 0
run_test "Redirection check" ">test1 >test2 echo bonjour" 0
run_test "Redirection check" ">> e" 0
run_test "Redirection check" "echo bonjour > \"\$PATHH\"" 1

echo -e "${RED}====== Parsing quotes Tests ======${RESET}"

run_test "Parsing quote check" "'echo' \"bonjour\" \"wesh\"" 0
run_test "Parsing quote check" "e\"ch\"o bonjour" 0
run_test "Parsing quote check" "       'ech'o bonjour" 0
run_test "Parsing quote check" "'echo \"\$HOME\"'" 127
run_test "Parsing quote check" "echo '''''' | cat -e" 0

echo -e "${RED}====== Expansion Tests ======${RESET}"

run_test "1 - Simple expansion" "echo \$USER" 0
run_test "2 - Undefined variable" "echo \$UNDEFINED" 0
run_test "3 - Double dollar" "echo \$\$USER" 0
run_test "4 - Simple single quotes" "echo '\$USER'" 0
run_test "5 - Expansion then single quotes" "echo '\$USER'\$HOME" 0
run_test "6 - Single double quotes" "echo '\$USER'\$HOME" 0
run_test "7 - Simple double quotes" "echo \"\$USER\"" 0
run_test "8 - Double quotes with single quotes inside" "echo \"\$USER'\$HOME'\"" 0
run_test "9 - Double quotes with single quotes plus expansion" "echo \"'\$USER'\"\$HOME" 0
run_test "10 - Double quotes inside single quotes" "echo '\"\$USER\"'" 0
run_test "11 - Single quotes inside double quotes" "echo \"'\$USER'\"" 0
run_test "12 - Mixed quotes with multiple expansions" "echo \"\$USER'\$HOME'\$PATH\"" 0
run_test "13 - Trailing dollar sign" "echo \$USER\$" 0
run_test "14 - Interrupted variable name" "echo \$U'SE'R" 0
run_test "15 - Consecutive single quotes" "echo '\$USE''R'" 0
run_test "16 - Expansion of a single quote" "export SINGLEQUOTE=\"'\" && echo \$SINGLEQUOTE" 0
run_test "17 - Non expansion of quote after dollar sign" "echo \$\"USER\"" 0
run_test "18 - Expansion of first and non print of second dollar sign" "echo \$HOME\$\"USER\"" 0
run_test "19 - Expansion with quotes part one" "export a=\$\"USER\" && echo \$a" 0
run_test "20 - Expansion with quotes part two" "export a=\$\"US'ER\" && echo \$a" 0
run_test "21 - Expansion with quotes part one" "export a=\$'US\"ER' && echo \$a" 0



# Make sure we're back in the starting directory before cleanup
cd "$STARTING_DIR"

# Clean up
echo -e "${BLUE}Cleaning up test files...${RESET}"
rm -rf "$TEST_DIR"

# Print summary
echo -e "${YELLOW}====== Test Summary ======${RESET}"
echo -e "Total tests: $TEST_COUNT"
echo -e "${GREEN}Passed: $PASSED_COUNT${RESET}"
echo -e "${RED}Failed: $FAILED_COUNT${RESET}"

if [ $FAILED_COUNT -eq 0 ]; then
    echo -e "${GREEN}All tests passed!${RESET}"
else
    echo -e "${RED}Some tests failed.${RESET}"
fi

# Return to starting directory at the end of the script
cd "$STARTING_DIR"
echo -e "${BLUE}Test script complete. Back in starting directory: ${RESET}$PWD"
rm "     test1" "e" "hey" "r1" "r2" "r3" "r4" "test1" "test2" "test3" "test4"
