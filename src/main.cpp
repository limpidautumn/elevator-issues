#include <elevator.hpp>

const array<Dataset, 3> toComp(const Dataset &acc) {
    const Dataset vel = integration(acc);
    const Dataset dsp = integration(vel);
    return {dsp, vel, acc};
}

const Dataset correction(const Dataset &acc0) { // Original Acceleration
    const Dataset vel0 = integration(acc0);     // Original Velocity
    const db &vf0 = vel0.back().se;             // Original Final Velocity
    const db bias = vf0 / (acc0.back().fi - acc0.front().fi); // Zero Bias
    const Dataset acc = acc0 - bias;                          // Acceleration
    return acc;
}

const Dataset filtering(const Dataset &acc0) {
    const db cutoffFreq = 3.0L; // Cut-off Frequency = 3Hz
    const size_t targetSize = roundUpToPowerOfTwo(acc0.size());
    const Dataset acc = toTypicalDataset(
        lowPassFilter(linearInterpolation(acc0, targetSize), cutoffFreq));
    return acc;
}

// [0] Program Name, [1] Source Data
signed main(int argc, char *argv[]) {
    if (argc != 2) throw std::runtime_error("Parameter error.");
    vector<string> args(argv, argv + argc);
    const Dataset _acc0 = csvRead(args[1], {0, 3});
    const Dataset acc0 = deduplication(_acc0);
    const array<Dataset, 3> res0 = toComp(acc0);
    csvWrite("./result/dsp.csv", res0[0], "displacement/m");
    csvWrite("./result/vel.csv", res0[1], "velocity/m⋅s⁻¹");
    csvWrite("./result/acc.csv", res0[2], "acceleration/m⋅s⁻²");
    const array<Dataset, 3> res1 = toComp(correction(acc0));
    csvWrite("./result/corr_dsp.csv", res1[0], "displacement/m");
    csvWrite("./result/corr_vel.csv", res1[1], "velocity/m⋅s⁻¹");
    csvWrite("./result/corr_acc.csv", res1[2], "acceleration/m⋅s⁻²");
    const array<Dataset, 3> res2 = toComp(filtering(acc0));
    csvWrite("./result/filt_dsp.csv", res2[0], "displacement/m");
    csvWrite("./result/filt_vel.csv", res2[1], "velocity/m⋅s⁻¹");
    csvWrite("./result/filt_acc.csv", res2[2], "acceleration/m⋅s⁻²");
    const array<Dataset, 3> res3 = toComp(correction(filtering(acc0)));
    csvWrite("./result/filt_corr_dsp.csv", res3[0], "displacement/m");
    csvWrite("./result/filt_corr_vel.csv", res3[1], "velocity/m⋅s⁻¹");
    csvWrite("./result/filt_corr_acc.csv", res3[2], "acceleration/m⋅s⁻²");
    return 0;
}
