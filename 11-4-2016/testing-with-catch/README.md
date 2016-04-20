# Testing with Catch

This subdirectory contains slides and code from the talk given at the
C++ User Group Hannover meeting on Monday, April 11th 2016.

## Structure

### Slides

You can view the slides [here](https://nbviewer.jupyter.org/format/slides/github/CPPUserGroups/Germany-Hannover/blob/master/11-4-2016/testing-with-catch/slides/Testing_with_Catch.ipynb).

To convert the Jupyter Notebook into [reveal.js](http://lab.hakim.se/reveal-js/)-powered
slides and serve them yourself, run

```sh
jupyter nbconvert Testing_with_Catch.ipynb --to slides --post serve

```

You may want to toy with any of the following options:

```sh
--ServePostProcessor.port=8910
--ServePostProcessor.ip=[IP]
--ServePostProcessor.open_in_browser=False
```

If you intent to edit the Jupyter notebook, you need to ensure the
following dependencies when running the examples:

* Python3
* Jupyter
* Bash
* `clang++`

```sh
cd slides
jupyter-notebook --no-browser --ip [IP]
```

I considered using the [Jupyter Cling Kernel](https://github.com/root-mirror/cling/tree/master/tools/Jupyter/kernel)
but it turned out that these slides required more features than just
compiling C++ code, especially running the unit test binaries, so I went
with the Python kernel instead.

### Code examples

Each of the subdirectories contains a self-contained CMake project
including submodules that may have been duplicated between the projects
(Catch in particular).

All examples build with

```sh
mkdir build && cd build && CC=clang CXX=clang++ cmake .. -G Ninja && time ninja
# or
mkdir build && cd build && cmake .. && make
```

#### operator<<

Contains a simple example of how to write `operator<<()` for a given
structure.

#### gmock-integration

Shows how to use Catch as a test runner for GoogleMock based on examples
given online.

#### trompeloeil-integration

Duplicates the example of using Catch as a test runner given in the
[Trompeloeil documentation](https://github.com/rollbear/trompeloeil/blob/master/docs/CookBook.md#adapt_catch).

#### demo-and-experiments

Contains the result of a quick live demo and some more toying with
Catch's support for BDD-style tests and matchers.

## License

[CreativeCommons Attribution-Share-Alike](https://creativecommons.org/licenses/by-sa/4.0/legalcode)
