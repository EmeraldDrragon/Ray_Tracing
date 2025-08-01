#ifndef INTERVAL_H
#define INTERVAL_H

class Interval {
public:
  double min, max;

  Interval() : min(+infinity), max(-infinity) {} // Default interval is empty

  Interval(double min, double max) : min(min), max(max) {}

  double size() const {
    return max - min;
  }

  bool contains(double x) const {
    return min <= x && x <= max;
  }

  bool surrounds(double x) const {
    return min < x && x < max;
  }

  double clamp(double x) const {
    if (x < min) return min;
    if (x > max) return max;
    return x;
  }

};

static const Interval empty    = Interval(+infinity, -infinity);
static const Interval universe = Interval(-infinity, +infinity);

#endif