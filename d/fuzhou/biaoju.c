// Room: /d/fuzhou/biaoju.c

inherit ROOM;

void create()
{
	set("short", "福威镖局");
	set("long", @LONG
你来到一座结构宏伟的建筑前，左右石坛上各插着一根两丈多高的旗杆，
杆上青旗飘扬。右首旗子用金线绣着一头张牙舞爪的狮子，狮子上头有一只蝙
蝠飞翔。左首旗子上写着“福威镖局”四个黑字，银钩铁划，刚劲非凡。入口
处排着两条长凳，几名镖头坐着把守。少镖头正跟他们说笑。
LONG
	);

	set("exits", ([
		"south" : __DIR__"zhengting",
        	"north" : __DIR__"xijie",
	]));

	set("objects", ([
		__DIR__"npc/linpingzhi" : 1,
		__DIR__"npc/biaotou" : 2,
	]));

	set("coor/x",90);
  set("coor/y",-480);
   set("coor/z",0);
   setup();
}

