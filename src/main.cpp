/* zangoro_server - main.cpp
 *
 * creating the code for the server by modifying some tutorial code provided on
 * websocketpp's github, see license in comment below
 *
 * I will modify it a lot so not going to mark every change (license allows
 * this).
 *
 * see websocketpp/tutorials/utility_server/step2.cpp from commit f54fb06
 * https://github.com/zaphoyd/websocketpp/blob/master/tutorials
 *     utility_server/step2.cpp
 */

/*
 * Copyright (c) 2015, Peter Thorson. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the WebSocket++ Project nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL PETER THORSON BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#define ASIO_STANDALONE
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

#include "constants.h"

typedef websocketpp::server<websocketpp::config::asio> server;

static server endpoint;

// simple handler to echo message back to client for testing

void echo_handler(websocketpp::connection_hdl hdl, server::message_ptr msg) {
    // write a new message
    endpoint.send(hdl, msg->get_payload(), msg->get_opcode());
}

int main(int argc, char *argv[]) {
    (void) argc;
    (void) argv;

    // Set logging settings
    endpoint.set_error_channels(websocketpp::log::elevel::all);
    endpoint.set_access_channels(websocketpp::log::alevel::all ^
        websocketpp::log::alevel::frame_payload);

    // Initialize Asio
    endpoint.init_asio();

    // Set the default message handler to the echo handler
    endpoint.set_message_handler(echo_handler);
    
    // Listen for connection
    endpoint.listen(PORT); // see include/constants.h for PORT

    // Queues a connection accept operation
    endpoint.start_accept();

    // Start the Asio io_service run loop
    endpoint.run();
    
    return 0;
}
