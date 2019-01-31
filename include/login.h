// login.h
// Modified for ShuJian by snowman@SJ
// Last modify by snowman@SJ 07/06/2000

#ifndef __LOGIN__
#define __LOGIN__

#define LOGIN_TIMEOUT           300

#define WELCOME                 "/adm/etc/welcome"
#define NEW_PLAYER_INFO         "/adm/etc/new_player"
#define UNREG_MOTD              "/adm/etc/unreg_motd"
#define MOTD                    "/adm/etc/motd"
#define SJ_EMAIL                ""
#define SJ_HOMEPAGE             ""

#define BANNED_ID		"/adm/etc/banned_id"
#define WIZLIST                 "/adm/etc/wizlist"

#define START_ROOM 		"/d/wuguan/dayuan"
#define DEATH_ROOM 		"/d/death/gate"
#define REVIVE_ROOM 		"/d/city/chmiao"
#define RELAX_ROOM 		"/d/wizard/relax"
#define REGISTER_ROOM 		"/cmds/leitai/regroom"

//  Modified by ilovemin@SJ: 230 is too low, so i changed it to 300
#define MAX_USERS 300

#define ROBOT_CHECK                     "/d/wiz/courthouse"

// This defines the minimum wiz_level of users that are allowed to 
// enter the mud. Note players has wiz_level 0.
#define WIZ_LOCK_LEVEL 0

#endif
