
#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

void do_huixuan(object me, object target, object weapon, int times);

int perform(object me, object target)
{
        string msg;
        object weapon;
        int time,exp;

       if( !target ) target = offensive_target(me);


      weapon = me->query_temp("weapon");
	if( !target || !target->is_character() || !me->is_fighting(target) )
       return notify_fail("[回旋十三式]只能在战斗中使用。\n");
       if (me->is_busy())
       return notify_fail("你正忙着呢。\n");
      if (!weapon || weapon->query("skill_type") != "whip"
       || me->query_skill_mapped("whip") != "huifeng-bian")
          return notify_fail("你手里没有鞭，无法使用「回旋十三式」！\n");             
        if( !target || !target->is_character()|| !me->is_fighting(target) )
       return notify_fail("「回旋十三式」只能对战斗中的对手使用。\n");

        if( target->is_busy() )
                return notify_fail(target->name() + "目前正自顾不暇，放胆攻击吧！\n");

        if( (int)me->query_skill("huifeng-bian", 1) < 100 )
                return notify_fail("你的回风鞭法不够娴熟，不会使用「回旋十三式」绝技。\n");

        if( (int)me->query_skill("huntian-qigong", 1) < 100 )
                return notify_fail("你的混天气功不够深厚，不会使用「回旋十三式」。\n");

        if( (int)me->query("neili")<300)
                return notify_fail("你现在内力太弱，不能使用「回旋十三式」。\n");

       if(me->query_skill_mapped("force") != "huntian-qigong")
              return notify_fail("你现在使用的内功与回风鞭法相抵触，不能使用「回旋十三式」。\n");

        me->add("neili", -200);
        me->set_temp("huixuan",1);
        msg = HIY+"\n$N"+HIY+"突然身形如陀螺般急转数圈，手中的"+weapon->query("name")+HIY+"，借助这股强劲\n";
		msg+="的回旋力量，连出十三种幻化莫测的招式，罩向$n！\n"NOR;
        message_vision(msg,me,target);
        exp=random(me->query("combat_exp")*16/10);
        if ( exp > random( target->query("combat_exp")))
        {      msg +=HIR+"$n一个没留神，被$N变幻莫测的招式所惑,罩在幻象般的鞭影里！\n"NOR;
                me->start_busy(1);
                target->start_busy(1);
                time = me->query_skill("whip")/40 +1 ;  
             message_vision(msg,me,target);
              me->start_call_out( (: call_other, __FILE__, "do_huixuan", me, target , weapon, time:), 1);
        }
        else {
                msg += CYN+"可是$n成竹在胸，抢中宫直进，从容不迫先手在握。\n"NOR;
                me->start_busy(random(8)+1);
              message_vision(msg,me,target);
		}
		return 1;
}

void do_huixuan(object me, object target, object weapon, int times)
{
        int force;
        if(!me->is_fighting(target)) {
       message_vision(HIY+"\n$N"+HIY+"内力已尽，"+weapon->query("name")+HIY+"软绵绵的垂将下来。\n"NOR,me);
	me->delete_temp("huixuan");	 
         return ;
        }
        if( !living( me ) || me->is_ghost() ) 
       {
         me->delete_temp("huixuan");  
         return;
       }
        if(times<=0) {
       message_vision(HIY+"\n$N"+HIY+"内力已尽，"+weapon->query("name")+HIY+"软绵绵的垂将下来。\n"NOR,me);
        me->delete_temp("huixuan");	 
                 return ;
        }
      
        force=random(me->query_skill("whip")*13/10);
         if(force  > random(target->query_skill("dodge")) ) {
           if (weapon->query("id")=="po budai")
		   { 
			message_vision( HIR+me->query("name")+"将手中的"+weapon->query("name")+"象$n头上一罩。\n"NOR,me,target);
            tell_object(target,BLU"你觉得脸上一阵剧痛，啊，你被蝎子咬了。\n"NOR);
			target->receive_wound("qi",me->query_skill("whip",1)/4);
            target->receive_wound("jing",me->query_skill("whip",1)/4);
target->apply_condition("scorpion_poison", 10+target->query_condition("scorpion_poison"));
           }
         	message_vision( HIR"$n"+HIR+"被幻影完全迷惑$N乘机连连出招\n"NOR,me,target);
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"), TYPE_QUICK);
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"), TYPE_QUICK);
                call_out("do_huixuan",4,me,target,weapon,times-1);
        }
        else
       call_out("do_huixuan",3,me,target,weapon,times-1);

}
