//mu_fa.c
//wzfeng
#include <ansi.h>
inherit ROOM;
void run_mufa(object me);
void run_mufa1(object me);
void run_mufa2(object me);
int do_order(string arg);

void create()
{
        set("short", "小帆船");
        set("long", @LONG
这是一艘小帆船，还没扬起帆来，只是随着海浪的起伏，缓缓
朝前飘去。水手站在船尾，正在等待你的命令。
LONG
);
		
        set("exits", ([
                
        ]));
	//set("no_fight",1);
        set("outdoors", "taishan");
        set_temp("curstatus","ready");
        setup();
}
void init()
{
	add_action("do_order", "order");
    
}

int do_order(string arg)
{
 	if( !arg || arg=="" ) return 0;
        if(query_temp("curstatus",1)=="run") return 0;
	if(arg!="开船")
	return notify_fail("你命令什么？\n");
	message_vision( HIY "$N对船尾的水手打了个手势，说道：“开船”。\n" NOR, this_player());
	message_vision( HIY "水手马上扬起风帆，调整好方向。\n"
		"一阵海风吹来，只见船身猛然加速，朝前疾驶而去。\n"NOR,this_player());
set("long","这是一艘小帆船，正扬起风帆朝前疾驶，随着海浪的起伏，船\n"
"身猛的左右摇晃。船尾的水手好象也有些颤颤惊惊，生怕一个不小\n"
"心被大海吞没。\n");
	
	set("player",this_player()->query("id"));
        set_temp("curstatus","run");
    remove_call_out("run_mufa");
    call_out("run_mufa", 10,this_player());

return 1;	
	
}

void run_mufa(object me)
{
     message("vision","小帆船突然向西一拐，继续向前疾驶而去。\n", this_object());
    remove_call_out("run_mufa1");
    call_out("run_mufa1", 6,me);		 

}

void run_mufa1(object me)
{
     message("vision","小帆船继续向西疾驶而去，你看不见一点陆地的影子。\n", this_object());
    remove_call_out("run_mufa2");
    //remove_call_out("run_mufa1");
    //if(random(10)>7)
           call_out("run_mufa2", 6,me);
    /*else		 
      call_out("run_mufa1", 30,me);*/	 

}

void run_mufa2(object me)
{
    object* ob;
    int i;

    message("vision","只见小帆船慢慢的减速，缓缓向岸边驶去。", this_object());
    //message("vision","“到了”水手对你吆喝一身。\n", this_object());
    ob = all_inventory(this_object());
    for(i=0; i<sizeof(ob); i++) 
    {
        if(!objectp(ob[i])) continue;
        tell_object(ob[i], "“到了”水手对你吆喝一身。\n");
        ob[i]->move("/d/sld/haitan");
        message_vision("$N轻轻一跃，下了船。\n",ob[i]); 
    }
    if(i>0)
    //message("vision","一条人影从小帆船上走下来。\n",me,);
    	message("vision","小帆船立即调头,缓缓驶向大海。\n",ob[0]);
    set_temp("curstatus","ready");
}



