inherit ROOM;

void create()
{
    set("short", "中军");
    set("long", @LONG
　　这是蒙古大军的中军，远处隐隐传来号角和战马
的嘶鸣之声。
LONG);
    set("exits", ([
        "north" : __DIR__"zhongjun4",
        "south" : __DIR__"zhongjun2",
        ]));
    set("objects", ([
        __DIR__"npc/yuanbing-shiwei" : 1,
	    ]));
    setup();
}

int valid_leave(object me, string dir)
{
	object ob;
	
    ob = present("zhongjun shiwei",environment(this_player()) );
    if(ob)
    	return notify_fail("中军侍卫一把将你拦住：哪里跑！\n" );
    
    return ::valid_leave(me, dir);
}
