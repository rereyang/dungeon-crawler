#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    char *qstr = getenv("QUERY_STRING");
    char *cmd = strstr(qstr, "gold=");
    int goldvar = 10;
    if (cmd != NULL) {
	cmd += strlen("gold=");
        char cmdd[1000];
	memset(cmdd, 0, 1000);
	strcpy(cmdd, cmd);
	char* numptr = cmdd;
	while ('0' <= *numptr && *numptr <= '9') numptr += 1;
	*numptr = '\0';
	goldvar = atoi(cmdd);
    }
    FILE* f = fopen("../index.html", "r");
    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    char *buffer = calloc(1, fsize + 10);
    fseek(f, 0, SEEK_SET);
    fread(buffer, 1, fsize, f);
    fclose(f);
    char *form_end = strstr(buffer, "<input type=\"submit\"");
    if (goldvar <= 0) {
	printf("Content-Type:text/html\n\n<html><h1>You Lose</h1></html>");
    } else if (goldvar >= 100) {
	printf("Content-Type:text/html\n\n<html><h1>You Win</h1></html>");
    } else {
	char *pref = calloc(1, fsize + 10);
	char tmp = *form_end;
	*form_end = '\0';
	strcpy(pref, buffer);
	*form_end = tmp;
	buffer[fsize] = '\0';
	char *simg = strstr(pref, "keaiduo.png");
	char *eimg = simg + strlen("keaiduo.png");
	memset(simg, 0, strlen("keaiduo.png"));
	char *scgi = strstr(eimg, "cgi-bin/answer.cgi");
	char *ecgi = scgi + strlen("cgi-bin/answer.cgi");
	memset(scgi, 0, strlen("cgi-bin/answer.cgi"));
	printf("Content-Type:text/html\n\n<html>%s../keaiduo.png%sanswer.cgi%s<input type=\"hidden\" name=\"gold\" value=\"%d\">\n%s</html>", pref, eimg, ecgi, goldvar, form_end);
        free(pref);
    }
    free(buffer);
    return 0;
}
