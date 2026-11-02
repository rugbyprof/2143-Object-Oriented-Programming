/*****************************************************************************
 * template_07.cpp — Templates as an "Interface Without Inheritance"
 *
 * What's new:
 *   - A class template that calls METHODS on T (item.Name(), item.Score())
 *   - Unrelated classes (Player, Team, Monster) all work, because each one
 *     provides the methods the template needs
 *   - This is called "duck typing": if it has Name() and Score(), it's rankable
 *
 * OOP angle: In the polymorphism lectures, Player and Team would both inherit
 * from an abstract Rankable base class. Here they share NO base class. The
 * template's requirements act as an implicit interface, checked at compile
 * time instead of runtime.
 *
 * Compile:  g++ -std=c++20 template_07.cpp -o template_07
 *****************************************************************************/
#include <algorithm>
#include <cstddef>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Requirements on T (the "implicit interface"):
//   - T can be copied
//   - t.Name()  returns something printable
//   - t.Score() returns something comparable with >
template <typename T>
class Leaderboard {
public:
    explicit Leaderboard(size_t max_entries)
        : max_entries_(max_entries) {
    }

    void Submit(const T& entry) {
        entries_.push_back(entry);
        sort(entries_.begin(), entries_.end(), [](const T& left, const T& right) {
            return left.Score() > right.Score();
        });
        if (entries_.size() > max_entries_) {
            entries_.pop_back();   // Drop the lowest score.
        }
    }

    void Print(const string& title) const {
        cout << "=== " << title << " ===\n";
        for (size_t i = 0; i < entries_.size(); ++i) {
            cout << i + 1 << ". " << entries_[i].Name() << " (" << entries_[i].Score() << ")\n";
        }
    }

private:
    vector<T> entries_;
    size_t max_entries_;
};

// Three unrelated classes. None inherits from anything.
class Player {
public:
    Player(const string& name, int points)
        : name_(name), points_(points) {
    }

    string Name() const {
        return name_;
    }

    int Score() const {
        return points_;
    }

private:
    string name_;
    int points_;
};

class Team {
public:
    Team(const string& name, int wins, int losses)
        : name_(name), wins_(wins), losses_(losses) {
    }

    string Name() const {
        return name_;
    }

    // A team's "score" is its win percentage. Score() returns double here,
    // int in Player. The template doesn't care, as long as > works.
    double Score() const {
        int games = wins_ + losses_;
        if (games == 0) {
            return 0.0;
        }
        return 100.0 * wins_ / games;
    }

private:
    string name_;
    int wins_;
    int losses_;
};

class Monster {
public:
    Monster(const string& species, int hit_points)
        : species_(species), hit_points_(hit_points) {
    }

    string Species() const {
        return species_;
    }

    int HitPoints() const {
        return hit_points_;
    }

private:
    string species_;
    int hit_points_;
};

int main() {
    Leaderboard<Player> players(3);
    players.Submit(Player("Thorin", 85));
    players.Submit(Player("Malakai", 92));
    players.Submit(Player("Jordan", 77));
    players.Submit(Player("Rhea", 99));   // Pushes Jordan off the board.
    players.Print("Top Players");

    Leaderboard<Team> teams(2);
    teams.Submit(Team("Mustangs", 8, 2));
    teams.Submit(Team("Bulldogs", 5, 5));
    teams.Submit(Team("Owls", 9, 3));
    teams.Print("Top Teams");

    // Monster has no Name() or Score(), so it does not fit the interface.
    // Leaderboard<Monster> monsters(5);                 // Compiles (!)
    // monsters.Submit(Monster("Troll", 40));             // Error here

    return 0;
}

/*****************************************************************************
 * Try it:
 *   1. Uncomment the two Monster lines one at a time. Why does the first
 *      line compile but the second fail?
 *   2. Make Monster rankable WITHOUT changing Leaderboard. (Two approaches:
 *      add methods to Monster, or write a small adapter class that wraps a
 *      Monster.) Which is better design if you can't edit Monster?
 *   3. Rewrite this using an abstract base class  Rankable  with pure
 *      virtual Name() and Score(). What do you need to store in the vector
 *      now? What problem does Team's double Score() cause?
 *   4. List one advantage of the template version and one advantage of
 *      the virtual version.
 *****************************************************************************/
