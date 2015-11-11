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
- [Make-a-Lisp Guide](https://github.com/sleep/mal/blob/master/process/guide.md)



<br/>
### Possible directions...
- Do away with standard library and readline, i.e roll my own malloc, free, strings.h, readline.
- Go halfway with C, pick up the rest in Rust?
<br/>



## Roadmap/Journal

Implementing a self-hosting lisp interpreter has got to be one of the most pedagogically cost-effective<b>*</b> projects. My goal is to juice as much knowledge/experience from this project, so I'm doing this project in C, a practical language most orthogonal to the interpreted, high-level languages I'm comfortable with. Having never written anything non-trivial in a non-garbage-collected language, I'm hoping this endeavor will fill in many holes in my CS knowledge.

Kanaka's Make-a-Lisp challenge gives a language-agnostic roadmap that's high-level enough to require architectural forethought on behalf of the implementer, but also clear enough to save the implementer from moments of design-decision Buridan's Assery. The making of any self-hosting compiler/interpreter is always a journey. With all explorations, there are things to be gained, things to be lost when journeying with a prescribed route. By sticking with someone else's (well-curated) route, efficiency and therefore breadth are undoubtably gained. However, one loses the sentimentality, the sense of ownership, the developing of natural sense of direction, that comes with impromptu, plan-as-you-go journeys. With that said, I've chosen to go with Kanaka's guide and treat this project more as exercise than exploration, with the latter choice saved for another journey...

<b>*</b><sub>i.e. ratio of personal gratification/breadth of knowledge gained over the time/energy spent. </sub>

### [x] Step 0: The REPL
- [x] set up project
- [x] set up print
- [x] Use gnu readline

First forays into C ecosystem; got familiar with make, valgrind, linking. Managed to wrap my head around pointers and null-terminated strings.

### [ ] Step 1: Read and Print

Scaffolding:
- [x] make a dynamic list data structure
- [x] design enum-based type system
- [x] make enum-based token type

`Read :: (String) -> AST`
[x] - make a tokenizer
[x] - make a recursive descent parser

`Print :: (AST) -> String`
[ ] - Figure out how to pass strings and combine them

