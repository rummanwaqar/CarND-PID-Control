#pragma once

#include <iostream>
#include <string>
#include <tuple>
#include <functional>
#include <uWS/uWS.h>
#include "json.hpp"

// callback function definition
// takes observations and control data
typedef std::function< std::tuple<double, double>(double cte, double speed,
  double angle) > ProcessCb;

/*
 * Interface to simulator
 */
class SimIO {
public:
  /*
   * Constructor
   * Creates uWebSocket object and defines all event handlers
   * @param port - port number for simulator uWebSocket
   * @param cb callback for processing function
   */
  SimIO(int port, ProcessCb cb);

  /*
   * Destructor
   */
  ~SimIO() = default;

  /*
   * Initializes connection to simulator and blocks it until simulator is closed.
   * event handling for simulator
   */
  void run();

private:
  /*
   * Checks if the SocketIO event has JSON data.
   * If there is data the JSON object in string format will be returned,
   * else the empty string "" will be returned.
   */
  std::string hasData(std::string s);

  // uWS object
  uWS::Hub h_;

  // connection port
  int port_;

  // processing callback
  ProcessCb callbackFunc_;
};
