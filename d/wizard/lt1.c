#include <ansi.h>

inherit ROOM;
string look_leitai();
void create()
{
        set("short", HIY"风云门"NOR);
        set("long", "这里是"+MUD_NAME+"里的风云门比武擂台，台下挤满了来自各门各派的观众。
围绕着擂台下(leitai)报名台(info)有无数高手，此处人声鼎沸，热闹无
比，这里通往东南西北各处比武看台。\n");
        set("no_fight", 1);
        set("no_sleep_room", 1);
        set("leitai", "/cmds/leitai/leitai1");
        set("exits", ([            
            "out" : "/d/city/leitai", 
            "east" : __DIR__"lt1a", 
            "west" : __DIR__"lt1b",  
            "south" : __DIR__"lt1c",
            "north" : __DIR__"lt1d",   
        ]));    
        set("item_desc",([            
            "leitai" : (: look_leitai :),
            "info" : "\n您如要打擂，请用打入： dalei 或 打擂\n",
        ]));
        
        set("outdoors", "比武擂台");  
        setup(); 
}
#include "leitai_fun.h"

void init()
{
	delete_temp("num");
	add_action("do_biwu", ({ "dalei", "打擂" }));
     	add_action("do_action", ({"dazuo", "tuna", "lian", "learn", "du", "steal", "hit",
                             "kill", "fight", "study", "practice","exercise", "exert",}));
}

int do_biwu()
{
	object me, ob;
	
	me = this_player();
	
	if( me->query("combat_exp") < 100000 ) 
        	return notify_fail("要想上台比武，你的资格还差了些，先去练练吧。\n");  
        	
	if (!(ob = find_object(query("leitai"))))
          	ob = load_object(query("leitai"));
        
        if( !ob ) 
        	return notify_fail("比武擂台没有准备好，请通知巫师。\n");  
	if( ob->query_temp("leitai") > 1 )
		return notify_fail("这里正在比武呢，你先等他们分出胜负再说吧。\n");  

	message_vision("\n$N拔开人群，大声说道："+RANK_D->query_self(me)+"来打擂，说完便往台上跳去！\n", me);
	return ob->load_user(me);
}



