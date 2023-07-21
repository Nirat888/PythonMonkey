#include "include/DateType.hh"

#include "include/PyType.hh"
#include "include/TypeEnum.hh"

#include <jsapi.h>
#include <js/Date.h>

#include <Python.h>
#include <datetime.h>

DateType::DateType(PyObject *object) : PyType(object) {}

DateType::DateType(JSContext *cx, JS::HandleObject dateObj) {
  JS::Rooted<JS::ValueArray<0>> args(cx);
  JS::Rooted<JS::Value> year(cx);
  JS::Rooted<JS::Value> month(cx);
  JS::Rooted<JS::Value> day(cx);
  JS::Rooted<JS::Value> hour(cx);
  JS::Rooted<JS::Value> minute(cx);
  JS::Rooted<JS::Value> second(cx);
  JS::Rooted<JS::Value> usecond(cx);
  JS_CallFunctionName(cx, dateObj, "getFullYear", args, &year);
  JS_CallFunctionName(cx, dateObj, "getMonth", args, &month);
  JS_CallFunctionName(cx, dateObj, "getDate", args, &day);
  JS_CallFunctionName(cx, dateObj, "getHours", args, &hour);
  JS_CallFunctionName(cx, dateObj, "getMinutes", args, &minute);
  JS_CallFunctionName(cx, dateObj, "getSeconds", args, &second);
  JS_CallFunctionName(cx, dateObj, "getMilliseconds", args, &usecond);

  if (!PyDateTimeAPI) { PyDateTime_IMPORT; }
  pyObject = PyDateTime_FromDateAndTime(
    year.toNumber(), month.toNumber() + 1, day.toNumber(),
    hour.toNumber(), minute.toNumber(), second.toNumber(),
    usecond.toNumber() * 1000);
}

JSObject *DateType::toJsDate(JSContext *cx) {
  // See https://docs.python.org/3/library/datetime.html#datetime.datetime.timestamp
  PyObject *timestamp = PyObject_CallMethod(pyObject, "timestamp", NULL); // the result is in seconds
  double milliseconds = PyFloat_AsDouble(timestamp) * 1000;
  Py_DECREF(timestamp);
  return JS::NewDateObject(cx, JS::TimeClip(milliseconds));
}
