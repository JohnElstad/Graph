#include "Node.h"
#include "Graph.h"


 
void Graph::add(char a, char b, int newWeight){
  Node* node1 = nodeLookup(a);
  Node* node2 = nodeLookup(b); 

  if ( node1 && node2 ){ 
    node1->add(node2,newWeight); 
  } 
}
void Graph::add(char a){ 
  bool isNew = true;
 
  for(vector<Node*>::iterator it = nodes.begin(); it!=nodes.end();it++){
    if ((*it)->name == a){
      isNew = false;
    }
  }
  if (isNew) nodes.push_back(new Node(a));
}
void Graph::remove(char a, char b){

  Node* node1 = nodeLookup(a);
  Node* node2 = nodeLookup(b);
 
  if ( node1 && node2 ){
    node1->remove(node2); 
  } 
}
void Graph::remove(char a){
  
  Node* removeNode = nodeLookup(a);
  if(!removeNode) return; 
 
  for(vector<Node*>::iterator it =  nodes.begin(); it != nodes.end();it++) {
      (*it)->remove(removeNode);
    }
 
  for(vector<Node*>::iterator it = nodes.begin(); it != nodes.end(); it++){
      if ((*it) == removeNode){
	nodes.erase(it);
	break;
      }
  }
}
void Graph::print(){
  for(vector<Node*>::iterator it = nodes.begin(); it != nodes.end(); it++){
    (*it)->print();
  }
}

Node* Graph::nodeLookup(char a){
 
  for(vector<Node*>::iterator it = nodes.begin(); it != nodes.end(); it++){
    if ( (*it)->name == a){
      return (*it);
    }
  }
  return NULL;
}
bool removeSmaller(vector<Link*>* links, Link* link){
 
  for(vector<Link*>::iterator it = links->begin(); it != links->end(); it++){
    if((*it)->next == link->next){
      if((*it)->weight > link->weight){
	links->erase(it);
	return true;
     
      }else return false;
    }
    
  }
  return true;

}
void orderedAdd(vector<Link*>* links,Link* link){
 
  
  if(removeSmaller(links,link)){
    bool inserted = false;
    for(vector<Link*>::reverse_iterator it = links->rbegin(); it != links->rend(); it++){      
      if(link->weight < (*it)->weight){
	links->insert(it.base(),link);
	inserted = true;
      }
    }
    if (!inserted){
      links->insert(links->rend().base(),link);
    }
  }
}
 void Graph::findPath(char a, char b){
 
   Node* start = nodeLookup(a);
   Node* end = nodeLookup(b);
 
   if(!start || !end){
     cout << "Those Nodes dont exist" << endl;

   }
   vector<Link*> active;
   vector<Link*> complete;
   
   Link* first = new Link();
 
   first->next = start;
   first->weight = 0;
   first->last = NULL;
   
   active.push_back(first);
   
   while((active.size()) > 0){
 
     if (complete.size() > 0){
       if((*complete.back()).next == end){
	 break;
       }
     }
 
     Link* current = (*active.rbegin());
 
     vector<Link*> newLinks = current->next->getLinks();
 
     for(vector<Link*>::iterator it = newLinks.begin(); it != newLinks.end(); it++){
       Link* newLink = (*it);
       
       bool isDone = false;
       
       for(vector<Link*>::iterator it = complete.begin(); it != complete.end(); it++){
	 if ((*it)->next == newLink->next){
	   isDone = true;
	   cout << "no" << endl;
	   break;
	 }
       }
       if(!isDone){
	 newLink->weight += current->weight;
	 orderedAdd(&active,newLink);
       }
     }
 
     complete.push_back(current);
     active.pop_back();
    
   }
 
   if((*complete.rbegin())->next == end){
     Node* nextPrint = end;
     cout << "The total weight was " << (*complete.rbegin())->weight << endl;
     
      for(vector<Link*>::reverse_iterator it = complete.rbegin(); it != complete.rend(); it++){
	 if ((*it)->next == nextPrint){
	   cout << nextPrint->name << "<-";
	   nextPrint = (*it)->last;
	 }
       }
      cout << endl;
   }
   else cout << "No posible path" << endl;
 }
