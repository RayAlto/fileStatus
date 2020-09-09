#pragma once
#ifndef __EXCEPTIONS_HPP__
#define __EXCEPTIONS_HPP__

#include <exception>
#include <string>

class PermissionError : public std::exception {
public:
    PermissionError(std::string message) : _message("Permission Error: " + message) {}
    const char* what() const noexcept override {
        return _message.c_str();
    }

private:
    std::string _message;
};

class FaultError : public std::exception {
public:
    FaultError(std::string message) : _message("Fault: " + message) {}
    const char* what() const noexcept override {
        return _message.c_str();
    }

private:
    std::string _message;
};

class LoopError : public std::exception {
public:
    LoopError(std::string message) : _message("Loop Error: " + message) {}
    const char* what() const noexcept override {
        return _message.c_str();
    }

private:
    std::string _message;
};

class NameTooLongError : public std::exception {
public:
    NameTooLongError(std::string message) : _message("Name Too Long Error: " + message) {}
    const char* what() const noexcept override {
        return _message.c_str();
    }

private:
    std::string _message;
};

class DoesNotExistsError : public std::exception {
public:
    DoesNotExistsError(std::string message) : _message("Does Not Exists Error: " + message) {}
    const char* what() const noexcept override {
        return _message.c_str();
    }

private:
    std::string _message;
};

class MemoryError : public std::exception {
public:
    MemoryError(std::string message) : _message("Memory Error: " + message) {}
    const char* what() const noexcept override {
        return _message.c_str();
    }

private:
    std::string _message;
};

class NotDirectoryError : public std::exception {
public:
    NotDirectoryError(std::string message) : _message("Not Directory Error: " + message) {}
    const char* what() const noexcept override {
        return _message.c_str();
    }

private:
    std::string _message;
};

class OverflowError : public std::exception {
public:
    OverflowError(std::string message) : _message("Overflow Error: " + message) {}
    const char* what() const noexcept override {
        return _message.c_str();
    }

private:
    std::string _message;
};

class IOError : public std::exception {
public:
    IOError(std::string message) : _message("I/O Error: " + message) {}
    const char* what() const noexcept override {
        return _message.c_str();
    }

private:
    std::string _message;
};

class InvalidError : public std::exception {
public:
    InvalidError(std::string message) : _message("Invalid Error: " + message) {}
    const char* what() const noexcept override {
        return _message.c_str();
    }

private:
    std::string _message;
};

class RangeError : public std::exception {
public:
    RangeError(std::string message) : _message("Range Error: " + message) {}
    const char* what() const noexcept override {
        return _message.c_str();
    }

private:
    std::string _message;
};

class UnknownError : public std::exception {
public:
    UnknownError() {}
    const char* what() const noexcept override {
        return "Unknown Error!";
    }
};

#endif // !__EXCEPTIONS_HPP