Graph Algorithms
A comprehensive C++ application built with the Qt Framework for visualizing and solving classic graph theory problems through an interactive Graphical User Interface (GUI).

🚀 Main Features
Algorithm Visualizations: Includes independent modules for several core graph algorithms:

Dijkstra's Algorithm: Shortest path finding (features a real-world Luxembourg map parser).

Breadth-First Search (BFS): Maze solving and traversal.

Connected Components: Detection of strongly and weakly connected components.

Topological Sorting: Dependency resolution for directed acyclic graphs.

Maximum Flow / Minimum Cut: Network flow optimization.

Traveling Salesperson Problem (TSP): Optimal routing calculations.

Interactive UI: A Qt-based interface (mainwindow) to draw, load, and visually interact with the graphs.

Advanced Data Structures: Uses KD-Trees (kdtree.cpp/h) for fast spatial queries and relies on pointers for efficient Node and Edge memory management.

Real Datasets: Includes parsers for real-world XML data (Harta_Luxemburg.xml) and text-based graph representations (orase.txt).

📁 Project Structure
The repository contains multiple Qt .pro files, allowing you to build and run each algorithm module independently:

Core Logic (graph, node, edge, kdtree): The mathematical foundation and pointer-based data structures.

UI Components (mainwindow.cpp/h/ui): The visual canvas and graphical event handlers.

Project Files (*.pro): Separate run configurations for each specific algorithm implementation (e.g., Dijkstra-HartaLuxemburg.pro, LabirintulBFS.pro).

🛠️ Required Dependencies
To compile and run this project, you will need:

C++ Compiler (supporting C++11 or newer).

Qt Framework (Qt Creator IDE is highly recommended for opening the .pro files and rendering the .ui components).
