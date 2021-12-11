// barret reduction for fast modular multiplication
uint64_t reduce(uint64_t a) {
  return a - (uint64_t)((__uint128_t(-1ULL / p) * a) >> 64) * p;
}