/* Copyright (C) 2015-2019, Wazuh Inc.
 * Copyright (C) 2009 Trend Micro Inc.
 * All right reserved.
 *
 * This program is a free software; you can redistribute it
 * and/or modify it under the terms of the GNU General Public
 * License (version 2) as published by the FSF - Free Software
 * Foundation
 */

#ifndef __SHA1_OP_H
#define __SHA1_OP_H

#include <sys/types.h>

typedef char os_sha1[65];

int OS_SHA1_File(const char *fname, os_sha1 output, int mode) __attribute((nonnull));
int OS_SHA1_Str(const char *str, ssize_t length, os_sha1 output) __attribute((nonnull));
int OS_SHA1_Str2(const char *str, ssize_t length, os_sha1 output) __attribute((nonnull));

/**
 * @brief Get the hexadecimal result of a SHA-1 digest
 *
 * @param digest[in] Binary SHA-1 digest.
 * @param output[out] Output string.
 */
void OS_SHA1_Hexdigest(const unsigned char * digest, os_sha1 output);

#endif
