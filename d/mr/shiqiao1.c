

// /u/beyond/mr/shiqiao1.c
// this is made by beyond
// update 1997.6.20
#include <ansi.h>
#include <room.h>
inherit ROOM;
void create()
{
         set("short",HIW"小石桥"NOR);
         set("long",@long
这是一座小小的白石拱桥。桥下碧绿的湖水正荡着微波。石桥的东面是
一条鹅卵石铺成的小径，西面是曼佗罗山庄的前院。
long);
set("outdoors","mr");
         set("exits",([
             "east" : __DIR__"xiaojing5",
             "west" : __DIR__"qianyuan",
]));
        setup();
}

void init()
{
        add_action("do_zuan", "zuan");        
}

int do_zuan(string arg)
{
	object me = this_player();
	mapping myfam;
	
	myfam = (mapping)me->query("family");
	
	if(!arg || arg != "didao")
	    return notify_fail("你要往哪里钻？\n");       
     
        if ( myfam && myfam["family_name"] != "姑苏慕容")
            return notify_fail(" gg");
            
	message_vision("$N一转身，忽然一下子钻到地下不见了。\n",me);
	me->move(__DIR__"didao");
	message("vision",me->name() + "从石桥边跃了上来。\n",environment(me), ({me}) );
        return 1;
}