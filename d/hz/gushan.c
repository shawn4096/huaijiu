// /u/beyond/hz/gushan.c 孤山
 
inherit ROOM;
void create()
{
        set("short","孤山");
        set("long", @LONG
在西湖的外湖与内湖之间，就是孤山，其实是一座小岛，岛上青峰独秀，
又多梅花。每当天晴之日，旭日东升之时，泛舟湖上，回首孤山，白雪皑皑，
宛如置身琼楼玉宇之中。唐代诗人白居易有诗云：“到岸请君回头望，蓬莱
宫在水中央”。孤山的东连白堤，西面就是西冷桥。
LONG
        );
    set("outdoors", "杭州");
        set("exits", ([
            "west" : __DIR__"xilengqiao",
            "northeast" : __DIR__"baidi",
            "south" : __DIR__"wenlange",
            "north" : __DIR__"fangheting",
]));
        set("coor/x",70);
  set("coor/y",-350);
   set("coor/z",0);
   setup();
}
