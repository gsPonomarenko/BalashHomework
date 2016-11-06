//Copyright Grigory Ponomarenko 2016 (c)

#pragma once

#include <iostream>
#include <exception>
#include <string>

/* Balash exception. */
class BalashException: public std::exception {
  public:
    BalashException(const std::string& msg) throw();
    virtual const char* what() const throw();
    ~BalashException() throw();

  protected:
    std::string ErrorMessage;
};
