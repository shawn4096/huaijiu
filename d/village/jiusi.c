// Room: /d/village/jiusi.c

inherit ROOM;

void create()
{
        set("short", "酒肆");
        set("long", @LONG
这里是村子西面的一个小酒肆，平时供村民门闲暇的时候来这里消遣
你一走进来，一股劣质水酒的刺鼻味道直向你扑过来。屋子的中央摆着几
张桌子，店家在一旁忙碌着。
LONG
        );
        set("exits", ([
		"south" : __DIR__"shilu3",
	]));

/*
        set("objects", ([
                __DIR__"npc/": 2 ]) );
*/
        set("no_clean_up", 0);

        set("coor/x",-10);
  set("coor/y",110);
   set("coor/z",0);
   setup();
}


