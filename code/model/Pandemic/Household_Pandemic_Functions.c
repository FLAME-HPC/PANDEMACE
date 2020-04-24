#include "../header.h"
#include "../Household_agent_header.h"
#include "../my_library_header.h"

/********************************* Household agent functions *************************************/

/********************************** Household Role: Pandemic module *********************/

/*\fn Household_pandemic_persistent()
 * brief: Persistent pandemic in which every single day households get exposed, infected, or die with a certain probability.
 */
int Household_pandemic_persistent()
{

/*
    #ifdef _DEBUG_MODE
    if(PRINT_DEBUG_PANDEMIC)
    {
        fprintf(stderr, "\n\t In %s:%s(), line %d: IT=%d ID=%d", __FILE__, __FUNCTION__, __LINE__, DAY, ID);
    }
    #endif
*/

    /****** SEIR MODEL STATE TRANSITIONS ****/
    //NOTE: Code must be in the reverse order of the states S-E-I-R, so R-I-E-S, to prevent all states are transitions imediately in the same iteration

    //Randomly households decease (persistent, daily rate)
    if(INFECTED && random_unif()<CONST_PANDEMIC_CASE_MORTALITY_RATE_PERSISTENT)
    {

        #ifdef _DEBUG_MODE
        if(PRINT_DEBUG_PANDEMIC)
        {
            fprintf(stderr, "\n\t IT=%d ID=%d Agent is deceased", DAY, ID);
        }
        #endif

        SUSCEPTIBLE = 0;
        EXPOSED = 0;
        INFECTED = 0;
        REMOVED = 1;
    }

    //Randomly households get infected (persistent, daily rate)
    if(EXPOSED && random_unif()<CONST_PANDEMIC_INFECTION_RATE_PERSISTENT)
    {

        #ifdef _DEBUG_MODE
        if(PRINT_DEBUG_PANDEMIC)
        {
            fprintf(stderr, "\n\t IT=%d ID=%d Agent is infected", DAY, ID);
        }
        #endif

        SUSCEPTIBLE = 0;
        EXPOSED = 0;
        INFECTED = 1;
        REMOVED = 0;
    }

    //Randomly households get exposed (persistent, daily rate)
    if(SUSCEPTIBLE && random_unif()<CONST_PANDEMIC_EXPOSURE_RATE_PERSISTENT)
    {

        #ifdef _DEBUG_MODE
        if(PRINT_DEBUG_PANDEMIC)
        {
            fprintf(stderr, "\n\t IT=%d ID=%d Agent is exposed", DAY, ID);
        }
        #endif

        SUSCEPTIBLE = 0;
        EXPOSED = 1;
        INFECTED = 0;
        REMOVED = 0;
    }

    //Inform about health state
    add_hh_health_data_message(ID, SUSCEPTIBLE, EXPOSED, INFECTED, REMOVED);

    return 0;
}
