# Ford-Fulkerson Algorithm Visualizer

This application provides a visual representation of the Ford-Fulkerson algorithm in action. It is designed to help users understand and visualize the process of finding the maximum flow in a network flow problem.

![image](https://github.com/AngAnda/FordFulkerson/assets/61116472/11bc2fee-6ca2-44fb-ae5f-a800e8a2c1fb)

## Features

- **Interactive Graph Visualization**: Users can create nodes and edges to form a flow network with capacities.
- **Real-time Simulation**: Watch the algorithm step through the network, updating flows in real time.
- **Result Display**: Immediate display of the maximum flow result after the algorithm completes.
- **Customizable Inputs**: Users can input custom flow network graphs and run the algorithm to find maximum flow.

## Interface Elements

- **Graph Area**: Displays the network with nodes and edges. Each edge shows the current flow and capacity in the format `flow/capacity`.
- **Controls**: Input fields for source and sink nodes, and a 'PushButton' to initiate the algorithm.
- **Result Window**: Shows the outcome of the algorithm with the total maximum flow from the source to the sink.

## Using the Application

1. Define the flow network by adding nodes and directed edges with capacities.
2. Specify the source (starting node) and sink (ending node) in the provided input fields.
3. Click the 'PushButton' to run the Ford-Fulkerson algorithm.
4. Observe the algorithm as it finds augmenting paths and updates flows.
5. View the result in the pop-up window that displays the maximum flow value.
