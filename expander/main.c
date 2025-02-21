#include "expand.h"

#include <stdio.h>
#include <string.h>

#define GREEN "\033[0;32m"
#define RED "\033[0;31m"
#define RESET "\033[0m"
#define BLUE "\033[0;34m"
#define YELLOW "\033[0;33m"

typedef struct  s_test_case
{
	char *name;
	char *input;
	char *expected;
}   t_test_case;

void	test_case(const char *test_name, char *input, char *expected)
{
	char	*expanded;
	char	*final;

	printf("\n%s=== Test %s ===%s\n", BLUE, test_name, RESET);
	printf("Input: %s\n", input);
	printf("Expected: %s%s%s\n", YELLOW, expected, RESET);
	expanded = expand_env_vars(input);
	if (expanded)
	{
		printf("After expansion: %s\n", expanded);
		final = remove_quotes(expanded);
		if (final)
		{
			printf("Final result: ");
			if (strcmp(final, expected) == 0)
				printf("%s%s%s\n", GREEN, final, RESET);
			else
				printf("%s%s%s\n", RED, final, RESET);
			free(final);
		}
		free(expanded);
	}
}

int main(void)
{
	t_test_case tests[] = {
		{"1 - Simple expansion", "$USER", "gueberso"},
		{"2 - Undefined variable", "$UNDEFINED", ""},
		{"3 - Double dollar", "$$USER", "???"},
		{"4 - Simple single quotes", "'$USER'", "$USER"},
		{"5 - Expansion then single quotes", "$USER'$HOME'", "gueberso$HOME"},
		{"6 - Single quotes then expansion", "'$USER'$HOME", "$USER/home/gueberso"},
		{"7 - Simple double quotes", "\"$USER\"", "gueberso"},
		{"8 - Double quotes with single quotes inside", "\"$USER'$HOME'\"", "gueberso'/home/gueberso'"},
		{"9 - Double quotes with single quotes plus expansion", "\"'$USER'\"$HOME", "'gueberso'/home/gueberso"},
		{"10 - Double quotes inside single quotes", "'\"$USER\"'", "\"$USER\""},
		{"11 - Single quotes inside double quotes", "\"'$USER'\"", "'gueberso'"},
		{"12 - Mixed quotes with multiple expansions", "\"$USER'$HOME'$PATH\"", "gueberso'/home/gueberso'/home/gueberso/bin:/home/gueberso/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin:/home/gueberso/.dotnet/tools"},
		{"13 - Trailing dollar sign", "$USER$", "gueberso$"},
		{"14 - Interrupted variable name", "$U'SE'R", "SER"},
		{"15 - Consecutive single quotes", "'$USE''R'", "$USER"},
		{"16 - Expansion of a single quote", "$USER", "'"}

	};

	size_t num_tests = sizeof(tests) / sizeof(t_test_case);

	for (size_t i = 0; i < num_tests; i++)
	{
		test_case(tests[i].name, tests[i].input, tests[i].expected);
	}

	return (0);
}
