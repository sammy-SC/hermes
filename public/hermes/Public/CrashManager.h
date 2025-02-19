/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the LICENSE
 * file in the root directory of this source tree.
 */
#ifndef HERMES_PUBLIC_CRASHMANAGER_H
#define HERMES_PUBLIC_CRASHMANAGER_H

#include <cstddef>
#include <functional>

namespace hermes {
namespace vm {

/// A CrashManager provides functions that determine what memory and data is
/// included in dumps in case of crashes.
class CrashManager {
 public:
  /// CallbackKey is the type of an identifier for a callback supplied to the
  /// CrashManager.
  using CallbackKey = int;
  /// Type for the callback function invoked on crash. The fd supplied is a raw
  /// file stream an implementation should write a JSON object to.
  using CallbackFunc = std::function<void(int fd)>;

  /// Registers some memory to be included in any crash dump that occurs.
  /// \param mem A pointer to allocated memory. It must be unregistered
  /// before being freed.
  /// \param length The number of bytes the memory controls.
  virtual void registerMemory(void *mem, size_t length) = 0;

  /// Unregisters some memory from being included in any crash dump that occurs.
  virtual void unregisterMemory(void *mem) = 0;

  /// Registers custom data to be included in any crash dump that occurs.
  /// Calling \c setCustomData on the same key twice will overwrite the previous
  /// value.
  /// \param key A tag to look for in the custom data output. Distinguishes
  ///   between multiple values.
  /// \param val The value to store for the given key.
  virtual void setCustomData(const char *key, const char *val) = 0;

  /// Registers a function to be called after a crash has occurred. This
  /// function can examine memory and serialize this to a JSON output stream.
  /// Implmentations decide where the stream is routed to.
  /// \param callback A function to called after a crash.
  /// \return A CallbackKey representing the function you provided. Pass this
  ///   key into unregisterCallback when it that callback is no longer needed.
  virtual CallbackKey registerCallback(CallbackFunc callback) = 0;

  /// Unregisters a previously registered callback. After this function returns,
  /// the previously registered function will not be executed by this
  /// CrashManager during a crash.
  virtual void unregisterCallback(CallbackKey key) = 0;

  virtual ~CrashManager() {}
};

/// A CrashManager that does nothing.
class NopCrashManager final : public CrashManager {
 public:
  void registerMemory(void *, size_t) override {}
  void unregisterMemory(void *) override {}
  void setCustomData(const char *, const char *) override {}
  CallbackKey registerCallback(CallbackFunc /*callback*/) override {
    return 0;
  }
  void unregisterCallback(CallbackKey /*key*/) override {}
  ~NopCrashManager() {}
};

} // namespace vm
} // namespace hermes
#endif
