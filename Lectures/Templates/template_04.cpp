/*****************************************************************************
 * template_04.cpp — Two Type Parameters and Out-of-Class Definitions
 *
 * What's new:
 *   - A class template with two type parameters: Entry<Key, Value>
 *   - Defining member functions BELOW the class (header-file style)
 *   - The syntax  template <typename K, typename V>  Entry<K, V>::Method()
 *   - A friend operator<< for a class template
 *
 * In a real project, everything in this file above main() would live in
 * Entry.h. Template definitions must be visible wherever the template is
 * used, so they go in the header, NOT in a separate .cpp file.
 *
 * Compile:  g++ -std=c++20 template_04.cpp -o template_04
 *****************************************************************************/
#include <iostream>
#include <string>

using namespace std;

// ---------------------- Entry.h would start here ---------------------------
template <typename Key, typename Value>
class Entry {
public:
    Entry(const Key& key, const Value& value);

    const Key& GetKey() const;
    const Value& GetValue() const;
    void SetValue(const Value& value);

    // A friend defined inside the class is the simplest way to give a class
    // template an operator<<. One is generated for each Entry<K, V>.
    friend ostream& operator<<(ostream& out, const Entry& entry) {
        out << entry.key_ << " => " << entry.value_;
        return out;
    }

private:
    Key key_;
    Value value_;
};

// Each out-of-class definition repeats the template header, and names the
// class as Entry<Key, Value> (not just Entry).
template <typename Key, typename Value>
Entry<Key, Value>::Entry(const Key& key, const Value& value)
    : key_(key), value_(value) {
}

template <typename Key, typename Value>
const Key& Entry<Key, Value>::GetKey() const {
    return key_;
}

template <typename Key, typename Value>
const Value& Entry<Key, Value>::GetValue() const {
    return value_;
}

template <typename Key, typename Value>
void Entry<Key, Value>::SetValue(const Value& value) {
    value_ = value;
}
// ---------------------- Entry.h would end here -----------------------------

int main() {
    Entry<string, int> high_score("Thorin", 100);
    Entry<int, string> student(1042, "Jordan");
    Entry<char, double> grade_cutoff('A', 90.0);

    high_score.SetValue(125);

    cout << high_score << "\n";
    cout << student << "\n";
    cout << grade_cutoff << "\n";

    // The standard library's version of this idea is std::pair:
    pair<string, int> same_idea("Malakai", 92);
    cout << same_idea.first << " => " << same_idea.second << "\n";

    return 0;
}

/*****************************************************************************
 * Try it:
 *   1. Move the out-of-class definitions into Entry.cpp, keep the class in
 *      Entry.h, and compile main in its own file. What error do you get, and
 *      is it a compiler error or a linker error?
 *   2. Remove  template <typename Key, typename Value>  from above GetKey().
 *      Read the error.
 *   3. Why are the parameters named Key and Value instead of T and U?
 *   4. Add a method  void Print() const  defined outside the class.
 *****************************************************************************/
