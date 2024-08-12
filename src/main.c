#include <stdio.h>
#include <errno.h>
#include <yaml.h>
#include <assert.h>

int main(int argc, char* argv[])
{
	if (argc != 3)
	{

		perror("needs 2 arguments. \n1: name of input file wit extension \n2: nmae of output file");
		return 1;
	}

	printf("%s \n%s\n", argv[1], argv[2]);
	FILE* IN;
	FILE* OUT;
	FILE* COMMANDS;

	IN = fopen(argv[1], "r");
	if(IN != NULL)
	{
		printf("found input file\n");
	}
	else
	{
		perror("couldent find input file");
		return 1;
	}

	OUT = fopen(argv[2], "w");
	if(OUT != NULL)
	{
		printf("made output file\n");
	}
	else
	{
		perror("couldent make output file");
		return 1;
	}


	COMMANDS = fopen("commands.yaml", "r");
	if(COMMANDS != NULL)
	{
		printf("found commands file\n");
	}
	else
	{
		perror("couldent find commands file");
		return 1;
	}


	yaml_parser_t parser;
	yaml_parser_initialize(&parser);
	yaml_parser_set_input_file(&parser, COMMANDS);

	yaml_parser_delete(&parser);
	fclose(IN);
	fclose(OUT);
	fclose(COMMANDS);

		
}
