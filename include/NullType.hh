/**
 * @file NullType.hh
 * @author Caleb Aikens (caleb@distributive.network)
 * @brief Struct for representing JS null in a python object
 * @date 2023-02-22
 *
 * @copyright Copyright (c) 2024 Distributive Corp.
 *
 */

#ifndef PythonMonkey_NullType_
#define PythonMonkey_NullType_

#include "PyType.hh"
#include "TypeEnum.hh"

/**
 * @brief This struct represents the JS null type in Python using a singleton object on the pythonmonkey module. It inherits from the PyType struct
 */
struct NullType : public PyType {
public:
  NullType();
  const TYPE returnType = TYPE::PYTHONMONKEY_NULL;
};

#endif