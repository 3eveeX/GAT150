#include "GameData.h"

namespace GameData {
    std::vector<whermst::vec2> shipPoints{
           {10, 0},
           {-10, -3},
           {-5, 0},
           {-10, 3}
    };

    std::vector<whermst::vec2> enemyPoints{
   { -2, -5 },
   { 0, -5 },
   { 1, -4 },
   { 0, -3 },
   { 1, 0 },
   { -1, 2 },
   { -5, 1 },
   { -5, -2 },
   { -4, -3 },
   { -4, -5 },
   { -3, -6 }
    };

    std::vector<whermst::vec2> projectilePoints{
        { -7, 0 },
        { -5, 0 },
        { -3, 0 }
	};
}

