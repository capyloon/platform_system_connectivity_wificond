/*
 * Copyright (C) 2016 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef WIFICOND_AP_INTERFACE_IMPL_H_
#define WIFICOND_AP_INTERFACE_IMPL_H_

#include <string>
#include <vector>

#include <android-base/macros.h>
#include <wifi_system/hostapd_manager.h>
#include <wifi_system/interface_tool.h>

#include "android/net/wifi/IApInterface.h"

namespace android {
namespace wificond {

class ApInterfaceBinder;

// Holds the guts of how we control network interfaces capable of exposing an AP
// via hostapd.  Because remote processes may hold on to the corresponding
// binder object past the lifetime of the local object, we are forced to
// keep this object separate from the binder representation of itself.
class ApInterfaceImpl {
 public:
  ApInterfaceImpl(const std::string& interface_name,
                  uint32_t interface_index,
                  wifi_system::InterfaceTool* if_tool,
                  wifi_system::HostapdManager* hostapd_manager);
  ~ApInterfaceImpl();

  // Get a pointer to the binder representing this ApInterfaceImpl.
  android::sp<android::net::wifi::IApInterface> GetBinder() const;

  bool StartHostapd();
  bool StopHostapd();
  bool WriteHostapdConfig(
      const std::vector<uint8_t>& ssid,
      bool is_hidden,
      int32_t channel,
      wifi_system::HostapdManager::EncryptionType encryption_type,
      const std::vector<uint8_t>& passphrase);

 private:
  const std::string interface_name_;
  const uint32_t interface_index_;
  wifi_system::InterfaceTool* const if_tool_;
  wifi_system::HostapdManager* const hostapd_manager_;
  const android::sp<ApInterfaceBinder> binder_;

  DISALLOW_COPY_AND_ASSIGN(ApInterfaceImpl);
};

}  // namespace wificond
}  // namespace android

#endif  // WIFICOND_AP_INTERFACE_IMPL_H_