//Copyright Grigory Ponomarenko 2016 (c)

#pragma once

#include "BalashException.h"

/* Balash exception realisation. */
BalashException::BalashException(const std::string& msg) {
  ErrorMessage = msg;
}

const char* BalashException::what() const {
  return ErrorMessage.c_str();
}