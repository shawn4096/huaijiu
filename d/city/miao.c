// Room: /u/firefox/miao.c

inherit ROOM;

void create()
{
        set("short", "英烈夫人庙");
        set("long", @LONG
这儿就是英烈妇人庙，供奉的是韩世忠夫人，当初韩世忠妇人曾经当过妓
女，应此妓女每年必到英烈夫人庙烧香许愿，祈祷这位宋朝的安国夫人有灵，
照顾后代的同行姐妹。
LONG    );
        set("no_clean_up", 0);
        set("exits", ([
                "east" : __DIR__"winmo",
        ]));
        set("objects", ([
                __DIR__"npc/xiangnu" : 2,
	]));
        set("no_fight", 1);
        set("coor/x",40);
  set("coor/y",10);
   set("coor/z",0);
   set("coor/x",40);
  set("coor/y",10);
   set("coor/z",0);
   set("coor/x",40);
  set("coor/y",10);
   set("coor/z",0);
   setup();
}
