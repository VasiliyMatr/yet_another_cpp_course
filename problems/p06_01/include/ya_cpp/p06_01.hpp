#ifndef P06_01_HPP
#define P06_01_HPP
#include <cassert>
#include <iostream>
#include <string>

namespace ya_cpp {

using namespace std::literals;

//  ===========================================================================

class Entity {
  public:
    Entity() : m_data_1(s_data_1), m_data_2(0), m_data_3(0) {}

    //  -------------------------------------------------------------------

    Entity(const int &data_1, int data_2, int data_3)
        : m_data_1(data_1), m_data_2(data_2), m_data_3(data_3) {}

    Entity(const int &data_1, int data_2) : Entity(data_1, data_2, 0) {}

    //  ---------------------------------------------------------------------

    ~Entity() { std::clog << "Entity::~Entity\n"; }

    //  ----------------------------------------

    auto data_1() const { return m_data_1; }
    auto data_2() const { return m_data_2; }
    auto data_3() const { return m_data_3; }

    //  ----------------------------------------

    const std::string &data_as_string() const;

    //  -----------------------------------------------------

    void set_data_3(int data);

    //  ------------------------------------

    static void test() {
        std::clog << "Entity::test : s_data_1 = " << s_data_1 << '\n';
    }

  private:
    struct Cached_Data {
        void update(const Entity &entity);

        std::string string;
        bool is_invalid = true;
    };

    //  -----------------------------------------------

    static inline auto s_data_1 = 0;

    static const auto s_data_2 = 0;

    //    static        const auto s_data_3 = "aaaaa"s; // error

    static inline const auto s_data_4 = "aaaaa"s;

    //  ---------------------------------------------

    const int &m_data_1 = 0;

    const int m_data_2 = 0;

    int m_data_3 = 0;

    //  ----------------------------------

    mutable Cached_Data m_cached_data;
};

} // namespace ya_cpp

#endif // P06_01_HPP
