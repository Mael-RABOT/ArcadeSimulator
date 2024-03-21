#pragma once

#include <exception>

class ArcadeException : public std::exception {
    private:
        std::string message;

    public:
        ArcadeException(const std::string &message) : message(message) {}
        const char *what() const noexcept override { return message.c_str(); }
};