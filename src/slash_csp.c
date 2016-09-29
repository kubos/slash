/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2014-2016 Satlab ApS <satlab@satlab.com>
 * Copyright (c) 2016 Space Inventor ApS
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <csp/csp.h>
#include <slash/slash.h>

static int slash_csp_ping(struct slash *slash)
{
	if ((slash->argc <= 1) || (slash->argc > 4))
		return SLASH_EUSAGE;

	unsigned int node = atoi(slash->argv[1]);

	unsigned int size = 1;
	if (slash->argc >= 3)
		size = atoi(slash->argv[2]);

	unsigned int timeout = 1000;
	if (slash->argc >= 4)
		timeout = atoi(slash->argv[3]);

	slash_printf(slash, "Ping node %u size %u timeout %u: ", node, size, timeout);

	int result = csp_ping(node, timeout, size, CSP_SO_NONE);

	if (result >= 0) {
		slash_printf(slash, "Reply in %d [ms]\n", result);
	} else {
		slash_printf(slash, "No reply\n");
	}

	return SLASH_SUCCESS;
}

slash_command(ping, slash_csp_ping, "<node> [size] [timeout]", "Ping a system");