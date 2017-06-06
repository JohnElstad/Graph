#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>

#include "Node.h"
#include "Graph.h"



using namespace std;

int main(){
  Graph* graph = new Graph();
  char input[128];
  bool running = true;
  cout<<"WElcome to Graph Creator"<<endl;
  count<<"Valid Commands are: Edge, Vertex< Delete, Find and Quit"<<endl;

  while(running){

    cin.getline(input, 128);
        
    if(input[0] == 'e' || input[0] == 'E'){
      cout << "Give me 2 single character vertex names and a scalor with a space in between" << endl;
      cin.getline(input,10);

      if(isdigit(input[4]) && input[1] == ' ' && input[3] == ' '){
	graph->add(input[0],input[2],atoi(&input[4]));
      }
      else cout << "Your input is wrong, the format should be, 'C' 'C' 'I'" << endl;

    }
    else if(input[0] == 'v' || input[0] == 'V'){
      cout << "What is the single character name for the new Vertex" << endl;
      cin.getline(input,10);
      graph->add(input[0]);

    }
    else if(input[0] == 'd' || input[0] == 'D'){
      cout << "Give me one vertex name to delete or two to delete the edge between them" << endl;
      cin.getline(input,10);
      if (strlen(input) <= 2){
	graph->remove(input[0]);
    } else if (strlen(input) >= 3){
	graph->remove(input[0],input[2]);
      }else{
	cout << "You mistyped something" << endl;
      }
    } 
    else if(input[0] == 'p' || input[0] == 'P'){
      graph->print();
    } 
    else if(input[0] == 'f' || input[0] == 'F'){
      cout << "Give me two nodes to find a path between them" << endl;
      cin.getline(input,10);
      if (strlen(input) >= 3){
	graph->findPath(input[0],input[2]);
      }

    }
    else if(input[0] == 'q' || input[0] == 'Q'){
      running = false;
    }
    else{
      cout << "You must have mistyped something." << endl;
      cout << "The possible commands are:\nEdge\nVertex\nDelete\nFind\nQuit" << endl;
    }
  }
}
