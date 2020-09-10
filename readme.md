# FileStatus

FileStatus is a C++ warp for `stat()`, `getcwd()` and `realpath()`.

## Usage

The C++17 `filesystem` does not work on one of my computer (Windows 10, MinGW-W64), so I have to use this. So if `filesystem` works on your computer, just use `filesystem`.

### Constructor

```c++
FileStatus("../config.json");
```

You can use absolute/relative path (`./`, `../` and extra `/` can be parsed correctly), but do NOT use `~` to represent the user folder, it will not work.

This method throw one of a series of exception, the important thing is if the file name does not really exists, it will throw a `DoesNotExistsError` exception

Example

```c++
#include "FileStatus.hpp"
#include <iostream>

int main(int argc, char const* argv[]) {
    std::cout << std::boolalpha
              << FileStatus("../shit").isRegularFile()
              << std::noboolalpha
              << std::endl;
    return 0;
}
```

Output

```plaintext
terminate called after throwing an instance of 'DoesNotExistsError'
  what():  Does Not Exists Error: File "../shit" does not exist.
```

### Get informations

Return value is bool type.

1. `fileStatus.isSocket()`
1. `fileStatus.isSymbolLink()`
1. `fileStatus.isRegularFile()`
1. `fileStatus.isBlockDevice()`
1. `fileStatus.isDirectory()`
1. `fileStatus.isCharacterDevice()`
1. `fileStatus.isFIFO()`
1. `fileStatus.ownerHasReadPermission()`
1. `fileStatus.ownerHasWritePermission()`
1. `fileStatus.ownerHasExecutePermission()`
1. `fileStatus.groupHasReadPermission()`
1. `fileStatus.groupHasWritePermission()`
1. `fileStatus.groupHasExecutePermission()`
1. `fileStatus.othersHasReadPermission()`
1. `fileStatus.othersHasWritePermission()`
1. `fileStatus.othersHasExecutePermission()`

Example

```c++
#include "FileStatus.hpp"
#include <iostream>

int main(int argc, char const* argv[]) {
    std::cout << std::boolalpha
              << FileStatus("../../../test").isRegularFile()
              << std::noboolalpha
              << std::endl;
    return 0;
}
```

Output

```plaintext
true
```

### Get the original data

Get the original data form `struct stat`.

1. `dev_t getDeviceId()`
1. `ino_t getInodeNumber()`
1. `mode_t getTypeAndMode()`
1. `nlink_t getHardLinksNumber()`
1. `uid_t getUid()`
1. `gid_t getGid()`
1. `off_t getSize()`
1. `blksize_t getBlockSize()`
1. `blkcnt_t getBlockCount()`
1. `time_t getLastAccessTimeSec()`
1. `time_t getLastModificationTimeSec()`
1. `time_t getLastStatusChangeTimeSec()`
1. `long getLastAccessTimeNanoSec()`
1. `long getLastModificationTimeNanoSec()`
1. `long getLastStatusChangeTimeNanoSec()`

## Exceptions

All types of exceptions are corresponding to `errno`, you can run:

```plaintext
man 3 errno
```

to get the original explanation of each type of exception.

The following are some general explanations, more precise explanations can be found in [Exceptions.hpp](https://github.com/RayAlto/fileStatus/blob/master/include/Exceptions.hpp).

| exception | why |
| --- | --- |
| `PermissionError` | Permission denied (POSIX.1-2001). |
| `FaultError` | Bad address (POSIX.1-2001). |
| `LoopError` | Too many levels of symbolic links (POSIX.1-2001). |
| `NameTooLongError` | Filename too long (POSIX.1-2001).     |
| `DoesNotExistsError` | No such file or directory (POSIX.1-2001). |
| `MemoryError` | Not enough space/cannot allocate memory (POSIX.1-2001). |
| `NotDirectoryError` | Not a directory (POSIX.1-2001). |
| `OverflowError` | Value too large to be stored in data type (POSIX.1-2001). |
| `IOError` | Input/output error (POSIX.1-2001). |
| `InvalidError` | Invalid argument (POSIX.1-2001). |
| `RangeError` | Result too large (POSIX.1, C99). |
| `UnknownError` | Other exceptions. |