#include "UDS.h"
#include "appl_diag.h"
#include "EOLT.h"
#include "Common.h"

unsigned int guiLibVersion_UDS = 0x011;

void UDS_Main(void)
{
	
	vAPPLLinDiag();// lin service and eol routine in this function.


	EOLT_Main();
	
}

