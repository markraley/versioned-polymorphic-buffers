# versioned-polymorphic-buffers

Versioned Polymorphic Buffers (vpbuf) - data interchange format

Versioned Polymorphic Buffers (vpbuf) is a language and platform neutral way of serializing structured data, either as flatten messages or to file. All data elements have a version range assigned to them and therefore may come in and out of scope as the version numbers are advanced between releases.

Advanced protocol design features such as continuous structure reordering and salted data creation/validation are demonstrated.

Currently cplusplus, python, and javascript are supported using a binary wire format based on a subset of AMF3.

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

Simple pod members types, such as string and varint, are defined as

```
<type> <name> <lowest version supported> [<highest version supported>]
```

Container pod members, such as vector and map, have additional parameters that will be covered in more detail later. They also have the same versioning parameters - the vrange. If the high version number is omitted, the vrange is open ended. If a second version number is added on the line, the second one is the highest version that carries that data element and the vrange is closed.

When the vpc compiler is run from the the examples/poker the targeted
sources are generated. The pathing is relative to the vpc file location, so that
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
Examples 1, 2 and 3 demonstrate language interoperability with the stack and draw programs from 3 different languages which depend on the vpc generated sources. The script run_r1.sh stacks a deck with a few cards from each different program language implemented and removes them with the other implementations. The vrange is 1-1 in all example output, which means the lowest and highest supported versions are 1 and 1 respectively.

```
$ ./run_r1.sh
----- Example 1 -----
[vrange=1-1, python] STACK 4 cards
write: t.dat, version=1, cards=4, bytes=93
[vrange=1-1, nodejs] DRAW 2 cards
read: t.dat, version=1, cards=4, bytes=93
card pop: Four of Diamonds Three of Diamonds
write: t.dat, version=1, cards=2, bytes=52
cards left 2
[vrange=1-1, cpp] DRAW 2 cards
read: t.dat, version= 1, cards=2, bytes=52
card pop: Two of Diamonds Ace of Diamonds
write: t.dat, version=1, cards=0, bytes=14
cards left 0

----- Example 2 -----
[vrange=1-1, nodejs] STACK 7 cards
write: t.dat, version=1, cards=7, bytes=153
[vrange=1-1, cpp] DRAW 4 cards
read: t.dat, version= 1, cards=7, bytes=153
card pop: Seven of Diamonds Six of Diamonds Five of Diamonds Four of Diamonds
write: t.dat, version=1, cards=3, bytes=73
cards left 3
[vrange=1-1, python] DRAW 3 cards
read: t.dat, version=1, cards=3, bytes=73
card pop: Three of Diamonds Two of Diamonds Ace of Diamonds
write: t.dat, version=1, cards=0, bytes=14
cards left 0

----- Example 3 -----
[vrange=1-1, cpp] STACK 5 cards
write: t.dat, version=1, cards=5, bytes=113
[vrange=1-1, python] DRAW 3 cards
read: t.dat, version=1, cards=5, bytes=113
card pop: Five of Diamonds Four of Diamonds Three of Diamonds
write: t.dat, version=1, cards=2, bytes=52
cards left 2
[vrange=1-1, nodejs] DRAW 2 cards
read: t.dat, version=1, cards=2, bytes=52
card pop: Two of Diamonds Ace of Diamonds
write: t.dat, version=1, cards=0, bytes=14
cards left 0
```

Each implementation consists of the generated sources plus a persist source file that with user defined types and some other boiler plate code. Bringing up all three persist files and reviewing them side by side si recommended.

## Version Interoperability - vpbuf/examples/poker/rel2

In poker release 2 the target high version numbers are advanced to 2.

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

The Card.name field is redundant (the Card.id field suffices by itself) and takes up much message space so by adding a number 1 to the Card.name line the vrange is closed out to 1-1. For javascript only, we've raised the lowest version as well to demonstrate version out of range errors. There are 3 possible vranges here, 1-1 as before, 1-2, and 2-2, new vranges being only possible with release 2.

```
$ ./run_r2.sh
----- Example 4 -----
[vrange=1-1, nodejs] STACK 7 cards
write: t.dat, version=1, cards=7, bytes=153
[vrange=1-2, cpp] DRAW 4 cards
read: t.dat, version= 1, cards=7, bytes=153
card pop: Seven of Diamonds Six of Diamonds Five of Diamonds Four of Diamonds
write: t.dat, version=2, cards=3, bytes=20
cards left 3
[vrange=1-2, python] DRAW 3 cards
read: t.dat, version=2, cards=3, bytes=20
card pop: Three of Diamonds Two of Diamonds Ace of Diamonds
write: t.dat, version=2, cards=0, bytes=14
cards left 0

----- Example 5 -----
[vrange=1-2, python] STACK 4 cards
write: t.dat, version=2, cards=4, bytes=22
[vrange=1-1, nodejs] DRAW 2 cards
version mismatch
[vrange=1-1, cpp] DRAW 2 cards
version out of range

----- Example 6 -----
[vrange=1-2, cpp] STACK 5 cards
write: t.dat, version=2, cards=5, bytes=24
[vrange=1-2, python] DRAW 3 cards
read: t.dat, version=2, cards=5, bytes=24
card pop: Five of Diamonds Four of Diamonds Three of Diamonds
write: t.dat, version=2, cards=2, bytes=18
cards left 2
[vrange=2-2, nodejs] DRAW 2 cards
read: t.dat, version=2, cards=2, bytes=18
card pop: Two of Diamonds Ace of Diamonds
write: t.dat, version=2, cards=0, bytes=14
cards left 0
```

Example 4 demonstrates a deck stacked by release 1 (vpc version 1) being read by a release 2 program successfully as expected. Example 5 shows that a release 2 stack cannot be read by a release 1 program and instead displays version errors as expected. Example 6 is a language interop test within release 2. Comparing the stacked deck size from example 3 and 6 - there is a substantial decrease in file size for a 5 card stack from 113 bytes to 24 bytes as a result of removing the Card.name data from the message/file. This demonstrates interoperability between versions.

## Polymorphic Language Interoperability - vpbuf/examples/uno/rel1

Two new keywords - 'poly' and 'is' - are introduced to the vpc IDL in order to implement polymorphism. They may be read as 'polymorphic class or struct' and 'is a' respectively. A poly is a type that maybe be inherited from and is allowed on the right side of the 'is' keyword.

Reverse, Skip, and DrawTwo cards are all of type Action, which is in turn of type Card (3 tier polymorphism). Value is of type Card as well.


```
target  language cplusplus 1 1 vp_uno "./cpp/src" cc
        language python 1 1 vp_uno "./python/vp_uno" py
        language javascript 1 1 vp_uno "./nodejs/src" js

pod Header
    varint version 1
    string tag 1

poly Card
    varint id 1

pod Value is Card
    varint value 1
    string color 1

poly Action is Card
    string color 1

pod Reverse is Action
pod Skip is Action
pod DrawTwo is Action

pod Deck
    vector *Card cards 1
```

The vpbuf/uno/run_1.sh demonstrates polymorphic language interoperability.

```
$ ./run_r1.sh
----- Example 1 -----
[vrange=1-1, python] STACK 4 cards
write: t.dat, version=1, cards=4, bytes=60
[vrange=1-1, nodejs] DRAW 2 cards
read: t.dat, version=1, cards=4, bytes=60
card pop: Blue 9 Blue 9
write: t.dat, version=1, cards=2, bytes=36
cards left 2
[vrange=1-1, cpp] DRAW 2 cards
read: t.dat, version= 1, cards=2, bytes=36
card pop: Blue 8 Blue 8
write: t.dat, version=1, cards=0, bytes=12
cards left 0

----- Example 2 -----
[vrange=1-1, nodejs] STACK 7 cards
write: t.dat, version=1, cards=7, bytes=96
[vrange=1-1, cpp] DRAW 4 cards
read: t.dat, version= 1, cards=7, bytes=96
card pop: Blue 9 Blue 9 Blue 8 Blue 8
write: t.dat, version=1, cards=3, bytes=48
cards left 3
[vrange=1-1, python] DRAW 3 cards
read: t.dat, version=1, cards=3, bytes=48
card pop: Blue 7 Blue 7 Blue 6
write: t.dat, version=1, cards=0, bytes=12
cards left 0

----- Example 3 -----
[vrange=1-1, cpp] STACK 5 cards
write: t.dat, version=1, cards=5, bytes=72
[vrange=1-1, python] DRAW 3 cards
read: t.dat, version=1, cards=5, bytes=72
card pop: Blue 9 Blue 9 Blue 8
write: t.dat, version=1, cards=2, bytes=36
cards left 2
[vrange=1-1, nodejs] DRAW 2 cards
read: t.dat, version=1, cards=2, bytes=36
card pop: Blue 8 Blue 7
write: t.dat, version=1, cards=0, bytes=12
cards left 0
```
## Scrambled Eggs with a Side of Hashed Browns - Scrambler - Structural Data Obfuscation Example

### Motivation

Encryption is a glass cannon, extremely powerful but fragile, with any misconfiguration or implementation flaw potentially exposing precious data. It is axiomatic then that when an attacker cannot succeeed by brute force, they will nibble at its edges, mapping, studying, and ultimately exploiting any underlying structure known or discovered. Therefore, security may be improved by systematically hiding this very structure an attacker relies on to navigate not one system but many.

#### Active Development
    adding reorderable string feature (rstring) for clarity in scrambler example
    scrambler example of reorder pods and salts

#### TODO

    build instructions/refinements
    refactor before adding additional languages
    upgrade boost version
    add comments to vpc interface description language
    improve parse error handling/reporting
    improve generated code polymorphism error handling

