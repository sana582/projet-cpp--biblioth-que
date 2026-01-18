#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>
#include <string>

class ProjetException : public std::runtime_error {
public:
    explicit ProjetException(const std::string& msg)
        : std::runtime_error(msg) {}
};

class InvalidArgumentException : public ProjetException {
public:
    explicit InvalidArgumentException(const std::string& msg)
        : ProjetException("Argument invalide: " + msg) {}
};

#endif
