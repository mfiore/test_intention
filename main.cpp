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

#include "EatCookie.h"
#include "DrinkWaterCookie.h"
#include "FillCookieBox.h"

#include "GetObjectKeys.h"

using namespace std;

/*
 * 
 */

void keyTest() {
    std::map<string,string> parameters;

    GetObjectKeys k;
    parameters["agent"]="agent";
    parameters["object"]="keys";
    k.assignParameters(parameters);
    k.create("get_keys", true);

    GetObjectKeys m;
    parameters["object"]="mug";
    m.assignParameters(parameters);
    m.create("get_mug",true);
    
    GetObjectKeys b;
    parameters["object"] = "book";
    b.assignParameters(parameters);
    b.create("get_book",true);
    
    IntentionGraph ig;

    std::vector<string> contexts = {"HotDay", "TimeToLeave", "BreakTime"};

    IntentionNode keys_intention;
    keys_intention.name = "GetKeys";
    keys_intention.linked_contexts = {"TimeToLeave"};

    keys_intention.influence=0.78;
    
    
    IntentionNode mug_intention;
    mug_intention.name = "GetMug";
    mug_intention.linked_contexts = {"HotDay"};
    mug_intention.influence=0.72;
    
    IntentionNode book_intention;
    book_intention.name = "ReadBook";
    book_intention.linked_contexts = {"BreakTime"};
    book_intention.influence=0.64;
    
    std::vector<IntentionNode> intentions = {keys_intention,mug_intention,book_intention};

    std::vector<string> actions = {"agent_move_kitchen", "agent_move_table"};

    VariableSet initial_state;
    initial_state.set["agent_isAt"] = "counter";
    initial_state.set["book_isAt"] = "trap";
    initial_state.set["keys_isAt"] = "table";
    initial_state.set["mug_isAt"] = "table";

//    b.printParameters();
//     b.simulate(2,initial_state);
    
    
    
    std::vector<Mdp*> mdps = {&k, &m,&b};
    ig.setGraph(contexts, intentions, actions, mdps, initial_state);

    VariableSet evidence;
    evidence.set["distance_agent_move_table"] = "close";
    evidence.set["toward_agent_move_table"] = "t";
    evidence.set["distance_agent_move_kitchen"] = "far";
    evidence.set["toward_agent_move_kitchen"] = "f";
    evidence.set["HotDay"] = "f";
    evidence.set["BreakTime"] = "f";
    evidence.set["TimeToLeave"] = "t";
    evidence.set["IntentionsOr"] = "t";
    evidence.set["ActionsOr"] = "t";

    ig.computeProbability(evidence);
}

void cookieTest() {
    EatCookie e;
    e.create("eat_cookie", true);

    FillCookieBox f;
    f.create("fill_box", true);

    DrinkWaterCookie d;
    d.create("drink_watercookie", true);

    IntentionGraph ig;

    std::vector<string> contexts = {"HotDay", "BreakTime"};

    IntentionNode drink_intention;
    drink_intention.name = "DrinkWater";
    drink_intention.linked_contexts = {"HotDay"};
    drink_intention.influence=0.72;

    IntentionNode fill_intention;
    fill_intention.name = "FillCookieBox";
    fill_intention.linked_contexts = {"BreakTime"};
    fill_intention.influence=0.50;
    
    IntentionNode eat_intention;
    eat_intention.name = "EatCookie";
    eat_intention.linked_contexts = {"BreakTime"};
    eat_intention.influence=0.65;
    
    std::vector<IntentionNode> intentions = {drink_intention, eat_intention, fill_intention};

    std::vector<string> actions = {"agent_move_kitchen", "agent_move_table"};

    VariableSet initial_state;
    initial_state.set["agent_isAt"] = "counter";
    initial_state.set["glass_isAt"] = "table";
    initial_state.set["agent_hasDrank"] = "0";
    initial_state.set["box_isAt"] = "table";
    initial_state.set["box_capacity"] = "1";
    initial_state.set["human_hasCookie"] = "0";
    initial_state.set["human_hasCookies"] = "0";

    initial_state.set["human_hasEaten"] = "0";

    //    d.simulate(2,initial_state);
    //    e.simulate(3,initial_state);
    f.simulate(5,initial_state);

    std::vector<Mdp*> mdps = {&d, &e,&f};
    ig.setGraph(contexts, intentions, actions, mdps, initial_state);

    VariableSet evidence;
    evidence.set["distance_agent_move_table"] = "close";
    evidence.set["toward_agent_move_table"] = "t";
    evidence.set["distance_agent_move_kitchen"] = "far";
    evidence.set["toward_agent_move_kitchen"] = "f";
    evidence.set["HotDay"] = "t";
    evidence.set["BreakTime"] = "f";
    evidence.set["IntentionsOr"] = "t";
    evidence.set["ActionsOr"] = "t";

    ig.computeProbability(evidence);
}

void drinkReorderTest() {
    DrinkWater d;
    d.create("drink_water", true);

    ReorderTable r;
    r.create("reorder_table", true);

    IntentionGraph ig;

    std::vector<string> contexts = {"HotDay", "AlreadyDrank"};

    IntentionNode drink_intention;
    drink_intention.name = "DrinkWater";
    drink_intention.linked_contexts = {"HotDay"};

    IntentionNode reorder_intention;
    reorder_intention.name = "ReorderTable";
    reorder_intention.linked_contexts = {"AlreadyDrank"};

    std::vector<IntentionNode> intentions = {drink_intention, reorder_intention};

    std::vector<string> actions = {"agent_fill_glass_bottle", "agent_move_kitchen", "agent_move_counter", "agent_place_bottle_table"};
    //    std::vector<string> actions = {"agent_take_glass", "agent_take_bottle", "agent_move_kitchen", "agent_move_counter"};

    VariableSet initial_state;
    initial_state.set["agent_isAt"] = "table";
    initial_state.set["glass_isAt"] = "agent";
    initial_state.set["bottle_isAt"] = "agent";
    initial_state.set["glass_capacity"] = "0";
    initial_state.set["bottle_capacity"] = "1";
    initial_state.set["has_drunk"] = "0";

    d.simulate(2, initial_state);


    std::vector<Mdp*> mdps = {&d, &r};
    ig.setGraph(contexts, intentions, actions, mdps, initial_state);

    VariableSet evidence;
    //    evidence.set["distance_agent_move_table"]="close";
    //    evidence.set["toward_agent_move_table"]="t";
    //    evidence.set["distance_agent_move_kitchen"]="far";
    //    evidence.set["toward_agent_move_kitchen"]="f";
    evidence.set["distance_agent_fill_glass_bottle"] = "close";
    evidence.set["toward_agent_fill_glass_bottle"] = "t";
    evidence.set["distance_agent_place_bottle_table"] = "medium";
    evidence.set["toward_agent_place_bottle_table"] = "t";
    evidence.set["distance_agent_move_kitchen"] = "far";
    evidence.set["toward_agent_move_kitchen"] = "f";
    evidence.set["toward_agent_move_counter"] = "f";
    evidence.set["distance_agent_move_counter"] = "far";
    //    evidence.set["distance_agent_take_bottle"] = "close";
    //    evidence.set["toward_agent_take_bottle"] = "t";
    //    evidence.set["toward_agent_take_glass"] = "f";
    //    evidence.set["distance_agent_take_glass"] = "far";
    evidence.set["HotDay"] = "t";
    evidence.set["AlreadyDrank"] = "f";
    evidence.set["IntentionsOr"] = "t";
    evidence.set["ActionsOr"] = "t";

    ig.computeProbability(evidence);

}

int main(int argc, char** argv) {
    cookieTest();

    return 0;
}