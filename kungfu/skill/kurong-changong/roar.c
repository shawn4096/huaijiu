// roar.c tls 狮子吼
//COOL@SJ 19990909

#include <ansi.h>

inherit F_CLEAN_UP;

int exert(object me, object target)
{
/*
        string force;
        mapping msg;
*/
        object *ob;
        
        int i, skill, damage;

        if( (int)me->query("neili") < 1500 )
                return notify_fail("你的内力不够。\n");

        if (me->query_skill_mapped("force") != "kurong-changong" )
                return notify_fail("你现在的内功没有这项功能。\n");     

        if( environment(me)->query("no_fight") )
                return notify_fail("在这里不能攻击他人。\n");

        if( (int)me->query_skill("force") < 200 )
                return notify_fail("你的内功修为不够。\n");
                
        if( (int)me->query_skill("buddhism",1) < 150 )
                return notify_fail("你的禅定功夫不够。\n");
        
        if( (int)me->query("jingli") < 150 )
                return notify_fail("你太累了，还是休息一下吧。\n");      


        me->add("neili", -300);
        me->receive_damage("jingli", 100);

        me->start_busy(2);
     	me->start_exert(8,"狮子吼");

        message_vision(HIY"猛听得“呜哗”一声大喝，各人耳中均震得嗡嗡作响。$N使出佛门中一门\n"+
                          "极上乘的功夫，叫作‘狮子吼’，一声断喝中蕴蓄深厚内力。\n" NOR, me);

        ob = all_inventory(environment(me));
        for(i=0; i<sizeof(ob); i++) {
        	skill = me->query_skill("force") + me->query_skill("buddhism",1);
                if( wizardp(ob[i])||!living(ob[i]) || ob[i]==me ) continue;
		if( !me->can_kill_ob(me, ob[i]) ) continue;
                if( random(skill) < (int)ob[i]->query_skill("force")/3*2) continue;
                skill -= ob[i]->query_skill("force")/2;
                damage = skill - ((int)ob[i]->query("neili") / 20);
                damage += random(damage);
            	if( (int)ob[i]->query("neili") < (int)me->query("neili")*2)
             		damage+=damage;
                tell_object(ob[i], "你被这巨吼震的眼前发晕，脑中一片空白，不由一阵恍惚。\n");
                if (ob[i]->is_fighting()){
                    	ob[i]->remove_all_enemy();
                    	message_vision("\n$N身体一缓，停止了战斗。\n", ob[i]); 
                }
/*
                else if ((int)ob[i]->query_temp("pending/exercise")){
                   	force = ob[i]->query_skill_mapped("force");
                   	if (force) msg = SKILL_D(force)->exercise_msg(ob[i]);
                   	if (!msg || undefinedp(msg["halt_msg"]))
                      		message_vision("$N你只觉气息不顺，站了起来。\n", ob[i]);
                   	else
                      		message_vision("$N只觉气息不顺,"+msg["halt_msg"], ob[i]);
                }
                else if ((int)me->query_temp("pending/respirate") != 0) 
                	message_vision("$N只觉气息不顺，猛吸几口大气，站了起来。\n", me);
                ob[i]->interrupt_me();
		if(ob[i] && living(ob[i])) ob[i]->start_busy(random(3));
*/
		ob[i]->receive_damage("jing", damage, me);
        }
        return 1;
}
