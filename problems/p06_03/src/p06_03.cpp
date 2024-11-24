module;

#include <cassert>
#include <iostream>
#include <string>

export module p06_03;

using namespace std::literals;

//  ===========================================================================

export class Entity {
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

    const auto &data_as_string() const {
        if (m_cached_data.is_invalid) {
            m_cached_data.update(*this);
        }

        return m_cached_data.string;
    }

    //  -----------------------------------------------------

    //    void set_data_3(int data) { m_data_3 = data; } // bad

    void set_data_3(int data) {
        m_data_3 = data;

        m_cached_data.is_invalid = true;
    }

    //  ------------------------------------

    static void test() {
        std::clog << "Entity::test : s_data_1 = " << s_data_1 << '\n';
    }

  private:
    struct Cached_Data {
        void update(const Entity &entity) {
            string = (std::to_string(entity.m_data_1) + '/' +
                      std::to_string(entity.m_data_2) + '/' +
                      std::to_string(entity.m_data_3));

            is_invalid = false;
        }

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
