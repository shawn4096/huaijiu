// by pishou

inherit ROOM;

void create()
{
    set("short", "杏子林");
       set("long", @LONG
这儿是杏子林中间的一片空地。一堆丐帮帮众坐在地上商议
着帮中大事。
LONG
       );

       set("exits", ([
        "south" : __DIR__"xinglin7",
        "north" : __DIR__"xinglin9",
       ]));

        set("objects", ([ 
                CLASS_D("gaibang") + "/song" : 1,  
            "/d/gb/npc/zfdizi" : 2,
                CLASS_D("gaibang") + "/bai" : 1,  
        ]));

        set("outdoors", "suzhou");
       setup();
}
