// /u/beyond/hangzhou/hongyuchi.c 牡丹园
inherit ROOM;
void create()
{
        set("short", "牡丹园");
        set("long", @LONG
你走到牡丹园内，看到假山高处有一重檐八角的牡丹亭，亭周植有各种
名贵的牡丹几百株，还有四季应时之花，八节常青之树，有的傲然挺立，有
的盘曲多姿，远看宛如一幅立体的中国山水画。
LONG
        );
set("objects",([
__DIR__"npc/you1" : 2,
]));
        set("exits", ([
        "east" : __DIR__"hggyu",
]));
        setup();
}
