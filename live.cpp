#include <bits/stdc++.h>

#define SIZE 50

using namespace std;

vector<int> counters(SIZE, 0);
int max_element = 0;
int min_element = 0;

int get_counter(int index) {
	if(index < 0 || index >= SIZE) return -1;

	if (counters[index] < min_element) {
  	counters[index] = min_element;
  }
  
  return counters[index];
}

void increment_counter(int index) {
	if(index < 0 || index >= SIZE) return -1;
  
  if (counters[index] < min_element) {
  	counters[index] = min_element;
  }
  
  counters[index]++;
    
  if(max_element < counters[index]) {
    max_element = counters[index];
  }
}

void set_all_counters_max(){
  min_element = max_element;
 
  /*
  for(int element : counters) {
    if(element > max) {
      element = max;
    }
  }
  
  for(int i; i < counters.size(); i++) {
   	counters[i] = max;
  }
  */
}

int main() {
  cout << get_counter(0) << endl;
  increment_counter(0);
  cout << get_counter(0) << endl;

  return 0;
}