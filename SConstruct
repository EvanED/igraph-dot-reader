# -*- python -*-

import os

graphviz_inc = "/unsup/graphviz/include"
graphviz_lib = "/unsup/graphviz/lib"

igraph_inc = "/u/d/r/driscoll/Downloads/igraph-0.6/install/include"
igraph_lib = "/u/d/r/driscoll/Downloads/igraph-0.6/install/lib"

env = Environment()

env.Append(CPPPATH=[graphviz_inc, igraph_inc])
env.Append(LIBPATH=[graphviz_lib, igraph_lib])
env.Append(RPATH=[graphviz_lib, igraph_lib])
env.Append(LIBS=["cgraph", "cdt", "igraph"])

env.Append(CCFLAGS=["-Wall", "-Wextra"])
env.Append(CFLAGS=["-std=c99"])

env.SharedLibrary("dot_igraph", "src/igraph_read_dot.c")



prog = env.Clone()
prog.Append(LIBS=["dot_igraph"])
prog.Append(LIBPATH=["."])
prog.Append(RPATH=[os.getcwd()])

prog.Program("dot-is-isomorphic", "src/main.cpp")
