// Room: //dali/ximen.c
// bbb 1997/06/11
// Modify By River 98/12/

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "��������");
	set("long", @LONG
������ͨ��������ɲ�ıؾ�֮�أ��������鷸�ƵĴ�ͽ�������������ɽ
�У������ڴ�ֵ�ڵ��佫�ٱ��ܻ񣬶���ү���ǳ����Լ���������������������
�����Խ������������ﲻ����
LONG
	);
//        set("outdoors", "����");
   set("no_fight",1);
	set("exits", ([
              "westup" : "/d/tls/diancang",
              "east" : __DIR__"xijie4",
	]));
	set("objects", ([
	       __DIR__"npc/zhudanchen" : 1,
		__DIR__"npc/wujiang" : 1,
		__DIR__"npc/bing" : 2,
	]));
	set("coor/x",-340);
  set("coor/y",-420);
   set("coor/z",-20);
   setup();
}

void init()
{       
        object me = this_player();
	int i, login_cnt = 0;
	object *usr;

	usr = filter_array(users(), (: environment :));
	i = sizeof(usr);
        if( wizardp(me)) return;

	while (i--) {
		if (query_ip_number(usr[i]) == query_ip_number(me))
			login_cnt++;
		}
	me->set_temp("multi_login",0);
	if (login_cnt > 5) 
		me->set_temp("multi_login",1);
	if (me->query_temp("multi_login") && query_ip_number(me) == "118.26.118.8" && login_cnt < 11) 
		me->set_temp("multi_login",0);
     
}



