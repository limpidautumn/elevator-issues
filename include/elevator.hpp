#pragma once
#define DEBUG

#include <algorithm>
#include <array>
#include <charconv>
#include <cstdio>
#include <fftw3.h>
#include <fstream>
#include <iostream>
#include <utility>
#include <vector>
#define fi first
#define se second
#define pb push_back
using std::array;
using std::pair;
using std::string;
using std::vector;

using db = long double;
using DataPoint = pair<db, db>;
using Dataset = vector<DataPoint>;

#ifdef DEBUG
#include <cassert>
#define DEBUG_ASSERT(expr) assert(expr)
#else
#define DEBUG_ASSERT(expr) ((void)0)
// #define DEBUG_ASSERT(expr) (expr, (void)0)
#endif

// data_structure.cpp
const Dataset operator+(const Dataset &, const db &);
const Dataset operator-(const Dataset &, const db &);
const Dataset deduplication(const Dataset &);

// file_operation.cpp
const string fileRead(const string &);
void fileWrite(const string &, const string &);
const vector<string> split(const string &, const char &);
const string dbToStr(const db &);
const Dataset csvRead(const string &, const pair<size_t, size_t> &);
const Dataset csvRead(const string &);
void csvWrite(const string &, const Dataset &, const string &);

// integration.cpp
const Dataset integration(const Dataset &);

// filter.cpp
size_t roundUpToPowerOfTwo(const size_t &);
const pair<vector<db>, db> linearInterpolation(const Dataset &, const size_t &);
const pair<vector<db>, db> lowPassFilter(const pair<vector<db>, db> &,
                                         const db &);
const Dataset toTypicalDataset(const pair<vector<db>, db> &);
