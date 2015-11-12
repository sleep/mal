# [Make-a-Lisp](https://github.com/kanaka/mal) implementation in C

**Objective:**
- Write a Lisp interpreter in C from scratch
- Get it to self-host

**Goals:**
- Learn about PL implementation
- Learn C
- Learn about Lisps

**Rules/Constraints:**
- Don't look at any reference implementations!
- Must use only C standard library. *(and GNU readline (and libpcre..))*

**Resources:**
- Kanaka's [Make-a-Lisp Guide](https://github.com/sleep/mal/blob/master/process/guide.md)



<br/>

**Possible directions to take this**
- Do away with standard library, readline, pcre, i.e roll my own malloc, free, strings.h, readline.h ,pcre.h
- Go halfway with C, pick up the rest in Rust?

<br/>



## Roadmap/Journal

### Preliminary thoughts

Implementing a self-hosting lisp interpreter has got to be one of the most pedagogically cost-effective<b>*</b> canonical projects out there. My goal is to juice as much knowledge/experience from this exercise, so I'm doing this project in C, a practical language most orthogonal to the interpreted, high-level languages I'm comfortable with. Having never written anything non-trivial in a non-garbage-collected language, I'm hoping this endeavor will fill in a few holes in my CS knowledge.

The making of any self-hosting compiler/interpreter is surely a lengthy journey, but also one within in a vast decision space. 
Fortunately, Kanaka's Make-a-Lisp challenge gives a language-agnostic roadmap that's high-level enough to require architectural forethought on behalf of the implementer, but also clear enough to save the implementer from moments of design-decision Buridan's Assery.

I've chosen to develop my Lisp interpreter against Kanaka's specifications and treat this project more as a PL-implementation exercise, rather than PL implementation-space exploration. I'll save the latter choice for another time, perhaps to be done concurrently as a PL *design*-space exploration...

<sub>*i.e. ratio of gratification/knowledge gained over energy spent. </sub>

<br/>

### Step 0: The REPL
- [x] set up project
- [x] set up print
- [x] Use gnu readline

First forays into C ecosystem; got familiar with make, valgrind, linking. Managed to wrap my head around pointers and null-terminated strings.

### Step 1: Read and Print

`Scaffolding:`
- [x] make a dynamic list data structure
- [x] design enum-based type system
- [x] make enum-based token type

`Read :: (String) -> AST`
- [x] make a tokenizer
- [x] make a recursive descent parser

`Print :: (AST) -> String`
- [x] implement a way to get string representation of nodes

Figured out more of the mess regarding C declaration syntax. Dealt with const correctectness. Getting the hang of heap vs stack. Grokking function pointers for testing. Immersed myself in `strings.h`.
I've decided to deal with dynamic strings closer to the metal with `char**`'s, instead of wrapper objects. This is the technique `asprintf` uses to write strings without knowing the length of strings to preallocate a buffer.
