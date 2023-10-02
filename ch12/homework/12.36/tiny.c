
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "../../../lib/csapp.h"

struct req
{
    char *key;
    char *value;
    struct req *next;
};

void doit(int fd);
int check_method(int fd, char *method);
void read_requesthdrs(rio_t *rp, struct req *head);
char *find_req(struct req *head, char *key);
void free_req(struct req *head);
int parse_uri(char *url, char *filename, char *cgiargs);
void serve_static(int fd, char *filename, int filesize, char *method);
void get_filetype(char *filename, char *filetype);
void serve_dynamic(rio_t *rp, struct req *head, char *filename, char *cgiargs, char *method);
void clienterror(int fd, char *cause, char *errnum, char *shortmsg, char *longmsg);

typedef struct
{
    int maxfd;
    fd_set read_set;
    fd_set ready_set;
    int nready;
    int maxi;
    int clientfd[FD_SETSIZE];
    rio_t clientrio[FD_SETSIZE];
} pool;

int byte_cnt = 0;

void init_pool(int listenfd, pool *p)
{
    int i;
    p->maxi = -1;
    for (i = 0; i < FD_SETSIZE; i++)
    {
        p->clientfd[i] = -1;
    }
    p->maxfd = listenfd;
    FD_ZERO(&p->read_set);
    FD_SET(listenfd, &p->read_set);
}

void add_client(int connfd, pool *p)
{
    int i;
    p->nready--;
    for (i = 0; i < FD_SETSIZE; i++)
    {
        if (p->clientfd[i] < 0)
        {
            p->clientfd[i] = connfd;
            Rio_readinitb(&p->clientrio[i], connfd);
            FD_SET(connfd, &p->read_set);
            if (connfd > p->maxfd)
            {
                p->maxfd = connfd;
            }
            if (i > p->maxi)
            {
                p->maxi = i;
            }
            break;
        }
    }
    if (i == FD_SETSIZE)
    {
        app_error("add_client error: Too many clients");
    }
}

void check_clients(pool *p)
{
    int i, connfd, n;
    char buf[MAXLINE];
    rio_t rio;
    for (i = 0; (i <= p->maxi) && (p->nready > 0); i++)
    {
        connfd = p->clientfd[i];
        rio = p->clientrio[i];
        if ((connfd > 0) && FD_ISSET(connfd, &p->ready_set))
        {
            p->nready--;
            printf("doit(%d)\n", connfd);
            doit(connfd);
            Close(connfd);
            FD_CLR(connfd, &p->read_set);
            p->clientfd[i] = -1;
            printf("close %d and update pool\n", connfd);
        }
    }
}

int main(int argc, char *argv[], char *envp[])
{
    int listenfd, connfd;
    socklen_t clientlen;
    struct sockaddr_storage clientaddr;
    char client_hostname[MAXLINE], client_port[MAXLINE];
    static pool pool;

    if (argc != 2)
    {
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        exit(1);
    }

    listenfd = Open_listenfd(argv[1]);
    init_pool(listenfd, &pool);

    while (1)
    {
        pool.ready_set = pool.read_set;
        pool.nready = Select(pool.maxfd + 1, &pool.ready_set, NULL, NULL, NULL);

        if (FD_ISSET(listenfd, &pool.ready_set))
        {
            clientlen = sizeof(struct sockaddr_storage);
            printf("ready accept...\n");
            connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
            Getnameinfo((SA *)&clientaddr, clientlen, client_hostname, MAXLINE, client_port, MAXLINE, 0);
            printf("connected to (%s %s)\n", client_hostname, client_port);
            add_client(connfd, &pool);
            printf("add %d\n", connfd);
        }

        check_clients(&pool);
    }
}

void doit(int fd)
{
    int is_static;
    struct stat sbuf;
    char buf[MAXLINE], method[MAXLINE], uri[MAXLINE], version[MAXLINE];
    char filename[MAXLINE], cgiargs[MAXLINE];
    rio_t rio;
    struct req REQ_HEAD = {NULL, NULL, NULL};

    Rio_readinitb(&rio, fd);
    memset(buf, 0, MAXLINE);

    sigjmp_buf jmpbuf;
    if (sigsetjmp(jmpbuf, 1))
    {
        free_req(&REQ_HEAD);
        return;
    }
    else
    {
        void sigpipe_handler(int sig)
        {
            int old_errno = errno;
            siglongjmp(jmpbuf, 1);
            errno = old_errno;
        };
        if (Signal(SIGPIPE, sigpipe_handler) == SIG_ERR)
            unix_error("sigpipe_handler error");
    }

    ssize_t rc = Rio_readlineb(&rio, buf, MAXLINE);
    if (rc == 0)
    {
        printf("fd(%d) not send any bytes\n", fd);
        fflush(stdout);
        return;
    }
    sscanf(buf, "%s %s %s", method, uri, version);
    if (check_method(fd, method))
    {
        clienterror(fd, method, "501", "Not implemented", "Tiny does not implement this method");
        return;
    }
    read_requesthdrs(&rio, &REQ_HEAD);

    is_static = parse_uri(uri, filename, cgiargs);
    if (stat(filename, &sbuf) < 0)
    {
        clienterror(fd, method, "404", "Not found", "Tiny could't find this file");
        return;
    }

    if (is_static)
    {
        if (!(S_ISREG(sbuf.st_mode)) || !(S_IRUSR & sbuf.st_mode))
        {
            clienterror(fd, method, "403", "Forbidden", "Tiny could't read this file");
            return;
        }
        serve_static(fd, filename, sbuf.st_size, method);
    }
    else
    {
        if (!(S_ISREG(sbuf.st_mode)) || !(S_IRUSR & sbuf.st_mode))
        {
            clienterror(fd, method, "403", "Forbidden", "Tiny could't run the CGI program");
            return;
        }
        serve_dynamic(&rio, &REQ_HEAD, filename, cgiargs, method);
    }
    free_req(&REQ_HEAD);
}

int check_method(int fd, char *method)
{
    if (!strcasecmp(method, "GET"))
    {
        return 0;
    }
    if (!strcasecmp(method, "HEAD"))
    {
        return 0;
    }
    if (!strcasecmp(method, "POST"))
    {
        return 0;
    }
    return 1;
}

void clienterror(int fd, char *cause, char *errnum, char *shortmsg, char *longmsg)
{
    char buf[MAXLINE], body[MAXBUF];
    sprintf(body, "<html><title>Tiny Error</title>");
    sprintf(body, "%s<body>\r\n", body);
    sprintf(body, "%s%s:%s\r\n", body, errnum, shortmsg);
    sprintf(body, "%s<p>%s: %s\r\n", body, longmsg, cause);
    sprintf(body, "%s<hr><em>The Tiny Web server</em>\r\n", body);

    sprintf(buf, "HTTP/1.0 %s %s\r\n", errnum, shortmsg);
    sprintf(buf, "%sContent-type: text/html\r\n", buf);
    sprintf(buf, "%sContent-length: %d\r\n\r\n", buf, (int)strlen(body));
    Rio_writen(fd, buf, strlen(buf));

    if (strcasecmp(cause, "HEAD"))
    {
        Rio_writen(fd, body, strlen(body));
    }
}

void read_requesthdrs(rio_t *rp, struct req *head)
{
    char buf[MAXLINE];
    char key[MAXLINE];
    char value[MAXLINE];
    struct req *current = head;
    memset(buf, 0, MAXLINE);
    while (strcmp(buf, "\r\n"))
    {
        memset(buf, 0, MAXLINE);
        Rio_readlineb(rp, buf, MAXLINE);
        // printf("%s", buf);

        char *value_pos = strchr(buf, ':');
        if (value_pos == NULL)
        {
            continue;
        }
        strncpy(key, buf, value_pos - buf);
        key[value_pos - buf] = '\0';
        value_pos++;
        while (*value_pos == ' ')
        {
            value_pos++;
        }
        char *end_pos = strstr(value_pos, "\r\n");
        if (end_pos == NULL)
        {
            continue;
        }
        strncpy(value, value_pos, end_pos - value_pos);
        value[end_pos - value_pos] = '\0';
        // printf("key = %s, value=%s\n", key, value);
        struct req *item = malloc(sizeof(struct req));
        item->key = malloc(strlen(key) + 1);
        strcpy(item->key, key);
        item->value = malloc(strlen(value) + 1);
        strcpy(item->value, value);
        item->next = NULL;

        current->next = item;
        current = item;
    }
    return;
}

char *find_req(struct req *head, char *key)
{
    struct req *current = head->next;
    // printf("%p\n", current);
    while (current)
    {
        // printf("%s %s\n", current->key, current->value);
        if (!strcasecmp(current->key, key))
        {
            return current->value;
        }
        current = current->next;
    }
    return NULL;
}

void free_req(struct req *head)
{
    struct req *current = head->next;
    while (current)
    {
        struct req *next = current->next;
        free(current->key);
        free(current->value);
        free(current);
        current = next;
    }
    head->next = NULL;
}

int parse_uri(char *uri, char *filename, char *cgiargs)
{
    char *ptr;
    strcpy(cgiargs, "");
    if (!strstr(uri, "cgi-bin"))
    {
        strcpy(cgiargs, "");
        strcpy(filename, ".");
        strcat(filename, uri);
        if (uri[strlen(uri) - 1] == '/')
        {
            strcat(filename, "home.html");
        }
        return 1;
    }
    else
    {
        ptr = index(uri, '?');
        if (ptr)
        {
            strcpy(cgiargs, ptr + 1);
            *ptr = '\0';
        }
        else
        {
            strcpy(cgiargs, "");
        }
        strcpy(filename, ".");
        strcat(filename, uri);
        return 0;
    }
}

void serve_static(int fd, char *filename, int filesize, char *method)
{
    int srcfd;
    char *srcp, filetype[MAXLINE], buf[MAXLINE];

    get_filetype(filename, filetype);
    sprintf(buf, "HTTP/1.0 %s %s\r\n", "200", "OK");
    sprintf(buf, "%sServer: Tiny Web Server\r\n", buf);
    sprintf(buf, "%sConnection: close\r\n", buf);
    sprintf(buf, "%sContent-length: %d\r\n", buf, filesize);
    sprintf(buf, "%sContent-type: %s\r\n\r\n", buf, filetype);
    Rio_writen(fd, buf, strlen(buf));
    // printf("Response headers: \n");
    // printf("%s", buf);

    if (!strcasecmp(method, "HEAD"))
    {
        return;
    }

    srcfd = Open(filename, O_RDONLY, 0);
    srcp = malloc(filesize);
    Rio_readn(srcfd, srcp, filesize);
    Close(srcfd);
    Rio_writen(fd, srcp, filesize);
    Free(srcp);
}

void get_filetype(char *filename, char *filetype)
{
    if (strstr(filename, ".html"))
        strcpy(filetype, "text/html");
    else if (strstr(filename, ".gif"))
        strcpy(filetype, "image/gif");
    else if (strstr(filename, ".png"))
        strcpy(filetype, "image/png");
    else if (strstr(filename, ".jpg"))
        strcpy(filetype, "image/jpeg");
    else if (strstr(filename, ".mp4"))
        strcpy(filetype, "video/mp4");
    else
        strcpy(filetype, "text/plain");
}

void serve_dynamic(rio_t *rp, struct req *head, char *filename, char *cgiargs, char *method)
{
    char buf[MAXLINE], *emptylist[] = {NULL};
    int fd = rp->rio_fd;
    if (Fork() == 0)
    {
        if (!strcasecmp(method, "POST"))
        {
            char *CONTENT_LENGTH = find_req(head, "Content-Length");
            char *CONTENT_TYPE = find_req(head, "Content-Type");
            // printf("CONTENT_LENGTH=%s CONTENT_TYPE=%d\n", CONTENT_LENGTH, CONTENT_TYPE);
            char POST_BODY[MAXLINE];
            memset(POST_BODY, 0, MAXLINE);
            ssize_t rc = Rio_readnb(rp, POST_BODY, atoi(CONTENT_LENGTH));
            // printf("POST_BODY=%s rc=%d\n", POST_BODY, rc);
            setenv("CONTENT_LENGTH", CONTENT_LENGTH, 1);
            setenv("CONTENT_TYPE", CONTENT_TYPE, 1);
            setenv("POST_BODY", POST_BODY, 1);
        }
        setenv("QUERY_STRING", cgiargs, 1);
        setenv("REQUEST_METHOD", method, 1);
        // Dup2(fd, STDIN_FILENO);
        Dup2(fd, STDOUT_FILENO);
        Execve(filename, emptylist, environ);
    }
    Wait(NULL);
}