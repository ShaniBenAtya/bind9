/*
 * Copyright (C) 1999, 2000  Internet Software Consortium.
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

/*
 * Principal Author: Brian Wellington
 * $Id: dst_result.c,v 1.5 2000/03/23 19:48:24 halley Exp $
 */

#include <config.h>

#include <stddef.h>

#include <isc/resultclass.h>
#include <isc/once.h>
#include <isc/error.h>

#include <dst/result.h>
#include <dst/lib.h>

static char *text[DST_R_NRESULTS] = {
	"algorithm is unsupported",		/*  0 */
	"key type is unsupported",		/*  1 */
	"signature mode is unsupported",	/*  2 */
	"illegal operation for a null key",	/*  3 */
	"public key is invalid",		/*  4 */
	"private key is invalid",		/*  5 */
	"key name is too long",			/*  6 */
	"error occurred writing key to disk",	/*  7 */
	"invalid algorithm specific parameter",	/*  8 */
	"sign init failure",			/*  9 */
	"sign update failure",			/* 10 */
	"sign final failure",			/* 11 */
        "verify init failure",			/* 12 */
	"verify update failure",		/* 13 */
	"verify final failure",			/* 14 */
	"not a public key",			/* 15 */
	"not a private key",			/* 16 */
	"not a key that can compute a secret",	/* 17 */
	"failure computing a shared secret",	/* 18 */
};

#define DST_RESULT_RESULTSET			2

static isc_once_t		once = ISC_ONCE_INIT;

static void
initialize_action(void) {
	isc_result_t result;

	result = isc_result_register(ISC_RESULTCLASS_DST, DST_R_NRESULTS,
				     text, dst_msgcat, DST_RESULT_RESULTSET);
	if (result != ISC_R_SUCCESS)
		UNEXPECTED_ERROR(__FILE__, __LINE__,
				 "isc_result_register() failed: %u", result);
}

static void
initialize(void) {
	dst_lib_initmsgcat();
	RUNTIME_CHECK(isc_once_do(&once, initialize_action) == ISC_R_SUCCESS);
}

char *
dst_result_totext(isc_result_t result) {
	initialize();

	return (isc_result_totext(result));
}

void
dst_result_register(void) {
	initialize();
}
