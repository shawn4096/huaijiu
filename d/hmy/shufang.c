// shufang.c
// Created by Numa 19991022

#include <ansi.h>
inherit ROOM;

mapping *book = ({
	(["name":	"������ҩ",
	  "color":	HIR,
	  "show":	"��ͭɫ",]),
	(["name":	"�ܹ���������",
	  "color":	HIC,
	  "show":	"��ͭɫ",]),
	(["name":	"���ϻ�ͯ",
	  "color":	HIY,
	  "show":	"��ͭɫ",]),
	(["name":	"�����ɵ�",
	  "color":	HIG,
	  "show":	"��ͭɫ",]),
	(["name":	"�ⶾ",
	  "color":	HIM,
	  "show":	"��ͭɫ",]),
});

string do_have();
string do_see();

void create()
{
	set("short", "�鷿");
	set("long", @LONG
����������ͤ���鷿���鰸������ż����顣ǽ������һ����ܣ�
����������İڷ���һ��һ�����顣
LONG
	);
	set("exits", ([ 
        "north" : __DIR__"changlang3",
	]));
	set("item_desc",([
		"���":	(: do_have :),
		"shujia":	(: do_have :),
		"�鼮": (: do_see  :),
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
		message_vision(RED"$N�����˲�һ�ᣬ�о�������鼮��Щ�Ź֣�����Ҫ������Щ�鼮��\n",me);
		time = 1;
		call_out("do_boom", 20, me, time);
		return 1;
	}
	if (time >0 && time < 6) {
		call_out("do_happen",1,me);
		return 1;
	}
	else {
		message_vision(HIR"\n$N�����еĹż���ͻȻ����������ܹ�����ͤ���˽�����\n"NOR,me);
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
	return "һ��ʮ�ֿ�����ܣ�������Ų����鼮��\n";
}
string do_see()
{
	object me = this_player();
	
	if (!me->query_temp("shufang/have"))
		return "��˳�ַ����˼����飬û������ʲô������\n";
	me->delete_temp("shufang/have");
	me->set_temp("shufang/see",1);
	return "����ϸ���˿���Щ�鼮��������һ���屾�ż��ƺ������ۣ������ס��Ҫȡ����������\n";
}

int do_get(string arg)
{
	object me = this_player();
	string tar;
	int i;
	
	if (!me->query_temp("shufang/see"))
		return notify_fail("ʲô��\n");
	if (!arg || sscanf(arg,"%s %d from %s",arg,i,tar)!=3)
		return notify_fail("��Ҫȡʲô��\n");
	if (arg != "shu" && arg != "��")
		return notify_fail("��Ҫȡʲô��\n");
	if (i > 5 || i < 1)
		return notify_fail("��Ҫȡ�ڼ����飿\n");
	if (tar != "jia" && arg != "���")
		return notify_fail("�������ȡ��\n");
	
	me->set_temp("shufang/shu",i);
	message_vision("$N�������������" + CHINESE_D->chinese_number(i) + "����������������\n",me);
	return 1;
}

int do_fankan(string arg)
{
	object me = this_player();
	mapping book_info;
	int i,j;
	
	if (!me->query_temp("shufang/shu"))
		return notify_fail("ʲô��\n");
	if (!arg)
		return notify_fail("ʲô��\n");
	if (arg != "shu" && arg != "��")
		return notify_fail("��Ҫ����ʲô��\n");
	
	i = me->query_temp("shufang/shu");
	i = random(i) + 1;
	for (j=1;j<6;j++) {
		if (i == j) {
			book_info = book[i];
			tell_object(me,book_info["color"]+"����һ���������"+ book_info["name"] +"�Ĺż��������"+ book_info["show"] +"����ҳ�Ѿ����ƣ����Ҳ�ȱ�˼�ҳ��\n"NOR);
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
			tell_object(me,"�㷭���˼�ҳ����û��ʲô�ر�֮���������ַ��˻�ȥ��\n");
			break;
		}
	}
	return 1;
}

int do_happen(object me)
{
	object ob;
	
	message_vision(HIR"\n����$Nר����־�����ż�ʱ��һλħ�̳��ϳ��˹�����\n"NOR,me);
	ob = new(__DIR__"npc/killer4");
	ob->set_temp("target",me->query("id"));
	ob->move(environment(me));
	return 1;
}

int do_key(object me)
{
	tell_object(me,"��ͻȻ�����Ȿ�ż��ƺ��������ͱ����Щ��ͬ��\n");
	tell_object(me,"����룬Կ�׿��ܾͲ����Ȿ���С�\n");
	me->set_temp("shufang/getkey",1);
	add_action("do_open","open");
}

int do_open(string arg)
{
	object me = this_player();
	object obj, ob;
	
	if (!me->query_temp("shufang/getkey"))
		return notify_fail("ʲô��\n");
	if (!arg)
		return notify_fail("��Ҫ��ʲô��\n");
	if (arg != "shu" && arg != "��")
		return notify_fail("��Ҫ��ʲô��\n");
	
	tell_object(me,"�����ķ�ҳ������������һ���в㡣\n");
	if (me->query("kar")/10 < 2) {
		message_vision("$N�����еĹż���ͻȻ����������ܹ�����ͤ���˽�����\n",me);
		remove_action("do_open","open");
		me->delete_temp("shufang/getkey");
		obj = new(__DIR__"npc/yang");
		obj->set_temp("target",me->query("id"));
		obj->move(environment(me));
		me->start_busy(random(4));
		return 1;
	}
	message_vision("$N���������йż��ļв㣬ȡ����Կ�ס�\n",me);
	remove_action("do_open","open");
	me->delete_temp("shufang/getkey");
	ob = new(__DIR__"obj/key");
	ob->set_temp("owner",me->query("id"));
	ob->move(me);
	"/d/hmy/npc/yingying.c"->give_reward_2(me);
	return 1;
}
