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
- Do away with standard library and readline, i.e roll my own malloc, free, strings.h, readline.
- Go halfway with C, pick up the rest in Rust?

<br/>



## Roadmap/Journal

### Preliminary thoughts

Implementing a self-hosting lisp interpreter has got to be one of the most pedagogically cost-effective<b>*</b> canonical projects out there. My goal is to juice as much knowledge/experience from this exercise, so I'm doing this project in C, a practical language most orthogonal to the interpreted, high-level languages I'm comfortable with. Having never written anything non-trivial in a non-garbage-collected language, I'm hoping this endeavor will fill in a few holes in my CS knowledge.

Kanaka's Make-a-Lisp challenge gives a language-agnostic roadmap that's high-level enough to require architectural forethought on behalf of the implementer, but also clear enough to save the implementer from moments of design-decision Buridan's Assery. The making of any self-hosting compiler/interpreter is surely a lengthy journey, but also one within in a vast decision space. So the question arises: do I follow this guide, or do I scout out the decision space for my own and attempt a path of my own?

With all journeys, there are things to be gained, things to be lost when going with a prescribed route over making one for oneself. By sticking with someone else's (hopefully well-curated) route, efficiency in regards to breadth is undoubtedly gained. Many rewards are to be gained from such a journey, perhaps especially more of the quantifiable nature, like things learned, topic covered, landmarks visited, etc. However, one loses the thrills of risk in making one's own turns, the moments of frustration-turned-angst from making too many of the wrong ones, the natural development of a sense of direction and location, and an exalting feelings of self-actualization at the end -- all of which comes with more impromptu journeys.

Having said that, I've chosen to develop my Lisp interpreter against Kanaka's specifications and treat this project more as a first-time PL-implementation exercise, rather than PL implementation-space exploration. I'll save the latter choice for another time, perhaps to be done concurrently as a PL *design*-space exploration...

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
- [ ] Figure out how to pass strings and combine them

Figured out more of the mess regarding C declaration syntax. Dealt with const correctectness. Getting the hang of heap vs stack. Grokking function pointers for testing.
