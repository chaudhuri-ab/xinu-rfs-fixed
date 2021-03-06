/* rsrmdir.c - rsrmdir */

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "xinudefs.h"
#include "rfilesys.h"
#include "rfserver.h"

/*------------------------------------------------------------------------
 * rsrmdir - handle a rmdir request
 *------------------------------------------------------------------------
 */
void	rsrmdir (
	 struct	rf_msg_xreq *reqptr,	/* ptr to read request		*/
	 struct	rf_msg_xres *resptr	/* ptr to read response		*/
	)
{
	int	retval;			/* return value			*/

	if (findex >=0 && ofiles[findex].desc != -1) {		/* file exists and is open	*/
            close(ofiles[findex].desc);
	}
	retval = rmdir(reqptr->rf_name);
	if (retval < 0) {
		snderr( (struct rf_msg_hdr *)reqptr,
			(struct rf_msg_hdr *)resptr,
			 sizeof(struct rf_msg_xres) );
			return;
	}

	/* Return OK status */

	sndok ( (struct rf_msg_hdr *)reqptr,
		(struct rf_msg_hdr *)resptr,
		 sizeof(struct rf_msg_xres) );
	return;
}
