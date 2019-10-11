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
  
  * End of file (in order from the back:
    - 32 characters are the MD5 hash of the entire file except the last the hash itself written in Ascii
    - A string of the form `\0%d\0` : the size of the creator signature (can be zero if there won't be a signature)
    - The creator signature - Either `HMAC-RIPEMD-160` over everything up to here or ommited if the creator signature size is 0. 
    - A string of the form `\0%d\0` : the size of the header in ASCII
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
          "size" : %d,
          "metadata":{},
          "encryption":{},
          "compression":{},
          "recovery":{}
         }
```

The `metadata`, `encryption`, `compression`, and `recorvery` fields are optional but if included can be used to store anything needed to read the file in your system.

This will be updated if I think of anything else.






   
