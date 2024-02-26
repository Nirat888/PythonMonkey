/**
 * @file pyTypeFactory.hh
 * @author Caleb Aikens (caleb@distributive.network), Giovanni Tedesco (giovanni@distributive.network) and Philippe Laporte (philippe@distributive.network)
 * @brief Function for wrapping arbitrary PyObjects into the appropriate PyType class, and coercing JS types to python types
 * @date 2022-08-08
 *
 * @copyright Copyright (c) 2022, 2023, 2024 Distributive Corp.
 *
 */

#ifndef PythonMonkey_PyTypeFactory_
#define PythonMonkey_PyTypeFactory_

#include "PyType.hh"

#include <jsapi.h>

#include <Python.h>


/**
 * @brief Function that takes a JS::Value and returns a corresponding PyType* object, doing shared memory management when necessary
 *
 * @param cx - Pointer to the javascript context of the JS::Value
 * @param thisObj - The JS `this` object for the value's scope
 * @param rval - The JS::Value who's type and value we wish to encapsulate
 * @return PyType* - Pointer to a PyType object corresponding to the JS::Value
 */
PyType *pyTypeFactory(JSContext *cx, JS::HandleObject thisObj, JS::HandleValue rval);

#endif