/*
 * Copyright (C) 2015 Jolla Ltd.
 * Contact: Slava Monich <slava.monich@jolla.com>
 *
 * You may use this file under the terms of BSD license as follows:
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *   1. Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright
 *      notice, this list of conditions and the following disclaimer in the
 *      documentation and/or other materials provided with the distribution.
 *   3. Neither the name of the Jolla Ltd nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef GRILIO_PRIVATE_H
#define GRILIO_PRIVATE_H

#include "grilio_request.h"
#include "grilio_channel.h"
#include "grilio_queue.h"

#define RIL_UNSOL_RIL_CONNECTED 1034

/* Byte order of the RIL payload (native?) */
#define GUINT32_FROM_RIL(x) (x) /* GUINT32_FROM_LE(x) ? */
#define GUINT32_TO_RIL(x)   (x) /* GUINT32_TO_LE(x) ? */

/*
 * 12 bytes are reserved for the packet header:
 *
 * [0] Length
 * [1] Request code
 * [2] Request id 
 */
#define GRILIO_REQUEST_HEADER_SIZE (12)

struct grilio_request {
    int refcount;
    int timeout;
    guint32 code;
    guint id;
    gint64 deadline;
    GRILIO_REQUEST_STATUS status;
    GByteArray* bytes;
    GRilIoRequest* next;
    GRilIoRequest* qnext;
    GRilIoQueue* queue;
    GRilIoChannelResponseFunc response;
    GDestroyNotify destroy;
    void* user_data;
};

void
grilio_request_unref_proc(
    gpointer data);

void
grilio_queue_remove(
    GRilIoRequest* req);

GRilIoRequest*
grilio_channel_get_request(
    GRilIoChannel* channel,
    guint id);

#endif /* GRILIO_PRIVATE_H */

/*
 * Local Variables:
 * mode: C
 * c-basic-offset: 4
 * indent-tabs-mode: nil
 * End:
 */
