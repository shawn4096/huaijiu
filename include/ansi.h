#ifndef _ANSI_H_
#define _ANSI_H_
//	File	:  /include/ansi.h
//	Creator	:  Gothic@TMI-2
//	Optimize:  Yuj@SJ
//	The standard set of ANSI codes for mudlib use.

#define ESC	""
#define CSI	ESC + "["

		/*  Foreground Colors  */

#define BLK ESC+"[0;30m"	/* Black   */
#define RED ESC+"[0;31m"	/* Red     */
#define GRN ESC+"[0;32m"	/* Green   */
#define YEL ESC+"[0;33m"	/* Yellow  */
#define BLU ESC+"[0;34m"	/* Blue    */
#define MAG ESC+"[0;35m"	/* Magenta */
#define CYN ESC+"[0;36m"	/* Cyan    */
#define WHT ESC+"[0;37m"	/* White   */

		/*  Hi Intensity Foreground Colors  */

#define HIR ESC+"[1;31m"	/* Red     */
#define HIG ESC+"[1;32m"	/* Green   */
#define HIY ESC+"[1;33m"	/* Yellow  */
#define HIB ESC+"[1;34m"	/* Blue    */
#define HIM ESC+"[1;35m"	/* Magenta */
#define HIC ESC+"[1;36m"	/* Cyan    */
#define HIW ESC+"[1;37m"	/* White   */

		/*  Hi Intensity Background Colors  */

#define HBRED ESC+"[41;1m"	/* Red     */
#define HBGRN ESC+"[42;1m"	/* Green   */
#define HBYEL ESC+"[43;1m"	/* Yellow  */
#define HBBLU ESC+"[44;1m"	/* Blue    */
#define HBMAG ESC+"[45;1m"	/* Magenta */
#define HBCYN ESC+"[46;1m"	/* Cyan    */
#define HBWHT ESC+"[47;1m"	/* White   */

		/*  Background Colors  */

#define BBLK ESC+"[40m"		/* Black   */
#define BRED ESC+"[41m"		/* Red     */
#define BGRN ESC+"[42m"		/* Green   */
#define BYEL ESC+"[43m"		/* Yellow  */
#define BBLU ESC+"[44m"		/* Blue    */
#define BMAG ESC+"[45m"		/* Magenta */
#define BCYN ESC+"[46m"		/* Cyan    */
#define BWHT ESC+"[47m"		/* White   */

#define NOR ESC+"[0;0m"		/* Puts everything back to normal */

/* Additional ansi Esc codes added to ansi.h by Gothic  april 23,1993 */
/* Note, these are Esc codes for VT100 terminals, and emmulators */
/*       and they may not all work within the mud               */

#define BOLD ESC+"[1m"		/* Turn on bold mode */
//#define CLR ESC+"[2J"		/* Clear the screen  */
#define HOME ESC+"[H"		/* Send cursor to home position */
#define REF CLR+HOME		/* Clear screen and home cursor */
#define BIGTOP ESC+"#3"		/* Dbl height characters, top half */
#define BIGBOT ESC+"#4"		/* Dbl height characters, bottem half */
#define SAVEC ESC+"[s"		/* Save cursor position */
#define REST ESC+"[u"		/* Restore cursor to saved position */
#define REVINDEX ESC+"M"	/* Scroll screen in opposite direction */
#define SINGW ESC+"#5"		/* Normal, single-width characters */
#define DBL ESC+"#6"		/* Creates double-width characters */
#define FRTOP ESC+"[2;25r"	/* Freeze top line */
#define FRBOT ESC+"[1;24r"	/* Freeze bottom line */
#define UNFR ESC+"[r"		/* Unfreeze top and bottom lines */
#define BLINK ESC+"[5m"		/* Initialize blink mode */
#define U ESC+"[4m"		/* Initialize underscore mode */
#define REV ESC+"[7m"		/* Turns reverse video mode on */
#define HIREV ESC+"[1,7m"	/* Hi intensity reverse video  */

#endif
