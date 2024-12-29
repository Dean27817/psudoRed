#include <stdio.h>
#include <yaml.h>
#include <assert.h>
#include <stdbool.h>

typedef struct
{
	char *name;
	char **commands;
} subCommand;

typedef struct
{
	char *name;

	//the paramiters for the sub-commands
	int *values;


	//the array of all  falsethe sub commands that a keyword has
	subCommand **subArray;
} command;

bool openFile(FILE **file, char *fileName, char *fileType)
{
	*file = fopen(fileName, fileType);

	if(file != NULL)
	{
		printf("found %s file\n", fileName);
		return true;
	}
	printf("couldent find %s file", fileName);
	return false;
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
	if(!openFile(&IN, argv[1], "r"))
	{
		return 1;
	}

	if(!openFile(&OUT, argv[2], "w"))
	{
		return 1;
	}

	if(!openFile(&COMMANDS, "src/commands.yaml", "rb"))
	{
		return 1;
	}

	//creates yaml parser object
	yaml_parser_t parser;
	yaml_token_t token;
	//starts parser
	if(!yaml_parser_initialize(&parser))
	{
		printf("faild to init parser");
		return 1;
	}
	printf("loaded parser\n");

	yaml_parser_set_input_file(&parser, COMMANDS);
	printf("set input command file\n");

	///////////////////////////////////////////////////////////////////done starting files
	
	int done = 0;

	//holds the list of commands
	bool firstLine = true;
	int i = 0;
	bool name = true;
	bool val = false;
	bool writeCommand= false;
	command **commandList;
	int commandNum = 8;

	//allocating memory
	commandList = (command **)malloc(commandNum * sizeof(command)); 
	for (int i = 0; i < commandNum; i++)
	{
		commandList[i] = (command *)malloc(sizeof(command)); 
	}
	//reads the yaml file to set up the commands that will be translated
	while(!done)
	{
		//creates the event and checks for errors
		if(!yaml_parser_scan(&parser, &token))
		{
			printf("error reading commands file\n");
			return 1;
		}
	
		//reads the tokens of the yaml file
		switch(token.type)
		{
			//start and end of the yaml file
			case YAML_STREAM_START_TOKEN:
				printf("started yaml file\n");
			break;
			case YAML_STREAM_END_TOKEN:
				printf("end of file\n");
			break;

			//token types (read before actual token)
			case YAML_KEY_TOKEN:
				printf ("(key token)");
				if (name)
				{
					commandList[i] -> name =  token.data.scalar.value;
					name = false;
					printf("starting new key word\n");
				}
				if(token.type == YAML_SCALAR_TOKEN)
				{
					printf("IDK What Is happening at this point %s\n", token.data.scalar.value);
					if (strcmp((char*)token.data.scalar.value, "values"))
					{
						printf("reading vars for command\n");
						val = true;
					}
					if ((char*)token.data.scalar.value == (char*)"command")
					{
						printf("starting new command\n");
						writeCommand= true;
					}
				}
			break;
			case YAML_VALUE_TOKEN:
				printf("(value token)");
				if (val)
				{
					for (int i = 0 ; i < (sizeof((char*)token.data.scalar.value) / sizeof(char)); i++)
					{
<<<<<<< Updated upstream
						printf("%c", token.data.scalar.value[i]);
=======
						if((char*)token.data.scalar)
						{
							printf("scalar");
						}
>>>>>>> Stashed changes
					}
					printf("\n");
					val = false;
				}
				if (writeCommand)
				{
					writeCommand = false;
				}
			break;
			//Block delimiters
			case YAML_BLOCK_SEQUENCE_START_TOKEN:
				printf("start blocking sequence\n");
			break;
			case YAML_BLOCK_ENTRY_TOKEN:
				printf("start block\n");
			break;
			case YAML_BLOCK_END_TOKEN:
				printf("end block\n");
				i++;
				name = true;
			break;
			//data
			case YAML_BLOCK_MAPPING_START_TOKEN:
				printf("Block Mapping\n");
			break;
			case YAML_SCALAR_TOKEN:
				printf("scalar %s\n", token.data.scalar.value);
			break;

			default:
			break;
		} 

		//checks if the file is done
		done = (token.type == YAML_STREAM_END_TOKEN);

		//frees up the event memory
		yaml_token_delete(&token);
	}

	////////////////////////////////////////////////////////////////////////////////////done reading yaml files
	//freeing memory
	for (int i = 0; i < commandNum; i++)
	{
		if (commandList[i] != NULL)
		{
			free(commandList[i]);
			commandList[i] == NULL;
		}
	}
	if (commandList != NULL)
	{
		free(commandList);
		commandList = NULL;
	}

	printf("done loading commands\n");
	
	//frees up the memory from the parser
	yaml_parser_delete(&parser);

	//unloads all objects from memory
	printf("exiting\n");
	fclose(IN);
	fclose(OUT);
	fclose(COMMANDS);
	printf("done\n");

		
}
