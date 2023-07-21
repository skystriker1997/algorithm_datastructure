#include "skiplist.h"

int main() {
    SkipList sl;
    for(int i=1; i<21; i++)
        sl.Insert(i);
    std::cout << "after inserting 1-20: *********************" << std::endl;
    sl.PrintAll();
    sl.Insert(10);
    std::cout << "after inserting 10: *********************" << std::endl;
    sl.PrintAll();
    sl.Delete(10);
    std::cout << "after deleting 10: *********************" << std::endl;
    sl.PrintAll();
    sl.DeleteAll();
    std::cout << "after deleting ALL: *********************" << std::endl;
    sl.PrintAll();
    return 0;
}