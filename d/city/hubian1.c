// /u/beyond/hangzhou/hubian.c 西湖边
#include <ansi.h>
#include <room.h>
inherit ROOM;
void create()
{
        set("short",GRN"瘦西湖边"NOR);
        set("long", @LONG
    瘦西湖湖山青水秀，碧波涟漪，湖光山色，相映成趣，泛舟湖上犹如
镜中行，漫步湖堤则如画中游。西湖之美令人陶醉。自古以来，人们常以艳、
娇、媚、秀、柔、嫩来形容她。
LONG
        );
set("objects",([
__DIR__"npc/you" : 2,

]));
        set("exits", ([
"west" : __DIR__"lxs",
"south" : __DIR__"dhq",
]));
	set("outdoors", "扬州");
        set("coor/x",90);
  set("coor/y",40);
   set("coor/z",0);
   set("coor/x",90);
  set("coor/y",40);
   set("coor/z",0);
   set("coor/x",90);
  set("coor/y",40);
   set("coor/z",0);
   set("coor/x",90);
  set("coor/y",40);
   set("coor/z",0);
   setup();
}
