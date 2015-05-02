#ifndef PGCONNS_H
#define PGCONNS_H

const int EXIT_ERR_USAGE         = 1;
const int EXIT_ERR_MALLOC        = 2;
const int EXIT_ERR_PARSE_IP      = 3;

typedef struct conndata_S
{
    const char *conninfo;
    unsigned long elapsed;
    const char *status;
} conndata;


    

conndata *conns;


void print_usage(void);


#endif
