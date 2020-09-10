#include "FileStatus.hpp"

void FileStatus::getStat(const std::string& fileName, struct stat& statStruct) {
    std::string absolutePath = toAbsolutePath(fileName);
    if (stat(absolutePath.c_str(), &statStruct) != 0) {
        switch (errno) {
        case EACCES:
            throw PermissionError("Search permission is denied for one of the directories in the path prefix of" + fileName);
            break;
        case EFAULT:
            throw FaultError("Buff got a bad address");
            break;
        case ELOOP:
            throw LoopError("Too many symbolic links encountered while traversing the path.");
            break;
        case ENAMETOOLONG:
            throw NameTooLongError("File name is too long.");
            break;
        case ENOENT:
            throw DoesNotExistsError("A component of " + absolutePath + " does not exist or is a dangling symbolic link.");
            break;
        case ENOMEM:
            throw MemoryError("Out of memory.");
            break;
        case ENOTDIR:
            throw NotDirectoryError("A component of the path prefix of " + absolutePath + " is not a directory.");
            break;
        case EOVERFLOW:
            throw OverflowError("The info of " + absolutePath + " is beyond the range that can be represented.");
            break;
        }
    }
}

FileStatus::FileStatus(const std::string& fileName) {
    getStat(fileName, _status);
}

std::string FileStatus::toAbsolutePath(const std::string& relativePath) {
    char absolutePath[PATH_MAX];
    if (realpath(relativePath.c_str(), absolutePath) == NULL) {
        switch (errno) {
        case EACCES:
            throw PermissionError("Read or search permission was denied for a component of the path prefix.");
            break;
        case EIO:
            throw IOError("An I/O error occurred while reading from the filesystem.");
            break;
        case ELOOP:
            throw LoopError("Too many symbolic links were encountered in translating the pathname.");
            break;
        case ENAMETOOLONG:
            throw NameTooLongError("A component of a pathname exceeded NAME_MAX characters, or an entire pathname exceeded PATH_MAX characters.");
            break;
        case ENOENT:
            throw DoesNotExistsError("File \"" + relativePath + "\" does not exist.");
            break;
        case ENOMEM:
            throw MemoryError("Out of memory.");
            break;
        case ENOTDIR:
            throw NotDirectoryError("A component of the path prefix is not a directory.");
            break;
        default:
            throw UnknownError();
            break;
        }
    }
    return absolutePath;
}

std::string FileStatus::getCurrentDirectoryName() {
    char currentDirectoryName[FILENAME_MAX];
    if (getcwd(currentDirectoryName, sizeof(currentDirectoryName)) == NULL) {
        switch (errno) {
        case EACCES:
            throw PermissionError("Permission to read or search a component of current directory was denied.");
            break;
        case EFAULT:
            throw FaultError("Buff got a bad address.");
            break;
        case EINVAL:
            throw InvalidError("Marco FILENAME_MAX expands to 0.");
            break;
        case ENAMETOOLONG:
            throw NameTooLongError("The size of the null-terminated absolute pathname string exceeds PATH_MAX bytes.");
            break;
        case ENOENT:
            throw DoesNotExistsError("The current working directory has been unlinked.");
            break;
        case ENOMEM:
            throw MemoryError("Out of memory.");
            break;
        case ERANGE:
            throw RangeError("The length of absolute path is too long.");
            break;
        default:
            throw UnknownError();
            break;
        }
    }
    return currentDirectoryName;
}

dev_t FileStatus::getDeviceId() const noexcept {
    return _status.st_dev;
}

ino_t FileStatus::getInodeNumber() const noexcept {
    return _status.st_ino;
}

mode_t FileStatus::getTypeAndMode() const noexcept {
    return _status.st_mode;
}

nlink_t FileStatus::getHardLinksNumber() const noexcept {
    return _status.st_nlink;
}

uid_t FileStatus::getUid() const noexcept {
    return _status.st_uid;
}

gid_t FileStatus::getGid() const noexcept {
    return _status.st_gid;
}

off_t FileStatus::getSize() const noexcept {
    return _status.st_size;
}

blksize_t FileStatus::getBlockSize() const noexcept {
    return _status.st_blksize;
}

blkcnt_t FileStatus::getBlockCount() const noexcept {
    return _status.st_blocks;
}

time_t FileStatus::getLastAccessTimeSec() const noexcept {
    return _status.st_atim.tv_sec;
}

time_t FileStatus::getLastModificationTimeSec() const noexcept {
    return _status.st_mtim.tv_sec;
}

time_t FileStatus::getLastStatusChangeTimeSec() const noexcept {
    return _status.st_ctim.tv_sec;
}

long FileStatus::getLastAccessTimeNanoSec() const noexcept {
    return _status.st_atim.tv_nsec;
}

long FileStatus::getLastModificationTimeNanoSec() const noexcept {
    return _status.st_mtim.tv_nsec;
}

long FileStatus::getLastStatusChangeTimeNanoSec() const noexcept {
    return _status.st_ctim.tv_nsec;
}

bool FileStatus::isSocket() const noexcept {
    return S_ISSOCK(_status.st_mode);
}

bool FileStatus::isSymbolLink() const noexcept {
    return S_ISLNK(_status.st_mode);
}

bool FileStatus::isRegularFile() const noexcept {
    return S_ISREG(_status.st_mode);
}

bool FileStatus::isBlockDevice() const noexcept {
    return S_ISBLK(_status.st_mode);
}

bool FileStatus::isDirectory() const noexcept {
    return S_ISDIR(_status.st_mode);
}

bool FileStatus::isCharacterDevice() const noexcept {
    return S_ISCHR(_status.st_mode);
}

bool FileStatus::isFIFO() const noexcept {
    return S_ISFIFO(_status.st_mode);
}

bool FileStatus::ownerHasReadPermission() const noexcept {
    return ((_status.st_mode & S_IRUSR) == S_IRUSR);
}

bool FileStatus::ownerHasWritePermission() const noexcept {
    return ((_status.st_mode & S_IWUSR) == S_IWUSR);
}

bool FileStatus::ownerHasExecutePermission() const noexcept {
    return ((_status.st_mode & S_IXUSR) == S_IXUSR);
}

bool FileStatus::groupHasReadPermission() const noexcept {
    return ((_status.st_mode & S_IRGRP) == S_IRGRP);
}

bool FileStatus::groupHasWritePermission() const noexcept {
    return ((_status.st_mode & S_IWGRP) == S_IWGRP);
}

bool FileStatus::groupHasExecutePermission() const noexcept {
    return ((_status.st_mode & S_IXGRP) == S_IXGRP);
}

bool FileStatus::othersHasReadPermission() const noexcept {
    return ((_status.st_mode & S_IROTH) == S_IROTH);
}

bool FileStatus::othersHasWritePermission() const noexcept {
    return ((_status.st_mode & S_IWOTH) == S_IWOTH);
}

bool FileStatus::othersHasExecutePermission() const noexcept {
    return ((_status.st_mode & S_IXOTH) == S_IXOTH);
}
