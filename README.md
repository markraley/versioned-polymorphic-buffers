# versioned-polymorphic-buffers

Versioned Polymorphic Buffers (vpbuf) - data interchange format

Versioned Polymorphic Buffers (vpbuf) is a language, platform, and wire protocol neutral way of serializing structured data, either as flatten messages or to file. Instead of being permissive about data elements, all elements have a version range assiged to them and may come in and out of scope as the version numbers advance between releases.

Currently cplusplus, python, and javascript are supported using a binary wire format based on AMF3. Another format, such as json, is intended to be implemented.

## Basics - Language Interoperability - vpbuf/examples/poker/rel1

The vpc compiler takes a data specification in vpc format (introduced here) and from that generates source code in the target section into the language, version range, location, and file extension specified. The pod keyword can be read as struct and stands for "plain old data".

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

Simple pod members (string and varint types above) are defined as

```
<type> <name> <lowest version supported> [<highest version supported>]
```

Container pod members, such as vector and map, have additional parameters that will be covered in more detail later. They also have the same versioning parameters. If the high version number is omitted, the range is open ended.

When the vpc compiler is run from the the examples/poker the targeted
sources are built. The pathing is relative to the vpc file location, so that
the auto generated sources always go to the same places. Caution should be used,
as the specified locations and extensions will be overwritten. A nonsense extension can be used during development, and a target can be disabled by placing a minus sign '-' directly in front of the keyword 'language' with no spaces.

```
$ vpc rel1/poker.vpc
vpc_path: rel1/
generating "rel1/./python/vp_poker/vp_poker.py" 1 1
generating "rel1/./nodejs/src/vp_poker.js" 1 1
generating "rel1/./cpp/src/vp_poker.cc" 1 1
parse succeeded, type count is: 6
```
Thus we can then demonstrate language interoperability with the stack and draw programs from 3 different languages.  The script run_r1.sh stacks a deck with a few cards from each different program language implemented and removes them with the others.

```
$ ./run_r1.sh
-------
[vrange=1:1, python] STACK 4 cards
write: t.dat, version=1, cards=4, bytes=93
[vrange=1:1, nodejs] DRAW 2 cards
read: t.dat, version=1, cards=4, bytes=93
card pop: Four of Diamonds Three of Diamonds
write: t.dat, version=1, cards=2, bytes=52
cards left 2
[vrange=1:1, cpp] DRAW 2 cards
read: t.dat, version= 1, cards=2, bytes=52
card pop: Two of Diamonds Ace of Diamonds
write: t.dat, version=1, cards=0, bytes=14
cards left 0

-------
[vrange=1:1, nodejs] STACK 7 cards
write: t.dat, version=1, cards=7, bytes=153
[vrange=1:1, cpp] DRAW 4 cards
read: t.dat, version= 1, cards=7, bytes=153
card pop: Seven of Diamonds Six of Diamonds Five of Diamonds Four of Diamonds
write: t.dat, version=1, cards=3, bytes=73
cards left 3
[vrange=1:1, python] DRAW 3 cards
read: t.dat, version=1, cards=3, bytes=73
card pop: Three of Diamonds Two of Diamonds Ace of Diamonds
write: t.dat, version=1, cards=0, bytes=14
cards left 0

-------
[vrange=1:1, cpp] STACK 5 cards
write: t.dat, version=1, cards=5, bytes=113
[vrange=1:1, python] DRAW 3 cards
read: t.dat, version=1, cards=5, bytes=113
card pop: Five of Diamonds Four of Diamonds Three of Diamonds
write: t.dat, version=1, cards=2, bytes=52
cards left 2
[vrange=1:1, nodejs] DRAW 2 cards
read: t.dat, version=1, cards=2, bytes=52
card pop: Two of Diamonds Ace of Diamonds
write: t.dat, version=1, cards=0, bytes=14
cards left 0
```

Each implementation consists of the generated sources plus a persist source file that with user defined types and some other boiler plate code. Bringing up all three persist.<language extension> files and looking at them together may prove interesting.

## Version Interoperability - vpbuf/examples/poker/rel2

Now let's advance the version number with a few simple changes.

```
target
    language python 1 2 vp_poker "./python/vp_poker" py
    language javascript 2 2 vp_poker "./nodejs/src" js
    language cplusplus 1 2 vp_poker "./cpp/src" cc

pod Header
    varint version 1
    string tag 1

pod Card
    varint id 1
    string name 1 1

pod Deck
    vector *Card cards 1

```

We've made the name field obsolete by adding a "highest number of 1", and we've advanced the language highest version target specifier to "2". For javascript, we've raised the lowest version as well to demonstrate version out of range errors.

```
-------
[vrange=1:1, nodejs] STACK 7 cards
write: t.dat, version=1, cards=7, bytes=153
[vrange=1:2, cpp] DRAW 4 cards
read: t.dat, version= 1, cards=7, bytes=153
card pop: Seven of Diamonds Six of Diamonds Five of Diamonds Four of Diamonds
write: t.dat, version=2, cards=3, bytes=20
cards left 3
[vrange=1:2, python] DRAW 3 cards
read: t.dat, version=2, cards=3, bytes=20
card pop: Three of Diamonds Two of Diamonds Ace of Diamonds
write: t.dat, version=2, cards=0, bytes=14
cards left 0
-------
[vrange=1:2, python] STACK 4 cards
write: t.dat, version=2, cards=4, bytes=22
[vrange=1:1, nodejs] DRAW 2 cards
version mismatch
[vrange=1:2, cpp] DRAW 2 cards
read: t.dat, version= 2, cards=4, bytes=22
card pop: Four of Diamonds Three of Diamonds
write: t.dat, version=2, cards=2, bytes=18
cards left 2
-------
[vrange=1:2, cpp] STACK 5 cards
write: t.dat, version=2, cards=5, bytes=24
[vrange=1:2, python] DRAW 3 cards
read: t.dat, version=2, cards=5, bytes=24
card pop: Five of Diamonds Four of Diamonds Three of Diamonds
write: t.dat, version=2, cards=2, bytes=18
cards left 2
[vrange=2:2, nodejs] DRAW 2 cards
read: t.dat, version=2, cards=2, bytes=18
card pop: Two of Diamonds Ace of Diamonds
write: t.dat, version=2, cards=0, bytes=14
cards left 0
```

### TODO

    complete map implentation with coverage test
    complete uno polymorphism example
    scale into more translation units before adding additional languages
    add alternative wire protocol (json?)


