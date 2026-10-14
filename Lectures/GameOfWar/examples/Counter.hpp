#pragma once

class Counter {
private:
    int value;

public:
    Counter();

    void increment();
    void decrement();
    void reset();

    int getValue() const;
};
