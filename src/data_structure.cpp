#include <elevator.hpp>
const Dataset operator+(const Dataset &a, const db &d) {
    Dataset result = Dataset();
    for (const auto &[x, y] : a) result.pb({x, y + d});
    return result;
}
const Dataset operator-(const Dataset &a, const db &d) { return a + (-d); }
bool cmp(const DataPoint &a, const DataPoint &b) { return a.fi == b.fi; }

const Dataset deduplication(const Dataset &input) {
    Dataset result = input;
    sort(result.begin(), result.end());
    Dataset::iterator it = unique(result.begin(), result.end(), cmp);
    result.erase(it, result.end());
    return result;
}
