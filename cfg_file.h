/*
 * $Id$
 */


#ifndef CFG_FILE_H
#define CFG_FILE_H

#include <sys/types.h>
#ifndef OWN_QUEUE_H
#include <sys/queue.h>
#else
#include "queue.h"
#endif
#include <netinet/in.h>
#include <sys/un.h>
#include <event.h>
#include "upstream.h"
#include "memcached.h"

#define DEFAULT_BIND_PORT 768
#define MAX_MEMCACHED_SERVERS 48
#define DEFAULT_MEMCACHED_PORT 11211
/* Memcached timeouts */
#define DEFAULT_MEMCACHED_CONNECT_TIMEOUT 1000
/* Upstream timeouts */
#define DEFAULT_UPSTREAM_ERROR_TIME 10
#define DEFAULT_UPSTREAM_ERROR_TIME 10
#define DEFAULT_UPSTREAM_DEAD_TIME 300
#define DEFAULT_UPSTREAM_MAXERRORS 10

/* 1 worker by default */
#define DEFAULT_WORKERS_NUM 1

#define yyerror(fmt, ...) \
		fprintf (stderr, "Config file parse error!\non line: %d\n", yylineno); \
		fprintf (stderr, "while reading text: %s\nreason: ", yytext); \
		fprintf (stderr, fmt, ##__VA_ARGS__); \
		fprintf (stderr, "\n")
#define yywarn(fmt, ...) \
		fprintf (stderr, "Config file parse warning!\non line %d\n", yylineno); \
		fprintf (stderr, "while reading text: %s\nreason: ", yytext); \
		fprintf (stderr, fmt, ##__VA_ARGS__); \
		fprintf (stderr, "\n")


enum { VAL_UNDEF=0, VAL_TRUE, VAL_FALSE };

struct memcached_server {
	struct upstream up;
	struct in_addr addr;
	uint16_t port;
	short alive;
	short int num;
};

struct config_file {
	char *cfg_name;
	char *pid_file;
	char *temp_dir;

	char *bind_host;
	struct in_addr bind_addr;
	uint16_t bind_port;
	uint16_t bind_family;

	char no_fork;
	unsigned int workers_number;

	struct memcached_server memcached_servers[MAX_MEMCACHED_SERVERS];
	size_t memcached_servers_num;
	memc_proto_t memcached_protocol;	
	unsigned int memcached_error_time;
	unsigned int memcached_dead_time;
	unsigned int memcached_maxerrors;
	unsigned int memcached_connect_timeout;
};

int add_memcached_server (struct config_file *cf, char *str);
int parse_bind_line (struct config_file *cf, char *str);
void init_defaults (struct config_file *cfg);
void free_config (struct config_file *cfg);

int yylex (void);
int yyparse (void);
void yyrestart (FILE *);

#endif /* ifdef CFG_FILE_H */
/* 
 * vi:ts=4 
 */
