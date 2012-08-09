#include "igraph_read_dot.h"

#include <graphviz/cgraph.h>


typedef struct record_index {
    Agrec_t header;
    int index;
} record_index;

char * record_name = "igraph_index";


int igraphext_read_graph_graphviz(igraph_t *graph, FILE *instream,
                                  int index)
{
    (void) index;
    
    Agraph_t * graphviz_graph = agread(instream, NULL);

    if (!graphviz_graph) {
        IGRAPH_ERROR("Graphviz library could not read the input",
                     IGRAPH_PARSEERROR);
    }

    // Assign each node a record
    int node_index = 0;
    for (Agnode_t * node = agfstnode(graphviz_graph); node;
         node = agnxtnode(graphviz_graph, node), ++node_index)
    {
        record_index * record = agbindrec(node, record_name, sizeof(record_index), TRUE);
        if (!record) {
            IGRAPH_ERROR("Graphviz library could not allocate a record",
                         IGRAPH_ENOMEM);
        }
        record->index = node_index;
    }
    
    // Create the igraph
    IGRAPH_CHECK(igraph_empty(graph, agnnodes(graphviz_graph),
                              agisdirected(graphviz_graph) ? IGRAPH_DIRECTED : IGRAPH_UNDIRECTED));

    // Add edges
    for (Agnode_t * source = agfstnode(graphviz_graph); source;
         source = agnxtnode(graphviz_graph, source))
    {
        for (Agedge_t * edge = agfstout(graphviz_graph, source); edge;
             edge = agnxtout(graphviz_graph, edge))
        {
            Agnode_t * target = aghead(edge);

            record_index * src_record = (record_index*) aggetrec(source, record_name, TRUE);
            record_index * tgt_record = (record_index*) aggetrec(target, record_name, TRUE);

            IGRAPH_CHECK(igraph_add_edge(graph, src_record->index, tgt_record->index));
        }
    }

    int ret = agclose(graphviz_graph);
    (void) ret; // don't know what this means

    return IGRAPH_SUCCESS;
}

