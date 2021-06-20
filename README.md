# versioned-polymorphic-buffers
Versioned Polymorphic Buffers (vpbuf) - data interchange format

Versioned Polymorphic Buffers (vpbuf) is a language, platform, and wire protocol neutral way of serializing structured data, either as flatten messages or to file. Instead of being permissive about data elements, all elements (integers, strings, vectors, maps) etc are versioned.

Currently cplusplus, python, and javascript are supported using a binary wire format based on AMF3. Other formats, such as json, are intended to be added as well.

Please stand by for additional documentation and functional details.


An introduction
---------------

The vpc compiler takes a .vpc the data specification and generates source code
as specified in the target section into the language, versions, location, and
file extension requested. The pod keyword can be read as struct and stands for
"plain old data".

```
target
    language python 1 1 vp_poker "./python/vp_poker" py
    language javascript 1 1 vp_poker "./nodejs/src" js
    language cplusplus 1 1 vp_poker "./cpp/src" cc

pod Header
    varint version 1
    string tag 1

pod Card
    varint id 1
    string name 1

pod Deck
    vector *Card cards 1
```

Which, from the vpbuf/examples/poker/rel1 folder looks like

```
$ vpc poker.vpc
vpc_path:
generating "./python/vp_poker/vp_poker.py" 1 1
generating "./nodejs/src/vp_poker.js" 1 1
generating "./cpp/src/vp_poker.cc" 1 1
parse succeeded, type count is: 6
```


