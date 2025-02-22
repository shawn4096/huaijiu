#ifndef _GLOBALS_H_
#define _GLOBALS_H_

// globals.h
// this file will be automatically included by the driver
#define private protected
#define TIME_TICK (time()*60)

#ifndef __SENSIBLE_MODIFIERS__ 
#define nosave          static 
#define protected       static 
#define oldcrypt crypt
#endif

#define move_to_ob(ob)	move(resolve_path(__DIR__, ob))
#define new_ob(str)	new(resolve_path(__DIR__, str))
#define replace_program(x)

// Important directories
#define COMMAND_DIR	"/cmds/"
#define CONFIG_DIR	"/adm/etc/"
#define DATA_DIR	"/data/"
#define HELP_DIR	"/help/"
#define INC_DIR		"/include/"
#define LOG_DIR		"/log/"
#define STORY_DIR       "/adm/daemons/story/"
#define SAVE_EXTENSION	".o"

// Daemons
#define PERFORM_D		"/adm/daemons/performd"
#define ALIAS_D		"/adm/daemons/aliasd"
#define BAOSHI_D	"/adm/daemons/baoshid"
#define BAN_D		"/adm/daemons/band"
#define BBS_D		"/adm/daemons/bbsd"
#define BALANCE_D       "/adm/daemons/balanced.c"
#define DOBET_D		"/adm/daemons/dobetd"
#define CHANNEL_D	"/adm/daemons/channeld"
#define CONFIG_D        "/adm/daemons/configd"
#define CHAR_D		"/adm/daemons/chard"
#define CHINESE_D	"/adm/daemons/chinesed"
#define CLIENT_D	"/adm/daemons/clientd"
#define CLOTH_D		"/adm/daemons/armord"
#define COMBAT_D	"/adm/daemons/combatd"
#define COMMAND_D	"/adm/daemons/commandd"
#define DB_D		"/adm/daemons/databased"
#define EMOTE_D		"/adm/daemons/emoted"
#define EXAMINE_D   "/adm/daemons/examined"
#define FINGER_D	"/adm/daemons/fingerd"
#define FTP_D		"/adm/daemons/ftpd"
#define GROUP_D		"/adm/daemons/groupd"
#define GIFT_D		"/adm/daemons/giftd"
#define INQUIRY_D	"/adm/daemons/inquiryd"
#define INTERJOB_D	"/adm/daemons/interjobd"
#define IP_D		"/adm/daemons/ipd"
#define LOG_D		"/adm/daemons/logd"
#define LOGIN_D		"/adm/daemons/logind"
#define MONEY_D		"/adm/daemons/moneyd"
#define MAP_D		"/adm/daemons/mapd"
#define NATURE_D	"/adm/daemons/natured"
#define NAME_D		"/adm/daemons/named"
#define PASSWD_D	"/adm/daemons/passwdd"
#define PIG_D		"/adm/daemons/pigd"
#define PROFILE_D	"/adm/daemons/profiled"
#define RANK_D		"/adm/daemons/rankd"
#define RNAME_D		"/adm/daemons/rnamed"
#define SECURITY_D	"/adm/daemons/securityd"
#define SHOP_D		"/adm/daemons/shopd"
#define STORY_D         "/adm/daemons/storyd"
#define SMTP_D		"/adm/daemons/smtpd"
#define TASK_D		"/adm/daemons/taskd"
#define TASKE_D		"/adm/daemons/tasked"
#define UPDATE_D	"/adm/daemons/updated"
#define VIRTUAL_D	"/adm/daemons/virtuald"
#define WEAPON_D	"/adm/daemons/weapond"
#define WORKER_D	"/adm/daemons/workerd"
#define ROOMLEASE_D     "/adm/daemons/roomleased"
#define QUEST_D     "/adm/daemons/questd"
#define TASKREWARD_D "/adm/daemons/jobrewardd"

//只是为了新任务系统
#define JOB_SERVER 	"/clone/obj/job_server"
#define TRAVERSER  	"/clone/obj/traverser"
#define MAPDB 	   	"/clone/obj/mapdb"
//end
//directories
#define ARMOR_D(x)	("/clone/armor/" + x)
#define BINGQI_D(x)	("/clone/weapon/" + x)
#define BOOK_D(x)		("/clone/book/" + x)
#define CLASS_D(x)	("/kungfu/class/" + x)
#define CONDITION_D(x)	("/kungfu/condition/" + x)
#define FOOD_D(x)	("/clone/food/" + x)
#define MEDICINE_D(x)	("/clone/medicine/" + x)
#define MISC_D(x)		("/clone/misc/" + x)
#define NPC_D(x)		("/clone/npc/" + x)
#define SKILL_D(x)		("/kungfu/skill/" + x)

// Clonable/Non-inheritable Standard Objects
#define COIN_OB		"/clone/money/coin"
#define CORPSE_OB	"/clone/misc/corpse"
#define EXPLORE_OB	"/clone/misc/explore_ob"
#define GOLD_OB		"/clone/money/gold"
#define LOADUSER_OB	"/clone/user/loaduser"
#define LOGIN_OB		"/clone/user/login"
#define MAILBOX_OB	"/clone/misc/mailbox"
#define MASTER_OB	"/adm/single/master"
#define SILVER_OB		"/clone/money/silver"
#define SIMUL_EFUN_OB	"/adm/single/simul_efun"
#define USER_OB		"/clone/user/user"
#define VOID_OB		"/clone/misc/void"

// add by akuma
#define CHARACTER2       "/inherit/char/char2.c"
#define F_COMMAND2       "/feature/command2.c"


//
// Inheritable Standard Objects
#define BANK		"/inherit/room/bank"
#define BULLETIN_BOARD	"/inherit/misc/bboard"
#define CHARACTER	"/inherit/char/char"
#define FIGHTER		"/inherit/char/fighter"
#define COMBINED_ITEM	"/inherit/item/combined"
#define EQUIP		"/inherit/misc/equip"
#define FIRE_ITEM		"/inherit/item/fire_item"
#define FORCE		"/inherit/skill/force"
#define HOCKSHOP		"/inherit/room/hockshop"
#define ILLNESS         	"/inherit/condition/illness"
#define ITEM		"/inherit/item/item"
#define LIQUID		"/inherit/food/liquid"
#define MONEY		"/inherit/item/money"
#define MISC_ROOM    	"/inherit/room/miscroom"
#define NPC		"/inherit/char/npc"
#define NPC_TRAINEE	"/inherit/char/trainee"
#define PILL		"/inherit/medicine/pill"
#define POWDER		"/inherit/medicine/powder"
#define ROOM		"/inherit/room/room"
#define FBROOM		"/inherit/room/new_room"
#define SHOP            	"/inherit/room/shop"
#define SKILL		"/inherit/skill/skill"
#define WAITER         	 "/inherit/char/waiter"
#define SPEC  		"/inherit/item/spec.c"

// User IDs
#define BACKBONE_UID	"Backbone"
#define ROOT_UID	"Root"

// Features
#define F_ACTION	"/feature/action.c"
#define F_ALIAS		"/feature/alias.c"
#define F_APPRENTICE	"/feature/apprentice.c"
#define F_ATTACK	"/feature/attack.c"
#define F_ATTRIBUTE	"/feature/attribute.c"
#define F_AUTOLOAD	"/feature/autoload.c"
#define F_BANKER	"/feature/banker.c"
#define F_BOAT		"/feature/boat.c"
#define F_CLEAN_UP	"/feature/clean_up.c"
#define F_COMMAND	"/feature/command.c"
#define F_COLOR         "/feature/color.c"
#define F_CONDITION	"/feature/condition.c"
#define F_DAMAGE	"/feature/damage.c"
#define F_DBASE		"/feature/dbase.c"
#define F_DEALER	"/feature/dealer.c"
#define F_EDIT		"/feature/edit.c"
#define F_EQUIP		"/feature/equip.c"
#define F_FINANCE	"/feature/finance.c"
#define F_FOOD		"/feature/food.c"
#define F_FROZEN	"/feature/frozen.c"
#define F_LINEUP	"/feature/lineupquery.c"
#define F_LIQUID	"/feature/liquid.c"
#define F_MASTER	"/inherit/char/master.c"
#define F_MESSAGE	"/feature/message.c"
#define F_MORE		"/feature/more.c"
#define F_MOVE		"/feature/move.c"
#define F_NAME		"/feature/name.c"
#define F_PILL		"/feature/pill.c"
#define F_REPORT	"/feature/report.c"
#define F_SAVE		"/feature/save.c"
#define F_SKILL		"/feature/skill.c"
#define F_SSERVER	"/feature/sserver.c"
#define F_TASK		"/feature/task.c"
#define F_TEAM		"/feature/team.c"
#define F_TREEMAP	"/feature/treemap.c"
#define F_UNIQUE	"/feature/unique.c"
#define F_VENDOR	"/feature/vendor.c"

// Profiling switches
//
// If you changed any of these defines, you'll need reboot to make it
// in effect.

#undef PROFILE_COMMANDS

// Mathematic
#define ABS(x)		((x) >= 0 ? (x) : -(x))
#define MAX(a, b)	((a) > (b) ? (a) : (b))
#define MIN(a, b)	((a) < (b) ? (a) : (b))
#define SGN(x)		((x) > 0 ? 1 : ((x) < 0 ? -1 : 0))
#define SWAP(x, y)	(x ^= y ^= x ^= y)

// Web
#define BBS_ADDR "http://www.xojh.cn"

#endif
