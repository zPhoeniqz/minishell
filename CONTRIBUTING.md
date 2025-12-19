# Contributing Guidelines

- pull before push
- always push after finishing a feature
- If you create a new branch always branch off master

**When cloning the repo always use the command `git clone --recursive` (this also downloads the libft, which is embedded as a submodule)**

## Do's and Don'ts

- When opening a file/directory, don't check for permissions/existence beforehand with `access`. Instead, rely directly on the `errno` value set by `open`/`opendir`. Reason: [TOCTOU Bugs](https://en.wikipedia.org/wiki/Time-of-check_to_time-of-use). Also, it's just cleaner/simpler.
