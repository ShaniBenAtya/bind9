/*
 * Copyright (C) 1998  Internet Software Consortium.
 * 
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS" AND INTERNET SOFTWARE CONSORTIUM DISCLAIMS
 * ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL INTERNET SOFTWARE
 * CONSORTIUM BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 * DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 * PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS
 * ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
 * SOFTWARE.
 */

#include <config.h>

#include <errno.h>
#include <string.h>

#include <isc/condition.h>
#include <isc/error.h>

isc_result_t
isc_condition_waituntil(isc_condition_t *c, isc_mutex_t *m, isc_time_t *t)
{
	int presult;
	struct timespec ts;

	ts.tv_sec = t->seconds;
	ts.tv_nsec = t->nanoseconds;
	presult = pthread_cond_timedwait(c, m, &ts);
	if (presult == 0)
		return (ISC_R_SUCCESS);
	if (presult == ETIMEDOUT)
		return (ISC_R_TIMEDOUT);

	UNEXPECTED_ERROR(__FILE__, __LINE__,
			 "pthread_cond_timedwait() returned %s",
			 strerror(presult));
	return (ISC_R_UNEXPECTED);
}
