// Room: /u/dubei/wudang/hsxl5
#include <ansi.h>

inherit ROOM;

void create()
{
    set("short", "С·");
        set("long", @LONG
����һ���˼������ɽ´�����ܹ�ľïʢ����ʱ��Ұ�޵ĳ�û��ż����һ
Щ��ҩ��������Ѱ��һЩϡ�еĲ�ҩ��
LONG    );
        set("exits", ([ 
                 "southup" : __DIR__"hsxl4",
                 "northwest" : "/d/wudang/shanlu2",
])); 
        set("objects", ([
                  __DIR__"npc/lang" : 1,
        ]));
          set("outdoors", "�䵱");
          setup();
}

int valid_leave(object me, string dir)
{
 if (dir == "southup" ) {
	me->start_busy(2);
      return 1; }     
      return ::valid_leave(me, dir);

} 
