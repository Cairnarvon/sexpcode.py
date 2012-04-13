#!/usr/bin/python

import os.path
import subprocess
import sys

from distutils.core import setup, Extension

if not os.path.isdir('sexpcode'):
    if subprocess.call(['git', 'clone',
                        'git://github.com/Cairnarvon/sexpcode.git']) != 0:
        print >> sys.stderr, "Couldn't clone SexpCode repository!"

sexpcode = Extension('sexpcode',
                     sources = ['sexpcode.c',
                                'sexpcode/sexpcode.c',
                                'sexpcode/html.c'])

setup(name = 'sexpcode',
      version = '1.0',
      description = 'Python bindings for SexpCode',
      author = 'Koen Crolla',
      author_email = 'cairnarvon@gmail.com',
      url = 'http://github.com/Cairnarvon/sexpcode.py',
      ext_modules = [sexpcode])
