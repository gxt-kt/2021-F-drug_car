#ifndef AK8975_H
#define AK8975_H

#include "sys.h"


extern int ak89_id;
 struct AK8975
{
	int16_t magX,magY,magZ;
};

uint8_t AK8975_init(void);

void AK8975_Updata( struct AK8975 *pAK8975);

void MAG_Restart(void);



#endif

