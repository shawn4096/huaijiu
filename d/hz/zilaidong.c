// /u/beyond/hz/zilaidong.c 紫来洞
 
inherit ROOM;
void create()
{
        set("short","紫来洞");
        set("long", @LONG
你从这里的前山林海亭循磴道上山，过“佛道崖”、“玉皇宫”，就到
了紫来洞。洞前可俯视山下的“八卦田”，传说这就是南宋皇帝所谓“躬耕
的籍田，每逢春耕，皇帝率文武百官到此籍礼，用以表示对农业的重视。
LONG
        );
        set("exits", ([
            "north" : __DIR__"yuhuangshan",
            "southup" : __DIR__"shanlu2",
                        
]));
        set("coor/x",100);
  set("coor/y",-360);
   set("coor/z",0);
   setup();
}
