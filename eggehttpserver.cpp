/*
     This file is part of libhttpserver
     Copyright (C) 2011, 2012, 2013, 2014, 2015 Sebastiano Merlino

     This library is free software; you can redistribute it and/or
     modify it under the terms of the GNU Lesser General Public
     License as published by the Free Software Foundation; either
     version 2.1 of the License, or (at your option) any later version.

     This library is distributed in the hope that it will be useful,
     but WITHOUT ANY WARRANTY; without even the implied warranty of
     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
     Lesser General Public License for more details.

     You should have received a copy of the GNU Lesser General Public
     License along with this library; if not, write to the Free Software
     Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301
     USA
*/

#include <QDebug>
#include <QByteArray>
#include <httpserver.hpp>
#include "eggehttpserver.h"
#include <iostream>

class hello_world_resource : public httpserver::http_resource {
 public:
     std::shared_ptr<httpserver::http_response> render(const httpserver::http_request&);

     std::shared_ptr<httpserver::http_response> render_POST(const httpserver::http_request &req);
     void set_some_data(const std::string &s) {data = s;}
     std::string data;
};

// Using the render method you are able to catch each type of request you receive
// Needs to be incapacitated. It's only post that we need.
//
std::shared_ptr<httpserver::http_response> hello_world_resource::render(const httpserver::http_request& req) {
    // It is possible to store data inside the resource object that can be altered through the requests
    qDebug() << "Data was: " << data << "\n";
    std::string_view datapar = req.get_arg("data");
    set_some_data(datapar == "" ? "no data passed!!!" : std::string(datapar));
    qDebug() << "Now data is:" << data << "\n";

    // It is possible to send a response initializing an http_string_response that reads the content to send in response from a string.
    return std::shared_ptr<httpserver::http_response>(new httpserver::string_response("Hello World!!!", 200));
}


std::shared_ptr<httpserver::http_response> hello_world_resource::render_POST(const httpserver::http_request& req) {
    // It is possible to store data inside the resource object that can be altered through the requests
  //  qDebug() << "Content too large: " << content_too_large() << "\n";
  //  qDebug() << "Data (POST) was: " << get_content() << "\n";
  // std::string_view datapar = req.get_arg("data");
  // set_some_data(datapar == "" ? "no data passed!!!" : std::string(datapar));
    // qDebug() << "Now data (POST) is:" << data << "\n";
    qDebug() << "Requestor:" << req.get_requestor() << "\n";

    // It is this get_content that should be further given to the GUI.
    //
    
    qDebug() << "Content: " << req.get_content() << "\n";

    // It is possible to send a response initializing an http_string_response that reads the content to send in response from a string.
    return std::shared_ptr<httpserver::http_response>(new httpserver::string_response("Hello World!!!", 200));
}

int eggehttpserver ( int port )
{
    // It is possible to create a webserver passing a great number of parameters. In this case we are just passing the port and the number of thread running.
    httpserver::webserver ws = httpserver::create_webserver(port).start_method(httpserver::http::http_utils::INTERNAL_SELECT).max_threads(5);
    // ws.content_size_limit(4096);

    hello_world_resource hwr;
    // This way we are registering the hello_world_resource to answer for the endpoint
    // "/hello". The requested method is called (if the request is a GET we call the render_GET
    // method. In case that the specific render method is not implemented, the generic "render"
    // method is called.
    // ws.register_resource("/hello", &hwr, true);
    ws.register_resource("/", &hwr, true);

    // This way we are putting the created webserver in listen. We pass true in order to have
    // a blocking call; if we want the call to be non-blocking we can just pass false to the method.
    ws.start(false);
    return 0;
}
