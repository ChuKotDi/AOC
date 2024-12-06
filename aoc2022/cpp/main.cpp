#include <ctime>
#include "day_01/day_01.hpp"
#include "day_02/day_02.hpp"
#include "day_03/day_03.hpp"
#include "day_04/day_04.hpp"
#include "day_05/day_05.hpp"
#include "day_06/day_06.hpp"
#include "day_07/day_07.hpp"
#include "day_08/day_08.hpp"
#include "day_09/day_09.hpp"
#include "day_10/day_10.hpp"
#include "day_11/day_11.hpp"
#include "day_12/day_12.hpp"
#include "day_13/day_13.hpp"
#include "day_14/day_14.hpp"
#include "day_15/day_15.hpp"
#include "day_16/day_16.hpp"
#include "day_17/day_17.hpp"
#include "day_18/day_18.hpp"
#include "day_19/day_19.hpp"
#include "day_20/day_20.hpp"
#include "day_21/day_21.hpp"
#include "day_22/day_22.hpp"
#include "day_23/day_23.hpp"
#include "day_24/day_24.hpp"
#include "day_25/day_25.hpp"

int main()
{
    unsigned int start_time = clock();
    day1_start("../day_01/input.txt");
    day2_start("../day_02/input.txt");
    day3_start("../day_03/input.txt");
    day4_start("../day_04/input.txt");
    day5_start("../day_05/input.txt");
    day6_start("../day_06/input.txt");
    day7_start("../day_07/input.txt");
    day8_start("../day_08/input.txt");
    day9_start("../day_09/input.txt");
    day10_start("../day_10/input.txt");
    day11_start("../day_11/input.txt");
    day12_start("../day_12/input.txt");
    day13_start("../day_13/input.txt");
    day14_start("../day_14/input.txt");
    day15_start("../day_15/input.txt");
    day16_start("../day_16/input.txt");
    day17_start("../day_17/input.txt");
    day18_start("../day_18/input.txt");
    day19_start("../day_19/input.txt");
    day20_start("../day_20/input.txt");
    day21_start("../day_21/input.txt");
    day22_start("../day_22/input.txt");
    day23_start("../day_23/input.txt");
    day24_start("../day_24/input.txt");
    day25_start("../day_25/input.txt");
    unsigned int end_time = clock();
    unsigned int search_time = end_time - start_time;
    cout << endl << "Total time: " << search_time / 1000.0 << endl;
}
