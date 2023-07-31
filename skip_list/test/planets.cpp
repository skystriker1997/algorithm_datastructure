#include "skiplist.h"





int main() {

    SkipList<std::string , std::string> sl{};

    std::string p1 = "mercury";
    std::string p1_intro = "the first close to sun";
    sl.Insert(p1_intro, p1);

    std::string p2 = "venus";
    std::string p2_intro = "the second close to sun";
    sl.Insert(p2_intro, p2);

    std::string p3 = "earth";
    std::string p3_intro = "the third close to sun";
    sl.Insert(p3_intro, p3);

    std::string p4 = "mars";
    std::string p4_intro = "the fourth close to sun";
    sl.Insert(p4_intro, p4);

    std::string p5 = "jupyter";
    std::string p5_intro = "the fifth close to sun";
    sl.Insert(p5_intro, p5);

    std::string p6 = "saturn";
    std::string p6_intro = "the sixth close to sun";
    sl.Insert(p6_intro, p6);

    std::string p7 = "uranus";
    std::string p7_intro = "the seventh close to sun";
    sl.Insert(p7_intro, p7);

    std::string p8 = "neptune";
    std::string p8_intro = "the eighth close to sun";
    sl.Insert(p8_intro, p8);

    std::string p9 = "pluto";
    std::string p9_intro = "the ninth close to sun";
    sl.Insert(p9_intro, p9);


    std::cout << "after inserting all planets from solar system:" << std::endl;
    sl.PrintAll();

    std::cout << "the intro of mars: " << sl.Find(p3)->val_ << std::endl;

    sl.Delete(p4);
    std::cout << "after deleting mars:" << std::endl;
    sl.PrintAll();

    sl.DeleteAll();
    std::cout << "after deleting ALL:" << std::endl;
    sl.PrintAll();

    return 0;
}