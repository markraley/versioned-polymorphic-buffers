# versioned-polymorphic-buffers
Versioned Polymorphic Buffers (vpbuf) - data interchange format

Versioned Polymorphic Buffers (vpbuf) is a language, platform, and wire protocol neutral way of serializing structured data, either as flatten messages or to file. Instead of being permissive about data elements, all elements (integers, strings, vectors, maps) etc are versioned and may come in and out of scope as the version
number advances between releases.

Currently cplusplus, python, and javascript are supported using a binary wire format based on AMF3. Other formats, such as json, are intended to be added as well.


Versioning Basics - vpbuf/examples/poker
----------------------------------------

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

Pod member elements (such as version and tag above) are defined as
```
<type> <name> <lowest version supported> [<highest_version_supported>]
```

If the high version number is omitted, the range is open ended. For now, only
varints (integers) and strings are supported.

When the vpc compiler is run from the the examples/poker/rel1 the targeted
sources are built. The pathing is relative to the vpc file location, so that
the auto generated sources always go to the same places. Caution should be used,
as the specified locations and extensions will be overwritten.

```
$ vpc poker.vpc
vpc_path:
generating "./python/vp_poker/vp_poker.py" 1 1
generating "./nodejs/src/vp_poker.js" 1 1
generating "./cpp/src/vp_poker.cc" 1 1
parse succeeded, type count is: 6
```


