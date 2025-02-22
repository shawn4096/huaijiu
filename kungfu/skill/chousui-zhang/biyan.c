#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
#include "/kungfu/skill/eff_msg.h";

int perform(object me, object target)
{
      object ob;
      string msg, *limbs;
      int i, neili, ap, dp, damage, p;
        
      i = (int)me->query_skill("chousui-zhang", 1);
      neili = (int)me->query("neili");   
        if( !target ) target = offensive_target(me);
        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) 
        || !living(target)
        || environment(me)!=environment(target) )
                return notify_fail("「碧焰」攻击只能对战斗中的对手使用。\n");
      
        if( objectp(me->query_temp("weapon")) )
                return notify_fail("你必须空手才能使用「碧焰」！\n");        
        if(!objectp(ob = present("huo yan", environment(me))))
                return notify_fail("没有火堆怎么驱动「碧焰」进行攻击？\n");
        if(me->query_temp("pfm_chousui"))
                return notify_fail("你正在驱动火堆进行攻击！\n");
        if( i < 80 )
                return notify_fail("你发现自己的星宿毒掌还不够娴熟，无法使用「碧焰」进行攻击。\n");

        if( (int)me->query_skill("huagong-dafa",1) < 80 )
                return notify_fail("你发现自己的化功大法修为不够，无法使用「碧焰」进行攻击。\n");

        if((int)me->query_skill("poison",1) < 60)
                return notify_fail("你发现自己体内聚毒不够，无法使用「碧焰」进行攻击。\n");         

        if (me->query_skill_prepared("strike") != "chousui-zhang"
        || me->query_skill_mapped("strike") != "chousui-zhang"
        || me->query_skill_mapped("parry") != "chousui-zhang")
                return notify_fail("你必须用抽髓掌才能使用「碧焰」进行攻击。\n"); 
                                                                              
        if( me->query_skill_mapped("force") != "huagong-dafa")
                return notify_fail("你发现自己所用的内功无法进行「碧焰」攻击。\n");

        if( (int)me->query("max_neili") < 500) 
                return notify_fail("你发现自己内力太弱，无法驱动「碧焰」进行攻击。\n");

        if(neili < 300)
                return notify_fail("你发现自己现在真气太弱，使不出「碧焰」进行攻击。\n");           
    
        if(target->query_condition("xx_poison") > 200)
                return notify_fail("对方已经身中无数剧毒，你不用再进行「碧焰」攻击了。\n");           

       message_vision(HIC"\n$N右手指向"HIR"火堆"HIC"，默不作声的注视着火焰，左掌按胸，口中喃喃的不知说些什么。。。\n"NOR,me);
       me->start_busy(1+random(2));
          
        ap = me->query("combat_exp")/1000 * i * me->query_str();
        dp = target->query("combat_exp")/1000 * target->query_skill("parry",1) * target->query_dex();
        if (ap < 1) ap = 1;
        if (dp < 1) dp = 1;
        me->add("neili", -200);
        me->add("jingli", -25);

        msg = HIC"\n然后$N突然双掌向前平平推出，但见"RED"火焰"HIC"微微颤动了两下，吐出一道"GRN"碧焰"HIC"，射向$n的$l！\n"NOR;        
        if(random(ap+dp) > dp){
        	damage = (i+me->query("jiali"))*4;
          	if(neili > target->query("neili")*2) damage *= 2;
                if( damage > 1500) damage = 1500;
          	target->receive_damage("qi", damage, me);
          	target->receive_wound("qi", random(damage), me);
          	target->apply_condition("xx_poison",  (me->query_skill("poison", 1)/2) + target->query_condition("xx_poison"));
		if (userp(me) && userp(target) && me->query_condition("killer") < 15 && 
		  me->query_temp("kill_other/"+target->query("id")) && target->query_temp("other_kill/"+me->query("id")))
			me->apply_condition("killer", 15);
          	p = (int)target->query("qi")*100/(int)target->query("max_qi");
          	msg += damage_msg(damage, "刺伤");
          	msg += "( $n"+eff_status_msg(p)+" )\n";
          	me->start_busy(1);
          	if(!target->is_busy())
          		target->start_busy(3);
          	}
        else{
          	me->start_busy(2);
          	msg += HIY"\n$p全力向后一纵一闪，凶险万分地避开了那急速而来的$w"HIY"！\n" NOR;
        }  
             
       limbs = target->query("limbs");
       msg = replace_string(msg, "$l", limbs[random(sizeof(limbs))]);
       msg = replace_string(msg, "$w", GRN"碧焰"NOR);
       message_vision(msg, me, target);
       me->start_perform(4,"碧焰");
       return 1;
}

