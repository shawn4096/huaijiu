// Room: /d/village/tiejiangpu.c

inherit ROOM;

void create()
{
        set("short", "铁匠铺");
	set("long", @LONG
这是一间甚是简陋的铁匠铺，入门正中是个大铁砧，满地煤渣碎铁，
墙上挂着几张犁头，屋子的角落里堆着几把破锄头、镰刀，靠墙放着几把
新出炉的铁锤。
LONG
        );
        set("exits", ([
	"west" : __DIR__"shilu2",
]));
        set("no_clean_up", 0);
        set("objects", ([
                __DIR__"npc/feng": 1 ]) );

        set("coor/x",10);
  set("coor/y",90);
   set("coor/z",0);
   setup();
}
 
