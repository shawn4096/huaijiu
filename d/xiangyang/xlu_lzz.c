// Room: xlu_lzz.c
// Looklove y2k/4/26

inherit ROOM;

void create()
{
        set("short","小路");
        set("long", @LONG
这是通往柳宗镇的一条小路，行人不是很多。路上偶尔能看到车轮碾压过
的痕迹。路两旁长满了低矮的灌木，树林里不时传出一两声鸟叫。再往北边走
就是柳宗镇了。
LONG
        );

        set("exits", ([
                "south" : __DIR__"xiaolu1",
                "north" : __DIR__"liuzz",
        ]));
 
        set("coor/x",-40);
  set("coor/y",10);
   set("coor/z",0);
   setup();
}

