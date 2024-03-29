/*
 * Argus-5.0 Software. Argus files - Events include files
 * Copyright (c) 2000-2024 QoSient, LLC
 * All rights reserved.
 *
 * This program is free software, released under the GNU General
 * Public License; you can redistribute it and/or modify it under the terms
 * of the GNU General Public License as published by the Free Software
 * Foundation; either version 3, or any later version.
 *
 * Other licenses are available through QoSient, LLC.
 * Inquire at info@qosient.com.
 *
 * This program is distributed WITHOUT ANY WARRANTY; without even the
 * implied warranty of * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 * Written by Carter Bullard
 * QoSient, LLC
 *
 */

/* 
 * $Id: //depot/gargoyle/argus/argus/ArgusEvents.h#4 $
 * $DateTime: 2015/04/13 00:39:28 $
 * $Change: 2980 $
 */


#ifndef ArgusEvents_h
#define ArgusEvents_h

#include <unistd.h>
#include <stdlib.h>
#include <limits.h>

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <strings.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>

#if defined(__NetBSD__)
#include <sys/sched.h>
#else
#include <sched.h>
#endif

#include <fcntl.h>
#include <signal.h>

#if defined(ARGUS_TILERA)
#include <argus_tilera.h>
#else
#include <pcap.h>
#endif

#include <argus_def.h>
#include <argus_filter.h>

#ifdef ARGUS_SASL
#include <sasl/sasl.h>
#endif

#define ARGUS_EVENT_OS_STATUS	0x00000001
#define ARGUS_ZLIB_COMPRESS	0x00000001
#define ARGUS_ZLIB_COMPRESS2	0x00000002

struct ArgusEventRecordStruct {
   struct ArgusListObjectStruct *nxt;
   struct timespec poptime, remaining;
   char *entry;
   int status, interval;
   char *method;
   char *filename;
   long long runs;
};

struct ArgusEventsStruct {
   int status;

#if defined(ARGUS_THREADS)
   pthread_t thread;
   pthread_mutex_t lock;
#endif

   struct ArgusListStruct *ArgusEventsList;
   struct ArgusListStruct *ArgusOutputList;
   struct ArgusModelerStruct *ArgusModel;
   struct ArgusSourceStruct *ArgusSrc;
};


#if defined(ArgusEvents)
struct ArgusEventsStruct *ArgusEventsTask = NULL;
void ArgusInitEvents (struct ArgusEventsStruct *);
void ArgusDeleteEvents (struct ArgusEventsStruct *);
void ArgusCloseEvents (struct ArgusEventsStruct *);
int ArgusSortEventList (const void *, const void *);
struct ArgusEventsStruct *ArgusNewEvents (void);
#else
extern struct ArgusEventsStruct *ArgusEventsTask;
extern void ArgusInitEvents (struct ArgusEventsStruct *);
extern void ArgusDeleteEvents (struct ArgusEventsStruct *);
extern void ArgusCloseEvents (struct ArgusEventsStruct *);
extern int ArgusSortEventList (const void *, const void *);
extern struct ArgusEventsStruct *ArgusNewEvents (void);
#endif
#endif /* #ifndef ArgusEvents_h */

