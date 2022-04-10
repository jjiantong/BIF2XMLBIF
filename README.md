# BIF2XMLBIF

This is a tool to convert files in the BIF format (.bif) to XMLBIF format (.xml).

BIF (Belief Network Interchange File) and XMLBIF (XML Belief Network Interchange File) formats are standard formats for the storage and manipulation of the Bayesian networks. 
See some more information on: http://www.cs.cmu.edu/afs/cs/user/fgcozman/www/Research/InterchangeFormat/, 
https://www.cs.cmu.edu/~javabayes/Home/node7.html#SECTION00730000000000000000, 
https://www.cs.cmu.edu/~javabayes/Home/node7.html#SECTION00750000000000000000

As I'm doing my research on Bayesian network stuff, I find I'm in need of a collection of XMLBIF format Bayesian networks. 
However, I couldn't find many XMLBIF format BNs from the Internet although there are many of them in other formats. 
So I think a convertor maybe useful.

## How to use
This is a CLion project. You can easily open it using CLion and reload to generate ```cmake-build-debug``` file. Build and run using CLion.
Or you can use the command to build and run:
```
mkdir build && cd build && cmake .. && make && ./BIF2XMLBIF
```

Note: change Lines 14 and 181 to use your own files.
