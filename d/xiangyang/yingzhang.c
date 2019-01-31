inherit ROOM;

void create()
{
        set("short", "营帐中");
        set("long", @LONG
这是蒙古攻击襄阳的临时军营，营帐中有许多大将、谋士
走来走去，大声的谈论、争执。
LONG
        );
        set("outdoors", "襄阳");
        set("objects", ([
//         "/d/xiangyang/npc/mengge" : 1,
                "/d/xiangyang/npc/weishi" : 3,
        ]));


        set("exits", ([
                "out" : __DIR__"junying",
        ]));

        set("no_fight",1);

        set("coor/x",30);
  set("coor/y",30);
   set("coor/z",10);
   setup();
}
