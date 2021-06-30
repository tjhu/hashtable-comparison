#include <iostream>
#include <x86intrin.h>
#include <absl/container/flat_hash_map.h>
#include <absl/container/node_hash_map.h>
#include <absl/container/btree_map.h>
#include <folly/container/F14Map.h>

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


int main() {
    const uint64_t TEST_SIZE = 1 << 22;

    bench_hashtable<absl::flat_hash_map, uint64_t, uint64_t>("flat_hash_map", TEST_SIZE);
    bench_hashtable<absl::node_hash_map, uint64_t, uint64_t>("node_hash_map", TEST_SIZE);
    bench_hashtable<absl::btree_map, uint64_t, uint64_t>("btree_map", TEST_SIZE);
    bench_hashtable<folly::F14FastMap, uint64_t, uint64_t>("F14FastMap", TEST_SIZE);
    bench_hashtable<folly::F14NodeMap, uint64_t, uint64_t>("F14NodeMap", TEST_SIZE);
    bench_hashtable<std::unordered_map, uint64_t, uint64_t>("unordered_map", TEST_SIZE);
    bench_hashtable<std::map, uint64_t, uint64_t>("std::map", TEST_SIZE);

    return 0;
}