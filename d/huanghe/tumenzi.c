// by XiaoYao

#include <room.h>

inherit ROOM;

void create()
{
	set("short", "������");
	set("long", @LONG
������Ҳ����ǰפ���ĵط�����Χȫ��ɳĮ���м�һ��СС�����ޣ�
���������е��ص������ס������ǰ��������һ������ռ������������
��Ϊ��Ӫ�ĳ����ӣ��޶�����
LONG );
	set("exits", ([
		"south"     : __DIR__"wuwei",
		"northeast" : __DIR__"shixiazi",
          "northwest" : "/d/hengshan/jinlongxia",
//       "east" : "/d/hmy/pingding/road1",
	]));
	set("no_clean_up", 0);
	set("outdoors", "�ƺ�");
	set("coor/x",60);
  set("coor/y",130);
   set("coor/z",0);
   setup();
}

int valid_leave(object me, string dir)
{
        if (userp(me) && !wizardp(me) && !me->query_temp("hmy_tester") && dir == "east")  
                return notify_fail("ֻ�в����߲��ܹ�ͨ����\n");
        return ::valid_leave(me, dir);
}
