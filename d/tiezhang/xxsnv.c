// Room: /d/tiezhang/xxsnv.c

inherit ROOM;

void create()
{
        set("short", "女弟子休息室");
        set("long", @LONG
这是一个黑暗的大房间。窗户用厚厚的帘子遮住，不露丝毫光亮。屋内整
齐的排列着十几张木板搭成的床铺，可以让练功后的帮众及时得到休息。这里
静悄悄的，黑暗中偶尔传来清微的鼾声。屋内淡淡的飘着一股幽幽的香气。
LONG
        );

        set("sleep_room", 1);
        set("no_fight", 1);

        set("exits",([
                "north" : __DIR__"zoulang-4.c",
        ]));

        set("coor/x",-310);
        set("coor/y",-260);
        set("coor/z",10);

        setup();
}

