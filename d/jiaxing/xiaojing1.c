// /d/jiaxing/xiaojing1.c 江南乡间小径

inherit ROOM;

void create()
{
        set("short", "乡间小径");
        set("long", @LONG
江南乡间阡陌纵横，小路弯来绕去，道路狭窄，你数次踏入
田中，双脚全是烂泥。
LONG
        );

        set("exits", ([
                "north" : __DIR__"jxnanmen",
                "southeast" : __DIR__"shulin1",
                "east" : __DIR__"river",
        ]));

        set("outdoors", "嘉兴");
        set("coor/x",140);
  set("coor/y",-320);
   set("coor/z",0);
   setup();
}
