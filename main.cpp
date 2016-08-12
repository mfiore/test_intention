/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: mfiore
 *
 * Created on August 12, 2016, 5:42 PM
 */

#include <cstdlib>
#include "Mdp.h"
#include "DrinkWater.h"
#include "VariableSet.h"
#include "ReorderTable.h"
#include "IntentionGraph.h"

using namespace std;

/*
 * 
 */
void drinkReorderTest() {
    DrinkWater d;
    d.create("drink_water", true);

    ReorderTable r;
    r.create("reorder_table", true);

    IntentionGraph ig;

    std::vector<string> contexts = {"HotDay, AlreadyDrank"};

    IntentionNode drink_intention;
    drink_intention.name = "DrinkWater";
    drink_intention.linked_contexts = {"HotDay"};

    IntentionNode reorder_intention;
    drink_intention.name = "ReorderTable";
    drink_intention.linked_contexts = {"AlreadyDrank"};

    std::vector<IntentionNode> intentions={drink_intention,reorder_intention};
    
    std::vector<string> actions={"agent_move_table","agent_move_kitchen"};

    VariableSet initial_state;
    initial_state.set["agent_isAt"] = "counter";
    initial_state.set["glass_isAt"] = "table";
    initial_state.set["bottle_isAt"] = "table";
    initial_state.set["glass_capacity"] = "0";
    initial_state.set["bottle_capacity"] = "1";
    initial_state.set["has_drunk"] = "0";

    std::vector<Mdp*> mdps;
//    {&d,&r};
    ig.setGraph(contexts,intentions,actions,mdps,initial_state);
    
    VariableSet evidence;
    evidence.set["distance_human_move_table"]="close";
    evidence.set["toward_human_move_table"]="t";
    evidence.set["distance_human_move_kitchen"]="far";
    evidence.set["toward_human_move_kitchen"]="f";
    
    ig.computeProbability(evidence);


}

int main(int argc, char** argv) {
    drinkReorderTest();

    return 0;
}