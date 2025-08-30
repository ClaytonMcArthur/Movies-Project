# Movies Project — Makefile & GitHub Guide

This README explains how to build and run the project with the provided **Makefile**, how to capture logs, and how to clean up/ignore build artifacts in Git/GitHub.

---

## Requirements
- **Compiler:** `g++` (or `clang++`) with C++17 support
- **OS:** macOS / Linux
- **Make:** GNU Make or BSD Make

---

## Build with Make

From the repository root:

```bash
make
```

This compiles all `*.cpp` files and links the binary **`movies_tester`**.

### Targets
- **`make`** or **`make all`** – builds the program
- **`make clean`** – removes object files and the binary

### Change compiler/flags (optional)
```bash
make CXX=clang++ CXXFLAGS='-std=c++17 -O2 -Wall -Wextra -pedantic'
# Debug build:
make clean && make CXXFLAGS='-std=c++17 -g -O0 -Wall -Wextra -pedantic'
# Sanitizers (clang):
make clean && make CXX=clang++ CXXFLAGS='-std=c++17 -g -O0 -fsanitize=address,undefined -fno-omit-frame-pointer -Wall -Wextra -pedantic'
```

---

## Run the Program

Defaults to the provided data files if no args are given.

```bash
./movies_tester [moviesFile] [customersFile] [commandsFile] [completedLogFile]
```

Examples:
```bash
# default (writes completed commands to ./completed_commands.txt)
./movies_tester

# specify a custom log filename as the 4th argument
./movies_tester data4movies.txt data4customers.txt data4commands.txt my_completed.txt
```

### Capture Output & Errors to Files
```bash
# stdout -> out.log, stderr -> errs.log, completed commands -> completed_commands.txt
./movies_tester data4movies.txt data4customers.txt data4commands.txt completed_commands.txt > out.log 2> errs.log
```

- **`out.log`**: inventory listings (`I`) and histories (`H`) printed to stdout  
- **`errs.log`**: parsing/validation errors, warnings, and info lines printed to stderr  
- **`completed_commands.txt`**: every command **that parsed and executed**

> Tip: If you ever see `zsh: command not found: #`, it means you pasted a comment line (`# ...`) into the shell. Remove the `#` and run only the command.

---

## What the Program Does

1. Loads movies into `Inventory` from `data4movies.txt`  
2. Loads customers into `CustomerHashTable` from `data4customers.txt`  
3. Parses and executes commands from `data4commands.txt` via `CommandFactory`  
4. Logs executed commands to `completed_commands.txt`, prints inventory/history to stdout, and errors to stderr.

The loader and main include extra validation + exception handling to avoid runtime crashes.

---

## Git/GitHub: Keep Build Artifacts Out of the Repo

### 1) Add a `.gitignore`
Create/edit `.gitignore` (example entries):
```
# Build artifacts
*.o
movies_tester

# Logs / outputs
out.log
errs.log
completed_commands.txt

# macOS
.DS_Store
```

### 2) Stop tracking artifacts that were already committed
Run these once to remove tracked junk **from the index only** (files stay on disk):
```bash
git rm --cached -r '*.o'
git rm --cached movies_tester out.log errs.log completed_commands.txt 2>/dev/null || true
git add .gitignore
git commit -m "chore: ignore build artifacts and logs"
git push
```

> If `.o` files are scattered deeply:
```bash
find . -name '*.o' -not -path './.git/*' -print0 | xargs -0 git rm --cached
git commit -m "chore: remove tracked object files"
git push
```

### 3) Pushing the correct branch
If you’re on a feature branch (e.g., `Movies-Implementation`), push it:
```bash
git push -u origin Movies-Implementation
```

To merge into `main`, open a Pull Request on GitHub (`Movies-Implementation` → `main`) or merge via CLI:
```bash
git switch main
git pull --rebase origin main
git merge --no-ff Movies-Implementation
git push origin main
```

> If you accidentally pushed to `main` but meant to push your feature branch, push the right branch (above) and open a PR.

### 4) (Advanced) Erase artifacts from all history
Rewriting history is disruptive—coordinate with teammates.
```bash
# macOS: brew install git-filter-repo
git filter-repo --path-glob '*.o' --invert-paths
git push --force-with-lease
```

---

## Common Issues & Fixes

### `trace trap` or crash at runtime
- Ensure all non-void functions **always return a value** (e.g., `operator<`, `operator==` in movie subclasses).  
- Rebuild without optimization for debugging: `make clean && make CXXFLAGS='-std=c++17 -g -O0 -Wall -Wextra -pedantic'`  
- Run with sanitizers (clang) to catch UB: see **Sanitizers** above.

### Include path case
If a file is `movie.h`, make sure includes use `"movie.h"` (not `"Movie.h"`). Case mismatches can build on macOS but fail on Linux.

### LLDB usage (macOS)
```bash
lldb -- ./movies_tester
(lldb) run data4movies.txt data4customers.txt data4commands.txt completed_commands.txt
(lldb) bt   # backtrace on crash
```

---

## Makefile (reference)

The provided `Makefile` compiles these sources:
```
main.cpp
movie.cpp comedy.cpp drama.cpp classics.cpp
Customer.cpp CustomerHashTable.cpp
Inventory.cpp MovieFactory.cpp
BorrowCommand.cpp ReturnCommand.cpp
HistoryCommand.cpp InventoryCommand.cpp
CommandFactory.cpp
Command.cpp
```
It produces the binary `movies_tester` and supports `make`, `make all`, and `make clean` targets.

---

## Verification Checklist

- Build succeeds with warnings treated seriously (fix any `non-void function does not return a value` warnings).  
- `./movies_tester ... > out.log 2> errs.log` produces:
  - `completed_commands.txt`: non-empty list of executed commands
  - `out.log`: inventory and history output
  - `errs.log`: ~10 expected errors (invalid action, unknown movie/customer, out of stock, etc.)

If any check fails, open `errs.log`, paste the relevant lines into an issue or message, and we’ll pinpoint the source.

---

Happy building! 🎬