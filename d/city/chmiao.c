// Room: /d/city/chmiao.c
inherit ROOM;
void create()
{
        set("short", "城隍庙");
        set("long", @LONG
这里是扬州城里的城隍庙。平日本来香客稀少，但最近突然拥挤起来。西
北方是巫师会客室，往北是扫雷游戏室，东边出去就是扬州北大街了。
LONG    );
        set("exits", ([ 
                "east" : __DIR__"beidajie1",
                "north" : __DIR__"mine_room",
                "northwest" : "/d/wizard/guest_room",
        ]));
        set("no_fight", 1);
        set("no_sleep_room", 1);
        set("objects", ([ /* sizeof() == 1 */
                __DIR__"npc/ymonk" : 1,
        	__DIR__"obj/box" : 1
        ]));
        set("coor/x",110);
  	set("coor/y",20);
   	set("coor/z",0);
   	setup();
        "/clone/board/wizto_b"->foo();
}

void init()
{
        object me = this_player();
        if (me->query("qiankun/qi") && me->query("qiankun/neili")) {
                 me->set("max_qi",me->query("qiankun/qi"));
                 me->set("max_neili",me->query("qiankun/neili"));
                 me->delete("qiankun/qi");
                 me->delete("qiankun/neili");
        }

     	me->delete_temp("die_record");
        add_action("action", ({
                "dazuo",
                "du",
                "exercise",
                "lian",
                "practice",
                "respirate",
                "study",
                "tuna"
        }));
}

int action()
{
        write("你无法静下心来修炼。\n");
        return 1;
}

