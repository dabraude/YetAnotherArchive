# YetAnotherArchive
Yet another archive format, mainly made for my own amusement, but I designed it around being included into other people's software.
The goal is to have something that could be easy to distribute to customers for say license files, models, game files ... 
but also something just for keeping things together.

I wanted something that fufills the following:
  * Random access of indiviual files
  * Easy to modify
  * Self verification
  * Indivual files can be treated different (encryption / compression / data-recovery)
  * Free to use
  * No hard limits on space (in principle)
  * Reference implementation in C++ with C API and Python bindings for it
  * if no files are in the archive, the entire thing should be text
  
I'm sure something like this exists already, but I couldn't find it with a 5 second Google.
 

You may be asking about the last requirement. This is so that an empty archive it could be used a license file
if all the license info was in the archive header. Thus saving an extra file type.

Format specification:

  * Start of the file magic string and version number `YAA_MAGIC_STRING|1|` where the 1 is the format version number
  
  * End of file (in order from the back, hashes are written in lower case ascii):
    - 32 characters are the `MD5` hash of the entire file other than the last 96 characters
    - 64 the size of the creator signature `HMAC-RSA-SHA256` or 0s for unsigned files, the hash covering the file other than the last 96 characters
    - the size of the file info JSON in ascii
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
          "metadata":{
          }
         }
```
Obviously the `name` and `size` need to be replaced as appropriate.
The `metadata` is required but can be empty.

The `MD5` hash show be used for only for an integrity of the data check since it is faster to compute `SHA256`. 




## Building

init & build the submodules (cJSON &  )

This will be updated if I think of anything else.






   
