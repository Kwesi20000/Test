#include "shell.h"


int main(void)
{
	char cmd[100];

	while(true)
	{
		prompt();
		read(cmd, sizeof(cmd);
		execute_cmd(cmd);
	}

	return (0);
}
