// Room: /d/village/miaoyu.c

inherit ROOM;

void create()
{
        set("short", "玄坛庙");
	set("long", @LONG
这是一间十分破旧的小庙，庙里供的神像是赵玄坛，神像已经很残破
了，神案上也积了很多尘土，看来已有很久没人来上香进供了。大概村民
贫困的太久，已不再寄望於老天降福给他们了。
LONG
        );
        set("exits", ([
	"north" : __DIR__"shilu5",
]));
        set("objects", ([
                __DIR__"npc/wupo": 1 ]) );

        set("no_clean_up", 0);

        set("coor/x",-20);
  set("coor/y",90);
   set("coor/z",0);
   setup();
}
