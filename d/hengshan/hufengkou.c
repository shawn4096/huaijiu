// Room: /d/hengshan/hufengkou.c
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "虎风口");
        set("long", @LONG
过 "步云桥" ， "望仙亭" ，就到了一个峰回路转的陡峭路口，
这里是一处风口，大风来处，声如虎啸，比别处强劲多多，故有是
名。
LONG);
        set("exits", ([ /* sizeof() == 4 */
           "southwest" : __DIR__"daziling",
           "west"      : __DIR__"xuangengsong",
           "northeast" : __DIR__"guolaoling",
        ]));
        set("outdoors", "恒山");
        set("no_clean_up", 0);
        set("coor/x",70);
  set("coor/y",90);
   set("coor/z",50);
   setup();
}

