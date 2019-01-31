
#include <ansi.h>
inherit ROOM;

void run_mufa(object me);
void run_mufa1(object me);
void run_mufa2(object me);
void run_mufa3(object me);


void create()
{
        set("short", "快船");
        set("long", @LONG
这是马武德雇来的一艘快船。
舱内陈设简洁，物品码放整齐，几名干练的船工在船老大的指挥下，紧张有序地操纵
着船只。
LONG
);
        set("no_fight",1);
        set_temp("curstatus","ready");
        setup();
}

void init()
{
        object me = this_player();

        if(!me->query_temp("marks/勇闯夺命岛2",1)) {
        	message_vision("突然有个人飞起一脚把$N踢了出去。\n",me);
        	me->move(__DIR__"dukou");
        	tell_object(environment(me),me->name()+"被人从快船上踢了下来。\n",({me}));
        	return;
       	}  
        if(userp(me)) {
                call_out("run_mufa", 2,me);
        }
}

void run_mufa(object me)
{        
        if(!me){
        	destruct(this_object());
        	return;
        }
        message_vision(HIC"\n\n$N倚在舷窗边向海面上望去，眼见波涛汹涌，云低遮日，几只海鸥在掠波滑翔。\n"NOR,me);
        call_out("run_mufa1", 1+random(1), me);
}

void run_mufa1(object me)
{        
        if(!me){
        	destruct(this_object());
        	return;
        }
        message_vision(CYN"\n\n此刻海风正急，快船疾速行驶，片刻功夫后$N便在海面东北方看到有一处陆地。\n"NOR,me);
        call_out("run_mufa2", 1+random(1), me);
}

void run_mufa2(object me)
{        
        if(!me){
        	destruct(this_object());
        	return;
        }
        message_vision(WHT"\n\n转眼间快船已然驶近陆地，但见岸上树木苍翠，长长的海滩望不到尽头，尽是雪白细沙。\n"NOR, me);
        call_out("run_mufa3", 1+random(1), me);
}

void run_mufa3(object me)
{
        int i;
        i = 1 + random(3);
        if(i>3) i = 3;
        
        if(!me){
        	destruct(this_object());
        	return;
        }
        message_vision("快船慢慢靠向陸地，$N机警地环视四周，一个纵身落在沙滩之上。\n",me);
        me->delete_temp("marks/勇闯夺命岛2");
        me->move("/cmds/leitai/dmd/haitan1");
        me->set_temp("marks/勇闯夺命岛3",i);
        tell_room(environment(me), me->name() + "从快船飞身落下。\n",me);  
        destruct(this_object());
}