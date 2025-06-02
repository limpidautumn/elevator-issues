#include <elevator.hpp>

const string fileRead(const string &filePath) {
    std::ifstream file(filePath);
    if (!file.is_open())
        throw std::runtime_error("Unable to open file: " + filePath);
    return string((std::istreambuf_iterator<char>(file)),
                  std::istreambuf_iterator<char>());
}

void fileWrite(const string &filePath, const string &content) {
    std::ofstream file(filePath);
    if (!file.is_open())
        throw std::runtime_error("Unable to open file: " + filePath);
    file << content;
    file.close();
}

const vector<string> split(const string &s, const char &delimiter) {
    vector<string> result;
    size_t start = 0;
    size_t end = s.find(delimiter);
    while (end != string::npos) {
        result.push_back(s.substr(start, end - start));
        start = end + 1;
        end = s.find(delimiter, start);
    }
    result.push_back(s.substr(start));
    return result;
}

const string dbToStr(const db &value) {
    array<char, 128> buffer{};
    auto [ptr, ec] = std::to_chars(buffer.data(), buffer.data() + buffer.size(),
                                   value, std::chars_format::general);
    if (ec != std::errc()) throw std::runtime_error("Failed to convert.");
    return string(buffer.data(), ptr);
}

const Dataset csvRead(const string &filePath, const pair<size_t, size_t> &pos) {
    Dataset result = Dataset();
    string content = fileRead(filePath);
    vector<string> v1 = split(content, '\n');
    if (v1.size() <= 5) throw std::runtime_error("Incorrect file format.");
    for (auto it = v1.begin() + 1; it != v1.end(); ++it) {
        if (*it == "") continue;
        vector<string> v2 = split(*it, ',');
        if (v2.size() != 5) throw std::runtime_error("Incorrect file format.");
        result.pb({std::stold(v2[pos.fi]), std::stold(v2[pos.se])});
    }
    return result;
}

const Dataset csvRead(const string &filePath) {
    return csvRead(filePath, {0, 1});
} // raw data: {0, 3}

// Labels: displacement/m, velocity/m⋅s⁻¹, acceleration/m⋅s⁻².
void csvWrite(const string &filePath, const Dataset &data,
              const string &label) {
    string result = "time/s," + label + '\n';
    for (const auto &[x, y] : data) {
        result += dbToStr(x) + ',' + dbToStr(y) + '\n';
    }
    fileWrite(filePath, result);
}
