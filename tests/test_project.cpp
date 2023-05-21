#include <criterion/criterion.h>
#include "../src/Cook.hpp"
#include "../src/Kitchen.hpp"


Test(Kitchen, kitchen_run)
{
    Plazza::Kitchen kitchen(2, 2, 1000);

    kitchen.run();
    // cr_assert_eq(kitchen.isStaturated(), false);
}

Test(Kitchen, kitchen_saturated)
{
    Plazza::Kitchen kitchen(2, 2, 1000);

    cr_assert_eq(kitchen.isStaturated(), false);
}

Test(Kitchen, kitchen_receive_order)
{
    Plazza::Kitchen kitchen(2, 2, 1000);

    std::vector<Plazza::Order> orderList = {
        Plazza::Order(Plazza::PizzaType::Regina, Plazza::PizzaSize::M),
        Plazza::Order(Plazza::PizzaType::Regina, Plazza::PizzaSize::M),
        Plazza::Order(Plazza::PizzaType::Regina, Plazza::PizzaSize::M),
        Plazza::Order(Plazza::PizzaType::Regina, Plazza::PizzaSize::M),
        Plazza::Order(Plazza::PizzaType::Regina, Plazza::PizzaSize::M)
    };

    kitchen.receiveOrder(orderList);
    cr_assert_eq(orderList.size(), 1);
}