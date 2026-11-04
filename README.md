# C_API: checkers move generator

[![build](https://github.com/Faterunner35/c-checkers-api-master-renamed/actions/workflows/build.yml/badge.svg)](https://github.com/Faterunner35/c-checkers-api-master-renamed/actions/workflows/build.yml)

A small library for 8x8 checkers (draughts). It generates the legal moves for a
piece, checks whether a move is legal, and builds a game tree of every position
reachable within a given number of plies.

The interface is plain C: the headers use `extern "C"`, opaque `void*` handles and
`char[8][8]` boards. The implementation is C++11 and uses `std::list`
internally, so a program that uses the library must be linked with the C++
runtime.

## Author and license

- Written by Aleksander Aksionau (GitHub: [Faterunner35](https://github.com/Faterunner35); `vttry` in the license is the same author).
- MIT License, **Copyright (c) 2019 vttry** — see [LICENSE](LICENSE).
- Third-party code in `thirdparty/` keeps its own license (see below).

## What the code does

**Board.** A board is `char status[8][8]`, indexed `status[row][column]`. Row 0
is White's home row: White moves towards row 7 and Black towards row 0. Dark
(playable) squares are the ones where `row % 2 == column % 2`. Squares hold
these characters (`src/Checker.h`):

| char  | meaning                    |
|-------|----------------------------|
| `' '` | light square (never used)  |
| `'#'` | empty dark square          |
| `'1'` | white man                  |
| `'2'` | white king                 |
| `'3'` | black man                  |
| `'4'` | black king                 |

Positions are `int pos[2] = {row, column}`. Players are `WHITE_PLAYER` (0) and
`BLACK_PLAYER` (1), defined in `src/Player.h`.

**Rules implemented** (as read from `src/CheckersGame.cpp` and
`src/CheckersGameApi.cpp`). They are close to Russian draughts:

- A man moves one square diagonally forward. It can capture in all four
  diagonal directions, and captures can be chained into multi-jumps.
- A man that reaches the far row becomes a king, including in the middle of
  a capture sequence.
- Kings are "flying": they move any distance along a free diagonal and can
  capture a piece from a distance.
- When the game tree is built, capturing is compulsory. If any piece can
  capture, only captures are expanded.
- Three kings against a single king get 15 moves to win. After that the
  branch is not expanded any further.

**Public API** (`src/CheckersGameApi.h`, `src/TreeBoard.h`):

| function | purpose |
|----------|---------|
| `initializeBoardStatus(board)` | set up the starting position |
| `makePossibleMovesForPiece(board, pos)` | all boards that can result from moving the piece at `pos`. Returns `BoardList*`, or `NULL` if the piece cannot move |
| `getLengthOfBoard`, `compareListBoardWithRaw`, `freeBoardList` | inspect and free a `BoardList`. `compareListBoardWithRaw` compares the *first* board in the list |
| `checkValidOfMoving(board, from, to, generator)` | whether the piece at `from` can end its move on `to` |
| `buildGameTree(board, player, generator, depth)` | game tree of every position up to `depth` plies. Returns `TreeBoard*` |
| `getChildCountOfGameTree`, `getFirstChildOfTreeBoard`, `getTreeBoard`, `iterateAllNodes`, `freeGameTree` | walk and free a game tree |

`checkValidOfMoving` and `buildGameTree` take the move generator as a function
pointer of type `MakePossibleMovesFunc`. Pass `makePossibleMovesForPiece` there.

The lower-level move-list and move-tree functions that the API is built on
(`createMoveTree`, `makeMoveTreeForPiece`, `findPossibleMoving`, and others)
are declared in `src/CheckersGame.h`.

**Known limitations** (unchanged behaviour of the original code):

- After a king captures, the only landing square generated is the one
  directly behind the captured piece.
- `buildGameTree` returns `NULL` if the starting position has fewer than two
  legal moves.

## Repository layout

```
src/            the library
  CheckersGame.*      move generation (static library CheckersGameLib)
  CheckersGameApi.*   board lists, move validation, game tree (static library CheckersGameApi)
  TreeBoard.*         game-tree accessors (part of CheckersGameApi)
  EngineDefine.h      internal C++ types (std::list based nodes)
  Checker.h, Player.h piece characters and player ids
examples/
  BuildGameTree.cpp   builds a 7-ply tree from the start position and prints one branch
test/
  CheckersTest.cpp    GoogleTest tests for the low-level move generation
  CheckersApiTest.cpp GoogleTest tests for the public API
thirdparty/
  catch/   Catch v2.9.1 single header (Boost Software License 1.0, Two Blue Cubes Ltd.)
  sglib/   SGLIB 1.0.4 header (Marian Vittek; free use of verbatim copies, see header)
```

The tests do not use either third-party header. `test/CheckersTest.cpp`
includes `sglib.h` but calls nothing from it, and Catch is bundled but no test
includes it. The tests use GoogleTest (see below).

## Building and testing

You need CMake 3.14 or newer and a C++ compiler: GCC, Clang or MSVC 2022.

```sh
cmake -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

With a multi-config generator such as Visual Studio, add `--config Release` to
the build command and `-C Release` to the `ctest` command.

The tests need GoogleTest. If CMake finds an installed copy (for example the
`libgtest-dev` package), it uses that copy. Otherwise googletest v1.14.0 is
downloaded with `FetchContent` at configure time.

To run the example:

```sh
./build/examples/BuildGameTree
```

The example prints one branch of the tree and ends with
`Total nodes in game three: 237442`.

GitHub Actions ([.github/workflows/build.yml](.github/workflows/build.yml))
builds the project and runs the tests on Linux with GCC and on Windows with
MSVC 2022.

## Usage example

This is a shortened version of `examples/BuildGameTree.cpp`:

```c
#include "CheckersGameApi.h"
#include <stdio.h>

int main(void)
{
    char status[8][8];
    initializeBoardStatus(status);

    TreeBoard *treeBoard = buildGameTree(status, BLACK_PLAYER,
                                         makePossibleMovesForPiece, 7);
    if (!treeBoard)
    {
        printf("I can't build treeBoard\n");
        return 0;
    }

    long nodesCount = 1;                      /* count the root as well */
    iterateAllNodes(treeBoard, &nodesCount);
    printf("Total nodes in game three: %ld\n", nodesCount);

    freeGameTree(treeBoard);
    return 0;
}
```

Link it against the `CheckersGameApi` CMake target:

```cmake
target_link_libraries(my_app PRIVATE CheckersGameApi)
```

## License

MIT, see [LICENSE](LICENSE). The files in `thirdparty/` keep their own licenses,
which are stated in their headers.
