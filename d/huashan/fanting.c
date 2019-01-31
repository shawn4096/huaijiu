// Room: /d/huashan/fanting.c
// Date: Look 99/03/25

inherit ROOM;

#include <ansi.h>

string* names = ({
	FOOD_D("baozi"),
	FOOD_D("cuishan"),
	FOOD_D("douhua"),
	FOOD_D("doufu"),
	FOOD_D("guoba"),
	FOOD_D("jitui"),
	FOOD_D("liji"),
	FOOD_D("liyu"),
	FOOD_D("niurou"),
	FOOD_D("peanut"),
//	FOOD_D("ruzhu"),
	FOOD_D("sansi"),
	FOOD_D("yaoliu"),
});

void create()
{
	set("short", "����");
	set("long", @LONG
������ǻ�ɽ�ɵ����÷��ĵط����������Ǻܴ󣬵��������������ϰ���
һЩʳ����˴������Ρ���ʱ��һЩ��ɽ����������ȥ��������æЩʲô��
LONG
	);

	set("exits", ([
		"north" : __DIR__"yaofang",
		"east" : __DIR__"celang3",
	]));
	set("objects",([
			__DIR__"npc/puren" : 1,
        	__DIR__"obj/qingshui-hulu" : 1,
	]));
	set("indoors", "��ɽ" );
	set("coor/x",60);
  set("coor/y",-30);
   set("coor/z",80);
   setup();
}

void init()
{
	object obj1, obj2;
	object me = this_player();
	if (me->query("family/family_name") == "��ɽ��" 
	&& (int)me->query("food") < 100
	&& present("pu ren", environment(me))
	&& random(10) < 8 ) {
	obj1 = new(FOOD_D("rice"));
        obj2 = new(names[random(sizeof(names))]);
        if( clonep(obj2) && clonep(obj1)) {
        	message_vision(HIC"\n����˵���������Ѿ�׼�����ˣ�����ȳ԰ɡ�\n" NOR, me);
        	obj1->move(me);
        	obj2->move(me);
		}
	}
}

int valid_leave(object me, string dir)
{
	if ( present("pu ren", environment(me))
    && (present("rice", me)
	  || present("fanqie yaoliu", me) || present("kousansi", me)
	  || present("niurou", me) || present("huasheng", me)
	  || present("tangcu liyu", me) || present("zhuachao liji", me)
	  || present("jitui", me) || present("rou pian", me)
	  || present("doufu", me) || present("douhua", me)
	  || present("liangxi cuishan", me) )
	  && ( dir == "east" || dir == "north" ) )
	{
		return notify_fail("����˵��������������ȳ԰ɣ����߸�ʲô��\n");
	}
	return ::valid_leave(me, dir);
}
