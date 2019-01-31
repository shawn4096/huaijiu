// automake group room , Fri May 20 12:17:50 2011
inherit ROOM;
#include <ansi.h>
#include "/d/group/entry.h"
void create()
{
set("short","黄土路");
set("long","你走在一条尘土飞扬的黄土路上，两旁是阴森森的树林。这里是鄂西，据
说经常有土匪出没，不可久留。
");
set("exits",([
"east":"/d/wudang/wdroad6","west":"/d/wudang/wdroad8","south":"/d/group/lili/1305865070.c",
]));
set("outdoors","武当山");
set("group",1);
setup();
}
