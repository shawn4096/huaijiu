inherit ROOM;

void create()
{
    set("short", "后仓");
    set("long", @LONG
　　这是蒙古大军的囤粮之所，所谓兵马未动，粮草先行，
这里的粮食和草料堆积如山。一队队巡逻兵来回守卫，戒备
森严。
LONG);
    set("exits", ([
"northup" : __DIR__"xiaodao",
        "south" : __DIR__"liangcang2",
        ]));
    set("objects", ([
    	__DIR__"obj/liangdun" : 1,
        __DIR__"npc/yuanbing" : 1,
	    ]));
    setup();
}

int valid_leave(object me, string dir)
{
	object ob;
	
    ob = present("yuan bing",environment(this_player()) );
    if(ob)
    	return notify_fail("元兵一把将你拦住：哪里跑！\n" );
    
    return ::valid_leave(me, dir);
}
