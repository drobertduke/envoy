#pragma once

#include "conn_manager_impl.h"

#include "envoy/http/header_map.h"
#include "envoy/network/connection.h"

namespace Http {

/**
 * Connection manager utilities split out for ease of testing.
 */
class ConnectionManagerUtility {
public:
  static uint64_t generateStreamId(const Router::Config& route_table,
                                   Runtime::RandomGenerator& random_generator);

  static void mutateRequestHeaders(Http::HeaderMap& request_headers,
                                   Network::Connection& connection, ConnectionManagerConfig& config,
                                   Runtime::RandomGenerator& random, Runtime::Loader& runtime);

  static void mutateResponseHeaders(Http::HeaderMap& response_headers,
                                    const Http::HeaderMap& request_headers,
                                    ConnectionManagerConfig& config);

  static bool shouldTraceRequest(const Http::AccessLog::RequestInfo& request_info,
                                 const Optional<TracingConnectionManagerConfig>& config);

private:
  static bool isTraceableFailure(const Http::AccessLog::RequestInfo& request_info);

  // NOTE: This is used for stable randomness in the case where the route table does not use any
  //       runtime rules. If runtime rules are used, we use true randomness which is slower but
  //       provides behavior that most consumers would expect.
  static std::atomic<uint64_t> next_stream_id_;
};

} // Http
