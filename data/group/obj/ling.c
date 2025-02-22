//  玩家自建帮派系统
//  Written By BBB 1999.08.18
//  大量优化 by yuj 2001.04.08

/*还没完成的：(如有人帮我写，请别忘了在后面说明一下，加了什么功能)

1、gup 帮内篡位，打败任何一上级，那么级别对换。限制挑战帮主者EXP必须达到要求，不可以 gup 同级、下级，其他不限制。
2、随便出帮，扣除 exp

以下的功能或工作量太大，或涉及到其他平衡的问题。我可不做了，谁有兴趣？

1、最好由玩家自己定义颜色。
2、帮主可否定义帮派口号、解散帮会，成员 login 后自动清除帮派标志。这个需要记录文件。
3、帮主可以自己建 room 、可以花钱买守卫 NPC、可以在 room 内定制兵器、自创武功。
4、帮主自己定义自己帮派的 ID ，可以由帮主下令对另一玩家帮派发起攻击，AUTOKILL
5、帮派内的任务奖励制度，以杀死仇人为任务，为防止作弊，被杀者 EXP 必须高于杀人者。
6、如果上一条可行，那么 gup 要加上完成任务次数的限制。
7、坚决反对加帮派内频道，门派频道就够烦人了，容易搞为小集团。目前各派间 PK 与 门派频道有很大关系。

(可以肯定，保证有玩家提出来，要求加频道。 kick )
*/

/* 将以前定义的4级职位改为6级，分别是帮主、副帮主、长老、使者、香主、帮众   tiantian
   相应的exp限制为500K , 1M, 1.5M, 2M */
/* gup 命令实现 tiantian */
/* 退帮或解散帮派 扣1% exp, 10% shen tiantian */
/* add 宗旨　tiantian */
/* add 帮主传位　tiantian */
/* add 帮主给帮派改名 扣1% exp tiantian*/
/* 玩家登录时或者死亡后new ling给玩家的时候自动根据帮派的历史更新令牌  tiantian */
/* 加入防止帮派重名的判断 tiantian */
/* 增加了玩家建立帮派总坛的功能 tiantian */
/* 增加帮派拦路抢劫的功能 tiantian */

#define _GRPDIR_ "/data/group"
#include <ansi.h>
#include <armor.h>
#include <command.h>

inherit ITEM;
inherit F_SAVE;

#include <mudlib.h>

int save_room_file(string yn, string file, string str);
int do_mkroom (string file);
int init_var();
int save_file();
int do_saveroom(string arg);
int do_connect(string arg);
int is_english(string str);

mapping tmp = ([
	"no_fight"		: 0,
	"no_clean_up"		: 0,
	"valid_startroom"	: 0,
	"file_name"		: "",
	"short"			: "",
	"long"			: "",
	"outdoors"		: "",
	"g_name"		: "",
	"hard"			: "",
	"damage"		: "",
	"combat_exp"		: "",
	"skill_lvl"		: "",
	"item_desc"		: ([]),
	"exits"			: ([]),
	"objects"		: ([]),
]);

string *special_props = ({
	"short", "long", "file_name"
});

mapping dir_alias = ([
	"n":    "north",
	"e":    "east",
	"w":    "west",
	"s":    "south",
	"nu":   "northup",
	"eu":   "eastup",
	"wu":   "westup",
	"su":   "southup",
	"nd":   "northdown",
	"ed":   "eastdown",
	"wd":   "westdown",
	"sd":   "southdown",
	"ne":   "northeast",
	"se":   "southeast",
	"nw":   "northwest",
	"sw":   "southwest",
	"u":    "up",
	"d":    "down"
]);

mapping dir_desc = ([
	"north":	"北面",
	"south":	"南面",
	"east":		"东面",
	"west":		"西面",
	"northup":	"北边",
	"southup":	"南边",
	"eastup":	"东边",
	"westup":	"西边",
	"northdown":	"北边",
	"southdown":	"南边",
	"eastdown":	"东边",
	"westdown":	"西边",
	"northeast":	"东北",
	"northwest":	"西北",
	"southeast":	"东南",
	"southwest":	"西南",
	"up":		"上面",
	"down":		"下面",
	"enter":	"里面",
	"out":		"外面"
]);

string *banned_name = ({
	"自己", "杀手", "闪电", "衡山", "某人", "尸体", "金庸", "武当",
	"你们", "峨嵋", "少林", "雪山", "他们", "混蛋", "坏蛋", "丐",
	"明", "明教", "少林寺", "武当山","铁掌", "华山", "嵩山", "恒山",
	"圣火神", "泰山", "密宗", "大轮寺","慕容", "古墓", "全真", "白驼山",
	"天龙", "大理", "黄山", "长江", "黄河", "中国", "中华","玩家",
	"冰火", "长白", "巫师", "天神","神仙", "吃人", "逍遥", "天山",
	"星宿", "邪", "正", "五毒","武林", "杀人", "抢劫", "盟主",
	"白驼", "正义", "邪恶", "书剑","金庸群侠", "桃花", "桃花岛", "统一",
	"官府","昆仑","法轮","法轮研究","法轮大","五岳","五岳剑","日月",
	"日月神","黑",
});

void create()
{
	set("unit","块");
	set("no_get", 1);
	set("no_drop", 1);
	set("no_put", 1);
	set("no_give", 1);
	set("material","wood");
	set_weight(1);
	set_name (HIR"帮派令牌"NOR, ({ "lingpai","ling","pai" }));
	setup();
}

void init()
{
	object me = this_player();
	string g_old_title, s_log;
	int line=1, found = 0, quit = 0;
	string g_title, g_header_name, g_header_id, g_number,g_new_title;
	string g_idea;

	if (me!=environment())
		return;		// 必须在身上

	if (me->query("g_name") && me->query("g_type")) {
		set("equipped", 1);
		g_old_title = me->set("g_title", me->query("g_name")+me->query("g_type"));

// 如果是某个帮派的人，就检查这个帮派的历史记录
	found = quit = 1;
	while (s_log = read_file("/log/group",line,1))	{
		if (sscanf(s_log, "%*s:%*s  %s 由 %s ( %s ) 担任第 %d 任帮主，宗旨 %s。",
		g_title, g_header_name, g_header_id, g_number, g_idea) == 7
		&& g_title == me->query("g_title")) {
			found = 1;
			quit = 0;
			me->set("g_header_name", g_header_name );
			me->set("g_header_id", g_header_id );
			me->set("g_number", g_number );
			me->set("g_idea", g_idea );
		}

		if (sscanf(s_log, "%*s:%*s  %s 解散，", g_title ) == 3
		&& g_title == me->query("g_title")) {
			found = 1;
			quit = 1;
		}

		if (sscanf(s_log, "%*s:%*s  %s 改名为 %s，宗旨 %s，",
		g_title, g_new_title, g_idea) == 4
		&& g_title == me->query("g_title")) {
			found = 1;
			quit = 0;
			me->set("g_title", g_new_title);
			me->set("g_name", g_new_title[0..<3]);
			me->set("g_type", g_new_title[<2..<1]);
			me->set("g_idea", g_idea);
		}
		line ++;
	}
	}
// 帮派曾经解散过，而且没有重新建立
	if (found == 1 && quit == 1)
		me->delete("g_title");

// 以前没有记录帮派的信息的情况的处理，主要是为了和以前的数据兼容
	if( found == 0 && me->query( "g_level" ) == 1 ) {
	// 将帮主的信息作为该帮派的最新信息
		if(!me->query("g_idea"))
			me->set("g_idea","未定");
		write_file("/log/group", sprintf("%s %s 由 %s ( %s ) 担任第 %d 任帮主，宗旨 %s。\n",
			ctime(time())[4..19],
			me->query("g_title"),
			me->query("name"),
			me->query("id"),
			me->query("g_number"),
			me->query("g_idea"))
		);
	}

	if (!me->query("g_title")) {
		if (!found)
			set_name(HIR "帮派令牌" NOR, ({ "lingpai", "ling", "pai" }));
		else {
			write(HIY BLINK "你所在的帮派已经解散了。\n" NOR);
			call_out("remove_ling", 1, me);
			return;
		}
	} else if (me->query("g_header_id") == me->query("marry/id")) {
		if( me->query("gender") == "女性" ) {
			set_name(HIR + me->query("g_title") + me->query("g_type") + "主夫人信物" NOR,
				({ "lingpai", "ling", "pai" }));
			me->set("title","［"HIW + me->query("g_title") + NOR "］"
				+ HIG + me->query("g_type") +"主夫人" NOR);
		} else {
			set_name(HIR + me->query("g_title") + me->query("g_type") + "主夫君信物" NOR,
				({ "lingpai", "ling", "pai" }));
			me->set("title","［"HIW+ me->query("g_title") + NOR "］"
				+ HIG + me->query("g_type") +"主夫君" NOR);
		}
		me->set("new_title", me->query("title"));
	} else switch(me->query("g_level")) {
		case 1:
			set_name(HIR + me->query("g_title") +  me->query("g_type") + "主令牌" NOR,
				({ "lingpai", "ling", "pai"}));
			break;
		case 2:
			set_name(HIR + me->query("g_title") + "副" + me->query("g_type") + "主令牌" NOR,
				({ "lingpai", "ling", "pai" }));
			break;
		case 3:
			set_name(HIR + me->query("g_title") + "长老令牌" NOR,
				({ "lingpai", "ling", "pai" }));
			break;
		case 4:
			set_name(HIR + me->query("g_title") + "使者令牌" NOR,
				({ "lingpai", "ling", "pai" }));
			break;
		case 5:
			set_name(HIR + me->query("g_title") + "香主令牌" NOR,
				({ "lingpai", "ling", "pai" }));
			break;
		default:
			set_name(HIR + me->query("g_title") + "帮众信物" NOR,
				({ "lingpai","ling","pai" }));
	}

	if (!me->query("g_invite_name") && !me->query("g_header_name"))
		set("long", "这是一块"HIG"帮派令牌"NOR"，可以用此创建玩家自己的门派。\n"
			+ "键入 "HIM "ghelp ling"NOR" 以获得更多的资讯。\n");
	else if (!me->query("g_invite_name") && me->query("g_header_name"))
		set("long", "这是"HIG + me->query("g_title") + NOR
			+ me->query("g_type") + "中令牌，"
			+ me->query("g_type") + "主是" HIY + me->query("g_header_name") + NOR
			"，帮派宗旨：" HIY + me->query("g_idea") + NOR "。\n"
			"键入 "HIM "ghelp ling"NOR" 以获得更多的资讯。\n");
	if (me->query("g_invite_name") && me->query("g_name"))
		set("long", "这是"HIG + me->query("g_title") + NOR
			+ me->query("g_type") + "中令牌，现任"
			+ me->query("g_type") + "主是第"
			+ CHINESE_D->chinese_number(me->query("g_number"))
			+ "任" + me->query("g_type") + "主"
			HIY + me->query("g_header_name") + NOR
			"，帮派宗旨：" HIY + me->query("g_idea") + NOR"。\n"
			"招募你加入的是" HIY + me->query("g_invite_name") + NOR"。\n"
			"键入 "HIM "ghelp ling"NOR" 以获得更多的资讯。\n");

	add_action("help", "ghelp");
	add_action("do_guild", "guild");
	add_action("do_rename", "gname");
	add_action("do_recruit", "grecruit");
	add_action("do_quit", "gquit");
	add_action("do_expell", "gexpell");
	add_action("do_level", "glevel");
	add_action("do_list", "glist");
	add_action("do_clear", "gclear");
	add_action("do_fgo", "gfgo");
	add_action("do_follow", "gfollow");
	add_action("do_pk", "gkill");
	add_action("do_halt", "ghalt");
	add_action("do_up", "gup");
//	add_action("do_groom","groom"); //因为分站code加密问题，暂时关闭此功能。
//	add_action("do_rob","grob");

    //玩家拜师升级后，会改变 title ,这样的话自己帮派的 title 被冲了
    //设置一个 new_title 来保存，用这样的办法解决。 BBB 1999.08.20
	if (me->query("new_title") && me->query("title") != me->query("new_title")) {
		me->set("old_title", me->query("title") );
		me->set("title", me->query("new_title") );
	}

	if (!me->query("g_title") || me->query("g_level") == 1) ;
	else if (me->query("combat_exp")<500000 && me->query("g_level")<6) {
		me->set("g_level", 6);
		write(HIR "因为经验不足，你在" + me->query("g_title") + "中的级别被降为帮众。\n" NOR);
		call_out("remling", 1, me);
	} else if (me->query("combat_exp")<1000000 && me->query("g_level")<5) {
		me->set("g_level", 5);
		write(HIR "因为经验不足，你在" + me->query("g_title") + "中的级别被降为香主。\n"NOR);
		call_out("remling", 1, me);
	} else if( me->query("combat_exp")<1500000 && me->query("g_level")<4) {
		me->set("g_level", 4);
		write(HIR "因为经验不足，你在" + me->query("g_title") + "中的级别被降为使者。\n"NOR);
		call_out("remling", 1, me);
	} else if( me->query("combat_exp")<2000000 && me->query("g_level")<3) {
		me->set("g_level", 3);
		write(HIR "因为经验不足，你在" + me->query("g_title") + "中的级别被降为长老。\n"NOR);
		call_out("remling", 1, me);
	}
	if (me->query("g_title") && me->query("g_header_id") != me->query("marry/id"))
	switch(me->query("g_level")) {
	case 1:
		me->set("title","［"HIW+ me->query("g_name") + me->query("g_type") + NOR "］"+ HIG + me->query("g_type") +"主"NOR);
		break;
	case 2:
		me->set("title","［"HIW+ me->query("g_name") + me->query("g_type") + NOR "］"+ HIG +"副"+ me->query("g_type") +"主"NOR);
		break;
	case 3:
		me->set("title","［"HIW+ me->query("g_name") + me->query("g_type") + NOR "］"+ HIG +"长老"NOR);
		break;
	case 4:
		me->set("title","［"HIW+ me->query("g_name") + me->query("g_type") + NOR "］"+ HIG +"使者"NOR);
		break;
	case 5:
		me->set("title","［"HIW+ me->query("g_name") + me->query("g_type") + NOR "］"+ HIG +"香主"NOR);
		break;
	default:
		me->set("title","［"HIW+ me->query("g_name") + me->query("g_type") + NOR "］"+ HIG +"帮众"NOR);
	}
	me->set("new_title",me->query("title") );
}

void remling(object me)
{
	if (me) move(me);
}

void remove_ling(object me)
{
	if (me) {
		me->delete("title");
		me->delete("g_level");
		me->delete("g_invite_name");
		me->delete("g_invite_id");
		me->delete("new_title");
		me->delete("old_title");
		me->delete("g_title");
		me->delete("g_name");
		me->delete("g_type");
		me->delete("g_idea");
	}
	destruct(this_object());
}

int help(string str)
{
	if (str != "ling")
		return 0;

	write(@Help

	你可以使用以下的几个命令:		<帮派内上级才能命令下级，有的命令帮众不能使用>

	guild <帮派名> type <类型> idea <宗旨>	<组建帮派，要求经验大于2M>
						<类型必须为：帮、堂、舵、楼、谷、教、盟、门、宫、堡>
	gname <帮派名> type <类型> idea <宗旨>	<帮派改名，仅限帮主使用，且要扣除帮主一定的经验>
	grecruit <某人> be <级别>		<招募他人在帮内任职，级别用数字1 2 3 4 5 6表示>
						<分别为帮主、副帮主、长老、使者、香主、帮众>
	gkill <下属> with <他人>		<命令下属攻击他人，相当于 kill >
	ghalt <下属>				<命令下属停止战斗，相当于 halt >
	glevel <下属> be <级别>			<调整下属的帮中等级，可以升降>
	gexpell <下属>				<开除下属出帮会，只有帮主才可以>
	gquit					<退出帮会，帮主解散帮派>
	glist					<本帮全部在线成员列表>
	gfgo <下属> <方向>			<命令下属前往某方向>
	gfollow <下属> with <某人>		<命令下属跟随某人一起行动>
	gup <上级>				<向上级挑战，杀死上级篡位>
	grob					<在当前位置拦路抢劫>
	*groom <方向>				<在当前位置指定方向的空地上建立帮派总坛>
	*genemy					<查看帮派仇人录，杀死本帮弟子者登入此录>

	* 标志的尚未开放。
	注意:  帮派取名虽然有限制，但可能限制不全，不要起武林门派的名字和容易引起误解的名字
	不要随便建帮、退帮，否则将会扣除一定比例的 exp 和 shen 做惩罚。
Help
);
	return 1;
}

int do_guild (string arg)
{
	object me=this_player();
	string g_name,g_type,g_idea;
	string g_idea2;
	int line=1, found = 0;
	string s_log;
	string g_title, g_header_name, g_header_id, g_number,g_new_title;
	int i;

// 防止玩家自己建个少林派出来。BBB 1999.08.19

	if (me->query("g_title"))
		return notify_fail("你已经是" + me->query("g_title") +"的人了。\n");
	if (me->query("combat_exp") < 2000000)
		return notify_fail("你江湖经验不够，暂时还不够资格组建自己的帮派。\n");
	if (!arg || sscanf(arg, "%s type %s idea %s", g_name,g_type,g_idea) != 3)
		return notify_fail("建帮派指令格式：\n"
			"	guild 帮派名 type 帮派类 idea 帮派宗旨。\n"
			"例如：guild 金风细雨 type 堂 idea 互相保护\n"
			"这样就建立了一个名为金风细雨堂的帮派。\n"
			"帮派的宗旨是互相保护，你自己就成为了堂主。\n"
		);
	switch(g_type) {
		case "帮":
		case "堂":
		case "舵":
		case "楼":
		case "谷":
		case "教":
		case "盟":
		case "门":
		case "宫":
		case "堡":
			break;
		default:
			return notify_fail("所建帮派类必须为：帮、堂、舵、楼、谷、教、盟、门、宫或堡。\n");
	}

	i = strlen(g_name);
	if (i < 2 || i > 8|| i%2)
		return notify_fail("对不起，你的帮派名字必须是 1 到 4 个中文字。\n");
	if (i % 2==0 && !is_chinese(g_name))
		return notify_fail("对不起，请您用「中文」给帮派取名。\n");
	i = strlen(g_idea);
	if (i < 2 || i > 20|| i%2)
		return notify_fail("对不起，你的帮派宗旨必须是 1 到 10 个中文字。\n");
	if (i % 2==0 && !is_chinese(g_idea) )
		return notify_fail("如果您用「中文」给帮派定宗旨，可能会更方便大家理解。\n");
	if (member_array(g_name, banned_name)!=-1)
		return notify_fail("对不起，这个帮派名会引起玩家的误会。\n");

	while (s_log = read_file("/log/group", line, 1)) {
		if (sscanf(s_log, "%*s:%*s  %s 由 %s ( %s ) 担任第 %d 任帮主，宗旨 %s。",
		g_title, g_header_name, g_header_id, g_number, g_idea2 ) == 7
		&& g_title == g_name + g_type)
			found = 1;
		if (sscanf(s_log, "%*s:%*s  %s 解散，", g_title) == 3
		&& g_title == g_name + g_type)
		    found = 0;
		if (sscanf(s_log, "%*s:%*s  %s 改名为 %s，宗旨 %s，",
		g_title, g_new_title, g_idea2 ) == 5
		&& g_title == g_name + g_type )
			found = 0;
		line ++;
	}

	if (found)
		return notify_fail( "这个名字已经有人用过了，给你的帮派另外起一个名字吧。\n" );

	me->set("g_name", g_name);
	me->set("g_type", g_type);
	me->set("g_header_name", me->query("name"));
	me->set("old_title",me->query("title"));
	me->set("g_title",g_name + g_type);
	me->set("g_level",1);
	me->set("g_idea",g_idea);
    //这里的 g_number 是为帮内篡位预留的，第一任帮主 g_number 是 1
	me->set("g_number",1);
	me->set("title", "［" HIW+ me->query("g_title") + NOR "］" HIG	+ me->query("g_type") + "主" NOR);
	me->set("new_title", me->query("title"));
	set_name(me->query("g_title") + me->query("g_type") + "主令牌",
		({ "lingpai", "ling", "pai" }));
	message_vision("$N决定组建帮派组织：" + g_name + g_type + "，$N成为第一任" + g_type
		+ "主。\n", me);
	message("channel:chat", HIC "【江湖传闻】"+ me->query("name") +"今日组建［"HIW + g_name
	+ g_type + HIC "］，宗旨："HIW + g_idea + HIC"。"HIG + me->query("name") +HIC "为第一任"
	+ g_type + "主。\n" NOR, users());
	write_file( "/log/group", sprintf("%s %s 由 %s ( %s ) 担任第 %d 任帮主，宗旨 %s。\n",
		ctime(time())[4..19], me->query("g_title"),
		me->query("name"), me->query("id"),
		me->query("g_number"),me->query("g_idea"))
	);
	move(me);
	return 1;
}

int do_rename (string arg)
{
	object me=this_player();
	string g_name,g_type,g_idea,g_old_title;
	string g_idea2;
	string s_log;
	int i;
	int line=1, found = 0;
	string g_title, g_header_name, g_header_id, g_number;
	object env;
	object ob;

	if (!me->query("g_name") || me->query("g_level") != 1)
		return notify_fail("你不是某个帮派的帮主。\n");

	env = environment(me);
/*	if (me->query("g_room")
	&& env->query("g_name") != me->query("g_name") + me->query("g_type"))
		return notify_fail("这么重要的决定还是在帮派的总坛发布比较好。\n");
*/
	if (!arg || sscanf(arg, "%s type %s idea %s", g_name,g_type,g_idea) != 3)
		return notify_fail("帮派改名指令格式：\n"
			"	gname 帮派名 type 帮派类 idea 帮派宗旨。\n"
			"例如：gname 金风细雨 type 堂 idea 互相保护\n"
			"这样就把你的帮派改名为金风细雨堂。\n"
			"帮派的宗旨改为互相保护。\n"
		);
	switch(g_type) {
		case "帮":
		case "堂":
		case "舵":
		case "楼":
		case "谷":
		case "教":
		case "盟":
		case "门":
		case "宫":
		case "堡":
			break;
		default:
			return notify_fail("所建帮派类必须为：帮、堂、舵、楼、谷、教、盟、门、宫或堡。\n");
	}

    i = strlen(g_name);
    if (i < 2 || i > 8|| i%2)
	return notify_fail("对不起，你的帮派名字必须是 1 到 4 个中文字。\n");
    if (i % 2==0 && !is_chinese(g_name) )
	return notify_fail("对不起，请您用「中文」给帮派取名。\n");
    i = strlen(g_idea);
    if (i < 2 || i > 20|| i%2)
	return notify_fail("对不起，你的帮派宗旨必须是 1 到 10 个中文字。\n");
    if (i % 2==0 && !is_chinese(g_idea) )
	return notify_fail("如果您用「中文」给帮派定宗旨，可能会更方便大家理解。\n");
    if (member_array(g_name, banned_name)!=-1 )
	return notify_fail("对不起，这个帮派名会引起玩家的误会。\n");

    while( s_log = read_file("/log/group",line,1) )
    {
	if( sscanf( s_log, "%*s:%*s  %s 由 %s ( %s ) 担任第 %d 任帮主，宗旨 %s。",
		g_title, g_header_name, g_header_id, g_number, g_idea2 ) == 7 )
	{
	    if( g_title == g_name + g_type )
	    {
		    found = 1;
	    }
	}
	if( sscanf( s_log, "%*s:%*s  %s 解散，", g_title ) == 3 )
	{
		if( g_title == g_name + g_type )
	    {
		    found = 0;
	    }
	}
	if( sscanf( s_log, "%*s:%*s  %s 改名为 %*s，", g_title) == 4 )
	{
	    if( g_title == g_name + g_type )
	    {
		found = 0;
	    }
	}
	line ++;
	}

	if( found == 1 )
		return notify_fail( "这个名字已经有人用过了，给你的帮派另外起一个名字吧。\n" );

	me->set("g_name", g_name);
	me->set("g_type", g_type);
	g_old_title=me->query("g_title");
	me->set("g_title",g_name + g_type);
	me->set("g_idea",g_idea);
	me->set("title","［" HIW + me->query("g_title") + HIW "］" HIG + me->query("g_type") + "主"NOR);
	me->set("new_title",me->query("title") );
	set_name(me->query("g_title") +  me->query("g_type") + "主令牌",
		({ "lingpai", "ling", "pai" }));
	message_vision("$N决定将帮派改名为：" + g_name + g_type + "。\n", me);
	message("channel:chat", HIC "【江湖传闻】："+ me->query("name") +"将［" HIW
		+ g_old_title + HIC"］改名为［"HIW + g_name
		+ g_type +HIC"］，宗旨："HIW + g_idea + HIC"。\n" NOR,users()
	);
	write(HIG BLINK"你因为随便给帮派改名，被扣除了" + CHINESE_D->chinese_number(me->query("combat_exp")/100)
		+ "点的经验。\n"NOR
	);
	me->add("combat_exp", - me->query("combat_exp")/100);
	write_file("/log/group", sprintf("%s %s 改名为 %s，宗旨 %s，%s ( %s ) 被扣除了 %d 点经验。\n", ctime(time())[4..19],
		g_old_title, me->query("g_title"), me->query("g_idea"),
		me->query("name"), me->query("id"), me->query("combat_exp")/100)
	);

	/* 修改帮派总坛的名称 */
	if(me->query("g_room") )
	{
		env->set("short", HIR "" + me->query("g_name") + me->query("g_type") + HIG " 总坛" NOR );
		env->set("long", "  这里是" + me->query("g_name") + me->query("g_type") + @ROOM_CODE
的总坛。上面供奉的是前任历代帮主的灵牌，
两位总坛护法伺立在下首。非本帮弟子不能随便进入，否则可能会
惹来杀身之祸。
ROOM_CODE );
		env->set("g_name",me->query("g_name") + me->query("g_type") );

		do_saveroom("");
	    if( (ob = present("hufa zhanglao", env) ) )
		destruct(ob);
	    if( (ob = present("hufa zhanglao", env) ) )
		destruct(ob);
	    new("/data/group/npc/hufa.c")->move(env);
	    new("/data/group/npc/hufa.c")->move(env);
	}

	move(me);
	return 1;
}

int do_recruit(string str)
{
	object ob1,me = this_player();
	string st1;
	int st2,st3 = me->query("g_level");

    if (!me->query("g_name") )
	    return notify_fail("你并没组建帮派或加入任何帮派，无法使用此命令。\n");
    if (!str || str=="") return notify_fail ("你想招募谁加入啊？\n");
    if (sscanf(str, "%s be %d", st1,st2) != 2)
	return notify_fail ("grecruit <玩家id> be <帮内等级>\n");
    if (!ob1 = find_living(st1))
	ob1 = LOGIN_D->find_body(st1);
    if (ob1 == me) return notify_fail("招募自己？\n");
    if(!objectp(ob1 = present(st1, environment(me))) )
	return notify_fail("这里没 " + st1 + " 这个人。\n");
    if (!userp(ob1) )
	return notify_fail("你只能招收玩家为帮派成员。\n");
    if( !living(ob1) )
	return notify_fail("你等" + ob1->name() + "醒来再说吧。\n");
    if (ob1->query("g_name") == me->query("g_name") )
       return notify_fail("" + ob1->name(1) + "已经是你帮派的人。\n");
    if (ob1->query("g_name") )
	return notify_fail("" + ob1->name(1) + "是其他帮派的人，需要脱离后才能加入你的帮会。\n");
    if ( present("invite letter", ob1))
	return notify_fail("" + ob1->name(1) + "已经接到了加入帮派的邀请了。\n");
    if (st2 < st3) return notify_fail("你无法招募上级。\n");
	if (st2 == st3) return notify_fail("你无法招募同级。\n");
    if (st2 > 6) return notify_fail("级别只有 1 "+ me->query("g_type") +"主 2 副"+ me->query("g_type")
	+"主 3 长老 4 使者 5 香主 6 "+ me->query("g_type") +"众。\n");

	message_vision("$N招募$n加入［" HIW+ me->query("g_title") + NOR"］。\n",
		me, ob1
	);

	switch(st2) {
    case 2:
	if (ob1->query("combat_exp") < 2000000 )
	{
		message_vision("很可惜，$N的经验不够，无法胜任［" HIW+ me->query("g_title")
			+ NOR"］副"+ me->query("g_type") +"主一职。\n", ob1
		);
	    return notify_fail ("请重新定级别。\n");
	}
	else
		message_vision("$N邀请$n担任［" HIW+ me->query("g_title")
			+ NOR"］副"+ me->query("g_type") +"主。\n",me,ob1 );
	break;
	case 3:
	if (ob1->query("combat_exp") < 1500000 )
	{
		message_vision("很可惜，$N的经验不够，无法胜任［" HIW+ me->query("g_title")
			+ NOR"］长老一职。\n",ob1 );
	    return notify_fail ("请重新定级别。\n");
	}
	else
	    message_vision("$N邀请$n担任［" HIW+ me->query("g_title")
		+ NOR"］长老。\n", me, ob1 );
	break;
    case 4:
	if (ob1->query("combat_exp") < 1000000 )
	{
		message_vision("很可惜，$N的经验不够，无法胜任［" HIW+ me->query("g_title")
		    + NOR"］使者一职。\n",ob1 );
	    return notify_fail ("请重新定级别。\n");
	}
	else
	    message_vision("$N邀请$n担任［" HIW+ me->query("g_title")
		+ NOR"］使者。\n",me,ob1 );
	    break;
    case 5:
	    if (ob1->query("combat_exp") < 500000 )
	{
	    message_vision("很可惜，$N的经验不够，无法胜任［" HIW+ me->query("g_title")
		+ NOR"］香主一职。\n",ob1 );
	    return notify_fail ("请重新定级别。\n");
	}
	else
		message_vision("$N邀请$n担任［" HIW+ me->query("g_title")
		    + NOR"］香主。\n",me,ob1);
	    break;
    default:
	if (ob1->query("combat_exp") < 50000 )
	{
	    message_vision("很可惜，$N的经验不够，还是继续闯荡江湖，积累些经验吧。\n",ob1 );
	    return notify_fail ("等些日子再招募吧。\n");
	}
	else
	    message_vision("$N邀请$n成为［" HIW+ me->query("g_title")
		    + NOR"］帮众。\n",me,ob1 );
    }

	ob1->set_temp("g_level",st2);
	ob1->set_temp("g_name",me->query("g_name"));
	ob1->set_temp("g_type",me->query("g_type"));
	ob1->set_temp("g_header_name",me->query("g_header_name"));
	ob1->set_temp("g_number",me->query("g_number"));
	ob1->set("g_invite_id",me->query("id"));
	ob1->set("g_invite_name",me->query("name"));
	ob1->set_temp("g_idea",me->query("g_idea"));
	message_vision("$N给$n一封［" HIW+ me->query("g_name")
		+ me->query("g_type") + NOR"］邀请信。\n", me, ob1
	);
	new("/data/group/obj/letter")->move(ob1);
	return 1;
}

int do_level(string str)
{
    object ob1,ob2,me = this_player();
    string st1;
    int st6;
    int mylevel=me->query("g_level");
    int oldlevel, newlevel;

    if (!me->query("g_name") )
	return notify_fail("你并没组建帮派或加入任何帮派，无法使用此命令。\n");
    if (!str || str=="")
	return notify_fail ("你想调整谁的级别啊？\n");
    if (sscanf(str, "%s be %d", st1,newlevel) != 2)
	return notify_fail ("glevel <玩家id> be <帮内新等级>\n");
    if (!ob1 = find_living(st1))
	ob1 = LOGIN_D->find_body(st1);
    if (ob1 == me)
	return notify_fail("调整自己的级别？只有上级才能调整你的级别。\n");
    if(!objectp(ob1 = present(st1, environment(me))) )
	return notify_fail("这里没 "+ st1 + " 这个人。\n");

    //加了 g_header_name 的判断，防止玩家组建帮派名相同，调整另外帮派的下属：
    if (ob1->query("g_name") != me->query("g_name") && ob1->query("g_header_name") != me->query("g_header_name") )
	return notify_fail("" + ob1->name(1) + "不是你帮派的人。\n");
    oldlevel = ob1->query("g_level");
    if( !living(ob1) )
	return notify_fail("你等" + ob1->name() + "醒来再说吧。\n");
    if (mylevel > oldlevel)
	return notify_fail("调整上级的级别，你想造反啊？\n");
    if (mylevel == oldlevel && mylevel != 1 )
	return notify_fail("你无法调整同级的级别。\n");
    if (mylevel >= newlevel && mylevel != 1 )
	return notify_fail("你不能把对方的级别调得这么高。\n");
    if (oldlevel == newlevel)
	return notify_fail("新级别和原级别相同。\n");
    if (newlevel > 6)
	return notify_fail("级别只有 1 "+ me->query("g_type") +"主 2 副"+
		me->query("g_type") +"主 3 长老 4 使者 5 香主 6 "+ me->query("g_type") +"众。\n");
	st6 = ob1->query("combat_exp");
    if (st6 < 2000000 && newlevel < 3 )
	return notify_fail("" + ob1->name(1)+"的经验不够，目前不够资格升级。\n");
    if (st6 < 1500000 && newlevel < 4 )
	return notify_fail("" + ob1->name(1)+"的经验不够，目前不够资格升级。\n");
    if (st6 < 1000000 && newlevel < 5 )
	return notify_fail("" + ob1->name(1)+"的经验不够，目前不够资格升级。\n");
    if (st6 < 500000 && newlevel < 6 )
	return notify_fail("" + ob1->name(1)+"的经验不够，目前不够资格升级。\n");

	message_vision("$N换了一个令牌给$n，调整了$n在［" HIW+ me->query("g_title") + NOR"］中的级别。\n",
		me,ob1
	);
    //这里加入帮主让位的代码，str==1，不过需要另外文件支持，否则其他成员login的时候不能更换。
    //Look@SJ 990822 15:41
    //支持代码已经加上 990901 tiantian
    switch(newlevel)
    {
    case 1:
	message_vision("$N决定让$n担任［" HIW+ me->query("g_title") + NOR"］"
	    + me->query("g_type") +"主一职。\n",me,ob1 );
	break;
    case 2:
	message_vision("$N决定让$n担任［" HIW+ me->query("g_title") + NOR"］副"
	    + me->query("g_type") +"主一职。\n",me,ob1 );
	break;
    case 3:
	message_vision("$N决定让$n担任［" HIW+ me->query("g_title")
	    + NOR"］长老一职。\n",me,ob1 );
	break;
	case 4:
	message_vision("$N决定让$n担任［" HIW+ me->query("g_title")
	    + NOR"］使者一职。\n",me,ob1 );
	break;
    case 5:
	message_vision("$N决定让$n担任［" HIW+ me->query("g_title")
	    + NOR"］香主一职。\n",me,ob1 );
	break;
    default:
	message_vision("$N决定让$n成为［" HIW+ me->query("g_title")
	    + NOR"］普通帮众。\n",me,ob1 );
    }

    ob1->set("g_level",newlevel);
	if (newlevel == 1) {
		ob1->set("title","［"HIW+ me->query("g_title") + NOR "］"
			+ HIG + me->query("g_type") +"主"NOR);
		ob1->set("g_number", me->query("g_number") + 1);
		if( me->query("g_room") )
			ob1->set("g_room", 1 );
		message("channel:chat", HIC "【江湖传闻】："+ me->query("name") +"今日将"HIW
			+ me->query("g_title") +HIC + me->query("g_type")
			+"主职位传与第"+ CHINESE_D->chinese_number(ob1->query("g_number"))
			+"任"+ me->query("g_type") +"主"+ ob1->query("name") +"。\n" NOR,users()
		);
		write_file( "/log/group", sprintf("%s %s 由 %s ( %s ) 担任第 %d 任帮主，宗旨 %s。\n",
			ctime(time())[4..19],
			me->query("g_title"), ob1->query("name"),
			ob1->query("id"), ob1->query("g_number"),
			me->query("g_idea"))
		);
		ob1->set("new_title",ob1->query("title"));
		ob1->set("g_header_name", ob1->query("name"));
		message_vision(HIR"$N退出了" + me->query("g_title") + "。\n"NOR ,me,ob1);
		me->delete("g_level");
		me->delete("g_title");
		me->delete("g_name");
		me->delete("g_header_name");
		me->delete("g_number");
		me->delete("g_type");
		me->delete("title");
		me->delete("g_invite_name");
		me->delete("g_invite_id");
		me->delete("new_title");
		me->delete("old_title");
		me->delete("g_idea");
	}
	ob1->set("new_title",ob1->query("title"));
	if (ob2 = present("lingpai", ob1)) ob2->move(ob1);
	else new(__DIR__"ling")->move(ob1);
	if (newlevel <2)
		destruct(this_object());
	return 1;
}

int do_quit(string arg)
{
	object me = this_player();
	object env = environment(me);
	object ob;

	if (!me->query("g_title"))
		return notify_fail ("你并没有加入任何玩家帮派，也没有组建自己的帮派。\n");

	if (arg) return notify_fail("这个指令不需要在后面跟参数。\n");
    if (me->query("g_level")<2)
    {
		if( me->query("g_room") )
		{
			if( env->query("g_name") != me->query("g_name") + me->query("g_type") )
				return notify_fail("这么重要的决定还是在帮派的总坛发布比较好。\n");
		}

	    message("channel:chat", HIC "【江湖传闻】"HIW + me->query("g_title")
	    +HIC+ me->query("g_type")+"主" + me->query("name") +"：本人才疏学浅、武功低微，无力在江湖光大本"
	    + me->query("g_type")+"，现在解散。\n" NOR,users());
		write_file( "/log/group", sprintf("%s %s 解散，%s ( %s ) 被扣除了 %d 点经验。\n", ctime(time())[4..19],
	    me->query("g_title"), me->query("name"), me->query("id"), me->query("combat_exp")/100 ));

		if(me->query("g_room") )
		{
		    if( (ob = present("hufa zhanglao", env) ) )
			destruct(ob);
		    if( (ob = present("hufa zhanglao", env) ) )
			destruct(ob);
		    if( (ob = present("ling pai", env) ) )
			destruct(ob);

			env->set("short", HIR "" + env->query("g_name") + HIG "总坛废墟" NOR );
			env->set("long", "这里曾经是" + env->query("g_name") + "的总坛，但是现在已经荒废了。\n");
			env->delete("combat_exp");
			env->delete("skill_lvl");
			env->delete("g_name");
			env->delete("damage");
			env->delete("hard");
			env->delete("objects");

			do_saveroom("");
		}

    }

	if( me->query("shen") >= 0 )
		message_vision(HIR"$N退出了" + me->query("g_title") + "。\n"
			+ HIG BLINK"$N因为随便"+(me->query("g_level")>1?"退出":"解散")+"帮派，被扣除了"
			+ CHINESE_D->chinese_number(me->query("combat_exp")/100)
			+ "点的经验和" + CHINESE_D->chinese_number(me->query("shen")/10) +"点的正神。\n"NOR,me );
	else
		message_vision(HIR"$N退出了" + me->query("g_title") + "。\n"
			+ HIG BLINK"$N因为随便"+(me->query("g_level")>1?"退出":"解散")+"帮派，被扣除了"
			+ CHINESE_D->chinese_number(me->query("combat_exp")/100)
			+ "点的经验和" + CHINESE_D->chinese_number(-me->query("shen")/10) +"点的负神。\n"NOR,me );

	me->delete("g_level");
	me->delete("g_title");
	me->delete("g_name");
	me->delete("g_header_name");
	me->delete("g_number");
	me->delete("g_type");
	me->delete("title");
	me->add("combat_exp", -me->query("combat_exp") / 100 );
	me->add("shen", -me->query("shen") / 10 );
	me->delete("g_invite_name");
	me->delete("g_invite_id");
	me->delete("new_title");
	me->delete("old_title");
	me->delete("g_idea");
	destruct(this_object() );
	return 1;
}

int do_expell(string str)
{
	object ob1,me = this_player();
    int st3 = me->query("g_level");

    if (!me->query("g_name") )
	return notify_fail("你先建好自己的帮派再去开除下属吧。\n");
    if (st3>1) return notify_fail("你不是"+me->query("g_type")+"主，无权开除。\n");
    if (!str || str=="") return notify_fail ("你想开除谁啊？\n");
    if (!ob1 = find_living(str)) ob1 = LOGIN_D->find_body(str);
    if (ob1 == me) return notify_fail("开除自己？你不是在开玩笑吧？\n");
    if(!objectp(ob1 = present(str, environment(me))) )
	return notify_fail("这里没 " + str + " 这个人。\n");
    if( !living(ob1) )
	return notify_fail("你等" + ob1->name() + "醒来再说吧。\n");
    if (ob1->query("g_name") != me->query("g_name") && ob1->query("g_header_name") != me->query("g_header_name") )
	return notify_fail("他不是你帮派的人，你无权开除他。\n");
    message_vision(HIR"$N从$n身上除下令牌，$n被开除出了" HIW+ me->query("g_title") + HIR"。\n"NOR, me, ob1);
    ob1->delete("g_level");
    ob1->delete("g_name");
    ob1->delete("g_title");
    ob1->delete("g_type");
    ob1->delete("g_header_name");
    ob1->delete("title");
    ob1->delete("new_title");
    ob1->delete("g_number");
    ob1->delete("old_title");
    ob1->delete("g_invite_name");
    ob1->delete("g_invite_id");
    ob1->delete("g_idea");
	if (ob1 = present("lingpai", ob1)) destruct(ob1);
	return 1;
}

int do_fgo(string str)
{
    object ob, obj, env, me = this_player();
    string st1, st2, dir, dest;
    mapping exit;

    if (!me->query("g_name") )
	return notify_fail("你并没组建帮派或加入任何帮派，无法使用此命令。\n");
    if (!str || str=="") return notify_fail ("你想让谁去哪里啊？\n");
    if (sscanf(str,"%s %s", st1, st2) != 2)
	return notify_fail ("gfgo <下属> <方向>\n");
    if (!ob = present(st1, environment(me)))
	return notify_fail("找不到 "+ st1 + " 这个人.\n");
    env = environment(me);
    if (!env) return notify_fail("哪里也去不了。\n");
    if (!undefinedp(dir_alias[st2])) st2 = dir_alias[st2];
    if (!mapp(exit = env->query("exits")) || undefinedp(exit[st2]))
	return notify_fail("那个方向没有出路。\n");
    dest = exit[st2];
    if (!(obj = find_object(dest)))
	call_other(dest, "???");
    if (!(obj = find_object(dest)))
	return notify_fail("无法移动。\n");
    dir = obj->query("short");
    if (!undefinedp(dir_desc[st2]))
	dir = dir_desc[st2] + "的" + dir;
    if( !living(ob) )
	return notify_fail("你等" + ob->name() + "醒来再说吧。\n");
    if (ob->query("g_header_name") != me->query("g_header_name")||!ob->query("g_name")||!me->query("g_name") )
	return notify_fail("" + ob->name(1) + "不是你帮派的人，不能下命令。\n");
    if (ob->query("g_level") <= me->query("g_level")|| !ob->query("g_header_name")|| !me->query("g_header_name") )
	return notify_fail("" + ob->name(1) + "不是你的下属，你不可以下命令。\n");
    message_vision(HIR"$N命令$n向" + dir + "走去。\n"NOR,me,ob);
    ob->force_me("go "+st2);
    return 1;
}

int do_follow(string str)
{
    object ob1, ob2, me = this_player();
    string st1, st2;

    if (!me->query("g_name") )
	return notify_fail("你并没组建帮派或加入任何帮派，无法使用此命令。\n");
    if (!str || str=="") return notify_fail ("你想让谁 follow 谁啊？\n");
    if (sscanf(str, "%s with %s", st1, st2) != 2)
	return notify_fail ("gfollow <下属> with <他人>\n");

    if (!ob1 = find_living(st1)) ob1 = LOGIN_D->find_body(st1);
    if (!ob2 = find_living(st2)) ob2 = LOGIN_D->find_body(st2);
    if (!ob1 = present(st1, environment(me)))
	return notify_fail("这里没有 "+ st1 + " 这个人.\n");
    if (!ob2 = present(st2, environment(me)))
	return notify_fail("这里没有 "+ st2 + " 这个人.\n");
    if (ob1 == ob2)
	return notify_fail("命令错误。\n");
    if( !living(ob2) )
	return notify_fail("你等" + ob2->name() + "醒来再说吧。\n");
    if (ob1->query("g_name") != me->query("g_name")
	    || ob1->query("g_header_name") != me->query("g_header_name")
	|| !ob1->query("g_name")
	|| !me->query("g_name") )
	return notify_fail("" + ob1->name(1) + "不是你帮派的人，不能下命令。\n");
    if (ob1->query("g_level") <= me->query("g_level")||!ob1->query("g_name")||!me->query("g_name") )
	return notify_fail("" + ob1->name(1) + "不是你的下属，你不可以下命令。\n");

    message_vision(HIR"$N命令$n跟随" + ob2->name(1) + "一起行动。\n"NOR,me,ob1);
    ob1->set_leader(ob2);
    return 1;
}

int do_pk(string str)
{
    object ob1, ob2, me = this_player();
    string st1, st2;

    if (!me->query("g_name") )
	return notify_fail("你并没组建帮派或加入任何帮派，无法使用此命令。\n");
    if (!str || str=="") return notify_fail ("你想让谁 PK 谁啊？\n");
    if (sscanf(str, "%s with %s", st1, st2) != 2)
	return notify_fail ("gkill <下属> with <他人>\n");

    if (!ob1 = present(st1, environment(me)))
	return notify_fail("这里没有 "+ st1 + " 这个人.\n");
    if (!ob2 = present(st2, environment(me)))
	return notify_fail("这里没有 "+ st2 + " 这个人.\n");
    if (ob1 == ob2) return notify_fail("你没问题吧？\n");
    if (ob1->query("g_name") != me->query("g_name")||!ob1->query("g_name")||!me->query("g_name") )
	return notify_fail("" + ob1->name(1) + "不是你帮派的人，怎能命令？\n");
    if (ob1->query("g_level") <= me->query("g_level")||!ob1->query("g_name")||!me->query("g_name") )
	return notify_fail("" + ob1->name(1) + "不是你的下属，怎能命令？\n");
	if( !ob2->is_character() || ob2->is_corpse() )
		return notify_fail("那不是个活物。\n");
    if ( !living(ob1) )
	return notify_fail("你等" + ob1->name() + "醒来再说吧。\n");
    if ( environment(ob1)->query("no_fight") )
	return notify_fail("这里不准战斗！\n");
    if(strsrch(file_name(environment(me)),"/d/wuguan/") >= 0 && !ob2->query_condition("killer"))
	return notify_fail("武馆内禁止杀人。\n");
    if (userp(ob2) && ( me->query_condition("killer") > 180
	|| ob1->query_condition("killer") > 180 ))
	return notify_fail("一日不过三，别杀上瘾了。\n");

    message_vision(HIR"$N命令$n向" + ob2->name(1) + "发起攻击。\n"NOR,me,ob1 );
    message_vision(HIR"$N对$n大吼一声，立即发起了攻击。\n"NOR,ob1,ob2 );
    ob1->force_me("kill " + st2);
    return 1;
}

int do_halt(string str)
{
    object ob1,ob2,me = this_player();

    if (!me->query("g_name") )
	return notify_fail("你并没组建帮派或加入任何帮派，无法使用此命令。\n");
    if (!str || str=="") return notify_fail ("你想命令谁停止战斗？\n");
    if (!ob1 = find_living(str)) ob1 = LOGIN_D->find_body(str);
    if (!ob2 = present(str, environment(me)))
	return notify_fail("这里没有 "+ str + " 这个人.\n");
    if (ob1 == me) return notify_fail("用 halt 命令吧。\n");
    if (ob2->query("g_name") != me->query("g_name") )
	return notify_fail("" + ob2->name(1) + "不是你帮派的人，怎能命令？\n");
    if (ob1->query("g_level") < me->query("g_level") )
	return notify_fail("" + ob1->name(1) + "不是你的下属，怎能命令？\n");
    if (!ob1->is_fighting())
	return notify_fail(""+ str + " 现在没有在战斗。\n");
    if (!ob1->is_busy())
    {
	ob1->remove_all_enemy();
	message_vision(HIR"$N大喝一声，命令$n停止战斗。\n"NOR,me,ob1 );
	message_vision("\n$N身行向后一跃，跳出战圈不打了。\n", ob1);
	return 1;
    }
}

int filldata(object obj1)
{
	if(wiz_level(obj1)) return 0;
	if(!environment(obj1)) return 0;
	else return 1;
}

//glist格式改变，Look@SJ 990821-13:55
int do_list()
{
    int max,i,count=1;
    object obj1,me = this_player();
    string str, show="";
    mixed *ob_list;

    ob_list = users();
    ob_list = filter_array(ob_list, (: filldata :));
    max=sizeof(ob_list);
    write("［"HIW + me->query("g_title") + NOR"］目前在线成员如下：\n");
    write("------------------------------------------------------------------------------------\n");
    for (i=0;i<max;i++)
    {
	    obj1 = ob_list[i];
	if (obj1->query("g_title")==me->query("g_title"))
	{
	    switch(obj1->query("g_level"))
	    {
	    case 1: str = HIR"【"+me->query("g_type") + "　　主】"NOR;
		break;
	    case 2: str = HIR"【 副" +me->query("g_type") + "主 】"NOR;
		break;
	    case 3: str = HIR"【长  　老】"NOR;
		break;
	    case 4: str = HIR"【使  　者】"NOR;
		break;
	    case 5: str = HIR"【香　　主】"NOR;
		break;
	    default:str = HIR"【帮　　众】"NOR;
		}
		if( obj1->query("g_header_id") == obj1->query("marry/id") )
		{
			str = ( obj1->query("gender")=="女性" ?
				HIR"【" + me->query("g_type") + "主夫人】"NOR :
				HIR"【" + me->query("g_type") + "主夫君】"NOR );
		}
		show += sprintf("%-28s",str+obj1->query("name")+"("+capitalize(obj1->query("id"))+")");
		if (!(count % 3)) show += "\n";
		count ++;
	    }
	}
	me->start_more(show);
	write("------------------------------------------------------------------------------------\n");
	return 1;
}

/*
int do_cmd(string str)
{
	object ob1, me = this_player();
	string st1, st2;

	if (!me->query("g_name") )
		return notify_fail("你并没组建帮派或加入任何帮派，无法使用此命令。\n");
	if (!str || str=="") return notify_fail ("你想命令谁?干什么？\n");
	if (sscanf(str, "%s do %s", st1,st2) < 2)
		return notify_fail ("命令错误。\n");
		if (!ob1 = find_living(st1)) ob1 = LOGIN_D->find_body(st1);
	if (!ob1) return notify_fail("找不到 " + st1 + " 这个人。\n");
	if (!ob1 = present(st1, environment(me)))
		return notify_fail("这里没有 "+ st1 + " 这个人.\n");
	if( !living(ob1) )
		return notify_fail("你等" + ob1->name() + "醒来再说吧。\n");
	if (ob1->query("g_name") != me->query("g_name")
		 || ob1->query("g_header_name") != me->query("g_header_name")
		 || !ob1->query("g_name")
		 || !me->query("g_name") )
		return notify_fail("" + ob1->name(1) + "不是你帮派的人，不能下命令。\n");
	if (ob1->query("g_level") <= me->query("g_level")||!ob1->query("g_name")||!me->query("g_name") )
		return notify_fail("" + ob1->name(1) + "不是你的下属，你不可以下命令。\n");
	message_vision(HIR"$N手举 ["+ me->query("g_name")+ me->query("g_type")+
			"] 令牌，对$n命令道：" + st2 + "\n"NOR,me,ob1);
		command(st2);

		return 1;
}
*/

int do_clear(string str)
{
    object ob1,me = this_player();

    if (!wiz_level(me))
	return notify_fail("此命令巫师专用。\n");
    if (!str || str=="") return notify_fail ("你想清除谁的帮派标志？\n");
    if (!ob1 = find_living(str)) ob1 = LOGIN_D->find_body(str);
    if(!objectp(ob1 = present(str, environment(me))) )
	return notify_fail("这里没 " + str + " 这个人。\n");
    if( !living(ob1) )
	return notify_fail("你等" + ob1->name() + "醒来再说吧。\n");
    message_vision(HIR"$N从$n身上除下令牌，$n被清除出了" HIW+ ob1->query("g_title") + HIR"。\n"NOR,me,ob1);
    ob1->delete("g_level");
    ob1->delete("g_title");
    ob1->delete("g_name");
    ob1->delete("g_type");
    ob1->delete("g_header_name");
    ob1->delete("title");
    ob1->delete("new_title");
    ob1->delete("g_number");
    ob1->delete("old_title");
    ob1->delete("g_invite_name");
    ob1->delete("g_invite_id");
    ob1->delete("g_idea");
    destruct(ob1 = present("lingpai", ob1) ) ;
    return 1;
}

// 篡位的代码，tiantian
int do_up(string str)
{
    object ob1,ob2,me = this_player();
    string st2;
    int st5,st6,st3 = me->query("g_level");

    if (!me->query("g_name") )
	return notify_fail("你并没组建帮派或加入任何帮派，无法使用此命令。\n");
    if (!str || str=="") return notify_fail ("你想篡谁的位啊？\n");
    if (!ob1 = find_living(str)) ob1 = LOGIN_D->find_body(str);
    if (ob1 == me) return notify_fail("篡自己的位？你不是开玩笑吧。\n");
    if(!objectp(ob2 = present(str, environment(me))) )
	return notify_fail("这里没有这个人。\n");
    if (ob2->query("g_name") != me->query("g_name") && ob2->query("g_header_name") != me->query("g_header_name") )
	return notify_fail("" + ob2->name(1) + "不是你帮派的人。\n");
    if(ob2->query("g_header_id") == ob2->query("marry/id") && ob2->query("gender")=="女性")
	return notify_fail( ob2->query("g_type") + "主夫人的位子是可以随便篡来的吗？" );
    if(ob2->query("g_header_id") == ob2->query("marry/id") && ob2->query("gender")=="男性")
	return notify_fail( ob2->query("g_type") + "主夫君的位子是可以随便篡来的吗？" );
    st5 = ob1->query("g_level");
    if( !living(ob2) )
	return notify_fail("你等" + ob2->name() + "醒来再说吧。\n");
    if (st5 > st3) return notify_fail("篡下级的位？\n");
    if (st5 == st3) return notify_fail("此人和你级别相同，不需要篡位。\n");
    if ((int)st3 > (int)st5 + 1) return notify_fail("你想一下子就爬这么高，不怕掉下来摔坏屁股吗？\n");
    st6 = me->query("combat_exp");
    st2 = me->query("g_level");
    if (st6 < 2000000 && (int)st2 > 2 )
	    return notify_fail("你这点水平，也想篡这么高的位子？\n");
    if (st6 < 1500000 && (int)st2 > 3 )
	return notify_fail("你这点水平，也想篡这么高的位子？\n");
    if (st6 < 1000000 && (int)st2 > 4 )
	return notify_fail("你这点水平，也想篡这么高的位子？\n");
    if (st6 < 500000 && (int)st2 > 5 )
	return notify_fail("你这点水平，也想篡这么高的位子？\n");
    if ( environment(ob1)->query("no_fight") )
	return notify_fail("这里不准战斗！\n");

    message_vision(HIR"$N对$n冷笑道：老不死的，你在这个宝座上做了这么久，今天也该换个人了。\n"NOR,this_player(),ob1 );
    me->kill_ob(ob1);
    call_out("check_fight", 1, me, ob1);
	return 1;
}

void remove_effect( object me, object ob1 )
{
    object ob2;
    string st4;

    st4 = me->query("g_level");
    if( ob1->is_ghost() )
    {
	switch( st4 )
	{
	case 2:
	    message("channel:chat", HIC "【江湖传闻】"HIW+ ob1->query("g_title")
		+HIC + me->query("g_type") +"主" + ob1->query("name") +"被" + me->query("name")
		+"篡位了。\n" NOR,users());
			if( ob1->query("g_room") )
				me->set("g_room", 1 );
	    me->set("g_number",(int)ob1->query("g_number") + 1);
	    write_file( "/log/group", sprintf("%s %s 由 %s ( %s ) 担任第 %d 任帮主，宗旨 %s。\n", ctime(time())[4..19],
		me->query("g_title"), me->query("name"), me->query("id"), me->query("g_number"), me->query("g_idea") ));
	    me->set("g_level",1);
	    me->set("g_header_name",me->query("name"));
	    message_vision(HIR"$n被迫退出了" + ob1->query("g_title") + "。\n"NOR , me, ob1);
	    new( "/data/group/obj/ling" )->move(ob1);
		(ob2 = present("lingpai", ob1) )->move(me);
	    me->set("title","［"HIW+ me->query("g_title")
		+ NOR "］"+ HIG + me->query("g_type") +"主"NOR);
	    me->set("new_title",me->query("title") );
	    break;
	case 3:
	    message("channel:chat", HIC "【江湖传闻】"HIW+ ob1->query("g_title")
		+ HIC + "副" + me->query("g_type") +"主" + ob1->query("name")
		+"被" + me->query("name") +"篡位了。\n" NOR,users());
	    me->set("g_level",2);
	    message_vision(HIR"$n被迫退出了" + ob1->query("g_title") + "。\n"NOR ,me,ob1);
	    new( "/data/group/obj/ling" )->move(ob1);
	    (ob2 = present("lingpai", ob1) )->move(me);
	    me->set("title","［"HIW+ me->query("g_title") + NOR "］"+ HIG +
		    "副" + me->query("g_type") +"主"NOR);
	    me->set("new_title",me->query("title") );
	    break;
	case 4:
	    message("channel:chat", HIC "【江湖传闻】"HIW+ ob1->query("g_title")
		+ HIC + "长老" + ob1->query("name") +"被" + me->query("name") +"篡位了。\n" NOR,users());
	    me->set("g_number",(int)ob1->query("g_number") + 1);
	    me->set("g_level",3);
	    me->set("g_header_name",me->query("name"));
	    message_vision(HIR"$n被迫退出了" + ob1->query("g_title") + "。\n"NOR ,me,ob1);
	    new( "/data/group/obj/ling" )->move(ob1);
	    (ob2 = present("lingpai", ob1) )->move(me);
	    me->set("title","［"HIW+ me->query("g_name") + me->query("g_type") + NOR "］"+ HIG + "长老"NOR);
	    me->set("new_title",me->query("title") );
	    break;
	    case 5:
	    message("channel:chat", HIC "【江湖传闻】"HIW+ ob1->query("g_title")
		+ HIC +"使者" + ob1->query("name") +"被" + me->query("name") +"篡位了。\n" NOR,users());
	    me->set("g_number",(int)ob1->query("g_number") + 1);
	    me->set("g_level",4);
	    me->set("g_header_name",me->query("name"));
	    message_vision(HIR"$n被迫退出了" + ob1->query("g_title") + "。\n"NOR ,me,ob1);
	    new( "/data/group/obj/ling" )->move(ob1);
	    (ob2 = present("lingpai", ob1) )->move(me);
	    me->set("title","［"HIW+ me->query("g_title") + NOR "］"+ HIG +"使者"NOR);
	    me->set("new_title",me->query("title") );
	    break;
	default:
	    message("channel:chat", HIC "【江湖传闻】"HIW+ ob1->query("g_title")
		+ HIC + "香主" + ob1->query("name") +"被" + me->query("name") +"篡位了。\n" NOR,users());
	    me->set("g_number",(int)ob1->query("g_number") + 1);
	    me->set("g_level",5);
	    me->set("g_header_name",me->query("name"));
	    message_vision(HIR"$n被迫退出了" + ob1->query("g_title") + "。\n"NOR ,me,ob1);
	    new( "/data/group/obj/ling" )->move(ob1);
	    (ob2 = present("lingpai", ob1) )->move(me);
	    me->set("title","［"HIW+ me->query("g_name") + me->query("g_type") + NOR "］"+ HIG +"香主"NOR);
	    me->set("new_title",me->query("title") );
	    break;
	}

	ob1->delete("g_level");
	ob1->delete("g_title");
	ob1->delete("g_name");
	ob1->delete("g_header_name");
	ob1->delete("g_number");
	ob1->delete("g_type");
	ob1->delete("title");
	ob1->delete("g_invite_name");
	ob1->delete("g_invite_id");
	ob1->delete("new_title");
	ob1->delete("old_title");
	ob1->delete("g_idea");
	destruct(this_object());
	}
    else
    {
	switch( st4 )
	{
	case 2:
	    message("channel:chat", HIC "【江湖传闻】"HIW+ ob1->query("g_title")
		+ HIC + "副" +  me->query("g_type") +"主" + me->query("name") +"的篡位阴谋被粉碎了。\n" NOR,users());
	    break;
	case 3:
	    message("channel:chat", HIC "【江湖传闻】"HIW+ ob1->query("g_title")
		+ HIC +"长老" + me->query("name") +"的篡位阴谋被粉碎了。\n" NOR,users());
	    break;
	case 4:
	    message("channel:chat", HIC "【江湖传闻】"HIW+ ob1->query("g_title")
		+ HIC +"使者" + me->query("name") +"的篡位阴谋被粉碎了。\n" NOR,users());
	    break;
	case 5:
	    message("channel:chat", HIC "【江湖传闻】"HIW+ ob1->query("g_title")
		+ HIC +"香主" + me->query("name") +"的篡位阴谋被粉碎了。\n" NOR,users());
	    break;
	default:
	    message("channel:chat", HIC "【江湖传闻】"HIW+ ob1->query("g_title")
		+ HIC +"帮众" + me->query("name") +"的篡位阴谋被粉碎了。\n" NOR,users());
	    break;
	}
    }
}

void check_fight( object me, object ob1 )
{
    if( !me ) return;

    if (!me->is_fighting())
    {
	remove_effect(me, ob1);
	    return;
    }
    call_out("check_fight", 1, me, ob1);
}

int do_groom(string str)
{
	object me = this_player();
	string	dir;
	string 	here;
	string	filename;
	object env = environment(me);
	mapping exits = env->query("exits");
	string *pdir;

    if (!me->query("g_name") )
	return notify_fail("你先建好自己的帮派再去开总坛吧。\n");
    if (me->query("g_level")>1)
	return notify_fail("你不是"+me->query("g_type")+"主，无权建立总坛。\n");
    if (!str || str=="")
	return notify_fail ("你想在哪块空地建总坛啊？\n");

    if(file_name(env) != "/data/group/zongtan")
	return notify_fail( "这个地方不能开坛。\n" );

	if( me->query("g_room") )
		return notify_fail( "你不是已经建立过自己的房间了吗？\n" );

	if( me->query("balance") < 30000000 )
		return notify_fail( "你没有足够的资金来盖房子。\n" );

	init_var();

	if (sscanf (str, "%s", dir) != 1 )
		return notify_fail( "建立房间的命令格式是 groom <方向>。 \n" );
	else
	{
//		if( dir != "north" && dir != "south" && dir != "east" && dir != "west" )
//			return notify_fail( "<方向> 只能选择 north、south、east、west。\n" );
		if( !is_english(dir) )
			return notify_fail( "你只能用小写英文来命名入口方向。\n" );
		if( sizeof(dir) < 3 )
			return notify_fail( "这个入口的名字太短了，选个长点的吧。\n");

	filename = _GRPDIR_ + "/groom/" + me->query("id") + ".c";

		pdir = keys(exits);
		if( member_array(str,pdir) != -1 )
			return notify_fail( "这个方向没有空地，你还是换个地方盖房子吧。\n");
	}

	tmp["file_name"] = filename;
	tmp["no_fight"] = 0;
	tmp["no_clean_up"] = 0;
	tmp["valid_startroom"] = 0;
	tmp["g_name"] = me->query("g_name") + me->query("g_type");
	tmp["hard"] = 2000;
	tmp["damage"] = 0;
	tmp["combat_exp"] = 2000000;
	tmp["skill_lvl"] = 250;

	tmp["short"] = HIR "" + me->query("g_name") + me->query("g_type") + HIG " 总坛" NOR;
	tmp["long"] = "  这里是" + me->query("g_name") + me->query("g_type") + @ROOM_CODE
的总坛。上面供奉的是前任历代帮主的灵牌，
两位总坛护法伺立在下首。非本帮弟子不能随便进入，否则可能会
惹来杀身之祸。
ROOM_CODE;

	here  = file_name (environment(this_player()));
	tmp["exits"]["out"] = here;

	tmp["objects"]["/data/group/obj/ling-pai.c"] = 1;
	tmp["objects"]["/data/group/npc/hufa.c"] = 2;

	save_file();

	me->set("g_room",1);
	me->add("balance",-30000000);
	message_vision( HIC"只听\"哗\"的一声，在你面前树起了一幢大宅。\n"NOR, me);

    env->set("exits/"+str,filename);
    write_file( "/data/group/groom/log", sprintf( "帮派总坛 %s 出口 %s\n", filename,str) );

	return 1;
}

int is_english(string str)
{
	int i;

	i = 0;
	while( i < sizeof( str) )
	{
		if( str[i] < 'a' || str[i] > 'z' )
			return 0;
		i++;
	}

	return 1;
}



int save_room_file(string yn, string file, string str)
{
	if( strlen(yn)<1 || yn[0]!='y' )
		return 1;

	if ( write_file(file, str, 1) )
	{
	    return 1;
	}
	else
	{
	    write ("Mudos 尝试写入("+file+")失败!!\n");
		return 0;
	}
}



int save_file()
{
	string	room_code, *name, file;
	int	   i;

	file = tmp["file_name"];

	// room_code 是房间的程式码, 底下这一段是所有房间的共通点
	room_code = "// Room: " + tmp["file_name"] + @ROOM_CODE

inherit ROOM;

void create()
{
ROOM_CODE;
  // 一直到这边结束

	room_code = sprintf ("%s  set (\"short\", \"%s\");\n"
	       "  set (\"long\", @LONG\n%sLONG);\n\n",
	     room_code, tmp["short"], tmp["long"]);

	name = keys(tmp);
	for(i=0; i<sizeof(name); i++)
	{
	if( member_array(name[i], special_props)!=-1 )
		continue;
	if ( (intp(tmp[name[i]]) && tmp[name[i]]>0) ||
		(stringp(tmp[name[i]]) && tmp[name[i]] != "") ||
	    (mapp(tmp[name[i]]) && tmp[name[i]] == ([])) ||
	    sizeof (tmp[name[i]]) > 0)
	    room_code += sprintf("  set(\"%s\", %O);\n", name[i], tmp[name[i]] );
	}

	room_code += "  setup();\n}\n";

	save_room_file("y", file, room_code);

	return 1;
}

int init_var ()
{
	tmp["no_fight"]	       =       0;
	tmp["no_clean_up"]	    =       0;
	tmp["valid_startroom"]	=       0;
	tmp["file_name"]	      =       "";
	tmp["short"]		  =       "";
	tmp["long"]		   =       "";
	tmp["outdoors"]	       =       "";
	tmp["g_name"]					=		"";
	tmp["hard"]					=		"";
	tmp["damage"]					=		"";
	tmp["combat_exp"]				=		"";
	tmp["skill_lvl"]				=		"";
	tmp["item_desc"]	      =       ([]);
	tmp["exits"]		  =       ([]);
	tmp["objects"]		=       ([]);
}


int do_saveroom(string arg)
{
	object env;
	string str, *name, file, pre, suc;
	mapping prop;
	int i;

	env = environment(this_player());
	file = file_name(env) + ".c";

	if (file_size(file) <= 0) return
	  notify_fail ("没有这房间的档案: "+file+"\n");

	name = explode (read_file (file), "\n");
	pre = "";
	for (i=0; i<sizeof (name); i++)
	  if (strsrch (name[i], "void create") != 0)
	    pre += name[i] + "\n";
	  else break;
	pre += "void create ()\n{\n";

	i += 2;
	while (name && name[i][0..0] != "}") i++;
	suc = ""; i++;
	while (i<sizeof(name)) suc += name[i++]+"\n";

	prop = env->query_entire_dbase();

	str = pre;
	str = sprintf ("%s  set (\"short\", \"%s\");\n"
	       "  set (\"long\", @LONG\n%sLONG);\n\n",
	     str, prop["short"], prop["long"]);

	name = keys(prop);
	for(i=0; i<sizeof(name); i++) {
	  if( member_array(name[i], special_props)!=-1 ) continue;
	  if ( (intp(prop[name[i]]) && prop[name[i]]>0) ||
		(stringp(prop[name[i]]) && prop[name[i]] != "" ) ||
		(mapp(prop[name[i]]) && prop[name[i]] == ([])) ||
		sizeof (prop[name[i]]) > 0)
		    str += sprintf("  set(\"%s\", %O);\n",
				   name[i], prop[name[i]] );
	}
	if (sizeof (suc) < 5)
	 str += "\n  setup();\n}\n";
	else
	 str += "\n  setup();\n}\n"+suc;

	return save_room_file("y", file, str);
}

int do_rob()
{
    object me = this_player();
	object env = environment(me);
    object ob;

    if (!me->query("g_name"))
	return notify_fail ("你并没有加入任何玩家帮派，也没有组建自己的帮派。\n");
    if( me->query("g_level") > 3 )
	return notify_fail( "你的地位太低了，恐怕找不到人帮你。\n" );
    if( env->query("no_fight"))
	   return notify_fail("这里不能设置路障。\n");
    if( present("lu zhang",env) )
	return notify_fail( "这里已经有人在抢劫，你就别来凑热闹了。\n" );
    if( me->query_temp("g_rob" ) )
	return notify_fail( "你不是已经在抢劫了吗？\n" );
    if( me->query_condition( "killer" ) )
	return notify_fail( "你正要抢劫，忽然想到自己还是个通缉犯，不由得手软了下来。\n" );

	me->set_temp( "g_rob",1 );
	me->apply_condition("killer", 90);
	message("channel:rumor", HIM "【谣言】某人：听说现在有人正在"
	+ env->query("short")
	+ HIM "一带拦路抢劫。\n" NOR,users());
	message_vision( HIC "$N在路中间设好了路障，偷偷躲起来，准备要抢劫过往行人。\n" NOR, me );

	ob = new( "/data/group/obj/luzhang.c" );
	ob->set( "robber", me->query("id") );
	ob->move( env );

    return 1;
}
