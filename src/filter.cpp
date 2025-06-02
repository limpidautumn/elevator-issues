#include <elevator.hpp>

size_t roundUpToPowerOfTwo(const size_t &n) {
    size_t res = 1;
    while (res < n) res <<= 1;
    return res;
}

// pair<Resampled Data, Sampling Interval>
const pair<vector<db>, db> linearInterpolation(const Dataset &input,
                                               const size_t &targetSize) {
    DEBUG_ASSERT(input.size() >= 2);
    const db &startTime = input.front().fi;
    const db &endTime = input.back().fi;
    const db duration = endTime - startTime;
    const db samplingInterval = duration / targetSize;
    DEBUG_ASSERT(startTime + samplingInterval * (targetSize - 1) <= endTime);
    vector<db> result;
    Dataset::const_iterator it = input.begin();
    for (size_t i = 0; i < targetSize; ++i) {
        db x = startTime + samplingInterval * i;
        while (next(it)->fi < x) ++it, DEBUG_ASSERT(next(it) != input.end());
        const db &x0 = it->fi, &y0 = it->se, &x1 = next(it)->fi,
                 &y1 = next(it)->se;
        DEBUG_ASSERT(x0 <= x && x <= x1 && x0 < x1);
        result.pb(y0 + (y1 - y0) * (x - x0) / (x1 - x0));
    }
    return {result, samplingInterval};
}

// pair<Resampled Data, Sampling Interval>, Cut-off Frequency
const std::pair<std::vector<db>, db>
lowPassFilter(const std::pair<std::vector<db>, db> &_input,
              const db &cutoffFreq) {
    auto &[input, samplingInterval] = _input;
    size_t n = input.size();
    db fs = 1.0 / samplingInterval;
    db df = fs / n;
    db *in = fftwl_alloc_real(n);
    size_t nc = n / 2 + 1;
    fftwl_complex *out = fftwl_alloc_complex(nc);
    fftwl_plan plan_forward = fftwl_plan_dft_r2c_1d(n, in, out, FFTW_ESTIMATE);
    fftwl_plan plan_backward = fftwl_plan_dft_c2r_1d(n, out, in, FFTW_ESTIMATE);
    for (size_t i = 0; i < n; ++i) in[i] = input[i];
    fftwl_execute(plan_forward);
    for (size_t k = 0; k < nc; ++k) {
        db freq = k * df;
        if (freq > cutoffFreq) {
            out[k][0] = 0.0;
            out[k][1] = 0.0;
        }
    }
    fftwl_execute(plan_backward);
    std::vector<db> result(n);
    for (size_t i = 0; i < n; ++i) result[i] = in[i] / n;
    fftwl_destroy_plan(plan_forward);
    fftwl_destroy_plan(plan_backward);
    fftwl_free(in);
    fftwl_free(out);
    return {result, samplingInterval};
}

const Dataset toTypicalDataset(const pair<vector<db>, db> &_input) {
    auto &[input, samplingInterval] = _input;
    Dataset result;
    for (size_t i = 0; i < input.size(); ++i)
        result.pb({samplingInterval * i, input[i]});
    return result;
}
