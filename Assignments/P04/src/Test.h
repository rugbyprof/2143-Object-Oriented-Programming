#pragma once

#include "Console.h"

#include <cmath>
#include <sstream>
#include <string>

// -----------------------------------------------------------------------
// TestReport — a tiny unit-test helper.  (provided, read it)
//
// It's also a worked example of FUNCTION TEMPLATES:
//
//   report.check("2 + 2", 2 + 2, 4);
//   report.check("orange + 20", Color(255,128,0) + 20, Color(255,148,20));
//   report.check("sharpen", Kernel::sharpen().sum(), 1.0);
//
// One check() works for ints, Colors, Matrices, strings: any types A and
// E where  actual == expected  compiles and both can be printed with <<.
// The compiler writes a separate check<int,int>, check<Color,Color>, ...
// for each combination you use. If Color had no operator== or <<, the
// check() call would not compile. Templates are checked when USED.
//
//   report.checkThrows<std::out_of_range>("at(9, 9)", [&] { m.at(9, 9); });
//
// checkThrows takes the expected exception type as an EXPLICIT template
// argument (in the <>) and the code to run as a lambda.
// -----------------------------------------------------------------------
class TestReport {
public:
    template <typename A, typename E>
    void check(const std::string& what, const A& actual, const E& expected) {
        if (actual == expected) {
            pass(what);
        } else {
            std::ostringstream detail;
            detail << "expected " << expected << ", got " << actual;
            fail(what, detail.str());
        }
    }

    template <typename Exception, typename F>
    void checkThrows(const std::string& what, F code) {
        try {
            code();
            fail(what, "expected an exception, nothing was thrown");
        } catch (const Exception&) {
            pass(what);
        } catch (...) {
            fail(what, "threw the wrong kind of exception");
        }
    }

    // For doubles: exact == is unreliable (9 * (1.0/9) may not be exactly 1.0).
    void checkNear(const std::string& what, double actual, double expected,
                   double tolerance = 1e-9) {
        check(what + " (within " + std::to_string(tolerance) + ")",
              std::abs(actual - expected) <= tolerance, true);
    }

    // Prints the totals. Returns true if nothing failed.
    bool summary() const {
        std::ostringstream line;
        line << passed_ << " passed, " << failed_ << " failed";
        printStatus(failed_ == 0 ? "ALL PASS:" : "SOME FAIL:", line.str());
        return failed_ == 0;
    }

private:
    int passed_ = 0;
    int failed_ = 0;

    void pass(const std::string& what) {
        ++passed_;
        printLine(ftxui::hbox({
            ftxui::text("PASS ") | ftxui::color(ftxui::Color::Green),
            ftxui::text(what),
        }));
    }

    void fail(const std::string& what, const std::string& detail) {
        ++failed_;
        printLine(ftxui::hbox({
            ftxui::text("FAIL ") | ftxui::color(ftxui::Color::Red) | ftxui::bold,
            ftxui::text(what + ": " + detail),
        }));
    }
};
