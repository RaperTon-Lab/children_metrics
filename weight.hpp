#include "date.hpp"
#include <utility>

double boysHeight[19] = {50.5, 76.1, 85.6, 94.9, 102.9, 109.9, 116.1, 121.7, 127.0, 132.2, 137.5, 140, 147, 153, 160, 166, 171, 175, 177};
double boysWeight[19] = {3.3, 10.2, 12.3, 14.6, 16.7, 18.7, 20.7, 22.9, 25.3, 28.1, 31.4, 32.4, 37.0, 40.9, 47.0, 52.6, 58.0, 62.7, 65.0};
double girlsHeight[19] = {49.9, 75.0, 84.5, 93.9, 101.6, 108.4, 114.6, 120.6, 126.1, 132.2, 138.3, 142, 148, 155, 159, 161, 162, 163, 164};
double girlsWeight[19] = {3.2, 9.5, 11.8, 14.1, 16.0, 17.7, 19.5, 21.8, 24.8, 28.5, 32.5, 33.7, 38.7, 44.0, 48.0, 51.4, 53.0, 54.0, 54.4};

std::pair<float, float> calculateMetrics(Age age, char sex)
{

    double meanWeight, meanHeight, dayRatio, baseHeight, baseWeight, multiplier, height, weight;
    std::pair<float, float> metrics;
    dayRatio = double(age.days) / 30;
    // std::cout << "dayratio=" << dayRatio << std::endl;
    sex = tolower(sex);
    if (sex == 'f')
    {
        if (age.years < 2)
        {
            if (age.years < 1)
            {
                if (age.months < 3)
                {
                    meanWeight = (5.4 - 3.2) / 3.0;
                    baseWeight = girlsWeight[0];
                    meanHeight = (60.2 - 49.9) / 3.0;
                    multiplier = age.months + dayRatio;
                    baseHeight = girlsHeight[0];
                }
                else if (age.months < 6)
                {
                    meanWeight = (7.2 - 5.4) / 3.0;
                    baseWeight = 5.4;
                    meanHeight = (66.6 - 60.2) / 3.0;
                    multiplier = (age.months - 3) + dayRatio;
                    baseHeight = 60.2;
                }
                else if (age.months < 9)
                {
                    meanWeight = (8.6 - 7.2) / 3.0;
                    baseWeight = 7.2;
                    meanHeight = (71.1 - 66.6) / 3.0;
                    multiplier = (age.months - 6) + dayRatio;
                    baseHeight = 66.6;
                }
                else
                {
                    meanWeight = (9.5 - 8.6) / 3.0;
                    baseWeight = 8.6;
                    meanHeight = (75.0 - 71.1) / 3.0;
                    multiplier = (age.months - 9) + dayRatio;
                    baseHeight = 71.1;
                }
            }
            else if (age.months < 6)
            {
                meanWeight = (10.8 - 9.5) / 6.0;
                baseWeight = girlsWeight[1];
                meanHeight = (80.9 - 75.0) / 6.0;
                multiplier = age.months + dayRatio;
                baseHeight = girlsHeight[1];
            }
            else
            {
                meanWeight = (11.8 - 10.8) / 6.0;
                baseWeight = 10.5;
                meanHeight = (84.5 - 80.9) / 6.0;
                baseHeight = 80.9;
                multiplier = (age.months - 6) + dayRatio;
            }
        }
        else
        {
            meanWeight = (girlsWeight[age.years + 1] - girlsWeight[age.years]) / 12.0;
            baseWeight = girlsWeight[age.years];
            meanHeight = (girlsHeight[age.years + 1] - girlsHeight[age.years]) / 12.0;
            multiplier = age.months + dayRatio;
            baseHeight = girlsHeight[age.years];
        }
    }
    else if (sex == 'm')
    {
        if (age.years < 2)
        {
            if (age.years < 1)
            {
                if (age.months < 3)
                {
                    meanWeight = (6.0 - 3.3) / 3.0;
                    baseWeight = boysWeight[0];
                    meanHeight = (61.1 - 50.5) / 3.0;
                    multiplier = age.months + dayRatio;
                    baseHeight = boysHeight[0];
                }
                else if (age.months < 6)
                {
                    meanWeight = (7.8 - 6.0) / 3.0;
                    baseWeight = 6.0;
                    meanHeight = (67.8 - 61.1) / 3.0;
                    multiplier = (age.months - 3) + dayRatio;
                    baseHeight = 61.1;
                }
                else if (age.months < 9)
                {
                    meanWeight = (9.2 - 7.8) / 3.0;
                    baseWeight = 7.8;
                    meanHeight = (72.3 - 67.8) / 3.0;
                    multiplier = (age.months - 6) + dayRatio;
                    baseHeight = 67.8;
                }
                else
                {
                    meanWeight = (10.2 - 9.2) / 3.0;
                    baseWeight = 9.2;
                    meanHeight = (76.1 - 72.3) / 3.0;
                    multiplier = (age.months - 9) + dayRatio;
                    baseHeight = 72.3;
                }
            }
            else if (age.months < 6)
            {
                meanWeight = (11.5 - 10.2) / 6.0;
                baseWeight = boysWeight[1];
                meanHeight = (82.4 - 76.1) / 6.0;
                multiplier = age.months + dayRatio;
                baseHeight = boysHeight[1];
            }
            else
            {
                meanWeight = (12.3 - 11.5) / 6.0;
                baseWeight = 11.5;
                meanHeight = (85.6 - 82.4) / 6.0;
                baseHeight = 82.4;
                multiplier = (age.months - 6) + dayRatio;
            }
        }
        else
        {
            meanWeight = (boysWeight[age.years + 1] - boysWeight[age.years]) / 12.0;
            baseWeight = boysWeight[age.years];
            meanHeight = (boysHeight[age.years + 1] - boysHeight[age.years]) / 12.0;
            multiplier = age.months + dayRatio;
            baseHeight = boysHeight[age.years];
        }
    }
    /*std::cout << "baseHeight= " << baseHeight << std::endl;
    std::cout << "baseWeight= " << baseWeight << std::endl;
    std::cout << "meanHeight= " << meanHeight << std::endl;
    std::cout << "meanWeight= " << meanWeight << std::endl;
    std::cout << "multiplier= " << multiplier << std::endl;*/
    height = baseHeight + meanHeight * multiplier;
    weight = baseWeight + meanWeight * multiplier;
    metrics.first = height;
    metrics.second = weight;
    // std::cout << "\nHeight = " << height << "\tWeight = " << weight << std::endl;
    return metrics;
}
