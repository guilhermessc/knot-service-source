/*
 * This file is part of the KNOT Project
 *
 * Copyright (c) 2015, CESAR. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *    * Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *    * Redistributions in binary form must reproduce the above copyright
 *      notice, this list of conditions and the following disclaimer in the
 *      documentation and/or other materials provided with the distribution.
 *    * Neither the name of the CESAR nor the
 *      names of its contributors may be used to endorse or promote products
 *      derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL CESAR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

typedef struct {
	char *data;
	size_t size;
} json_raw_t;

/* Node operations */
struct proto_ops {
	const char *name;
	unsigned int source_id;
	int (*probe) (const char *host, unsigned int port);
	void (*remove) (void);

	/* Abstraction for connect & close/sign-off */
	int (*connect) (void);
	void (*close) (int sock);

	/* Abstraction for session establishment or registration */
	int (*mknode) (int sock, const char *owner_uuid, json_raw_t *json);
	int (*signin) (int sock, const char *uuid, const char *token,
							json_raw_t *json);
	int (*rmnode)(int sock, const char *uuid, const char *token,
							json_raw_t *jbuf);
	/* Abstraction for device data */
	int (*schema) (int sock, const char *uuid, const char *token,
					const char *jreq, json_raw_t *json);
	int (*data) (int sock, const char *uuid, const char *token,
					const char *jreq, json_raw_t *jbuf);
};

/*
 * Watch that polls or monitors the cloud to check if "CONFIG" changed or
 * "SET DATA".
 */
unsigned int proto_register_watch(int proto_sock, const char *uuid,
				const char *token, void (*proto_watch_cb)
				(json_raw_t, void *), void *user_data);

void proto_unregister_watch(unsigned int source_id);
