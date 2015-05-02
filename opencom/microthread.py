import umicrothread
from umicrothread import MicroThread as _MicroThread
from umicrothread import *

assert umicrothread._init()

def auto(*args, **kwargs):
    def warp(func):
        return MicroThread(func.__name__, func, *args, **kwargs)
    return warp
    
_current_thread = None

def current_thread():
    return _current_thread

INVAILD = object()

class MicroThread():
    def __init__(self, name, function, *args, **kwargs):
        self._thread = _MicroThread(name, function, *args, **kwargs)
        
    def __repr__(self):
        return "<%s name=%r, function=%r>" % (type(self).__name__, self.name, self.function)
    
    def __dir__(self):
        return dir(self._thread)
    
    # __setattr__ are not exists.

    @property
    def name(self):
        return self._thread.name
    
    @property
    def function(self):
        return self._thread.function
    
    @property
    def cpu_hard_limit(self):
        return self._thread.cpu_hard_limit
    
    @cpu_hard_limit.setter
    def cpu_hard_limit(self, value):
        self._thread.cpu_hard_limit = value
    
    @property
    def cpu_soft_limit(self):
        return self._thread.cpu_soft_limit
    
    @cpu_soft_limit.setter
    def cpu_soft_limit(self, value):
        self._thread.cpu_soft_limit = value
    
    @property
    def cpu_current_executed(self):
        return self._thread.cpu_current_executed
    
    @cpu_current_executed.setter
    def cpu_current_executed(self, value):
        self._thread.cpu_current_executed = value
    
    def __call__(self, value=INVAILD):
        return self.resume(value)
    
    def resume(self, value=INVAILD):
        global _current_thread
        thread = self._thread
        
        if value is INVAILD:
            thread.send_value = None
        else:
            thread.send_value = value

        try:
            _current_thread = thread
            kind, result = thread.resume()
        finally:
            _current_thread = None
        
        return kind, result
