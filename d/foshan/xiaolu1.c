//xiaolu1.c 

inherit ROOM;

void create()
{
        set("short", "小路");
        set("long",
"北面是一条上山的小路，南面就是岭南山口了。东北面隐隐传来哭
声，西北面传来阵阵木鱼声，间或有诵经的声音传来。\n"
        );
        set("outdoors", "佛山");
        set("exits", ([
            "northup" : __DIR__"xiaolu2",
            "south" : __DIR__"lingnan",
            "northeast" : __DIR__"fenchang",
            "northwest" : __DIR__"zumiao",
        ]));
        set("coor/x",0);
  set("coor/y",-490);
   set("coor/z",0);
   setup();
}

