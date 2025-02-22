// wushuang.c 无双无对
// by hunthu
// modified by Olives@SJ 5/4/2001
// for some judgement fault
#include <ansi.h>
#include "/kungfu/skill/eff_msg.h";
#include <combat.h>
inherit F_SSERVER;

int perform(object me, int amount)
{
        string msg;
        object weapon, target;
        int skill, damage,p;
        weapon = me->query_temp("weapon");
        skill= me->query_skill("zixia-gong",1);

        if( !target ) target = offensive_target(me);

        if( !target
         || !target->is_character()
         || !me->is_fighting(target) )
                return notify_fail("「无双无对,宁氏一剑」只能对战斗中的对手使用。\n");

        if (!weapon || weapon->query("skill_type") != "sword"
                        || me->query_skill_mapped("sword") != "huashan-jianfa")
                return notify_fail("你现在无法使出「无双无对,宁氏一剑」之技！\n");

        if((int)me->query_skill("huashan-jianfa", 1) < 300 )
                return notify_fail("你的华山剑法火候不够，无法「无双无对,宁氏一剑」。\n");

        if((int)me->query_skill("sword", 1) < 300 )
                return notify_fail("你的基本剑法还不够娴熟，使不出「无双无对,宁氏一剑」绝技。\n");

        if( (int)me->query_skill("zixia-gong", 1) < 300 )
                return notify_fail("你的紫霞功修为不够，使不出「无双无对,宁氏一剑」绝技。\n");

        if (me->query_skill_mapped("force") != "zixia-gong")
                return notify_fail("没有紫霞功作为根基，是无法使出「无双无对,宁氏一剑」绝技的！\n");

        if (me->query("max_neili") < 3000)
                return notify_fail("「无双无对，宁氏一剑」乃是气宗绝学，你内力修为不够，无法发出如此凌厉的剑招。\n");

        if (me->query("neili") < 1500)
                return notify_fail("你的内力不够。\n");

        if (me->query("jingli") < 1000)
                return notify_fail("你的精力不够。\n");

        me->add("neili", -800);
        me->add("jingli", -200);
        msg =HIR"\n$N突然间一声清啸，手中的"+weapon->name()+HIR"闪烁不定，围着$n身围疾刺，银光飞舞!\n"+
                "猛地里$N一剑挺出，直刺$n心口，当真是捷如闪电，势若奔雷。\n"NOR;
        if(random(me->query("combat_exp",1)) > target->query("combat_exp",1)*3/4){
          msg += HIW"\n$n大吃一惊，惊叫一声：“哎呀！”其时长剑剑尖已刺破他衣衫。$N右手向前疾送，长剑护手已碰到$n的胸膛，眼见这一剑是在$n身上对穿而过，直没至柄。\n"NOR;
          message_vision(msg, me, target);
          me->add_temp("apply/damage",skill/2);
          me->add("jiali",skill/2);
          target->set_temp("must_be_hit",1);
          COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_SUPER);
          target->delete_temp("must_be_hit");
          me->add_temp("apply/damage",-skill/2);
          me->add("jiali",-skill/2);
          me->start_busy(1+random(2));
          me->start_perform(1+random(4), "「无双无对，宁氏一剑」");
          return 1;
        }
        else
        if(random(me->query("combat_exp",1)) > (target->query("combat_exp",1)/4)){
    msg += HIG"\n$n大声叫道：“来的好！”知这一招凌厉绝伦，不敢正撄其锋，急忙斜身闪开,却也大是狼狈。\n"NOR;
          message_vision(msg, me, target);
          target->start_busy(3);
          me->start_perform(2+random(3), "「无双无对，宁氏一剑」");
          return 1;
        }
        msg += HIC"\n$n身子一矮，沉腰斜坐，将手中兵器对准了$N的来剑。紧接着自然而然挺出，点向$N咽喉，\n"NOR;
        damage = skill*5;
        me->receive_damage("qi", damage);
        me->receive_wound("qi", damage);
        p = (int)me->query("qi")*100/(int)me->query("max_qi");
        msg += "( $N"+eff_status_msg(p)+" )\n";
        message_vision(msg, me, target);
        me->start_perform(3+random(3), "「无双无对，宁氏一剑」");
        return 1;
}

