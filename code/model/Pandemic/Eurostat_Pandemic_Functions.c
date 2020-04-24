//#include <assert.h>
#include "../header.h"
#include "../Eurostat_agent_header.h"
#include "../my_library_header.h"

/** \Eurostat_health_data_aggregation()
  */
int Eurostat_health_data_aggregation()
{

/*
    #ifdef _DEBUG_MODE
    if(PRINT_DEBUG_PANDEMIC)
    {
        fprintf(stderr, "\n\t In %s:%s(), line %d: IT=%d ID=%d", __FILE__, __FUNCTION__, __LINE__, DAY, ID);
    }
    #endif
*/
	SUM_SUSCEPTIBLE = 0;
	SUM_EXPOSED     = 0;
	SUM_INFECTED    = 0;
	SUM_REMOVED     = 0;

    //Inform about health state
    START_HH_HEALTH_DATA_MESSAGE_LOOP

    	SUM_SUSCEPTIBLE += hh_health_data_message->susceptible;
    	SUM_EXPOSED     += hh_health_data_message->exposed;
    	SUM_INFECTED    += hh_health_data_message->infected;
    	SUM_REMOVED     += hh_health_data_message->removed;

	FINISH_HH_HEALTH_DATA_MESSAGE_LOOP

	int total = SUM_SUSCEPTIBLE + SUM_EXPOSED + SUM_INFECTED + SUM_REMOVED;

	if(total>0)
	{
		RATIO_SUSCEPTIBLE    = ((double) SUM_SUSCEPTIBLE) / ((double) total);
		RATIO_EXPOSED        = ((double) SUM_EXPOSED)     / ((double) total);
		RATIO_INFECTED       = ((double) SUM_INFECTED)    / ((double) total);
		RATIO_REMOVED        = ((double) SUM_REMOVED)     / ((double) total);
	}

    #ifdef _DEBUG_MODE
    if(PRINT_DEBUG_PANDEMIC)
    {
        printf("\n\t In %s:%s(), line %d:\n\t IT=%d ID=%d (Eurostat)", __FILE__, __FUNCTION__, __LINE__, DAY, ID);
		printf("\n\t Count: S %d E %d I %d R %d Total: %d", SUM_SUSCEPTIBLE, SUM_EXPOSED, SUM_INFECTED, SUM_REMOVED, total);
		printf("\n\t Ratio: S %2.2f E %2.2f I %2.2f R %2.2f\n\n", RATIO_SUSCEPTIBLE, RATIO_EXPOSED, RATIO_INFECTED, RATIO_REMOVED);
    }
    #endif

    return 0;   
}
