# Typetrainer
## Advanced Programming bonus project
CLI unix-specific typing trainer\
To download the New Curses library, run:
```
$ sudo apt-get install libncurses5-dev libncursesw5-dev
```

To build and run a major project:
```
$ mkdir build
$ mkdir texts
$ cd build/
$ cmake ../src
$ make
$ ./tt 
```

or execute build_and_run (with cleanup):
```
$ chmod +x build_and_run.sh
$ ./build_and_run.sh
// play another time
$ ./build/tt 2>build/errors
// clean up building
$ chmod +x cleanup.sh
$ ./cleanup.sh
```

To test text splitting tool:
```
$ cd tools/
$ g++ text_splitter.cpp -o spl
$ ./spl <max line length> <path to file> [path to result file]
```

To test text generating tool:
```
$ cd tools/
$ g++ text_generator.cpp -o gen
$ ./gen <number of lines> <difficulty 1 to 3> [path to result file]
```

Sourses:
- [Ncurses documentation](https://invisible-island.net/ncurses/ncurses-intro.html)
- [Ncurses tutorials](https://www.youtube.com/playlist?list=PL2U2TQ__OrQ8jTf0_noNKtHMuYlyxQl4v)
- [Markdown basics website](https://commonmark.org/help/tutorial/)
