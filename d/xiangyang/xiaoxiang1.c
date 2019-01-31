// /d/xiangyang/xiaoxiang

inherit ROOM;

void create()
{
        set("short", "小巷");
        set("long", @LONG
这是一条安静的小巷，两边种着许多大树。南面就是温家的宅院了。北面
是个钱庄，再往西走就是襄阳府衙了，没什么事最好别去那个地方。
LONG
        );
        set("exits", ([
        "east"  : __DIR__"cross2",
        "west"  : __DIR__"yamen",
        "north"  : __DIR__"bank",
        "south" : __DIR__"damen1",
]));
 

        set("coor/x",-10);
 set("coor/y",0);
   set("coor/z",0);
   set("coor/x",-10);
  set("coor/y",0);
   set("coor/z",0);
   set("coor/x",-10);
  set("coor/y",0);
   set("coor/z",0);
   set("coor/x",-10);
  set("coor/y",0);
   set("coor/z",0);
   setup();
}

