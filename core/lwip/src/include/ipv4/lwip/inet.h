/*
 * Copyright (c) 2001-2004 Swedish Institute of Computer Science.
 * All rights reserved. 
 * 
 * Redistribution and use in source and binary forms, with or without modification, 
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission. 
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED 
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT 
 * SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT 
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING 
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
 * OF SUCH DAMAGE.
 *
 * This file is part of the lwIP TCP/IP stack.
 * 
 * Author: Adam Dunkels <adam@sics.se>
 *
 */
#ifndef __LWIP_INET_H__
#define __LWIP_INET_H__

#include "lwip/opt.h"

#ifdef __cplusplus
extern "C" {
#endif

/* For compatibility with BSD code */
#include <netinet/in.h>

#define INADDR_NONE         ((u32_t)0xffffffffUL)  /* 255.255.255.255 */
#define INADDR_LOOPBACK     ((u32_t)0x7f000001UL)  /* 127.0.0.1 */
#define INADDR_ANY          ((u32_t)0x00000000UL)  /* 0.0.0.0 */
#define INADDR_BROADCAST    ((u32_t)0xffffffffUL)  /* 255.255.255.255 */

u32_t inet_addr(const char *cp);
int inet_aton(const char *cp, struct in_addr *addr);
char *inet_ntoa(struct in_addr addr); /* returns ptr to static buffer; not reentrant! */

/* Byte order functions removed in favor of <netinet/in.h> */
#define LWIP_PLATFORM_HTONS(x) htons(x)
#define LWIP_PLATFORM_NTOHS(x) ntohs(x)
#define LWIP_PLATFORM_HTONL(x) htonl(x)
#define LWIP_PLATFORM_NTOHL(x) ntohl(x)

#ifdef __cplusplus
}
#endif

#endif /* __LWIP_INET_H__ */
