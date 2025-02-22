// shufang.c
// Created by Numa 19991022

#include <ansi.h>
inherit ROOM;

mapping *book = ({
	(["name":	"制作毒药",
	  "color":	HIR,
	  "show":	"红铜色",]),
	(["name":	"能够长生不老",
	  "color":	HIC,
	  "show":	"青铜色",]),
	(["name":	"返老还童",
	  "color":	HIY,
	  "show":	"黄铜色",]),
	(["name":	"提炼仙丹",
	  "color":	HIG,
	  "show":	"绿铜色",]),
	(["name":	"解毒",
	  "color":	HIM,
	  "show":	"紫铜色",]),
});

string do_have();
string do_see();

void create()
{
	set("short", "书房");
	set("long", @LONG
这里是杨莲亭的书房，书案上面摆着几摞书。墙边立着一个书架，
里面层层叠叠的摆放着一摞一摞的书。
LONG
	);
	set("exits", ([ 
        "north" : __DIR__"changlang3",
	]));
	set("item_desc",([
		"书架":	(: do_have :),
		"shujia":	(: do_have :),
		"书籍": (: do_see  :),
		"shuji": (: do_see  :),
	]));
	setup();
}

void init()
{
	object me = this_player();
	int time;
	
	if (me->query_temp("hostage/job_2") == 2) {
		add_action("do_get",({"na","qu"}));
		add_action("do_fankan","fan");
		time = 0;
		call_out("do_boom", 10, me, time);
	}
}

int do_boom(object me, int time)
{
	object obj;
	
	if (!me || environment(me) != this_object())
		return 1;
	if (time = 0) {
		message_vision(RED"$N进来了不一会，感觉这里的书籍有些古怪，便想要翻看这些书籍。\n",me);
		time = 1;
		call_out("do_boom", 20, me, time);
		return 1;
	}
	if (time >0 && time < 6) {
		call_out("do_happen",1,me);
		return 1;
	}
	else {
		message_vision(HIR"\n$N打开手中的古籍，突然，日月神教总管杨莲亭冲了进来。\n"NOR,me);
		obj = new(__DIR__"npc/yang");
		obj->set_temp("target",me->query("id"));
		obj->move(environment(me));
		me->start_busy(random(4));
		return 1;
	}
}
	
string do_have()
{
	object me = this_player();
	
	me->set_temp("shufang/have",1);
	return "一个十分宽大的书架，上面放着不少书籍。\n";
}
string do_see()
{
	object me = this_player();
	
	if (!me->query_temp("shufang/have"))
		return "你顺手翻看了几本书，没发现有什么异样。\n";
	me->delete_temp("shufang/have");
	me->set_temp("shufang/see",1);
	return "你仔细看了看这些书籍，发现有一套五本古籍似乎很显眼，你禁不住想要取下来翻看。\n";
}

int do_get(string arg)
{
	object me = this_player();
	string tar;
	int i;
	
	if (!me->query_temp("shufang/see"))
		return notify_fail("什么？\n");
	if (!arg || sscanf(arg,"%s %d from %s",arg,i,tar)!=3)
		return notify_fail("你要取什么？\n");
	if (arg != "shu" && arg != "书")
		return notify_fail("你要取什么？\n");
	if (i > 5 || i < 1)
		return notify_fail("你要取第几本书？\n");
	if (tar != "jia" && arg != "书架")
		return notify_fail("你从哪里取？\n");
	
	me->set_temp("shufang/shu",i);
	message_vision("$N从书架上面抽出第" + CHINESE_D->chinese_number(i) + "本书拿下来翻看。\n",me);
	return 1;
}

int do_fankan(string arg)
{
	object me = this_player();
	mapping book_info;
	int i,j;
	
	if (!me->query_temp("shufang/shu"))
		return notify_fail("什么？\n");
	if (!arg)
		return notify_fail("什么？\n");
	if (arg != "shu" && arg != "书")
		return notify_fail("你要翻看什么？\n");
	
	i = me->query_temp("shufang/shu");
	i = random(i) + 1;
	for (j=1;j<6;j++) {
		if (i == j) {
			book_info = book[i];
			tell_object(me,book_info["color"]+"这是一本讲述如何"+ book_info["name"] +"的古籍，封面呈"+ book_info["show"] +"，书页已经泛黄，而且残缺了几页。\n"NOR);
			if (random(me->query("kar")/10) < 1 && me->query_temp("shufang/killed") < 5) {
				me->delete_temp("shufang/shu");
				remove_call_out("do_happen");
				call_out("do_happen",1,me);
				me->start_busy(1);
				break;
			}
			if (random(me->query("kar")/10) > 0 && me->query_temp("shufang/killed") > 4) {
				me->delete_temp("shufang/shu");
				me->delete_temp("shufang/see");
				remove_call_out("do_key");
				call_out("do_key",1,me);
				me->start_busy(1);
				break;
			}
			me->delete_temp("shufang/shu");
			tell_object(me,"你翻看了几页，并没有什么特别之处，于是又放了回去。\n");
			break;
		}
	}
	return 1;
}

int do_happen(object me)
{
	object ob;
	
	message_vision(HIR"\n正在$N专心致志翻看古籍时，一位魔教长老冲了过来。\n"NOR,me);
	ob = new(__DIR__"npc/killer4");
	ob->set_temp("target",me->query("id"));
	ob->move(environment(me));
	return 1;
}

int do_key(object me)
{
	tell_object(me,"你突然发现这本古籍似乎的重量和别的有些不同。\n");
	tell_object(me,"你猜想，钥匙可能就藏在这本书中。\n");
	me->set_temp("shufang/getkey",1);
	add_action("do_open","open");
}

int do_open(string arg)
{
	object me = this_player();
	object obj, ob;
	
	if (!me->query_temp("shufang/getkey"))
		return notify_fail("什么？\n");
	if (!arg)
		return notify_fail("你要打开什么？\n");
	if (arg != "shu" && arg != "书")
		return notify_fail("你要打开什么？\n");
	
	tell_object(me,"你打开书的封页，发现里面是一个夹层。\n");
	if (me->query("kar")/10 < 2) {
		message_vision("$N打开手中的古籍，突然，日月神教总管杨莲亭冲了进来。\n",me);
		remove_action("do_open","open");
		me->delete_temp("shufang/getkey");
		obj = new(__DIR__"npc/yang");
		obj->set_temp("target",me->query("id"));
		obj->move(environment(me));
		me->start_busy(random(4));
		return 1;
	}
	message_vision("$N缓缓打开手中古籍的夹层，取出了钥匙。\n",me);
	remove_action("do_open","open");
	me->delete_temp("shufang/getkey");
	ob = new(__DIR__"obj/key");
	ob->set_temp("owner",me->query("id"));
	ob->move(me);
	"/d/hmy/npc/yingying.c"->give_reward_2(me);
	return 1;
}
