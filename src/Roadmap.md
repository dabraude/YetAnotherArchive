# MVP

* add fields to header 
    * simple string fields
    * cjson objects
    * json string fields

* add entities
* load entities
* signing
* Working with in memory version


# Longer term todos:

* C++ reference implementation with C Api
    * Set up testing
    * Set up Doxygen
    * Linting
    * Get the documentation up
    * Mutex locking for io
    * Remove required OpenSSL dependency - still leave in support for speed

* Python 3 bindings
    * Deploy into pip
    * Directly pickle into / out of .yaa files
    * Numpy save and load
    * Numpy memmap directly into file

* Other language bindings
    * Node.js
    * Javascript web
    * Java
