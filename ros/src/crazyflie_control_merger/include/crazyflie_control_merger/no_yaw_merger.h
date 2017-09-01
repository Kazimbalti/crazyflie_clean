/*
 * Copyright (c) 2017, The Regents of the University of California (Regents).
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *    1. Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *
 *    2. Redistributions in binary form must reproduce the above
 *       copyright notice, this list of conditions and the following
 *       disclaimer in the documentation and/or other materials provided
 *       with the distribution.
 *
 *    3. Neither the name of the copyright holder nor the names of its
 *       contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS AS IS
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * Please contact the author(s) of this library if you have any questions.
 * Authors: David Fridovich-Keil   ( dfk@eecs.berkeley.edu )
 */

///////////////////////////////////////////////////////////////////////////////
//
// Class to merge control messages from two different controllers into
// a single ControlStamped message.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef CRAZYFLIE_CONTROL_MERGER_NO_YAW_MERGER_H
#define CRAZYFLIE_CONTROL_MERGER_NO_YAW_MERGER_H

#include <crazyflie_utils/types.h>
#include <crazyflie_utils/angles.h>
#include <crazyflie_msgs/ControlStamped.h>
#include <crazyflie_msgs/Control.h>
#include <crazyflie_msgs/NoYawControlStamped.h>
#include <crazyflie_msgs/NoYawControl.h>

#include <ros/ros.h>
#include <math.h>
#include <fstream>

namespace crazyflie_control_merger {

class NoYawMerger {
public:
  ~NoYawMerger() {}
  explicit NoYawMerger()
    : been_updated_(false),
      initialized_(false) {}

  // Initialize this class.
  bool Initialize(const ros::NodeHandle& n);

private:
  // Load parameters and register callbacks.
  bool LoadParameters(const ros::NodeHandle& n);
  bool RegisterCallbacks(const ros::NodeHandle& n);

  // Process an incoming reference point.
  void ControlCallback(const crazyflie_msgs::ControlStamped::ConstPtr& msg);

  // Process an incoming state measurement.
  void NoYawControlCallback(
    const crazyflie_msgs::NoYawControlStamped::ConstPtr& msg);

  // Timer callback.
  void TimerCallback(const ros::TimerEvent& e);

  // Most recent control signals.
  crazyflie_msgs::Control control_;
  crazyflie_msgs::NoYawControl no_yaw_control_;

  // Flag for whether control or no yaw control has been updated.
  bool been_updated_;

  // Timer.
  ros::Timer timer_;
  double dt_;

  // Publishers, subscribers, and topics.
  ros::Publisher merged_pub_;
  ros::Subscriber control_sub_;
  ros::Subscriber no_yaw_control_sub_;

  std::string merged_topic_;
  std::string control_topic_;
  std::string no_yaw_control_topic_;

  // Naming and initialization.
  bool initialized_;
  std::string name_;
}; //\class NoYawMerger

} //\crazyflie_control_merger

#endif