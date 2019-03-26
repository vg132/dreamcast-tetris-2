#include <kos.h>
#include "tetris.hpp"

pvr_init_params_t params = {
  /* Enable opaque and translucent polygons with size 16 */
  {PVR_BINSIZE_16, PVR_BINSIZE_0, PVR_BINSIZE_16, PVR_BINSIZE_0,
   PVR_BINSIZE_0},

  /* Vertex buffer size 512K */
        512 * 1024
};

#ifdef _TETRIS_DEBUG_
extern uint8 romdisk[];
KOS_INIT_ROMDISK(romdisk);
#endif

int main(int argc, char **argv)
{
	dbglog(DBG_INFO, "--main()\n");
	pvr_init (&params);
	CTetris *t(NULL);
	int ret(0);
	//malloc_stats();
	t=new CTetris();
	ret=t->Start();
	delete t;
	//malloc_stats();
	return(ret);
}

