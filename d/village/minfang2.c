// Room: /d/village/minfang2.c

inherit ROOM;

void create()
{
        set("short", "民房");
	set("long", @LONG
这是一个泥土夹草堆起的民房，可见房屋的主人并不是十分富裕，屋
子不大，弥漫着一股刺鼻的味道。
LONG
        );
        set("exits", ([
	"north" : __DIR__"shilu6",
]));
        set("objects", ([
                __DIR__"npc/oldwoman": 1 ]) );
        set("no_clean_up", 0);

        set("coor/x",20);
  set("coor/y",90);
   set("coor/z",0);
   setup();
}
 
