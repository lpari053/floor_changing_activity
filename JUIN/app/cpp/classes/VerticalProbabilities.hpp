//
//  StepProbabilities.hpp
//
//  Created by William OCCELLI on 11/03/2022.
//

#ifndef VerticalProbabilities_hpp
#define VerticalProbabilities_hpp

#include <stdio.h>
#include <vector>
class VerticalProbabilities
{
public:
    VerticalProbabilities();
    VerticalProbabilities(double vertical);
    ~VerticalProbabilities();

    void set_vertical(std::vector<double>);
    std::vector<double> get_vertical();


private:
    std::vector<double> _vertical;
};

#endif /* VerticalProbabilities_hpp */
