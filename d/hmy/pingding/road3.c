// road3.c
// Created by Numa 19991027

inherit ROOM;

void create()
{
        set("short", "土路");
        set("long", @LONG
这是一条去黑木崖的必经之路，路上黄沙弥漫。你努力向东边望去，发现
有一座小城，那就是日月神教管辖的平定州了。
LONG
        );
        set("exits", ([ 
          "westdown" : __DIR__"road2",
          "east" : __DIR__"gate1",
]));
        setup();
}

