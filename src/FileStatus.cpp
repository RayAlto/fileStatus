#include "FileStatus.hpp"

void FileStatus::getStat(const std::string& fileName, struct stat& statStruct) {
    std::string absolutePath = toAbsolutePath(fileName);
    if (stat(absolutePath.c_str(), &statStruct) != 0) {
        switch (errno) {
        case EACCES:
            throw std::runtime_error("Search permission is denied for one of the directories in the path prefix of" + fileName);
            break;
        case EFAULT:
            throw std::runtime_error("Buff got a bad address");
            break;
        case ELOOP:
            throw std::runtime_error("Too many symbolic links encountered while traversing the path.");
            break;
        case ENAMETOOLONG:
            throw std::runtime_error("File name is too long.");
            break;
        case ENOENT:
            throw std::runtime_error("A component of " + absolutePath + " does not exist or is a dangling symbolic link.");
            break;
        case ENOMEM:
            throw std::runtime_error("Out of memory.");
            break;
        case ENOTDIR:
            throw std::runtime_error("A component of the path prefix of " + absolutePath + " is not a directory.");
            break;
        case EOVERFLOW:
            throw std::runtime_error("The info of " + absolutePath + " is beyond the range that can be represented.");
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
            throw std::runtime_error("Read or search permission was denied for a component of the path prefix.");
            break;
        case EIO:
            throw std::runtime_error("An I/O error occurred while reading from the filesystem.");
            break;
        case ELOOP:
            throw std::runtime_error("Too many symbolic links were encountered in translating the pathname.");
            break;
        case ENAMETOOLONG:
            throw std::runtime_error("A component of a pathname exceeded NAME_MAX characters, or an entire pathname exceeded PATH_MAX characters.");
            break;
        case ENOENT:
            throw std::runtime_error("File \"" + relativePath + "\" does not exist.");
            break;
        case ENOMEM:
            throw std::runtime_error("Out of memory.");
            break;
        case ENOTDIR:
            throw std::runtime_error("A component of the path prefix is not a directory.");
            break;
        default:
            throw std::runtime_error("Unknown error.");
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
            throw std::runtime_error("Permission to read or search a component of current directory was denied.");
            break;
        case EFAULT:
            throw std::runtime_error("Buff got a bad address.");
            break;
        case EINVAL:
            throw std::runtime_error("Marco FILENAME_MAX expands to 0.");
            break;
        case ENAMETOOLONG:
            throw std::runtime_error("The size of the null-terminated absolute pathname string exceeds PATH_MAX bytes.");
            break;
        case ENOENT:
            throw std::runtime_error("The current working directory has been unlinked.");
            break;
        case ENOMEM:
            throw std::runtime_error("Out of memory.");
            break;
        case ERANGE:
            throw std::runtime_error("The length of absolute path is too long.");
            break;
        default:
            throw std::runtime_error("Unknown error.");
            break;
        }
    }
    return currentDirectoryName;
}

dev_t FileStatus::getDeviceId() const {
    return _status.st_dev;
}

ino_t FileStatus::getInodeNumber() const {
    return _status.st_ino;
}

mode_t FileStatus::getTypeAndMode() const {
    return _status.st_mode;
}

nlink_t FileStatus::getHardLinksNumber() const {
    return _status.st_nlink;
}

uid_t FileStatus::getUid() const {
    return _status.st_uid;
}

gid_t FileStatus::getGid() const {
    return _status.st_gid;
}

off_t FileStatus::getSize() const {
    return _status.st_size;
}

blksize_t FileStatus::getBlockSize() const {
    return _status.st_blksize;
}

blkcnt_t FileStatus::getBlockCount() const {
    return _status.st_blocks;
}

time_t FileStatus::getLastAccessTimeSec() const {
    return _status.st_atim.tv_sec;
}

time_t FileStatus::getLastModificationTimeSec() const {
    return _status.st_mtim.tv_sec;
}

time_t FileStatus::getLastStatusChangeTimeSec() const {
    return _status.st_ctim.tv_sec;
}

long FileStatus::getLastAccessTimeNanoSec() const {
    return _status.st_atim.tv_nsec;
}

long FileStatus::getLastModificationTimeNanoSec() const {
    return _status.st_mtim.tv_nsec;
}

long FileStatus::getLastStatusChangeTimeNanoSec() const {
    return _status.st_ctim.tv_nsec;
}

bool FileStatus::isSocket() const {
    return S_ISSOCK(_status.st_mode);
}

bool FileStatus::isSymbolLink() const {
    return S_ISLNK(_status.st_mode);
}

bool FileStatus::isRegularFile() const {
    return S_ISREG(_status.st_mode);
}

bool FileStatus::isBlockDevice() const {
    return S_ISBLK(_status.st_mode);
}

bool FileStatus::isDirectory() const {
    return S_ISDIR(_status.st_mode);
}

bool FileStatus::isCharacterDevice() const {
    return S_ISCHR(_status.st_mode);
}

bool FileStatus::ifFIFO() const {
    return S_ISFIFO(_status.st_mode);
}

bool FileStatus::ownerHasReadPermission() const {
    return ((_status.st_mode & S_IRUSR) == S_IRUSR);
}

bool FileStatus::ownerHasWritePermission() const {
    return ((_status.st_mode & S_IWUSR) == S_IWUSR);
}

bool FileStatus::ownerHasExecutePermission() const {
    return ((_status.st_mode & S_IXUSR) == S_IXUSR);
}

bool FileStatus::groupHasReadPermission() const {
    return ((_status.st_mode & S_IRGRP) == S_IRGRP);
}

bool FileStatus::groupHasWritePermission() const {
    return ((_status.st_mode & S_IWGRP) == S_IWGRP);
}

bool FileStatus::groupHasExecutePermission() const {
    return ((_status.st_mode & S_IXGRP) == S_IXGRP);
}

bool FileStatus::othersHasReadPermission() const {
    return ((_status.st_mode & S_IROTH) == S_IROTH);
}

bool FileStatus::othersHasWritePermission() const {
    return ((_status.st_mode & S_IWOTH) == S_IWOTH);
}

bool FileStatus::othersHasExecutePermission() const {
    return ((_status.st_mode & S_IXOTH) == S_IXOTH);
}
