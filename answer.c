#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main() {
    char *qstr = getenv("QUERY_STRING"); 
    char *gold = strstr(qstr, "gold=");
    int goldvar = 10;
    if (gold != NULL) {
        gold += strlen("gold=");
        char cmdd[1000];
	memset(cmdd, 0, 1000);
	strcpy(cmdd, gold);
	char* numptr = cmdd;
	while ('0' <= *numptr && *numptr <= '9') numptr += 1;
	*numptr = '\0';
	goldvar = atoi(cmdd);
    }
    char *cmd = strstr(qstr, "command=") + strlen("command="); 
    printf("Content-Type:text/html\n\n");
    printf("<html>");
    if (!strncmp(cmd, "NORTH", 5)) {
        printf("<a href=\"https://www.cs.mcgill.ca/~zyu29/cgi-bin/addgold.cgi?gold=%d\">Press HERE to go North</a>", goldvar);
    } else if (!strncmp(cmd, "EAST", 4)) {
        printf("<a href=\"https://www.cs.mcgill.ca/~byouso/cgi-bin/addgold.cgi?gold=%d\">Press HERE to go East</a>", goldvar);
    } else if (!strncmp(cmd, "WEST", 4)) {
        printf("<a href=\"https://www.cs.mcgill.ca/~xdeng10/cgi-bin/addgold.cgi?gold=%d\">Press HERE to go West</a>", goldvar);
    } else if (!strncmp(cmd, "SOUTH", 5)) {
        printf("<a href=\"https://www.cs.mcgill.ca/~zgao20/cgi-bin/addgold.cgi?gold=%d\">Press HERE to go South</a>", goldvar);
    } else if (!strncmp(cmd, "GOLD", 4)) {
        printf("<html><h1>%d</h1>", goldvar); 
	printf("<a href=\"http://www.cs.mcgill.ca/~yyang180/cgi-bin/addgold.cgi?gold=%d\">Press HERE to go Back</a>", goldvar);
    } else {
	int is_correct = 0;
	if (!strncmp(cmd, "2", 1)) is_correct = 1;
	if (is_correct) {
            goldvar += 10;
	    printf("<h1>Correct</h1>");
	} else {
	    goldvar -= 5;
	    printf("<h1>Not Correct</h1>");
	}
	printf("<a href=\"http://www.cs.mcgill.ca/~yyang180/cgi-bin/addgold.cgi?gold=%d\">Press HERE to go Back</a>", goldvar);
    }
    printf("</html>");
    return 0;
}
