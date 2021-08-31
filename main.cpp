#include <iostream>
#include <x86intrin.h>
#include <string_view>
#include <absl/container/flat_hash_map.h>
#include <absl/container/node_hash_map.h>
#include <absl/container/btree_map.h>
// #include <folly/container/F14Map.h>


struct Flow {
  uint32_t src_ip;
  uint32_t dst_ip;
  uint16_t src_port;
  uint16_t dst_port;
  uint16_t proto;

  friend bool operator==(const Flow &lhs, const Flow &rhs) {
    return lhs.src_ip == rhs.src_ip && lhs.dst_ip == rhs.dst_ip &&
        lhs.src_port == rhs.src_port && lhs.dst_port == rhs.dst_port &&
        lhs.proto == rhs.proto;
  }
};

template <typename H>
H AbslHashValue(H h, const Flow &f) {
  return H::combine(std::move(h), f.src_ip, f.dst_ip, f.src_port, f.dst_port,
                    f.proto);
}

template <template <typename K, typename V> class HT, typename K, typename V>
void bench_hashtable(std::string_view name, uint64_t test_size) {
    unsigned int tmp;
    HT<K, V> map;

    const auto start = __rdtsc();
    for (uint64_t i = 0; i < test_size; i++) {
        map.insert({i, i});
    }
    const auto end = __rdtscp(&tmp);
    const auto duration = end - start;

    std::cout << "Benchmark results for " << name << std::endl;
    std::cout << "Duration: " << duration << " cycles"  << std::endl;
    std::cout << "Insertions: " << test_size << std::endl;
    std::cout << "Cycles per insertion: " << (double)duration / test_size << " cycles"  << std::endl;
    std::cout << std::endl;
}

void bench_flow() {
    const uint64_t TEST_SIZE = 1 << 22;
    const std::string name("c flat Flow");
    unsigned int tmp;
    absl::flat_hash_map<Flow, Flow> map;
    Flow f;

    const auto start = __rdtsc();
    for (uint64_t i = 0; i < TEST_SIZE; i++) {
        f.src_ip = i;
        map.insert({f, f});
    }
    const auto end = __rdtscp(&tmp);
    const auto duration = end - start;

    std::cout << "Benchmark results for " << name << std::endl;
    std::cout << "Duration: " << duration << " cycles"  << std::endl;
    std::cout << "Insertions: " << TEST_SIZE << std::endl;
    std::cout << "Cycles per insertion: " << (double)duration / TEST_SIZE << " cycles"  << std::endl;
    std::cout << std::endl;
}


int main() {
    const uint64_t TEST_SIZE = 1 << 22;

    // bench_hashtable<absl::flat_hash_map, uint64_t, uint64_t>("flat_hash_map", TEST_SIZE);
    // bench_hashtable<absl::node_hash_map, uint64_t, uint64_t>("node_hash_map", TEST_SIZE);
    // bench_hashtable<absl::btree_map, uint64_t, uint64_t>("btree_map", TEST_SIZE);
    // bench_hashtable<folly::F14FastMap, uint64_t, uint64_t>("F14FastMap", TEST_SIZE);
    // bench_hashtable<folly::F14NodeMap, uint64_t, uint64_t>("F14NodeMap", TEST_SIZE);
    // bench_hashtable<std::unordered_map, uint64_t, uint64_t>("unordered_map", TEST_SIZE);
    // bench_hashtable<std::map, uint64_t, uint64_t>("std::map", TEST_SIZE);
    bench_flow();

    return 0;
}