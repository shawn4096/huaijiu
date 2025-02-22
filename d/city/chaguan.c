// Room: /city/chaguan.c

inherit ROOM;

void create()
{
	set("short", "茶馆");
	set("long", @LONG
这是扬州城南的一家茶馆。一走进来，就闻到一股茶香沁入心脾，你的精
神为之一爽。几张八仙桌一字排开，坐满了客人，或高声谈笑，或交头接耳。
壁上挂了一幅字贴(zitie) 。茶馆中有一说书之人，讲述三国志、水浒传、大
明英烈传等等英雄故事。茶博士正在吆喝着招呼客人, 递茶送水, 忙的不亦乐
乎。
LONG
	);
	set("resource/water", 1);

	set("exits", ([
		"east" : __DIR__"nandajie2",
	]));

        set("item_desc", ([
		"zitie" : "十年一觉扬州梦，赢得青楼薄幸名。\n"
        ]));
	set("objects", ([
		__DIR__"npc/boshi" : 1,
		__DIR__"npc/shuren" : 1,
	]));

	set("coor/x",90);
  set("coor/y",-30);
   set("coor/z",0);
   set("coor/x",90);
  set("coor/y",-30);
   set("coor/z",0);
   set("coor/x",90);
  set("coor/y",-30);
   set("coor/z",0);
   set("coor/x",90);
  set("coor/y",-30);
   set("coor/z",0);
   setup();
}

