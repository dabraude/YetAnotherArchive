# YetAnotherArchive
Yet another archive format, mainly made for my own amusement, but please feel free to use

I wanted something that fufills the following:
  * Random access of indiviual files
  * Easy to modify
  * Self verification
  * Indivual files can be treated different (encryption / compression / data-recovery)
  * Free to use
  * No hard limits on space (in principle)
  * Reference implementation in C++ with C API and Python bindings for it
  
I'm sure something like this exists already, but I couldn't find it with a 5 second Google.
 

Format specification (`%d` is an integer in ascii `\0` is null termination):

  * Start of the file small header = `YAA_MAGIC_STRING|%d\0` 
    - The integer is the file format number
  
  * End of file (in order from the back, hashes are written in lower case ascii):
    - 32 characters are the `MD5` hash of the entire file other than the last 96 characters
    - 64 the size of the creator signature `HMAC-RSA-SHA256` or 0s for unsigned files, the hash covering the file other than the last 96 characters
    - A string of the form `\0%d\0` : the size of the file info JSON in ascii
    - The file info JSON
    
   * The header (a JSON):
    - Anything can be included in the header but it must include the file index, so at a minimum:
```json
{
  "files": [
   ]
}
```    

Each files entry looks like this:

```json
        {
          "name":"file name",
          "size" : 0,
          "metadata":{},
          "encryption":{},
          "compression":{},
          "recovery":{}
         }
```
Obviously the `name` and `size` need to be replaced as appropriate.
The `metadata`, `encryption`, `compression`, and `recorvery` fields are optional but if included can be used to store anything needed to read the file in your system.

The `MD5` hash show be used for only for an integrity of the data check since it is faster to compute `SHA256`. 


## Building

init & build the submodules (cJSON &  )

This will be updated if I think of anything else.






   
