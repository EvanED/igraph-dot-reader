#ifndef IGRAPH_READ_DOT_H
#define IGRAPH_READ_DOT_H

#include <igraph/igraph.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

extern int igraph_read_graph_graphviz(igraph_t *graph, FILE *instream, int index);

#ifdef __cplusplus
}
#endif

#endif /* IGRAPH_READ_DOT_H */
