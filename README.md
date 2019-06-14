# Graph-Theory-Project-Template
Project template of course - Graph Theory (EE6622E) in National Cheng Kung University.

## How to run

### Linux

```
# clone first (with submodule)
$ git clone --recursive https://github.com/<your-name>/Graph-Theory-Project-Template.git
# (Option) build libfakemn.a
$ cd fake-mininet && make lib && cd .. && cp fake-mininet/libfakemn.a .
# build
$ make 
# run 
$ ./main.out
```

### Windows

If your PC is `window 10`, then you need to install the related dependencies. For example, if you are using `VSCode` as your IDE, then you can install the plugin of `C/C++` in your vscode. And then install the following programs/packages:
* mingw
* git

Step by step to create `c_cpp_properties.json` and `tasks.json`:
* `Ctrl+Shift+P` -> `C/C++: Edit Configuration` -> then you have the first JSON file.
* `Ctrl+Shift+P` -> `Tasks: Configure Task` -> then you have the second JSON file.

Here is the setting of `c_cpp_properties.json` and `tasks.json`:
```json
# c_cpp_properties.json (If your mingw installed in another folder, then you have to change the value in `compilterPath`)
{
    "configurations": [
        {
            "name": "MinGW",
            "intelliSenseMode": "gcc-x64",
            "includePath": [
                "$(workspaceFolder)"
            ],
            "compilerPath": "C:/mingw/bin/gcc.exe",
            "cStandard": "c11",
            "cppStandard": "c++11"
        }
    ],
    "version": 4
}

# tasks.json
{
    "version": "2.0.0",
    "tasks": [
        {
            "label": "build",
            "type": "shell",
            "command": "g++",
            "args": [
                "-g",
                "main.cc",
                "-o",
                "main.exe",
                "-Ifake-mininet/lib",
                "-g3",
                "-L.",
                "-lfakemn_win",
                "-std=c++11"
            ],
            "group": {
                "kind": "build",
                "isDefault": true
            }
        }
    ]
}
```

After all the settings have been done, we can press `Ctrl+Shift+B` to run the task, if your settings is correct, then there will have an executable file which named `main.exe`.

Or you can just [DOWNLOAD a pre-built VM images](http://gofile.me/39GpL/XU5tznyO6) provided by TA.

> [Guide of environment setting](https://hackmd.io/-5WZQC-1QqOeV3KUX65tEw?view) on Windows.

## TODO - Your descriptions about solutions/algorithms/results
Proposition :
	In graph theory, a branch of mathematics and computer science, the Chinese postman problem
	(CPP), postman tour or route inspection problem is to find a shortest closed path or circuit
	visits every edge of an (connected) undirected graph. When the graph has an Eulereian circuit
	(a closed walk that covers every edge once), that circuit is an optimal solution. Otherwise,
	the optimization problem is to find the smallest number of graph edges to duplicat (or the
	subset of edges with the minimum possible total weight) so that the resulting multigraph does
	have an Eulerian circuit. It may be solved in polynomial time. (Reference by WIKI)

Algorithm :
	My program is target to undirected graph which the degree equals to odd number is two or zero.
	Firstly, I will find the input graph whether it has the points which has deree equals odd number
	, if it has the points, the points will be saved in the other graph nm2, If it has no points, program go to
	next function that is find EulerPath, in the graph nm1¡Awe will use Breadth-First Search to find shortest
	distance betweeen this tow points, and the edge which has beed found pass by the function will be
	saved in nm2, then the edge in nm2 will be saved in nm. 
	
	And, We want to find the shortest path by HIERHOLZER'S ALGORITHM
	
		HIERHOLZER'S ALGORITHM :
			This is an algorithm to find an Eulerian circuit in a connected graph in which every vertex has 
			even degree.
			1.Choose any vertex v and push, it onto a stack. Initailly all edges are unmarked.
			2.While the stack is noempty, look at the top vertex, u, on the stack. If u has an unmarked
			incident edge,, the pop u off the stack and print it.
			3.When the stack is empty, you will have printed a sequence of vertices that correspond to 
			Eulerian circuit.
			
	pseudocode reference by : 
	https://iampandiyan.blogspot.com/2013/10/c-program-to-find-euler-path-or-euler.html	
	
	The Path which I found will be saved in output.txt.
		
Supplement : 
	BFS Algorithm : A strategy for searching in a graph. The BFS begins at aroot node and inspects all the 
	neighborings nodes. Then for each of those neighbor nodes in turn, it inspects their neighbors nodes which
	were unvisited, and so on.
	
	BFS code is referenced by :
	http://alrightchiu.github.io/SecondRound/graph-breadth-first-searchbfsguang-du-you-xian-sou-xun.html
		
File : 
	topo.txt : get graph data
	output.txt : ouptut the path (look from the back)
	output.dot : output dot file
	output.png : output image data 
	
Program :
	
	main : 
		including 
		1.access of input file"topo", 
		2.find which vertex is odd, 
		3.find EulerPath, 
		4.output the answer"output.txt","output.dot","output.png".
	distance_calcultate : to find the shortest distance about two point.
	pathfromBFS : to find the shortest path between two vertex.
	
Find Bug About API : 

	The function path->debug() doesn't include all possible, it just print some combination.
	When I input a data likes topo.txt. First Line a b, Second Line b c, Third line c d, program will add 
	capacity to each, although it doesn't influence the work, but it is a bug.

	
	

			
