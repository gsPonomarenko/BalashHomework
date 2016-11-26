//Copyright Grigory Ponomarenko 2016 (c)

#include "BalashException.h"

/* Balash exception realisation. */
BalashException::BalashException(const std::string& msg) throw() {
  ErrorMessage = msg;
}

const char* BalashException::what() const throw() {
  return ErrorMessage.c_str();
}

BalashException::~BalashException() throw() {
  int i = 0;
}
