//
// Created by shawnfeng on 2021/9/8.
//

#pragma once

#include <ucfg/internal/file.h>
#include <ucfg/internal/parser.h>

#include <string>
#include <tuple>

namespace ucfg {
namespace internal {

/**
 * This class tries to ensure that the configuration will not be lost when an
 * unexpected shutdown occurs.
 *
 * The specific method is to always have at least one backup file when saving
 * files.
 *
 * Even during rename, the document of rename pointed out that old_path and
 * new_path may point to the same file, so the unexpected shutdown during rename
 * will not lose the file.
 */
class FileStorage {
 public:
  explicit FileStorage(const std::string& filename) {
    std::tie(file_directory_, file_basename_) =
        internal::SplitFilename(filename);

    auto temp_filename = TempFilename();

    // If there are only temporary files. This situation occurred when the power
    // was cut off unexpectedly during the last save.
    if (!PathExists(filename) && PathExists(temp_filename)) {
      RenameFile(temp_filename, filename);
    }
  }

  bool IsModifiedByExternal() {
    return internal::IsFileModified(Filename(), last_modified_time_);
  }

  void SaveData(const ConfigData& data) {
    auto filename = Filename();
    auto temp_filename = TempFilename();

    DumpToFile(temp_filename, data);
    RenameFile(temp_filename, filename);

    internal::GetFileModifiedTime(filename, &last_modified_time_);
  }

  ConfigData LoadData() {
    auto filename = Filename();

    auto data = ParserFile(filename);
    GetFileModifiedTime(filename, &last_modified_time_);
    return data;
  }

 private:
  std::string Filename() { return file_directory_ + "/" + file_basename_; };
  std::string TempFilename() {
    return file_directory_ + "/." + file_basename_ + ".ucfg_new";
  };
  struct timespec last_modified_time_ {};
  std::string file_directory_;
  std::string file_basename_;
};

}  // namespace internal
}  // namespace ucfg
