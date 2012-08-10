#include <cassert>
#include <cstdio>

#include "igraph_read_dot.h"

int main(int argc, char** argv)
{
    (void) argc;
    igraph_t g_left, g_right;
    
    igraphext_read_graph_graphviz(&g_left, std::fopen(argv[1], "r"), 0);
    igraphext_read_graph_graphviz(&g_right, std::fopen(argv[2], "r"), 0);

    igraph_bool_t is_iso;
    int err = igraph_isomorphic_vf2(&g_left, &g_right, // graphs 1/2
                                    NULL, NULL, // vertex colors 1/2
                                    NULL, NULL, // edge colors 1/2
                                    &is_iso,    // output result
                                    NULL, NULL, // map12, map21
                                    NULL, NULL, // node/edge compat
                                    NULL);      // arg

    assert(err == IGRAPH_SUCCESS);

    return !is_iso;
}
