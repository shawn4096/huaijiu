// xingyi.c 斗转星移perform星移
//COOL@SJ,20000909

#include <ansi.h>

inherit F_SSERVER;

#include "/kungfu/skill/eff_msg.h";

int perform(object me, object target)
{
        int damage,p;
        string msg;

        if( !target ) target = offensive_target(me);

        if( !target
         || !target->is_character()
         || !me->is_fighting(target) )
                return notify_fail("星移斗转之星移只能对战斗中的对手使用。\n");

        if( (int)me->query_skill("douzhuan-xingyi", 1) < 120 )
                return notify_fail("你的星移斗转还未练成，不能使用！\n");

        if( (int)me->query("max_neili") < 1800 )
                return notify_fail("你现在内力修为不够，不能使用星移斗转之星移！\n");     

        if( (int)me->query("neili") < 800 )
                return notify_fail("你现在真气不足，不能使用星移斗转之星移！\n");

        if( (int)me->query_skill("parry", 1) < 120 )
                return notify_fail("你的基本招架之法不够娴熟，不能使用星移斗转之星移。\n");

        if (me->query_skill_mapped("parry") != "douzhuan-xingyi")
                return notify_fail("你现在无法使用星移斗转。\n");                                                                                 
        msg = HIY "\n忽然天昏地暗，$N催动内劲，使出$n的绝招，袍袖中两股内家真气向$n扑去！\n"NOR;
        if(me->query("neili") < random(target->query("neili")*2/3)){
           me->start_busy(1);
           target->start_busy(1); 
           me->add("neili", -me->query_skill("force"));
           me->add("jingli", -50);
           target->add("jingli", -50);
           target->add("neili", -me->query_skill("force"));
           msg += HIY"结果$p和$P两人内力一拼，双方都没占到丝毫好处！\n"NOR;
           message_vision(msg, me, target);
		me->start_perform(4,"星移");                 
           call_out("xingyi_hit", 3, me, target);   
           return 1;
        }
        if ((random(me->query_skill("parry"))+me->query_skill("literate",1)/4) 
           > target->query_skill("parry")/2){
           me->start_busy(1);
           target->start_busy(1);

           me->add("jingli", -100);
           damage = (int)me->query_skill("shenyuan-gong", 1);
           damage = (int)me->query_skill("douzhuan-xingyi", 1) +damage;
           damage += me->query("max_neili")/20;
           damage += damage;
           if( damage > 1500 ) damage = 1500;
        me->start_perform(5,"星移");                 
           target->receive_damage("qi", damage);
           target->receive_wound("qi", damage/3);   
           me->add("neili", -(damage/3));             
           p = (int)target->query("qi")*100/(int)target->query("max_qi");
           msg += damage_msg(damage, "内伤");
           msg += "( $n"+eff_status_msg(p)+" )\n";
           if (me->query("neili",1)>300)
           call_out("xingyi_hit", 2, me, target);                      
        }
        else{
           me->start_busy(3);
        me->start_perform(2+random(2),"星移");                 
           me->add("jingli", -50);
           me->add("neili", -200);
           msg += CYN"\n$p怎么也想不到$N能够使出自己的成名绝技，危及之中双脚跋地而起，艰难的躲过这一招，脸色变的苍白。\n" NOR;
        }
        message_vision(msg, me, target);
        return 1;
}

int xingyi_hit(object me, object target)
{
        int skill,i,j;
     string msg;   
        mapping apply;
        skill = (int)me->query_skill("douzhuan-xingyi", 1);                
        j = skill/80;   
        skill = skill/6;
        if(skill>100) skill=100;
        
        
        if (j>3) j=3;     
        if( !target
         || !target->is_character()
         || !me->is_fighting(target) )
              return notify_fail("你正要催力再击出一诏，却见对手已经落荒而逃了。\n");
       
        if(!living(target)) 
              return notify_fail("对手已经不能再战斗了。\n");

        if((int)me->query("neili", 1) < 200 )
              return notify_fail("你正要催力再击出一诏，却发现自己的内力不够了！\n"); 
                
        if(me->query_skill_mapped("parry") != "douzhuan-xingyi")
             return notify_fail("你现在无法使用星移斗转。\n");         
        
        apply=target->query_temp("apply");
     if(apply) {
        me->set_temp("douzhuan/damage_apply",(apply["damage"]+apply["strength"])/2);
        me->set_temp("douzhuan/attack_apply",apply["attack"]);
    }
      msg = HIR "\n紧接着$N运招犹如行云流水,连续使出几下对方的招数,将对方的攻击尽数反了回去！\n"NOR;
	message_vision(msg, me, target);
        me->add_temp("apply/damage", skill+me->query_temp("douzhuan/damage_apply"));
        me->add_temp("apply/attack", skill+me->query_temp("douzhuan/attack_apply"));
        for (i=0;i< j;i++) {
            if(me->is_fighting(target))
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
        }
        me->add_temp("apply/damage", -(skill+me->query_temp("douzhuan/damage_apply")));
        me->add_temp("apply/attack", -(skill+me->query_temp("douzhuan/attack_apply")));
        me->add("neili", -j*50);
        me->start_busy(2);
        return 1;
}
