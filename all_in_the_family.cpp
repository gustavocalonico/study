
/*

QUESTION 1:

Suppose we have some input data describing a graph of relationships between parents and children over multiple families and generations. The data is formatted as a list of (parent, child) pairs, where each individual is assigned a unique positive integer identifier.

For example, in this diagram, 3 is a child of 1 and 2, and 5 is a child of 4:

1   2    4           30
 \ /   /  \           \ 
  3   5    9  15      16
   \ / \    \ / 
    6   7   12  


Sample input/output (pseudodata):

parent_child_pairs = [
    (5, 6), (1, 3), (2, 3), (3, 6), (15, 12),
    (5, 7), (4, 5), (4, 9), (9, 12), (30, 16)
]


Write a function that takes this data as input and returns two collections: one containing all individuals with zero known parents, and one containing all individuals with exactly one known parent.


Output may be in any order:

find_nodes_with_zero_and_one_parents(parent_child_pairs) => [
  [1, 2, 4, 15, 30],   # Individuals with zero parents
  [5, 7, 9, 16]        # Individuals with exactly one parent
]

Complexity Analysis variables:

n: number of pairs in the input

*/

/*
QUESTION 2

Suppose we have some input data describing a graph of relationships between parents and children over multiple generations. The data is formatted as a list of (parent, child) pairs, where each individual is assigned a unique positive integer identifier.

For example, in this diagram, 6 and 8 have common ancestors of 4 and 14.

             15
             |
         14  13
         |   |
1   2    4   12
 \ /   / | \ /
  3   5  8  9
   \ / \     \
    6   7     11

parent_child_pairs_1 = [
    (1, 3), (2, 3), (3, 6), (5, 6), (5, 7), (4, 5),
    (4, 8), (4, 9), (9, 11), (14, 4), (13, 12),
    (12, 9), (15, 13)
]

Write a function that takes this data and the identifiers of two individuals as inputs and returns true if and only if they share at least one ancestor. 

Sample input and output:

has_common_ancestor(parent_child_pairs_1, 3, 8) => false
has_common_ancestor(parent_child_pairs_1, 5, 8) => true
has_common_ancestor(parent_child_pairs_1, 6, 8) => true
has_common_ancestor(parent_child_pairs_1, 6, 9) => true
has_common_ancestor(parent_child_pairs_1, 1, 3) => false
has_common_ancestor(parent_child_pairs_1, 3, 1) => false
has_common_ancestor(parent_child_pairs_1, 7, 11) => true
has_common_ancestor(parent_child_pairs_1, 6, 5) => true
has_common_ancestor(parent_child_pairs_1, 5, 6) => true

Additional example: In this diagram, 4 and 12 have a common ancestor of 11.

        11
       /  \
      10   12
     /  \
1   2    5
 \ /    / \
  3    6   7
   \        \
    4        8

parent_child_pairs_2 = [
    (1, 3), (11, 10), (11, 12), (2, 3), (10, 2),
    (10, 5), (3, 4), (5, 6), (5, 7), (7, 8),
]

has_common_ancestor(parent_child_pairs_2, 4, 12) => true
has_common_ancestor(parent_child_pairs_2, 1, 6) => false
has_common_ancestor(parent_child_pairs_2, 1, 12) => false

n: number of pairs in the input

*/

/*
QUESTION 3

Suppose we have some input data describing a graph of relationships between parents and children over multiple generations. The data is formatted as a list of (parent, child) pairs, where each individual is assigned a unique positive integer identifier.

For example, in this diagram, the earliest ancestor of 6 is 14, and the earliest ancestor of 15 is 2. 

         14
         |
  2      4
  |    / | \
  3   5  8  9
 / \ / \     \
15  6   7    11

Write a function that, for a given individual in our dataset, returns their earliest known ancestor -- the one at the farthest distance from the input individual. If there is more than one ancestor tied for "earliest", return any one of them. If the input individual has no parents, the function should return null (or -1).

Sample input and output:

parent_child_pairs_3 = [
    (2, 3), (3, 15), (3, 6), (5, 6), (5, 7),
    (4, 5), (4, 8), (4, 9), (9, 11), (14, 4),
]

find_earliest_ancestor(parent_child_pairs_3, 8) => 14
find_earliest_ancestor(parent_child_pairs_3, 7) => 14
find_earliest_ancestor(parent_child_pairs_3, 6) => 14
find_earliest_ancestor(parent_child_pairs_3, 15) => 2
find_earliest_ancestor(parent_child_pairs_3, 14) => null or -1
find_earliest_ancestor(parent_child_pairs_3, 11) => 14


Additional example:

  14
  |
  2      4    1
  |    / | \ /
  3   5  8  9
 / \ / \     \
15  6   7    11

parent_child_pairs_4 = [
    (2, 3), (3, 15), (3, 6), (5, 6), (5, 7),
    (4, 5), (4, 8), (4, 9), (9, 11), (14, 2), (1, 9)
]

find_earliest_ancestor(parent_child_pairs_4, 8) => 4
find_earliest_ancestor(parent_child_pairs_4, 7) => 4
find_earliest_ancestor(parent_child_pairs_4, 6) => 14
find_earliest_ancestor(parent_child_pairs_4, 15) => 14
find_earliest_ancestor(parent_child_pairs_4, 14) => null or -1
find_earliest_ancestor(parent_child_pairs_4, 11) => 4 or 1

n: number of pairs in the input

*/

#include <bits/stdc++.h>

using namespace std;

void print_vector(vector<int> vect) {
  for(int i : vect)
    cout << i << " ";
  cout << endl;
}

void print_set(set<int> set, bool line = true) {
  for(int i : set)
    cout << i << " ";
  if(line) cout << endl;
}

pair<vector<int>, vector<int>> find_one_zeroes(vector<pair<int, int>> pairs) {
  set<int> zeroes, ones;

  for(auto pair : pairs) {
    int times_child = 0, times_parent = 0;
    int parent = pair.first;
    int child = pair.second;
    
    for(auto pair2 : pairs) {
      int child2 = pair2.second;
      if(child == child2) {
        times_child++;
      }
      if(parent == child2) {
        times_parent++;
      }
    }

    if(times_parent == 0) {
      zeroes.insert(parent);
    }
    if(times_child == 1) {
      ones.insert(child);
    }
  }

  vector<int> zeroes_vect(zeroes.begin(), zeroes.end());
  vector<int> ones_vect(ones.begin(), ones.end());
  return make_pair(zeroes_vect, ones_vect);
}

void dfs(int node, map<int, set<int>> graph, set<int> &ancestors) {
  for(int parent : graph[node]) {
    ancestors.insert(parent);
    dfs(parent, graph, ancestors);
  }
}

bool has_common_ancestor(vector<pair<int, int>> pairs, int a, int b) {
  map<int, set<int>> parent_graph;

  // List the graph containing all direct parents from that child
  for(auto pair : pairs) {
    int parent = pair.first;
    int child = pair.second;
    parent_graph[child].insert(parent);
  }

  set<int> a_ancestors, b_ancestors;
  dfs(a, parent_graph, a_ancestors);
  dfs(b, parent_graph, b_ancestors);
  
  cout << a << ": ["; print_set(a_ancestors, false); cout << "] ";
  cout << b << ": ["; print_set(b_ancestors, false); cout << "] ";

  for(int a_it : a_ancestors) {
    for(int b_it : b_ancestors) {
      if(a_it == b_it) {
        cout << "true" << endl;
        return true;
      }
    }
  }
  
  cout << "false" << endl;
  return false;
}

int earliest_ancestor(vector<pair<int, int>> pairs, int node) {
  map<int, vector<int>> parent_graph;

  // List the graph containing all direct parents from that child
  for(auto pair : pairs) {
    int parent = pair.first;
    int child = pair.second;
    parent_graph[child].push_back(parent);
  }

  queue<int> queue;

  for(int el : parent_graph[node]) {
    queue.push(el);
  }

  int earliest_ancestor = -1;
  while(!queue.empty()) {
    int current_node = queue.front();
    queue.pop();
    for(int parent : parent_graph[current_node]) {
      queue.push(parent);
      earliest_ancestor = parent;
    }
  }

  cout << node << ": " << earliest_ancestor << endl;
  return earliest_ancestor;
}

int main() {
  vector<pair<int, int>> parent_child_pairs = {
    make_pair(5, 6),
    make_pair(1, 3),
    make_pair(2, 3),
    make_pair(3, 6),
    make_pair(15, 12),
    make_pair(5, 7),
    make_pair(4, 5),
    make_pair(4, 9),
    make_pair(9, 12),
    make_pair(30, 16)
  };

  vector<pair<int, int>> parent_child_pairs_1 = {
    make_pair(1, 3),
    make_pair(2, 3),
    make_pair(3, 6),
    make_pair(5, 6),
    make_pair(5, 7),
    make_pair(4, 5),
    make_pair(4, 8),
    make_pair(4, 9),
    make_pair(9, 11),
    make_pair(14, 4),
    make_pair(13, 12),
    make_pair(12, 9),
    make_pair(15, 13)
  };

  vector<pair<int, int>> parent_child_pairs_2 = {
    make_pair(1, 3),
    make_pair(11, 10),
    make_pair(11, 12),
    make_pair(2, 3),
    make_pair(10, 2),
    make_pair(10, 5),
    make_pair(3, 4),
    make_pair(5, 6),
    make_pair(5, 7),
    make_pair(7, 8)
  };

  vector<pair<int, int>> parent_child_pairs_3 = {
    make_pair(2, 3),
    make_pair(3, 15),
    make_pair(3, 6),
    make_pair(5, 6),
    make_pair(5, 7),
    make_pair(4, 5),
    make_pair(4, 8),
    make_pair(4, 9),
    make_pair(9, 11),
    make_pair(14, 4)
  };

  vector<pair<int, int>> parent_child_pairs_4 = {
    make_pair(2, 3),
    make_pair(3, 15),
    make_pair(3, 6),
    make_pair(5, 6),
    make_pair(5, 7),
    make_pair(4, 5),
    make_pair(4, 8),
    make_pair(4, 9),
    make_pair(9, 11),
    make_pair(14, 2),
    make_pair(1, 9)
  };

  pair<vector<int>, vector<int>> response = find_one_zeroes(parent_child_pairs);
  
  // Question 1
  print_vector(response.first);
  print_vector(response.second);

  // Question 2
  has_common_ancestor(parent_child_pairs_2, 4, 12);
  has_common_ancestor(parent_child_pairs_2, 1, 6);
  has_common_ancestor(parent_child_pairs_2, 1, 12);

  // Question 3
  earliest_ancestor(parent_child_pairs_3, 8);
  earliest_ancestor(parent_child_pairs_3, 7);
  earliest_ancestor(parent_child_pairs_3, 6);
  earliest_ancestor(parent_child_pairs_3, 15);

  return 0;
}