////////////////////////////////////////////////////////////////////////////////
/// @brief AQL, options for COLLECT
///
/// @file
///
/// DISCLAIMER
///
/// Copyright 2010-2014 triagens GmbH, Cologne, Germany
///
/// Licensed under the Apache License, Version 2.0 (the "License");
/// you may not use this file except in compliance with the License.
/// You may obtain a copy of the License at
///
///     http://www.apache.org/licenses/LICENSE-2.0
///
/// Unless required by applicable law or agreed to in writing, software
/// distributed under the License is distributed on an "AS IS" BASIS,
/// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
/// See the License for the specific language governing permissions and
/// limitations under the License.
///
/// Copyright holder is triAGENS GmbH, Cologne, Germany
///
/// @author Max Neunhoeffer
/// @author Copyright 2014, triagens GmbH, Cologne, Germany
////////////////////////////////////////////////////////////////////////////////

#include "Aql/CollectOptions.h"
#include "Basics/Exceptions.h"

using namespace triagens::aql;
using Json = triagens::basics::Json;
using JsonHelper = triagens::basics::JsonHelper;
      
////////////////////////////////////////////////////////////////////////////////
/// @brief constructor, using JSON
////////////////////////////////////////////////////////////////////////////////

CollectOptions::CollectOptions (Json const& json) {
  Json obj = json.get("collectOptions");

  method = methodFromString(JsonHelper::getStringValue(obj.json(), "method", ""));
}

////////////////////////////////////////////////////////////////////////////////
/// @brief whether or not the hash method can be used
////////////////////////////////////////////////////////////////////////////////
      
bool CollectOptions::canUseHashMethod () const {
  if (method == CollectMethod::COLLECT_METHOD_SORTED) {
    return false;
  }
  
  return true;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief convert the options to JSON
////////////////////////////////////////////////////////////////////////////////

void CollectOptions::toJson (triagens::basics::Json& json,
                                 TRI_memory_zone_t* zone) const {
  Json options;

  options = Json(Json::Object, 1)
    ("method", Json(methodToString(method)));

  json("collectOptions", options);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief get the aggregation method from a string
////////////////////////////////////////////////////////////////////////////////
          
CollectOptions::CollectMethod CollectOptions::methodFromString (std::string const& method) {
  if (method == "hash") {
    return CollectMethod::COLLECT_METHOD_HASH;
  }
  if (method == "sorted") {
    return CollectMethod::COLLECT_METHOD_SORTED;
  }

  return CollectMethod::COLLECT_METHOD_UNDEFINED;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief stringify the aggregation method
////////////////////////////////////////////////////////////////////////////////
          
std::string CollectOptions::methodToString (CollectOptions::CollectMethod method) {
  if (method == CollectMethod::COLLECT_METHOD_HASH) {
    return std::string("hash");
  }
  if (method == CollectMethod::COLLECT_METHOD_SORTED) {
    return std::string("sorted");
  }

  THROW_ARANGO_EXCEPTION_MESSAGE(TRI_ERROR_INTERNAL, "cannot stringify unknown aggregation method");
}

