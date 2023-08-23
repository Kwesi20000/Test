#include "shell.h"


void oprint(const *char mes)
{
	write(STDOUT_FILEN0, mes, strlen(mes));
}
