/*   $OSSEC, read_snortfull.c, v0.2, 2005/04/04, Daniel B. Cid$   */

/* Copyright (C) 2003,2004,2005 Daniel B. Cid <dcid@ossec.net>
 * All right reserved.
 *
 * This program is a free software; you can redistribute it
 * and/or modify it under the terms of the GNU General Public
 * License (version 2) as published by the FSF - Free Software
 * Foundation
 */

/* Read the snort full log */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "headers/debug_op.h"
#include "headers/mq_op.h"
#include "headers/defs.h"
#include "logcollector.h"

#include "error_messages/error_messages.h"


/* Read snort_full/barnyard full logs */
void *read_snortfull(int pos, int *rc)
{
    int i=0,frst=0;
    int c;
    char str[OS_MAXSTR];

    short int _bg = 0;
    short int _nl = 0;
    short int _igspace = 0;
    short int _ignewline = 0; /* To deal with barnyard dump output */

    memset(str,'\0',OS_MAXSTR); 	/* Cleaning the string */

    while((c = fgetc(logr[pos].fp)) != EOF)
    {
        if((_ignewline == 1)&&(c != '\n'))
            continue;
        if((_ignewline == 1)&&(c == '\n'))
        {
            if((c = fgetc(logr[pos].fp)) == '=')
            {
                /* Barnyard bad output */
                _bg=0;
                _nl=0;
                _igspace=0;
                _ignewline=0;
                i=0;
                memset(str,'\0',OS_MAXSTR);
                frst=1;
                continue;
            }
            else
                fputc(c,logr[pos].fp);
            _ignewline=2;
        }

        if((_igspace == 1) && (c != ' '))
            continue;

        if((_igspace == 1) && (c == ' '))
            _igspace=2;

        if((_bg == 0) && (c == '[') && 
                ((c = fgetc(logr[pos].fp)) == '*') &&
                ((c = fgetc(logr[pos].fp)) == '*') &&
                ((c = fgetc(logr[pos].fp)) == ']') &&
                ((c = fgetc(logr[pos].fp)) == ' ') &&
                ((c = fgetc(logr[pos].fp)) == '['))
        {
            strcpy(str,"[**] [");
            i=6;
            _bg=1;
            continue;
        }
        else if((_bg == 1) && (c == '\n') && (i < OS_MAXSTR) )
        {
            _nl++;
            if(_nl == 1)
            {
                if(str[i-1] != ']')
                {
                    merror("%s: Bad formated snort full file",ARGV0);
                    *rc = ftell(logr[pos].fp);
                    return(NULL);
                }
                str[i]=' ';
                i++;
                continue;
            }
            else if((_nl == 2) && (_igspace == 0))
            {
                if((_ignewline == 0)&&((c = fgetc(logr[pos].fp)) == 'E'))
                {
                    _ignewline=1;
                    _igspace=1;
                }
                else
                {		
                    _igspace=1;
                    fputc(c,logr[pos].fp);
                }

                continue;
            }
        }

        else if(_nl >= 3 || i >= OS_MAXSTR)
        {
            str[i]='\0';

            if(SendMSG(logr_queue,str,logr[pos].file,
                       logr[pos].logformat, LOCALFILE_MQ) < 0)
            {
                merror(QUEUE_SEND, ARGV0);
                if((logr_queue = StartMQ(DEFAULTQPATH,WRITE)) < 0)
                {
                    ErrorExit(QUEUE_FATAL, ARGV0, DEFAULTQPATH);
                }
            }
            i = 0;
            frst = 1;
            _nl = 0;
            _bg = 0;
            _igspace = 0;
            _ignewline = 0;
            memset(str,'\0',OS_MAXSTR);

            frst=1;
            continue;
        }

        if(_bg == 1)
        {
            str[i]=c;
            i++;
        }
    }

    if(frst == 1)
    {
        *rc = 0;
    }

    else
    {
        *rc = ftell(logr[pos].fp);
    }
    
    return(NULL);

}

/* EOF */
