// Room: /d/xingxiu/xxh.c

#include <wanted.h>
inherit ROOM;

void create()
{
        set("short", "���޺�");
        set("long", @LONG
��������ɽ���µ����޺����ߡ���Բ�����ﶼ��һ���޼ʵĺ���
�����󣬵��������˳�֮Ϊ��������һ���м�ֻ��Ⱥ���������ڡ������
����Ҳ�Ҳ����ˡ�������������������̳�����ں����롣
LONG
        );
        set("exits", ([
             "north" : __DIR__"xxh1",
             "south" : __DIR__"shanjiao",
             "southeast" : __DIR__"yili",
        ]));
        set("objects", ([
                __DIR__"npc/gushou"  : 1,
                __DIR__"npc/haoshou" : 1,
                __DIR__"npc/boshou" : 1,
                __DIR__"npc/azi" : 1,
        ]) );

        set("outdoors", "xingxiuhai");

        set("coor/x",-310);
  set("coor/y",140);
   set("coor/z",0);
   setup();
}

int valid_leave(object me, string dir)
{
	if (is_wanted(me) && dir == "north")
		return 0;
	return ::valid_leave(me, dir);
}
