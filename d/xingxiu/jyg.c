// Room: /d/xingxiu/jyg.c
#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIY"雁门关"NOR);
        set("long", @LONG
这里是长城最西的关隘雁门关，又称嘉峪关。岁月沧桑，掩不住它的风采。群山环
抱之下，更显它的雄浑。。再往西走便是著名的“丝绸之路”，值通西域，往东
顺着万里长城便可通往中原。这儿驻扎有边防军队，不时盘问来往行人。你小心
翼翼，急步离开这是非之地。
LONG);
        set("outdoors", "jyg");
        set("exits", ([
                "east" : __DIR__"jyge",
                "north" : __DIR__"xiaowu",
                "west" : __DIR__"jygw",
                "south" : __DIR__"jyg_1",
        ]));

        set("objects", ([
                __DIR__"npc/wujiang2" : 1, 
                __DIR__"npc/wujiang1" : 2, 
        ]));
        set("coor/x",-210);
  set("coor/y",70);
   set("coor/z",-10);
   set("coor/x",-210);
 set("coor/y",70);
   set("coor/z",-10);
   setup();
}
