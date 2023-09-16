
#include <stdio.h>
#include <assert.h>
#include "../../../../lib/csapp.h"

int main(int argc, char *argv[], char *envp[])
{
    char *buf, *method, tmp[MAXLINE], postbody[MAXLINE], *p, *v;
    char arg1[MAXLINE], arg2[MAXLINE], content[MAXLINE];
    int n1 = 0;
    int n2 = 0;
    memset(content, 0, MAXLINE);
    memset(postbody, 0, MAXLINE);

    method = getenv("REQUEST_METHOD");
    if (method == NULL)
    {
        method = malloc(sizeof("GET"));
        strcpy(method, "GET");
    }
    if (!strcasecmp(method, "GET"))
    {
        if ((buf = getenv("QUERY_STRING")) != NULL)
        {
            strcpy(tmp, buf);

            p = strchr(buf, '&');
            *p = '\0';
            sscanf(buf, "a=%d", &n1);
            sscanf(p + 1, "b=%d", &n2);
        }
        sprintf(content, "url param= ?%s\r\n", tmp);
    }
    else if (!strcasecmp(method, "POST"))
    {
        if ((buf = getenv("POST_BODY")) != NULL)
        {
            strcpy(tmp, buf);
            p = strchr(buf, '&');
            *p = '\0';
            sscanf(buf, "a=%d", &n1);
            sscanf(p + 1, "b=%d", &n2);
        }
        sprintf(content, "postbody= %s\r\n", tmp);
    }

    sprintf(content, "%sWelcome to add.com: ", content);
    sprintf(content, "%sTHE Internet addition portal.\r\n<p>", content);
    sprintf(content, "%sThe answer is: %d + %d = %d\r\n<p>", content, n1, n2, n1 + n2);
    sprintf(content, "%sTanks for visiting!\r\n", content);

    printf("HTTP/1.0 %s %s\r\n", "200", "OK");
    printf("Server: Tiny Web Server\r\n");
    printf("Connection: close\r\n");
    printf("Connection-Length: %d\r\n", (int)strlen(content));
    printf("Content-type: text/html\r\n\r\n");

    if (strcasecmp(method, "HEAD"))
    {
        printf("%s", content);
    }

    fflush(stdout);
}