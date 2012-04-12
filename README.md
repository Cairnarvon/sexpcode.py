**sexpcode.py** at long last brings SexpCode support to Python.

## Installation

>    # python setup.py install

You will need a C compiler, the Python headers (package `python-dev` on Debian and Debian-like distros), and `git` (not just to pull this repository, I mean; the module is just a thin wrapper around [the C SexpCode implementation](https://github.com/Cairnarvon/sexpcode), and that repository is cloned during installation).

## Usage

>    >>> from sexpcode import sexpcode
>    >>> sexpcode('{b test}')
>    '<b>test</b>'
