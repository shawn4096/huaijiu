// room: /d/xingxiu/tianshan
#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "天山山路");
        set("long","
这里是天山东麓，山风从山上吹下来，冷得你瑟瑟发抖。这儿背靠
天山，阳光充裕。常年有雪水灌溉，土地肥沃，滋长了一片草原。草原
上肥羊成群结队，一对对牧羊男女弹起了冬不拉，互诉衷肠。
------------------"WHT"天山暂时关闭！"NOR"----------------------\n");

        set("exits", ([
           "southeast" : "/d/hj/senlin1",
        ]));

        set("outdoors", "tianshan");

        set("objects", ([
                __DIR__"npc/hkid" : 1,
                __DIR__"npc/hgirl" : 1,
                __DIR__"npc/yang" : 3,
        ]));

        set("coor/x",-320);
  set("coor/y",120);
   set("coor/z",0);
   setup();
}
