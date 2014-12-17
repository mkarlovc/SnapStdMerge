========================================================================
    CorePeriphery : Core/Periphery structure analysis
========================================================================

Loads a directed (or undirected) graph and computes:
  -- Core/Periphery partition Lip, S. (2011) A Fast Algorithm for the 
  Discrete Core-Periphery Bipartitioning Problem. Working
  Paper, University of Cambridge.

The code works under Windows with Visual Studio or Cygwin with GCC,
Mac OS X, Linux and other Unix variants with GCC. Make sure that a
C++ compiler is installed on the system. Visual Studio project files
and makefiles are provided. For makefiles, compile the code with
"make all".

/////////////////////////////////////////////////////////////////////////////
Parameters:
   -i:Input graph (one edge per line, tab/space separated) (default:'graph.txt')

/////////////////////////////////////////////////////////////////////////////
Usage:

Compute degree distribution and clustering coefficient of a network

coreperiphery.exe -i:../as20graph.txt
