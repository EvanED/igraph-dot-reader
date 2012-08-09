#include <cstdio>

#include "igraph_read_dot.h"

int main(int argc, char** argv)
{
    (void) argc;
    igraph_t graph;
    igraph_read_graph_graphviz(&graph, std::fopen(argv[1], "r"), 0);
    igraph_write_graph_dot(&graph, stdout);
}
