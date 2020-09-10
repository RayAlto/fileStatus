#pragma once
#ifndef __FILESTATUS_HPP__
#define __FILESTATUS_HPP__

#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>

#include "Exceptions.hpp"

class FileStatus {
private:
    std::string _fileName;
    struct stat _status;

protected:
    static void getStat(const std::string&, struct stat&);

public:
    FileStatus(const std::string&);
    static std::string toAbsolutePath(const std::string&);
    static std::string getCurrentDirectoryName();
    dev_t getDeviceId() const noexcept;
    ino_t getInodeNumber() const noexcept;
    mode_t getTypeAndMode() const noexcept;
    nlink_t getHardLinksNumber() const noexcept;
    uid_t getUid() const noexcept;
    gid_t getGid() const noexcept;
    off_t getSize() const noexcept;
    blksize_t getBlockSize() const noexcept;
    blkcnt_t getBlockCount() const noexcept;
    time_t getLastAccessTimeSec() const noexcept;
    time_t getLastModificationTimeSec() const noexcept;
    time_t getLastStatusChangeTimeSec() const noexcept;
    long getLastAccessTimeNanoSec() const noexcept;
    long getLastModificationTimeNanoSec() const noexcept;
    long getLastStatusChangeTimeNanoSec() const noexcept;
    bool isSocket() const noexcept;
    bool isSymbolLink() const noexcept;
    bool isRegularFile() const noexcept;
    bool isBlockDevice() const noexcept;
    bool isDirectory() const noexcept;
    bool isCharacterDevice() const noexcept;
    bool isFIFO() const noexcept;
    bool ownerHasReadPermission() const noexcept;
    bool ownerHasWritePermission() const noexcept;
    bool ownerHasExecutePermission() const noexcept;
    bool groupHasReadPermission() const noexcept;
    bool groupHasWritePermission() const noexcept;
    bool groupHasExecutePermission() const noexcept;
    bool othersHasReadPermission() const noexcept;
    bool othersHasWritePermission() const noexcept;
    bool othersHasExecutePermission() const noexcept;
};

#endif // !__FILESTATUS_HPP__