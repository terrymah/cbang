/******************************************************************************\

          This file is part of the C! library.  A.K.A the cbang library.

                Copyright (c) 2003-2019, Cauldron Development LLC
                   Copyright (c) 2003-2017, Stanford University
                               All rights reserved.

         The C! library is free software: you can redistribute it and/or
        modify it under the terms of the GNU Lesser General Public License
       as published by the Free Software Foundation, either version 2.1 of
               the License, or (at your option) any later version.

        The C! library is distributed in the hope that it will be useful,
          but WITHOUT ANY WARRANTY; without even the implied warranty of
        MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
                 Lesser General Public License for more details.

         You should have received a copy of the GNU Lesser General Public
                 License along with the C! library.  If not, see
                         <http://www.gnu.org/licenses/>.

        In addition, BSD licensing may be granted on a case by case basis
        by written permission from at least one of the copyright holders.
           You may request written permission by emailing the authors.

                  For information regarding this software email:
                                 Joseph Coffland
                          joseph@cauldrondevelopment.com

\******************************************************************************/

#pragma once

#include "Request.h"
#include "HTTPStatus.h"
#include "RequestMethod.h"

#include <cbang/json/Value.h>
#include <cbang/json/Sink.h>

#include <functional>


namespace cb {
  namespace Event {
    struct HTTPRequestHandler : public HTTPStatus, public RequestMethod {
      virtual ~HTTPRequestHandler() {}
      virtual bool operator()(Request &req) = 0;
    };


    typedef SmartPointer<HTTPRequestHandler> HTTPRequestHandlerPtr;


    struct HTTPRequestFunctionHandler : public HTTPRequestHandler {
      typedef std::function<bool (Request &)> callback_t;
      callback_t cb;

      HTTPRequestFunctionHandler(callback_t cb) : cb(cb) {
        if (!cb) CBANG_THROW("Callback cannot be NULL");
      }

      // From HTTPRequestHandler
      bool operator()(Request &req) {return cb(req);}
    };


    template <class T>
    struct HTTPRequestMemberHandler : public HTTPRequestHandler {
      typedef bool (T::*member_t)(Request &);
      T *obj;
      member_t member;

      HTTPRequestMemberHandler(T *obj, member_t member) :
        obj(obj), member(member) {
        if (!obj) CBANG_THROW("Object cannot be NULL");
        if (!member) CBANG_THROW("Member cannot be NULL");
      }

      // From HTTPRequestHandler
      bool operator()(Request &req) {return (*obj.*member)(req);}
    };


    template <class T>
    struct HTTPRequestRecastHandler : public HTTPRequestHandler {
      typedef bool (T::*member_t)();
      member_t member;

      HTTPRequestRecastHandler(member_t member) : member(member) {
        if (!member) CBANG_THROW("Member cannot be NULL");
      }

      // From HTTPRequestHandler
      bool operator()(Request &req) {return (req.cast<T>().*member)();}
    };


    struct HTTPRequestJSONHandler : public HTTPRequestHandler {
      virtual void operator()
      (Request &, const JSON::ValuePtr &, JSON::Sink &) = 0;

      // From HTTPRequestHandler
      bool operator()(Request &req);
    };


    template <class T>
    struct HTTPRequestJSONMemberHandler : public HTTPRequestJSONHandler {
      typedef void (T::*member_t)
        (Request &, const JSON::ValuePtr &, JSON::Sink &);
      T *obj;
      member_t member;

      HTTPRequestJSONMemberHandler(T *obj, member_t member) :
        obj(obj), member(member) {
        if (!obj) CBANG_THROW("Object cannot be NULL");
        if (!member) CBANG_THROW("Member cannot be NULL");
      }

      // From HTTPRequestJSONHandler
      void operator()(Request &req, const JSON::ValuePtr &msg,
                      JSON::Sink &sink) {(*obj.*member)(req, msg, sink);}
    };


    template <class T>
    struct HTTPRequestJSONRecastHandler : public HTTPRequestJSONHandler {
      typedef void (T::*member_t)(const JSON::ValuePtr &, JSON::Sink &);
      member_t member;

      HTTPRequestJSONRecastHandler(member_t member) : member(member) {
        if (!member) CBANG_THROW("Member cannot be NULL");
      }

      // From HTTPRequestJSONHandler
      void operator()(Request &req, const JSON::ValuePtr &msg,
                      JSON::Sink &sink) {
        (req.cast<T>().*member)(msg, sink);
      }
    };
  }
}
