// Room: /d/xingxiu/xxhh3.c 星宿海
// by shang 97/6

#include <room.h>

inherit ROOM;

void create()
{
        set("short", "星宿海");
        set("long", @LONG
这里是星宿海。因方圆几百里都是一望无际的湖泊和沼泽，当地
牧羊人称之为“海”。也因阴暗潮湿，毒虫繁殖甚富。星宿弟子常来
此捕捉毒虫，以备练毒之用。这里通向星宿海的深处。
LONG);
       
        set("exits", ([
                "east" : __DIR__"xxh1",
                "south" : __FILE__,
                "west" : __DIR__"xxh4",
                "north" : __DIR__"xxh2",
        ]));

        set("outdoors", "xingxiuhai");

        set("coor/x",-300);
  set("coor/y",170);
   set("coor/z",0);
   set("coor/x",-300);
  set("coor/y",170);
   set("coor/z",0);
   set("coor/x",-300);
 set("coor/y",170);
   set("coor/z",0);
   setup();

}
#include "/d/xingxiu/xxh.h";
