Sorting a templated std::vector in C++ involves using the std::sort algorithm from the <algorithm> header. Since the vector is templated, the type of its elements is determined at runtime, and std::sort relies on the elements supporting the less-than operator (<) or a custom comparator.

Here’s a comprehensive guide:

1. Sorting with Default Behavior

If the vector contains elements of a type that supports the < operator (e.g., int, float, std::string), you can directly use std::sort.

#include <iostream>
#include <vector>
#include <algorithm> // For std::sort

template <typename T>
void sortVector(std::vector<T>& vec) {
std::sort(vec.begin(), vec.end());
}

int main() {
std::vector<int> numbers = {4, 2, 5, 1, 3};
sortVector(numbers);

    for (int num : numbers) {
        std::cout << num << " ";
    }
    // Output: 1 2 3 4 5
    return 0;

}

2. Sorting with a Custom Comparator

If the vector contains elements where the < operator isn’t sufficient or when you want a different sorting criterion, pass a custom comparator to std::sort.

#include <iostream>
#include <vector>
#include <algorithm> // For std::sort

template <typename T>
void sortVector(std::vector<T>& vec, bool (\*comp)(T, T)) {
std::sort(vec.begin(), vec.end(), comp);
}

bool descending(int a, int b) {
return a > b;
}

int main() {
std::vector<int> numbers = {4, 2, 5, 1, 3};
sortVector(numbers, descending);

    for (int num : numbers) {
        std::cout << num << " ";
    }
    // Output: 5 4 3 2 1
    return 0;

}

3. Sorting a Vector of Pairs

When working with std::pair or a similar custom type, you often need to specify a sorting criterion.

Example: Sorting by First Element

#include <iostream>
#include <vector>
#include <algorithm> // For std::sort

bool sortByFirst(const std::pair<int, int>& a, const std::pair<int, int>& b) {
return a.first < b.first;
}

int main() {
std::vector<std::pair<int, int>> vec = {{3, 10}, {1, 20}, {2, 15}};
std::sort(vec.begin(), vec.end(), sortByFirst);

    for (const auto& p : vec) {
        std::cout << "(" << p.first << ", " << p.second << ") ";
    }
    // Output: (1, 20) (2, 15) (3, 10)
    return 0;

}

4. Sorting Custom Objects

If your vector contains objects of a custom class, you can either: 1. Overload the < operator in your class. 2. Provide a custom comparator.

Using Overloaded <

#include <iostream>
#include <vector>
#include <algorithm> // For std::sort

class Person {
public:
std::string name;
int age;

    Person(std::string n, int a) : name(n), age(a) {}

    bool operator<(const Person& other) const {
        return age < other.age;  // Sort by age
    }

};

int main() {
std::vector<Person> people = {{"Alice", 30}, {"Bob", 25}, {"Charlie", 35}};
std::sort(people.begin(), people.end());

    for (const auto& person : people) {
        std::cout << person.name << " (" << person.age << ") ";
    }
    // Output: Bob (25) Alice (30) Charlie (35)
    return 0;

}

Using a Custom Comparator

#include <iostream>
#include <vector>
#include <algorithm> // For std::sort

class Person {
public:
std::string name;
int age;

    Person(std::string n, int a) : name(n), age(a) {}

};

bool sortByName(const Person& a, const Person& b) {
return a.name < b.name; // Sort by name
}

int main() {
std::vector<Person> people = {{"Alice", 30}, {"Charlie", 35}, {"Bob", 25}};
std::sort(people.begin(), people.end(), sortByName);

    for (const auto& person : people) {
        std::cout << person.name << " (" << person.age << ") ";
    }
    // Output: Alice (30) Bob (25) Charlie (35)
    return 0;

}

5. Sorting a Vector of Vectors

Sorting a std::vector<std::vector<T>> typically requires specifying the sorting criterion.

Example: Sorting by First Element of Inner Vectors

#include <iostream>
#include <vector>
#include <algorithm> // For std::sort

int main() {
std::vector<std::vector<int>> matrix = {{3, 2}, {1, 4}, {2, 5}};
std::sort(matrix.begin(), matrix.end(), [](const std::vector<int>& a, const std::vector<int>& b) {
return a[0] < b[0];
});

    for (const auto& row : matrix) {
        for (int val : row) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
    // Output:
    // 1 4
    // 2 5
    // 3 2
    return 0;

}

Key Notes on Sorting Templated Vectors

    1.	Requirements for std::sort:
    •	Elements must be comparable using < or a provided comparator.
    •	The vector must support random-access iterators.
    2.	Custom Comparators:
    •	Use a function pointer, lambda, or functor to define the sorting logic.
    3.	Performance:
    •	std::sort uses a hybrid algorithm (introsort), offering O(N log N) complexity in the average case.
    4.	Templated Function for Sorting:

You can generalize the sorting logic for any type using templates.

template <typename T, typename Compare>
void sortVector(std::vector<T>& vec, Compare comp) {
std::sort(vec.begin(), vec.end(), comp);
}

Let me know if you’d like further clarification or examples for specific scenarios! 🚀
