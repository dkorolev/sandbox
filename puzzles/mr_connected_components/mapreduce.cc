#include <algorithm>
#include <cassert>
#include <iostream>
#include <map>
#include <tuple>
#include <unordered_set>
#include <vector>

struct Edge {
  int a;
  int b;
  Edge() {}
  Edge(int a, int b) : a(a), b(b) {}
  bool operator==(const Edge& rhs) const {
    return std::tie(a, b) == std::tie(rhs.a, rhs.b);
  }
  bool operator<(const Edge& rhs) const {
    return std::tie(a, b) < std::tie(rhs.a, rhs.b);
  }
};

template<
  typename T_INPUT,
  typename T_MAPPER,
  typename T_REDUCER,
  typename T_OUTPUT_KEY,
  typename T_INTERMEDIATE_VALUE,
  typename T_OUTPUT_VALUE>
struct MapReduceRunner {
  typedef std::map<T_OUTPUT_KEY, std::vector<T_OUTPUT_VALUE>> output_type;
  template<typename T> static output_type Run(T begin, T end) {
    typedef std::map<T_OUTPUT_KEY, std::vector<T_INTERMEDIATE_VALUE>>
      INTERMEDIATE_OUTPUT_MAP_TYPE;
    INTERMEDIATE_OUTPUT_MAP_TYPE intermediate_output;
    while (begin != end) {
      // For the sake of pure experiment, create a new instance of mapper
      // for each input record.
      T_MAPPER mapper;
      mapper.Map(
        *begin++,
        [&intermediate_output](T_OUTPUT_KEY key, T_INTERMEDIATE_VALUE value) {
          intermediate_output[key].push_back(value);
        });
    }
    output_type output;
    for (auto record : intermediate_output) {
      T_OUTPUT_KEY key = record.first;
      typename INTERMEDIATE_OUTPUT_MAP_TYPE::mapped_type values = record.second;
      std::sort(values.begin(), values.end());
      T_REDUCER reducer;
      size_t i = 0;
      std::vector<T_OUTPUT_VALUE> this_key_output;
      reducer.Reduce(
        key,
        [&i, &values](){ assert(i < values.size()); return values[i++]; },
        [&i, &values](){ return i == values.size(); },
        [&this_key_output](T_OUTPUT_VALUE x){ this_key_output.push_back(x); });
      if (!this_key_output.empty()) {
        output[key] = this_key_output;
      }
    }
    return output;
  }
  template<typename T> static output_type Run(const T& x) {
    return Run(x.begin(), x.end());
  }
};

struct ConnectedComponents {
  // Phase 1: Have all "connected components", as seen from each node,
  // "look straight up": only keep the edges that connect each node
  // to its local master.
  struct Phase1Mapper {
    template<typename OUTPUT> void Map(const Edge& e, OUTPUT output) const {
      output(e.a, e.b);
      output(e.b, e.a);
    }
  };
  struct Phase1Reducer {
    template<typename NEXT, typename DONE, typename OUTPUT>
    void Reduce(int key, NEXT next, DONE done, OUTPUT output) {
      if (!done()) {
        std::vector<int> adjacent;
        adjacent.push_back(key);
        while (!done()) {
          const int i = next();
          adjacent.push_back(i); 
        }
        int& placeholder = *std::min_element(adjacent.begin(), adjacent.end());
        const int master = placeholder;
        placeholder = -1;  // Allow loops, but only when they are explicit.
        std::unordered_set<int> added;
        for (auto i : adjacent) {
          if (i != -1 && !added.count(i)) {
            output(Edge(i, master));
            added.insert(i);
          }
        }
      }
    }
  };
  // Phase 2: Collapse the output of stage 1 into the graph again.
  struct Phase2Mapper {
    typedef std::pair<int, std::vector<Edge>> T_INPUT;
    template<typename OUTPUT> void Map(const T_INPUT& record, OUTPUT output) {
      for (auto e : record.second) {
        assert(e.b <= e.a);
        output(e.a, e.b);
      }
    }
  };
  struct Phase2Reducer {
    template<typename NEXT, typename DONE, typename OUTPUT>
    void Reduce(int key, NEXT next, DONE done, OUTPUT output) {
      std::unordered_set<int> added;
      while (!done()) {
        const int adjacent = next();
        if (!added.count(adjacent)) {
          output(adjacent);
          added.insert(adjacent);
        }
      }
    }
  };
};

int main() {
  // Read the input, as an unstructured set of edges.
  typedef std::vector<Edge> INPUT_TYPE;
  INPUT_TYPE input;
  Edge e;
  while (std::cin >> e.a >> e.b) {
    input.push_back(e);
  }

  // Run the mapreduce, as many times as necessary until the graph is stable.
  bool done = false;
  do {
    // Should not matter, so why not randomize the order of records
    // in the input for the purposes of this test? :-)
    INPUT_TYPE randomized_input = input;
    std::random_shuffle(randomized_input.begin(), randomized_input.end());

    // Run stage1: Expand and reshuffle the edges.
    std::map<int, std::vector<Edge>> phase1_result = 
      MapReduceRunner<
        Edge,
        ConnectedComponents::Phase1Mapper,
        ConnectedComponents::Phase1Reducer,
        int,
        int,
        Edge>::Run(randomized_input);

    // Run stage2: Collapse.
    std::map<int, std::vector<int>> phase2_result =
      MapReduceRunner<
        std::pair<int, std::vector<Edge>>,
        ConnectedComponents::Phase2Mapper,
        ConnectedComponents::Phase2Reducer, 
        int,
        int,
        int>::Run(phase1_result);

    // Prepare the input for the next iteration.
    INPUT_TYPE new_input;
    for (auto entry : phase2_result) {
      for (auto subentry : entry.second) {
        new_input.push_back(Edge(entry.first, subentry));
      }
    }
    std::sort(new_input.begin(), new_input.end());

    // Run the iterations as long as the graph keeps changing.
    if (new_input == input) {
      done = true;
    } else {
      input = new_input;
    }
  } while (!done);

  // Construct and write the output.
  std::map<int, std::vector<int>> result;
  for (auto entry : input) {
    result[entry.b].push_back(entry.a);
  }
  for (auto entry : result) {
    printf("%d", entry.first);
    for (auto subentry : entry.second) {
      if (subentry > entry.first) {
        printf(" %d", subentry);
      }
    }
    printf("\n");
  }
}
