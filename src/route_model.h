#ifndef ROUTE_MODEL_H
#define ROUTE_MODEL_H

#include <limits>
#include <cmath>
#include <unordered_map>
#include "model.h"
#include <iostream>
#include <math.h>
#include <vector>


using std::unordered_map;
using std::vector;


class RouteModel : public Model {
  public:
    class Node : public Model::Node {
      public:
        // Add public Node variables and methods here.
      	Node *parent = nullptr;
      	float h_value = std::numeric_limits<float>::max();
      	float g_value = 0.0;
      	bool visited = false;
      	vector<Node *> neighbors;
      
      	float distance(Node other) const{
          float e_dist;
          e_dist = sqrt(pow((x - other.x), 2)+pow((y - other.y), 2));
          return e_dist;
        }
      	void FindNeighbors();
        Node(){}
        Node(int idx, RouteModel * search_model, Model::Node node) : Model::Node(node), parent_model(search_model), index(idx) {}
      
      private:
        // Add private Node variables and methods here.
        int index;
        RouteModel *parent_model = nullptr;
      	Node * FindNeighbor(vector<int> node_indices);
    };
    
    // Add public RouteModel variables and methods here.
    RouteModel(const std::vector<std::byte> &xml);
  	auto &SNodes() { return m_Nodes;}
  
    std::vector<Node> path; // This variable will eventually store the path that is found by the A* search.
  
  	auto &GetNodeToRoadMap(){
      return node_to_road;
    }
  
  	Node &FindClosestNode(float x, float y);

  private:
    // Add private RouteModel variables and methods here.
  	vector<Node> m_Nodes;
  	unordered_map <int, vector<const Model::Road*>> node_to_road;
  	void CreateNodeToRoadHashmap();

};

#endif