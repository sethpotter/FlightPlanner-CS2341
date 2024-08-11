#include "includes/catch.hpp"

#include <iostream>
#include "DSAdjacencyList.h"
#include "DSStack.h"

using namespace std;

TEST_CASE("AdjacencyList class", "[DSAdjacencyList]")
{
    SECTION("Insert")
    {
        DSAdjacencyList<int, int> temp;

        REQUIRE(temp.insert(5, 1) == true);
        REQUIRE(temp.insert(5, 1) == false);
        REQUIRE(temp.insert(5, 5) == true);
        REQUIRE(temp.insert(5, 2) == true);
        REQUIRE(temp.insert(1, 5) == true);

        temp.print();
    }

    SECTION("Remove Key & Remove Value")
    {
        DSAdjacencyList<int, int> temp;

        temp.insert(5, 1);
        temp.insert(5, 1);
        temp.insert(5, 5);
        temp.insert(5, 2);
        temp.insert(1, 5);

        REQUIRE(temp.removeValue(5, 1) == true);
        REQUIRE(temp.removeValue(5, 1) == false);
        REQUIRE(temp.removeKey(5) == true);
        REQUIRE(temp.removeKey(5) == false);

        temp.print();
    }
}

TEST_CASE("Stack class", "[DSStack]")
{
    SECTION("All Methods")
    {
        DSStack<int> stack;

        /// Push Testing.
        stack.push(3);
        stack.push(2);
        stack.push(1);

        cout << "Stack (Push): " << endl;
        stack.print();

        /// Peek Testing.
        REQUIRE(stack.peek() == 1);

        /// Pop Testing.
        REQUIRE(stack.pop() == 1);
        REQUIRE(stack.pop() == 2);
        REQUIRE(stack.pop() == 3);

        cout << "Stack (Pop): " << endl;
        stack.print();

        /// Is Empty Testing.
        REQUIRE(stack.isEmpty());
    }
}