// 海潮汹涌
// By River 
// Modify By River@SJ 2000.2.22
#include <ansi.h>
#include <combat.h> 
inherit F_SSERVER;
string *xue_name = ({ 
"劳宫穴","膻中穴","曲池穴","关元穴","曲骨穴","中极穴","承浆穴","天突穴","百会穴",
"幽门穴","章门穴","大横穴","紫宫穴","冷渊穴","天井穴","极泉穴","清灵穴","至阳穴",
}); 

int perform(object me, object target)
{
        string msg,dodge_skill;
        int i,j,busy,exp,texp,skill,tskill,p;
        object weapon;
        if( me->query("gender") =="男性"){
           i = me->query_skill("xuantie-jianfa", 1)/4;
           j = me->query_skill("sword", 1)/4;
        }
        else {
           i = me->query_skill("xuantie-jianfa", 1)/6;
           j = me->query_skill("sword", 1)/6;
        }
        weapon = me->query_temp("weapon");

        if( !target ) target = offensive_target(me);

        if( !target || !me->is_fighting(target) )
                return notify_fail("玄铁剑法的「海潮汹涌」只能在战斗中对对手使用。\n");

        if( !weapon || weapon->query("skill_type") != "sword")
                return notify_fail("你必须使用武器才能使用「海潮汹涌」！\n");

        if((int)me->query_skill("xuantie-jianfa", 1) < 130 )
                return notify_fail("你的玄铁剑法还不够娴熟，使不出「海潮汹涌」绝技。\n");

        if((int)me->query_skill("yunu-xinjing", 1) < 130 )
                return notify_fail("你的玉女心经等级还不够，使不出「海潮汹涌」绝技。\n");

        if((int)me->query_skill("force") < 180 )
                return notify_fail("你的内功等级不够，不能使用「海潮汹涌」。\n");

        if((int)me->query_str() < 33 )
                return notify_fail("你的膂力还不够强劲，使不出「海潮汹涌」来。\n");

        if( target->query_temp("xtjf/haichao"))
                return notify_fail(target->name()+"正自顾不暇，你可以放心地进攻。\n");

        if( me->query_skill_mapped("sword") != "xuantie-jianfa" && userp(me))
                return notify_fail("你现在无法使用「海潮汹涌」！\n");

        if( me->query_skill_mapped("parry") != "xuantie-jianfa" && userp(me))
                return notify_fail("你现在无法使用「海潮汹涌」！\n");

        if((int)me->query_temp("xinjing")) 
                return notify_fail("你正在使用「心经」字诀。\n");

        if((int)me->query("max_neili") < (me->query_skill("force")+j+200) )
                return notify_fail("你现在内力太弱，使不出「海潮汹涌」。\n");      
        if( me->query("env/玄铁剑法") != "海潮" ){
         message_vision(HIB"\n$N微笑不语，将手中的"+weapon->query("name")+HIB"从轻而响，从响而轻，忽寂然无声，忽轰轰之声，向$n席卷而去。\n"NOR,me,target);
         me->add_temp("apply/sword", i);
         me->add_temp("apply/attack", j);
         me->set_temp("xtjf_pfm", 1);
         COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
         if (present(target,environment(me)) && me->is_fighting(target))
         COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
         if (present(target,environment(me)) && me->is_fighting(target)){
          if( random(me->query("combat_exp",1)) > target->query("combat_exp", 1)/3)
            COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
          else
            COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
         }
         me->add_temp("apply/sword", -i);
         me->add_temp("apply/attack", -j);
         if(userp(me))
            me->add("neili", -(me->query_skill("force")));
         else
            me->add("neili", -200);
         me->add("jingli", -150);
         me->delete_temp("xtjf_pfm");
         me->start_perform(5,"「海潮汹涌」");
        }
        if((int)me->query_skill("xuantie-jianfa", 1) > 150
         &&(int)me->query("neili", 1) > (me->query_skill("force")+j)
         && objectp(target)
         && present(target,environment(me))
         && me->is_fighting(target)
         && me->query("env/玄铁剑法") !="汹涌"){
         if( me->query("env/玄铁剑法") == "海潮")
          message_vision(HIB"\n$N持"+weapon->query("name")+HIB"挟巨浪潮涌之势，剑气形成一个旋转的气涡，向$n笼罩过去。\n"NOR,me,target);
         else
          message_vision(HIB"\n紧跟着$N持"+weapon->query("name")+HIB"挟巨浪潮涌之势，剑气形成一个旋转的气涡，向$n笼罩过去。\n"NOR,me,target);
         if( random(me->query("combat_exp", 1)) > target->query("combat_exp",1) /2
          || me->query("combat_exp", 1) > target->query("combat_exp", 1)*10 
          || !living(target)){
             message_vision(HIR"结果$n全身被剑气所形成的气涡所笼罩着，只觉得犹如身陷洪涛巨浪，跌跌撞撞。\n"NOR,me,target);
             skill = me->query_skill("xuantie-jianfa", 1);
             tskill = target->query_skill("dodge", 1);
             exp = me->query("combat_exp", 1);
             texp = target->query("combat_exp", 1);
             busy= 4 + random(skill)/100;
             if( busy > 8) busy= 8;
             if( exp > texp){
              p = texp/100* tskill;
              if( p < 1 ) p = 1;
              busy = busy * exp/100 * skill/p;
             }
              if( busy > 15) busy = 15;
             if( me->query("env/玄铁剑法") == "海潮")
               target->start_busy(busy);
             else 
               target->start_busy(2 + random(2));
             target->set_temp("xtjf/haichao", 1);
             me->add("neili", -i*3);
             if (present(target,environment(me)) && me->is_fighting(target))
             COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
             me->start_perform(4, "「海潮汹涌」");
             call_out("remove_effect", 1, me, target);
         }
         else {
              me->start_busy(random(2));
              me->start_perform(3,"「海潮汹涌」");
              me->add("neili", -100);
              dodge_skill = target->query_skill_mapped("dodge");
              if( !dodge_skill ) dodge_skill = "dodge";
              msg = SKILL_D(dodge_skill)->query_dodge_msg(target, 1);
              message_vision(msg, me, target);
         }
        }
        return 1;
}

void remove_effect(object me, object target)
{
        if( !me) return;
        if( objectp(target) && !me->is_fighting(target)){
          target->delete_temp("xtjf");
          return;
        }
        if( objectp(target)
         && me->is_fighting(target)
         && !target->is_busy()
         && random(2) == 1
         && me->query_temp("weapon")
         && me->query_skill("xuantie-jianfa", 1) > 180
         && me->query("env/玄铁剑法") != "汹涌" ){
          target->delete_temp("xtjf");
          call_out("perform2", 1, me, target);
          return;
        }
        call_out("remove_effect", 1 ,me ,target);
}

int perform2(object me,object target)
{
        string msg, dodge_skill,name;
        object weapon = me->query_temp("weapon");        
        int p;
        
        if( !target ) target = offensive_target(me);

        if( !target || !me->is_fighting(target) )
                return notify_fail("你已经不用继续使用「海潮汹涌」了。\n");

        if( !weapon || weapon->query("skill_type") != "sword")
                return notify_fail("你必须使用武器才能继续使用「海潮汹涌」！\n");

        if( me->query_skill_mapped("sword") != "xuantie-jianfa" && userp(me))
                return notify_fail("你无法继续使用「海潮汹涌」！\n");

        if( me->query_skill_mapped("parry") != "xuantie-jianfa" && userp(me))
                return notify_fail("你无法继续使用「海潮汹涌」！\n");

        if((int)me->query("neili") < 1000)
                return notify_fail("你真气太弱，无法继续使出「海潮汹涌」。\n");

        if((int)me->query("jingli") < 500 )
                return notify_fail("你精力太弱，无法继续使出「海潮汹涌」。\n");

        if( me->query("gender")=="男性" )
         p = me->query_skill("force") / 6;
        else
         p = me->query_skill("force") / 8;

        name = xue_name[random(sizeof(xue_name))];
        msg =HIB"\n$n好不容易缓过劲来，$N身形飘忽，转了几转，移步向西，紧跟一剑刺向$n的"RED+name+HIB"。\n"NOR;
        if( me->query_kar()/2 > random(target->query_kar())){
           msg += CYN"$n顿觉眼前一阵迷惑，一时不备，身上的"RED+name+CYN"已被"+weapon->name()+CYN"点中。\n"NOR;
           message_vision(msg, me, target);
           target->add_temp("apply/attack", -p/2);
           target->add_temp("apply/dodge", -p/2);
           target->add_temp("apply/parry", -p/2);
           target->set_temp("xtjf/haichao", 1);
           if( random(5) == 1){
            target->apply_condition("no_exert", 1+ random(2));
            target->set_temp("xtjf/exert", 1);
            tell_object(me,MAG"由于"RED+name+MAG"被点中，"+target->name()+"暂时无法施用内功。\n"NOR);
           }
           else { 
            target->apply_condition("no_perform", 1+random(2));
            target->set_temp("xtjf/perform", 1);
            tell_object(me,YEL"由于"RED+name+YEL"被点中，"+target->name()+"暂时无法施用外功。\n"NOR);
           }
           me->add("neili", - p * 6);
           me->add("jingli", - p * 2);
           call_out("check_fight", 1, me, target, weapon, p );
        }
        else {
               me->start_busy(random(2));
               me->add("neili", -100);
               dodge_skill = target->query_skill_mapped("dodge");
               if( !dodge_skill ) dodge_skill = "dodge";
               msg += SKILL_D(dodge_skill)->query_dodge_msg(target, 1);
               message_vision(msg, me, target);
        }
        me->start_perform(4,"「海潮汹涌」");
        return 1;
}

void check_fight(object me,object target,object weapon, int p)
{
        if( !target) return;
        if( ! me 
         || ! me->is_fighting("target")
         || ! me->query_temp("weapon")
         || weapon->query("skill_type") != "sword"
         || ! present(target,environment(me))
         || me->query_skill_mapped("sword") != "xuantie-jianfa"){
            target->add_temp("apply/attack", p/2);
            target->add_temp("apply/dodge", p/2);
            target->add_temp("apply/parry",p/2);
            if( target->query_temp("xtjf/perform"))
            target->clear_condition("no_perform");
            if( target->query_temp("xtjf/exert"))
            target->clear_condition("no_exert");
            target->delete_temp("xtjf");
            message_vision(HIW"\n$N竭力挣脱了纠缠，身形恢复了原先的矫捷。\n"NOR, target);
            return ;
        }
        else {
           call_out("check_fight", 1, me, target, weapon, p );
           target->add("neili", - random(me->query_skill("sword")));
           if(target->query("neili") < 0 ) target->set("neili", 0);
        }
}
