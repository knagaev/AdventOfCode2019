// Day 3_2
//

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

pair<int, int> findCross(pair<int, int> firstBegin,
    pair<int, int> firstEnd,
    pair<int, int> secondBegin,
    pair<int, int> secondEnd)
{
    bool firstVertical = firstBegin.first != firstEnd.first;
    bool secondVertical = secondBegin.first != secondEnd.first;

    if ((firstVertical && secondVertical) || (!firstVertical && !secondVertical))
        return { 0, 0 };

    if (firstVertical)
    {
        auto firstBottom = min(firstBegin.first, firstEnd.first);
        auto firstTop = max(firstBegin.first, firstEnd.first);

        auto secondLeft = min(secondBegin.second, secondEnd.second);
        auto secondRight = max(secondBegin.second, secondEnd.second);

        if (secondBegin.first >= firstBottom
            && secondBegin.first <= firstTop
            && firstBegin.second >= secondLeft
            && firstBegin.second <= secondRight
            )
            return { secondBegin.first, firstBegin.second };
    }
    else
    {
        auto secondBottom = min(secondBegin.first, secondEnd.first);
        auto secondTop = max(secondBegin.first, secondEnd.first);

        auto firstLeft = min(firstBegin.second, firstEnd.second);
        auto firstRight = max(firstBegin.second, firstEnd.second);

        if (firstBegin.first >= secondBottom
            && firstBegin.first <= secondTop
            && secondBegin.second >= firstLeft
            && secondBegin.second <= firstRight
            )
            return { firstBegin.first, secondBegin.second };
    }

    return { 0, 0 };
}

int main()
{
    ifstream fin("input3_1.txt");

    vector<vector<string>> wires;
    string line;
    if (fin)
    {
        while (fin >> line)
        {
            vector<string> result;
            stringstream ss(line);
            string item;

            while (getline(ss, item, ','))
            {
                result.push_back(item);
            }
            wires.push_back(result);
        }
        fin.close();
    }

    vector<vector<pair<int, int>>> wireCoords;
    for (const auto& wire : wires)
    {
        vector<pair<int, int>> wireCoord;
        auto currentPoint = make_pair(0, 0);
        wireCoord.push_back(currentPoint);

        for (const auto& part : wire)
        {
            auto direction = part[0];
            auto distance = stoi(part.substr(1));
            switch (direction)
            {
            case 'R':
                currentPoint.second += distance;
                break;
            case 'U':
                currentPoint.first += distance;
                break;
            case 'L':
                currentPoint.second -= distance;
                break;
            case 'D':
                currentPoint.first -= distance;
                break;
            }
            wireCoord.push_back(currentPoint);
        }
        wireCoords.push_back(wireCoord);
    }

    int minDistance = numeric_limits<int>::max();
    for (auto it = cbegin(wireCoords); it != prev(cend(wireCoords)); ++it)
    {
        auto firstWireDistance = 0;
        for (auto jt = cbegin(*it); jt != prev(cend(*it)); ++jt)
        {
            auto firstWireSegment = make_pair(*jt, *next(jt));
            firstWireDistance += abs(firstWireSegment.first.first - firstWireSegment.second.first)
                + abs(firstWireSegment.first.second - firstWireSegment.second.second);

            auto secondWireDistance = 0;
            for (auto kt = cbegin(*next(it)); kt != prev(cend(*next(it))); ++kt)
            {
                auto secondWireSegment = make_pair(*kt, *next(kt));
                secondWireDistance += abs(secondWireSegment.first.first - secondWireSegment.second.first)
                    + abs(secondWireSegment.first.second - secondWireSegment.second.second);
                auto cross = findCross(firstWireSegment.first, firstWireSegment.second, secondWireSegment.first, secondWireSegment.second);
                if (cross != make_pair(0, 0))
                {
                    auto firstWireSegmentTillCross = firstWireDistance
                        - abs(firstWireSegment.second.first - cross.first)
                        - abs(firstWireSegment.second.second - cross.second);

                    auto secondWireSegmentTillCross = secondWireDistance
                        - abs(secondWireSegment.second.first - cross.first)
                        - abs(secondWireSegment.second.second - cross.second);

                    minDistance = min(minDistance, firstWireSegmentTillCross + secondWireSegmentTillCross);
                }
            }
        }
    }

    cout << minDistance << endl;

    return 0;
}

