# @file         helpers.py - Python->JS helpers for PythonMonkey
#               - typeof operator wrapper
#               - new operator wrapper
#
# @author       Wes Garland, wes@distributive.network
# @date         July 2023
#

from . import pythonmonkey as pm 
evalOpts = { 'filename': __file__, 'fromPythonFrame': True }

def typeof(jsval):
    """
    typeof function - wraps JS typeof operator
    """
    return pm.eval("""'use strict'; (
function pmTypeof(jsval) 
{
  return typeof(jsval)
}
    )""", evalOpts)(jsval);

def new(ctor, *args):
    """
    new function - wraps JS new operator
    """
    if (typeof(ctor) == 'string'):
        ctor = pm.eval(ctor)

    return pm.eval("""'use strict'; (
function pmNew(ctor, args) 
{
  if (arguments.length === 1)
    args = [];
  
  // work around pm list->Array bug, /wg july 2023
  if (!Array.isArray(args))
  {
    const newArgs = [];
    for (let i=0; i < args.length; i++)
      newArgs[i] = args[i];
    args = newArgs;    
  }
  return new ctor(...args);
}
    )""", evalOpts)(ctor, list(args));

# Restrict what symbols are exposed to the pythonmonkey module.
__all__ = ["new", "typeof"]
