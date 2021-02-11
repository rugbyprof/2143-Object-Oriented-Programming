#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

/**
 * Class: Group 
 * Extends: sf::Drawable
 * https://github.com/SFML/SFML/wiki/Tutorial:-Drawable-Group
 * Purpose:
 *      This class inherits from sf::Drawable so it can print multiple sprites with a 
 *      single call to window.draw. It makes it possible by using a vector to hold 
 *      multiple sprites, then overloads the draw method and applies it to all items
 *      within the vector.
 * @Methods:
 * public:
 *    Group() : m_drawables {}  // initialization list to create the data type at the bottom of the class
 *    virtual ~Group() = default; // = default is a c++11 way of saying use the compiler-generated version of that function
 *    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const    // const means we are not changing anything
 *          sf::RenderTarget is the base class for all drawables
 *          sf::RenderStates is define the state for the target being drawn (blend, transform, texture, shader)
 *    const sf::Drawable &operator[](std::size_t index) // overload the square brackets to access our vector and get a drawable
 *    std::size_t push_back(const sf::Drawable &drawable) // overload the push_back method to place a drawable on our vector
 *    const sf::Drawable &pop_back() // overload pop_back to remove a drawable from the vector
 * private:
 *    std::vector<std::reference_wrapper<const sf::Drawable>> m_drawables;  // a vector of Drawables 
 */
class Group : public sf::Drawable {
public:
    /**
     * Constructor
     *     https://stackoverflow.com/questions/2785612/c-what-does-the-colon-after-a-constructor-mean
     * @Params: none
     */
    Group() : m_drawables{}
    {
    }

    /**
     * Destructor
     *     https://stackoverflow.com/questions/6502828/what-does-default-mean-after-a-class-function-declaration
     * @Params: none
     */
    virtual ~Group() = default;

    /**
     * virtual = A virtual function a member function which is declared within base class and is re-defined (Overriden) by derived class.
     * function draw:
     *     draw an SFML object to some window
     */
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        for (const auto& drawable : m_drawables) {
            target.draw(drawable, states);
        }
    }

    /**
     * overloaded operator "[]"
     * @Params:
     *    index {std::size_t} : index of a drawable
     * @Returns:
     *     a drawable from prescribed index
     */
    const sf::Drawable& operator[](std::size_t index)
    {
        return m_drawables[index];
    }

    /**
     * push_back
     * @Params:
     *    drawable {const sf::Drawable} : what we are pushing
     * @Returns:
     *     The new size of the vector
     */
    std::size_t push_back(const sf::Drawable& drawable)
    {
        m_drawables.push_back(drawable);
        return m_drawables.size() - 1;
    }

    /**
     * pop_back
     * @Params:
     *    drawable {const sf::Drawable} : what we are pushing
     * @Returns:
     *     drawable {const sf::Drawable}
     */
    const sf::Drawable& pop_back()
    {
        const auto& drawable = m_drawables.back();
        m_drawables.pop_back();
        return drawable;
    }

private:
    /**
     * templated vector type
     * This defines a:
     *     - vector that holds drawables
     *     - The std::reference_wrapper is "type" that holds references since vectors cant really handle reference types.
     */
    std::vector<std::reference_wrapper<const sf::Drawable> > m_drawables;
};