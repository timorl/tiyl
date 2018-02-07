# This Is Your Life

Tiyl is a simple program for managing your life. Probably doesn't work very well, so don't try using it.

## Compilation

To compile run the following commands in your favourite shell:

```sh
$ git clone https://github.com/timorl/tiyl.git
$ cd tiyl
$ cmake .
$ make all
```

## Usage

The binary should be in `bin/`, so to run the program type:

```sh
$ bin/tiyl
```

This should create pretty reasonable default files for you. Sadly there is no documentation for the commands so you can either read the code or pester me about creating some.

Oh hell, there you go, a list of basic commands:

* status
* project
* mess
* action
* habit
* event
* annual
* dep
* all
* down
* up
* top

Most of those have subcommands, usually `add`, `del`, `list` and `show`. There are some others, but for now I am to lazy to write all this down. You don't really want to use this program anyways.
