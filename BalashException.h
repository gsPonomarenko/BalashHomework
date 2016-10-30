//Copyright Grigory Ponomarenko 2016 (c)

#pragma once

#include <iostream>
#include <exception>
#include <string>

/* Balash exception. */
class BalashException: public std::exception {
  public:
    BalashException(const std::string& msg);
    const char* what() const;

  protected:
    std::string ErrorMessage;
};