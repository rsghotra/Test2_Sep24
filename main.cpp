#include <iostream>
#include <vector>
#include<queue>
#include<unordered_map>
#include<math.h>
using namespace std;

//signatures
void SmallestNumberRange();
void KDistanceApartString();
string KDistanceApartString(const string& str, int K);
pair<int, int> FindSmallestNumberRange(vector<vector<int>>& lists);


//compareror
struct ListValCompare {
  bool operator() (pair<int, pair<int, int>>& x, pair<int, pair<int, int>>& y) {
    return x.first > y.first;
  }
};

struct FrequencyCompare {
  bool operator()(pair<char, int>& x, pair<char, int>& y) {
    return x.second < y.second;
  }
};


pair<int, int> FindSmallestNumberRange(vector<vector<int>>& lists) {
  priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, ListValCompare> minHeap;
  int rangeStart = 0;
  int rangeEnd = INT32_MAX;
  int currentMax = INT32_MIN;
  for(int i = 0; i < lists.size(); i++) {
    if(lists[i].empty() == false) {
      minHeap.push(make_pair(lists[i][0], make_pair(i, 0)));
      currentMax = max(currentMax, lists[i][0]);
    }
  }

  while(minHeap.size() == lists.size()) {
    auto entry = minHeap.top();
    minHeap.pop();
    if(rangeEnd - rangeStart > currentMax - entry.first) {
      rangeEnd = currentMax; //current max need to be updated
      rangeStart = entry.first;
    }
    entry.second.second++;
    if(lists[entry.second.first].size() > entry.second.second) {
      entry.first = lists[entry.second.first][entry.second.second];
      minHeap.push(entry);
      currentMax = max(currentMax, entry.first);
    }
  }
  return make_pair(rangeStart, rangeEnd);
}

void SmallestNumberRange() {
  vector<vector<int>> lists = {{1, 5, 8}, {4, 12}, {7, 8, 10}};
  auto result = FindSmallestNumberRange(lists);
  cout << "Smallest range is: [" << result.first << ", " << result.second << "]\n";
}

string KDistanceApartString(const string& str, int K) {
  //check this out: priority queue, queue, map
  string result = "";
  unordered_map<char, int> mappings;
  queue<pair<char, int>> inputs;
  priority_queue<pair<char, int>, vector<pair<char, int>>, FrequencyCompare> maxHeap;
  for(char ch: str) {
    mappings[ch]++;
  }

  for(auto entry: mappings) {
    maxHeap.push(entry);
  }

  while(!maxHeap.empty()) {
    auto entry = maxHeap.top();
    maxHeap.pop();
    result += entry.first;
    entry.second--;
    inputs.push(entry); //regardless if its frequency is zero as it will contri to queue length
    if(inputs.size() == K) {
      auto entry = inputs.front();
      inputs.pop();
      if(entry.second > 0) {
        maxHeap.push(entry);
      }
    }
  }
  return result.size() == str.size() ? result : "";
}

void KDistanceApartString() {
  cout << "KDistance Apart String is: " << KDistanceApartString("mmpp", 2) << endl;
}

bool CanUniquelyConstructSequence(vector<int>& originalSeq, vector<vector<int>>& sequences){
  vector<int> sortedOrder;
  //as number of vertices are not given we will find out from the sequencies only;
  unordered_map<int, vector<int>> graph;
  unordered_map<int, int> inDegree;
  for(auto sequence: sequences) {
    for(int i = 0; i < sequence.size(); i++) {
      graph[sequence[i]] = vector<int>();
      inDegree[sequence[i]] = 0;
    }
  } 

  //build graph
  for(auto sequence: sequences) {
    for(int i = 0; i < sequence.size() - 1; i++) {
      int parent = sequence[i];
      int child = sequence[i+1];
      graph[parent].push_back(child);
      inDegree[child]++;
    }
  }

  //first early exit; If inDegree.size() != originalSequence then we do not have rules for all the vertices;
  if(inDegree.size() != originalSeq.size()) {
    return false;
  }

  queue<int> inputs;
  for(auto entry: inDegree) {
    if(entry.second == 0) {
      inputs.push(entry.first);
    }
  }

  while(!inputs.empty()) {
    if(inputs.size() > 1) {
      return false;
    }
    int entry = inputs.front();
    inputs.pop();
    if(entry != originalSeq[sortedOrder.size()]) {
      return false;
    }
    sortedOrder.push_back(entry);
    vector<int> children = graph[entry];
    for(auto child: children) {
      inDegree[child]--;
      if(inDegree[child] == 0) {
        inputs.push(child);
      }
    }
  }
  return sortedOrder.size() == originalSeq.size();
}


void CanUniquelyConstructSequence() {
  vector<int> originalSequence{3, 1, 4, 2, 5};
  vector<vector<int>> sequences{{3, 1, 5},{1, 4, 2, 5}};
  bool result = CanUniquelyConstructSequence(originalSequence, sequences);
  cout << "Can we Uniquely Construct: " << endl;
  cout << result << endl;
}

int SearchInARotatedArray(int key, vector<int>& nums) {
  int start = 0;
  int end = nums.size() - 1;
  while(start <= end) {
    int mid = start + (end - start)/2;
    if(nums[mid] == key) return mid;
    if(nums[start] < nums[mid]) {
      //left side if sorted;
      //find if num is present in sorted range
      if(key >= nums[start] && key < nums[mid]) {
        end = mid - 1;
      } else {
        start = mid + 1;
      }
    } else {
      if(key > nums[mid] && key <= nums[end]) {
        start = mid + 1;
      } else {
        end = mid -1;
      }
    }
  }
  return -1;
}

int Complement(int num) {
  // complement = number ^ all bit  set
  int count = 0;
  int n = num;
  while(n > 0) {
    count++;
    n = n >> 1;
  }

  int all_bits_set = pow(2, count) - 1;
  return all_bits_set ^ num;
  
}

void Complement() {
  cout << "Bitwise complement is: " << Complement(8) << endl;
  cout << "Bitwise complement is: " << Complement(10) << endl;
}

void SearchInARotatedArray() {
  vector<int> input{4,5,7,9,10,-1,2};
  int key = 10;
  int idx = SearchInARotatedArray(key, input);
  cout << "Searched in a Rotated Array: " << idx << endl;
}

int main() {
  SmallestNumberRange();
  KDistanceApartString();
  CanUniquelyConstructSequence();
  SearchInARotatedArray();
  Complement();
}