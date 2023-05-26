#include <criterion/criterion.h>
#include "../src/Cook.hpp"
#include "../src/Kitchen.hpp"


Test(Kitchen, kitchen_run)
{
    // std::array<int, 2> fd = {1, 1};
    // Plazza::Kitchen kitchen(2, 2, 1000, fd);

    // kitchen.run();
    // cr_assert_eq(kitchen.isStaturated(), false);
}

Test(Kitchen, kitchen_saturated)
{
    // std::array<int, 2> fd = {1, 1};
    // Plazza::Kitchen kitchen(2, 2, 1000, fd);

    // cr_assert_eq(kitchen.isStaturated(), false);
}

Test(Kitchen, kitchen_receive_order)
{
    // std::array<int, 2> fd = {1, 1};
    // Plazza::Kitchen kitchen(2, 2, 1000, fd);

    // std::vector<Plazza::Order> orderList = {
    //     Plazza::Order(Plazza::PizzaType::Regina, Plazza::PizzaSize::M),
    //     Plazza::Order(Plazza::PizzaType::Regina, Plazza::PizzaSize::M),
    //     Plazza::Order(Plazza::PizzaType::Regina, Plazza::PizzaSize::M),
    //     Plazza::Order(Plazza::PizzaType::Regina, Plazza::PizzaSize::M),
    //     Plazza::Order(Plazza::PizzaType::Regina, Plazza::PizzaSize::M)
    // };

    // kitchen.receiveOrder(orderList);
    // cr_assert_eq(orderList.size(), 1);
}