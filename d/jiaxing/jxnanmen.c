// Room: /d/jiaxing/jxnanmen.c

inherit ROOM;

void create()
{
        set("short", "嘉兴南门");
        set("long", @LONG
这里是嘉兴的南门。周围长着茂密的竹林。东面是座庙宇。
向南是一片江南水乡。
LONG
        );

        set("exits", ([
                "north" : __DIR__"jiaxing",
                "east" : __DIR__"tieqiang",
                "south" : __DIR__"xiaojing1",
        ]));

        set("outdoors", "嘉兴");
        set("coor/x",140);
  set("coor/y",-310);
   set("coor/z",0);
   setup();
}
