// Tests.cpp — unit tests for Matrix, Color, Kernel, and Pipeline.
//
// The tests marked PROVIDED are written for you; they fail until your
// code is right, so use them as a checklist. Then write your own in the
// YOUR TESTS section (see the README for how many and what kind).
//
//   ./build/imgtool --test

#include "Tests.h"

#include "Color.h"
#include "FilterFactory.h"
#include "Kernel.h"
#include "Matrix.h"
#include "Pipeline.h"
#include "Test.h"

#include <stdexcept>
#include <string>

namespace {

void provided(TestReport& t) {
    // ---- Matrix<int> ----
    Matrix<int> m(2, 3, {1, 2, 3,
                         4, 5, 6});
    t.check("Matrix rows", m.rows(), 2);
    t.check("Matrix cols", m.cols(), 3);
    t.check("Matrix at(1, 2)", m.at(1, 2), 6);
    t.checkThrows<std::out_of_range>("Matrix at(2, 0) throws", [&] { m.at(2, 0); });
    t.checkThrows<std::invalid_argument>("Matrix wrong value count throws",
                                         [] { Matrix<int>(2, 2, {1, 2, 3}); });

    Matrix<int> doubled = m;
    doubled.forEach([](int& x) { x *= 2; });
    t.check("Matrix forEach doubles", doubled, Matrix<int>(2, 3, {2, 4, 6, 8, 10, 12}));

    // ---- Color ----
    t.check("Color clamps in constructor", Color(300, -5, 128), Color(255, 0, 128));
    t.check("Color + int clamps", Color(250, 10, 0) + 10, Color(255, 20, 10));
    t.check("Color * 0.5", Color(200, 100, 51) * 0.5, Color(100, 50, 26));
    t.check("Color fromHex", Color::fromHex("#ff8000"), Color(255, 128, 0));
    t.checkThrows<std::invalid_argument>("Color fromHex bad input throws",
                                         [] { Color::fromHex("#ff80"); });
    t.check("Color operator[] green", Color(1, 2, 3)[1], 2);

    // ---- Kernel ----
    t.checkNear("sharpen sums to 1", Kernel::sharpen().sum(), 1.0);
    t.checkNear("edgeDetect sums to 0", Kernel::edgeDetect().sum(), 0.0);
    t.checkThrows<std::invalid_argument>("2x2 kernel throws",
                                         [] { Kernel(Matrix<double>(2, 2)); });

    // ---- Pipeline (Composite) ----
    auto inner = std::make_unique<Pipeline>("inner");
    inner->add(FilterFactory::create({"invert", 0}));
    Pipeline outer("outer");
    outer.add(FilterFactory::create({"brighten", 10}));
    outer.add(std::move(inner));
    t.check("nested pipeline name", outer.name(),
            std::string("outer[brighten(10) -> inner[invert]]"));

    Grid g(1, 1, Color(0, 0, 0));
    outer.apply(g);   // brighten 10 -> (10,10,10), invert -> (245,245,245)
    t.check("nested pipeline applies in order", g(0, 0), Color(245, 245, 245));
}

void yours(TestReport& t) {
    // TODO: your tests. See the README for what to cover.
    (void)t;
}

}  // namespace

bool runAllTests() {
    TestReport t;
    provided(t);
    yours(t);
    return t.summary();
}
