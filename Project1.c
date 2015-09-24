//####################
//Dylan Guldy
//Operating Systems
//Project 1
//####################
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/timeb.h>
#include <string.h>
#include <time.h>

void byte_at_a_time(void);
void line_at_a_time(void);
//This defines what the end of line characters are for both systems
#ifdef WIN32
	char EOL[] = "\r\n";
#else 
	char EOL[] = "\n";
#endif

int main()
{
	int mode;
	//Get mode of operation
	printf("Select a mode to operate in, 0 is character by character andand 1 is line by line: ");
	scanf("%d",&mode);
	while(mode != 0 && mode != 1)
	{
		printf("Invalid number please try again: ");
		scanf("%d",&mode);
	}

	if(mode == 0)
	{
		byte_at_a_time();
	}
	if(mode == 1)
	{
		line_at_a_time();
	}
	return 0;
}





void byte_at_a_time(void)

{
	//Variable declarations 
	char input_file_name[64], new_file_name[64];
	FILE * input_file;
	FILE * copy_file;
	//Buffer
	char buff;	
	//Timing
	struct timeb clock_start, clock_end;
	clock_t cpu_start, cpu_end;
	int wall_diff = 0, cpu_diff = 0;

#ifdef WIN32
	char EOL[] = "\r\n";
#else
	char EOL[] = "\n";
#endif

	//Open file to be read. 
	printf("Enter name of file to open, be sure to include .txt when typing name: ");
	scanf("%63s", input_file_name);
	input_file = fopen(input_file_name,"r");
	while (input_file == NULL)
	{
		printf("File not found please make sure file is in the correct direcory andand the name is correct, \n then try again, use exit to leave: ");	
		scanf("%63s", input_file_name);
		input_file = fopen(input_file_name, "r");
		if(input_file_name == "exit")
		{
			exit(0);
		}
	}


	//Open file to copy to.
	printf("Enter name of file to write to: ");
	scanf("%63s", new_file_name);
	copy_file = fopen(new_file_name,"w");
	while (copy_file == NULL)
	{
		printf("File not found please make sure file is in the correct direcory andand name is correct, \n then try again: ");
		scanf("%63s", new_file_name);
		copy_file = fopen(new_file_name, "w");
		if(new_file_name == "exit")
		{
			exit(0);
		}
	}	

	//Copy file into new file
	
	if(input_file != NULL && copy_file != NULL)
	{
		printf("Starting copy:\n");
		ftime(&clock_start);
		cpu_start = clock();
		while(fscanf(input_file, "%c", &buff) != EOF)
		{
			if(buff != '\n')
			{
				fprintf(copy_file, "%c", buff);
			}
			if(buff == '\n')
			{
				fprintf(copy_file, "%s", EOL);
			}
		}
	}
	fclose(input_file);
	fclose(copy_file);
	ftime(&clock_end);
	cpu_end = clock();

	//Find wall time andand cpu time
	wall_diff = (1000 * (clock_end.time - clock_start.time) + (clock_end.millitm - clock_start.millitm));
	cpu_diff = (cpu_end - cpu_start) / (CLOCKS_PER_SEC / (clock_t)1000);

	printf("Task completed in %d milliseconds Wall-clock time and %d milliseconds CPU time.\n", wall_diff, cpu_diff);
}




void line_at_a_time(void)
{
	//Variable declarations
	char input_file_name[64], new_file_name[64];
	FILE * input_file;
	FILE * copy_file;
	//Buffer
	char buff[81];
	//Timing
	struct timeb clock_start, clock_end;
	clock_t cpu_start, cpu_end;
	int wall_diff = 0, cpu_diff = 0;
	//Open file to be read. 

#ifdef WIN32
	char EOL[] = "\r\n";
#else
	char EOL[] = "\n";
#endif

	printf("Enter name of file to open, be sure to include .txt when typing name: ");
	scanf("%63s", input_file_name);
	input_file = fopen(input_file_name,"r");
	while (input_file == NULL)
	{
		printf("File not found please make sure file is in the correct direcory and the name is correct, \n then try again, use exit to leave: ");	
		scanf("%63s", input_file_name);
		input_file = fopen(input_file_name,"r");
		if(input_file_name == "exit")
		{
			exit(0);
		}
	}

	//Open file to copy to.
	printf("Enter name of file to write to: ");
	scanf("%63s", new_file_name);
	copy_file = fopen(new_file_name,"w");
	while (copy_file == NULL)
	{
		printf("File not found please make sure file is in the correct direcory and name is correct, \n then try again: ");
		scanf("%63s", new_file_name);
		copy_file = fopen(new_file_name, "w");
		if(new_file_name == "exit")
		{
			exit(0);
		}
	}	
	


	//Copy file into new file
	
	if(input_file != NULL && copy_file != NULL)
	{
		printf("Starting copy:\n");
		ftime(&clock_start);
		cpu_start = clock();
		while(fgets(buff, 81, input_file) != (char *)NULL)
		{
			fprintf(copy_file, "%s", buff);
		}	
	}
	fclose(input_file);
	fclose(copy_file);
	ftime(&clock_end);
	cpu_end = clock();

	//Find wall time andand cpu time
	wall_diff = (1000 * (clock_end.time - clock_start.time) + (clock_end.millitm - clock_start.millitm));
	cpu_diff = (cpu_end - cpu_start) / (CLOCKS_PER_SEC / (clock_t)1000);

	printf("Task completed in %d milliseconds Wall-clock time and %d milliseconds CPU time.\n", wall_diff, cpu_diff);
}
