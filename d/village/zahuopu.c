// Room: /d/village/zahuopu.c

inherit ROOM;

void create()
{
        set("short", "杂货铺");
	set("long", @LONG
这是一间小小的杂货店，墙角摆著一堆堆的货物，上山的游客可以在这买
些上山用品。墙上贴着个牌子，是个价目表(sign)。
LONG
        );
        set("exits", ([
	"south" : __DIR__"shilu4",
]));
        set("item_desc", (["sign" :
        "牌子上写道：
	手杖(stick)	一百文
	麻鞋(shoes)	一百五十文
	水壶(bottle)	一百文

	兼售 皮蛋(egg) 五十文\n"
]));

        set("no_clean_up", 0);

        set("objects", ([
	                __DIR__"npc/xiaofan": 1
        ]) );

        set("coor/x",10);
  set("coor/y",110);
   set("coor/z",0);
   setup();
}
 