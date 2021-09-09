//
// Created by shawnfeng on 2021/9/7.
//

#pragma once

#include <unistd.h>

namespace ucfg {
namespace internal {

// delete the target if exists, and rename the src file  to target
// return true on success, false otherwise.
static inline bool RenameFile(const std::string &src_filename,
                              const std::string &target_filename) {
  // try to delete the target file in case it already exists.
  (void)std::remove(target_filename.c_str());
  return std::rename(src_filename.c_str(), target_filename.c_str()) == 0;
}

// Return directory name from given path or empty string
// "abc/file" => "abc"
// "abc/" => "abc"
// "abc" => ""
// "abc///" => "abc//"
static inline std::string DirName(const std::string &path) {
  auto pos = path.find_last_of('/');
  return pos != std::string::npos ? path.substr(0, pos) : std::string{};
}

// Split file path is directory name and basename
static inline std::tuple<std::string, std::string> SplitFilename(
    const std::string &path) {
  using StringPair = std::tuple<std::string, std::string>;
  auto pos = path.find_last_of('/');
  if (pos != std::string::npos)
    return StringPair{path.substr(0, pos), path.substr(pos + 1)};
  else
    return StringPair{".", path};
}

// Return true if path exists (file or directory)
static inline bool PathExists(const std::string &filename) {
  if (access(filename.c_str(), R_OK | W_OK) != -1) {
    return true;
  }
  return false;
}

static inline bool GetFileModifiedTime(const std::string &filename,
                                       struct timespec *modified_time) {
  struct stat st {};
  if (stat(filename.c_str(), &st) == 0) {
    if (modified_time) {
      *modified_time = st.st_mtim;
    }
    return true;
  }
  return false;
}

static inline bool IsFileModified(const std::string &filename,
                                  const struct timespec &last_modified_time) {
  struct timespec m_time {};
  if (GetFileModifiedTime(filename, &m_time)) {
    if (last_modified_time.tv_sec != m_time.tv_sec ||
        last_modified_time.tv_nsec != m_time.tv_nsec) {
      return true;
    }
  }
  return false;
}

}  // namespace internal
}  // namespace ucfg
