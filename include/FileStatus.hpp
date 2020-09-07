#pragma once
#ifndef __FILESTATUS_HPP__
#define __FILESTATUS_HPP__

#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include <stdexcept>

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
    dev_t getDeviceId() const;
    ino_t getInodeNumber() const;
    mode_t getTypeAndMode() const;
    nlink_t getHardLinksNumber() const;
    uid_t getUid() const;
    gid_t getGid() const;
    off_t getSize() const;
    blksize_t getBlockSize() const;
    blkcnt_t getBlockCount() const;
    time_t getLastAccessTimeSec() const;
    time_t getLastModificationTimeSec() const;
    time_t getLastStatusChangeTimeSec() const;
    long getLastAccessTimeNanoSec() const;
    long getLastModificationTimeNanoSec() const;
    long getLastStatusChangeTimeNanoSec() const;
    bool isSocket() const;
    bool isSymbolLink() const;
    bool isRegularFile() const;
    bool isBlockDevice() const;
    bool isDirectory() const;
    bool isCharacterDevice() const;
    bool ifFIFO() const;
    bool ownerHasReadPermission() const;
    bool ownerHasWritePermission() const;
    bool ownerHasExecutePermission() const;
    bool groupHasReadPermission() const;
    bool groupHasWritePermission() const;
    bool groupHasExecutePermission() const;
    bool othersHasReadPermission() const;
    bool othersHasWritePermission() const;
    bool othersHasExecutePermission() const;
};

#endif // !__FILESTATUS_HPP__