#include <stdio.h>
#include <yaml.h>
#include <assert.h>
#include <stdbool.h>

bool openFile(FILE *file, char *fileName, char *fileType)
{
	file = fopen(fileName, fileType);

	if(file != NULL)
	{
		printf("found %s file\n", fileName);
		return true;
	}
	else
	{
		printf("couldent find %s file", fileName);
		return false;
	}
}



int main(int argc, char* argv[])
{
	//makes sure the user put the correct number of files
	if (argc != 3)
	{

		perror("needs 2 arguments. \n1: name of input file wit extension \n2: nmae of output file");
		return 1;
	}

	//creates the file objects
	printf("%s \n%s\n", argv[1], argv[2]);
	FILE* IN;
	FILE* OUT;
	FILE* COMMANDS;

	//loads the files into memory
	if(!openFile(IN, argv[1], "r"))
	{
		return 1;
	}

	if(!openFile(OUT, argv[2], "w"))
	{
		return 1;
	}

	if(!openFile(COMMANDS, "src/commands.yaml", "rb"))
	{
		return 1;
	}

	//creates yaml parser object
	yaml_parser_t parser;
	yaml_document_t keyDocs;
	yaml_node_t *node;

	//starts parser
	if(!yaml_parser_initialize(&parser))
	{
		printf("faild to init parser");
		return 1;
	}
	printf("loaded parser\n");

	yaml_parser_set_input_file(&parser, COMMANDS);
	printf("set input command file");

	if(!yaml_parser_load(&parser, &keyDocs))
	{
		printf("faild to load parser");
		return 1;
	}
	else
	{
		printf("loaded yaml parser\n");
	}


	///////////////////////////////////////////////////////////////////done starting files


	//unloads all objects from memory
	printf("exiting\n");
	yaml_parser_delete(&parser);
	fclose(IN);
	fclose(OUT);
	fclose(COMMANDS);
	printf("done\n");

		
}
