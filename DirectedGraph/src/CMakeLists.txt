project(dg_src)

add_library(${PROJECT_NAME} INTERFACE)
add_library(dg_impl ALIAS ${PROJECT_NAME})

target_link_directories(${PROJECT_NAME} INTERFACE
    AdjacentNodesIterator.hpp
    ConstAdjacentNodesIterator.hpp
    ConstDirectedGraphIterator.hpp
    DirectedGraph.hpp
    DirectedGraphIterator.hpp
    DirectedGraphNode.hpp
    DirectedGraphNodeAllocator.hpp
)
