#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "libpq-fe.h"
#include "pgconns.h"


void
print_usage(void)
{
    fprintf(stderr, "Usage: pgconns <conn string 1>  <conn string 2> ...\n");
    
}

long
tv2usec(struct timeval elapsed)
{
    return ((1000000L * elapsed.tv_sec) + elapsed.tv_usec);
}



void
try_connect(conndata *ci)
{
    PGconn *c;
    struct timeval s,e,diff;

    gettimeofday(&s,NULL);
    c = PQconnectdb(ci->conninfo);
    ci->status = (PQstatus(c) == CONNECTION_OK) ? "OK" : "FAILED";
    gettimeofday(&e,NULL);
    timersub(&e,&s,&diff);
    ci->elapsed=tv2usec(diff);
}

void
print_result(conndata *ci) 
{
    printf("%s : %s[%luus]  ",ci->conninfo,ci->status,ci->elapsed);
}


int 
main(int argc, char *argv[])
{
    if(argc < 2){
        print_usage();
        exit(EXIT_ERR_USAGE);
    }

    // assume all arguments are pq conninfo strings
    if ((conns = calloc(argc,sizeof(conndata))) == NULL )
        exit(EXIT_ERR_MALLOC);
    
    // initialise the connections
    for(int i = 1, x=0; i <= argc; i++,x++){
        conns[x].conninfo = argv[i];
        conns[x].elapsed = 0L;
        
    }

    // make the connections and report the times

    for (int i = 0; i < argc-1; i++){
        try_connect(&conns[i]);
    }
    

    // report the results

    for (int i = 0; i < argc-1; i++){
        print_result(&conns[i]);
    }
    printf("\n");
    
    exit(EXIT_SUCCESS);
}
