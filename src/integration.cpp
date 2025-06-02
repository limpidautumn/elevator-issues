#include <elevator.hpp>

const Dataset integration(const Dataset &origin) {
    Dataset result = Dataset();
    if (origin.empty()) return result;
    result.pb({origin.front().fi, 0.0L});
    for (auto it = ++origin.begin(); it != origin.end(); ++it) {
        db cur = (prev(it)->se + it->se) * (it->fi - prev(it)->fi) / 2;
        result.pb({it->fi, result.back().se + cur});
    }
    DEBUG_ASSERT(result.size() == origin.size());
    return result;
}
