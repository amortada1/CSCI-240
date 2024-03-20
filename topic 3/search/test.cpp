#include "search.h"
#include "test.h"

void testMembership();
void testNonmembership();

int main(int argc, char const *argv[])
{
    testMembership();
    testNonmembership();

    return 0;
}

void testMembership()
{
    int array[]{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int count = sizeof(array) / sizeof(array[0]);

    testTrue(Searcher<int>::binSearch(array, count, 0) == 0, "test 0 membership");
    testTrue(Searcher<int>::binSearch(array, count, 9) == 9, "test 9 membership");
    testTrue(Searcher<int>::binSearch(array, count, 4) == 4, "test 4 membership");
}

void testNonmembership()
{
    int array[]{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int count = sizeof(array) / sizeof(array[0]);

    testTrue(Searcher<int>::binSearch(array, count, -1) == -1, "test -1 nonmembership");
    testTrue(Searcher<int>::binSearch(array, count, 10) == -1, "test 10 nonmembership");
}
