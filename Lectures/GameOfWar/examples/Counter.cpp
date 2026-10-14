#include "Counter.hpp"

Counter::Counter() : value(0) {
}

void Counter::increment() {
    value++;
}

void Counter::decrement() {
    value--;
}

void Counter::reset() {
    value = 0;
}

int Counter::getValue() const {
    return value;
}
