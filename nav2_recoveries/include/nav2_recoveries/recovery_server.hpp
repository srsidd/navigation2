// Copyright (c) 2018 Samsung Research America
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License. Reserved.


#include <chrono>
#include <string>
#include <memory>
#include <vector>

#include "nav2_util/lifecycle_node.hpp"
#include "tf2_ros/transform_listener.h"
#include "tf2_ros/create_timer_ros.h"
#include "pluginlib/class_loader.hpp"
#include "pluginlib/class_list_macros.hpp"
#include "nav2_core/recovery.hpp"

#ifndef NAV2_RECOVERIES__RECOVERY_SERVER_HPP_
#define NAV2_RECOVERIES__RECOVERY_SERVER_HPP_

namespace recovery_server
{

class RecoveryServer : public nav2_util::LifecycleNode
{
public:
  RecoveryServer();
  ~RecoveryServer();

  void loadRecoveryPlugins();

protected:
  // Implement the lifecycle interface
  nav2_util::CallbackReturn on_configure(const rclcpp_lifecycle::State & state) override;
  nav2_util::CallbackReturn on_activate(const rclcpp_lifecycle::State & state) override;
  nav2_util::CallbackReturn on_deactivate(const rclcpp_lifecycle::State & state) override;
  nav2_util::CallbackReturn on_cleanup(const rclcpp_lifecycle::State & state) override;
  nav2_util::CallbackReturn on_shutdown(const rclcpp_lifecycle::State & state) override;
  nav2_util::CallbackReturn on_error(const rclcpp_lifecycle::State & state) override;

  std::shared_ptr<tf2_ros::Buffer> tf_;
  std::shared_ptr<tf2_ros::TransformListener> transform_listener_;

  // Plugins
  std::vector<pluginlib::UniquePtr<nav2_core::Recovery>> recoveries_;
  pluginlib::ClassLoader<nav2_core::Recovery> plugin_loader_;
  std::vector<std::string> plugin_names_, plugin_types_;
};

}  // namespace recovery_server

#endif  // NAV2_RECOVERIES__RECOVERY_SERVER_HPP_
