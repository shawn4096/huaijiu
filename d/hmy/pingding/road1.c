// road1.c
// Created by Numa 19991027

inherit ROOM;

void create()
{
        set("short", "土路");
        set("long", @LONG
这是一条去黑木崖的必经之路，路上不断有人骑马经过，掀起了阵阵黄沙
，伸手难见五指。
LONG
        );
        set("exits", ([ 
          "west" : "/d/huanghe/tumenzi",
          "northeast" : __DIR__"road2",
]));
        setup();
}